/*
**********************************************************************************************************
	*@  file: elmo.c
	*@  author: Kevin
	*@  data: 03/17/2014
	*@  version: v1.6�����԰棩
	*@  brief: ������ELMO���Լ칦�ܣ������˵ײ���룬�޸���һ������ʱ���BUG��ʹ�÷�����100us�����Ĵ�������
	*...............................................................................
	*@ Notes1: (1)��ʼ��������       
	*@              name      : Elmo_Init(CAN_TypeDef* CANx, uint8_t PPr, uint8_t SPr)
	*@              function  : ���ó�ʼ����������ʹ��CANͨ��ģ�飬���ΪCAN1��CAN2������ѡ��
	*@			                CAN�ڣ�ȷ������ͨ�Ų���ȷ��ͨ���ٶ�Ϊ1Mbps��ͬʱѡ��TIM7���ж�
	*@	     		            ���ȼ���Ϊ�ײ㱨�ķ����ṩʱ��	
	*@              input     : CANx      CAN1 or CAN2
	*@						    					PPr       TIM7����ռ���ȼ�
	*@                          SPr       TIM7�Ĵ����ȼ�
	*@              output    : 0	        ��ʼ���ɹ�
	*@                          0x80000000  ����û������CAN����
	*@ 													����        ��Ӧ��ELMO��IDλû����1
	*@	
	*@         (2)����ģʽ������        		
	*@  		    name      : Elmo_PTM(u8 elmoID, float torque);
	*@  		    function  : �������ؿ��ƺ�����ά�ֵ�����غ㶨,֧��ģʽ�л�  
	*@              input     : elmoID    ȡelmo�ڵ�ID     
	*@			    			orque     Ŀ��ת��(A)
	*@  			output    : 0         �������óɹ�
	*@                          1         ��������ʧ��
	*@ 	
	*@         (3)�ٶ�ģʽ������  
	*@              name      : Elmo_PVM(u8 elmoID, s32 speed);      
	*@ 			    function  : �����ٶȿ��ƺ���,֧��ģʽ�л� ��֧���������ã�elmo 
	*@                          ���������ٶȻ���ٶ�ʹ�� ��ת�ٴﵽ�趨ֵ
	*@              input     : elmoID    ȡelmo�ڵ�ID      
	*@					        speed     Ŀ���ٶ�(cnt/s)
	*@  			output    : 0         �������óɹ�
	*@                          1         ��������ʧ��
	*@
	*@         (4)λ��ģʽ������   
	*@              name      : Elmo_PPM(u8 elmoID, u32 speed, s32 position, u8 PPMmode);
	*@              function  : �����ٶȿ��ƺ�����֧��ģʽ�л���֧���������ã�����POS_ABSģʽ
	*@ 						    ����ָ���յ����λ��������ϵ��ĵ����λ�ã�Ҳ���ǵ�� �У�Ŀ    
	*@ 						    ��λ��ʼ�ľ���λ�á�����POS_RELģʽ�У����յ����λ��������elmo
	*@ 				            ����λ�üĴ����еľ���λ�ü���Ŀ��λ�ã�����λ�üĴ�����CAN_init 
	*@                          ��Ĭ��Ϊ0
	*@						     ����1��
	*@						     Elmo_PPM(1, 50000, 500000, POS_ABS);
	*@						     while(position != 500000);
	*@					   	     Elmo_PPM(1, 50000, 250000, POS_REL);		
	*@                             ���λ����750000��		
	*@						     ����2��
	*@						     Elmo_PPM(1, 50000, 500000, POS_ABS);
	*@						     while(position != 500000);
	*@						     Elmo_PPM(1, 50000, 250000, POS_ABS);			
	*@						       ���λ����250000��		
	*@						     ����3��
	*@						     Elmo_PPM(1, 50000, 500000, POS_ABS);
	*@						     while(position <= 250000);
	*@						     Elmo_PPM(1, 50000, 250000, POS_REL);			
	*@					           ���λ����750000��		
	*@              input     : elmoID      ȡelmo�ڵ�ID,�����ڵ��̿����е���1--4        
	*@ 						    speed       �ٶ�(cnt/s)
	*@ 					        position    Ŀ��λ��(cnt)
	*@ 						    PPMmode     ����ģʽ
	*@ 						    POS_ABS    // PPM���з�ʽ:����λ��
	*@ 		   			        POS_REL    // PPM���з�ʽ:���λ��
	*@  			output    : 0         �������óɹ�
	*@                          1         ��������ʧ��
	*@
	*@         (5)����ͷź�����   
	*@              name      : Elmo_Close(u8 elmoID);
	*@              function  : ��������رգ���������Լ�����ʻ,֧���������ã�֧�����ϵ��ã���
	*@						    ���ڸ���elmo����ǰ����ã�������Ӱ�����������Ĺ���ʵ�ֺ�elmo��
	*@						    ����														
	*@              input     : elmoID      ȡelmo�ڵ�ID     
	*@  						output    : 0         �������óɹ�
	*@                          1         ��������ʧ��
	*@         
	*@         (6)�������������
	*@              name      : Elmo_Stop(u8 elmoID);
	*@              function  : ���������ά�ֵ����ǰλ�ò��䣬֧���������ã�֧�����ϵ��ã���
	*@ 						    ���ڸ���elmo����ǰ����ã�������Ӱ�����������Ĺ���ʵ�ֺ�elmo��
	*@ 						    ����	
	*@              input     : elmoID      ȡelmo�ڵ�ID     
	*@  						output    : 0         �������óɹ�
	*@                          1         ��������ʧ��
	*@	
	*@         (7)���ٶ����ú�����	
	*@  			 name      : Elmo_SetAcc(u8 elmoID, u32 acc, u32 dec)
	*@               function  : �����ٶ�ģʽ��λ��ģʽ�ĵ���Ӽ��٣����û���ں����е��ã���ʼ��
	*@	                         ����ٶ�Ĭ��Ϊ1000000000�����ٶ�Ĭ��Ϊ1000000000
	*@			     input     : elmoID      ȡelmo�Ľڵ�ID
	*@                           acc         ���ٶ�,���ٶ�����ܳ���1000000000,ͬʱӦ���ǵ������
	*@                           dec         ���ٶ�,���ٶ�����ܳ���1000000000,ͬʱӦ���ǵ������
	*@  			output    : 0         �������óɹ�
	*@                          1         ��������ʧ��
	*@   
	*...............................................................................
	*@ Notes2: (1)��CAN������ 
	*@			     CAN1 RX -> PB8     CAN1 TX -> PB9
	*@               CAN2 RX -> PB5     CAN2 TX -> PB6
	*@         (2)���޸ĺ궨��CAN_BUF_NUM��ֵ�޸Ļ�����Ŀ
	*@         (3)���޸�TIM7_Configuration()��TIM7�����ж����ȼ�
	*@         (4)��ע��CANʱ��Ϊ42MHz,TIM7ʱ��Ϊ42MHz
	*@ 	       (5)��ע��д���ȼ����麯��
	*...............................................................................
	*@ Notes3: (1)��û��д�ڵ�ID����ID�ķ��亯��
	*@	       (2)��û�мӷ������Ļ��� 
	*@		   (3)��û�м�ƽ���������ú���	    
	*@		   (4)��Elmo_Stop()��Elmo_PTM()����Ӧʱ��̫������Ҫ�Ż�			
	*@         (5)��û�мӽڵ㱣��������������������				 
	*@    	   (6)��Elmo_Delay100us()���ԸĽ������Ч��    
	*@         (7)��GroupIDռʱ��������	
**********************************************************************************************************
*/
#include "elmo.h"
#include "stdio.h"

static CANQUEUE QUEUE_CAN;       //CAN2�ײ㷢�ͱ��Ķ���
static Elmo elmo[ELMO_NUM + 1];
static Elmo elmogroup;
static CAN_TypeDef* can;         //��ʼ��ѡ��CANx�Ľӿڱ���
static u8 CAN_Error = 0;         //���CAN����ʧ�ܣ�CAN_Error��1
static u32 Elmo_Init_Flag = 0;   //������¼ELMOʵ�ʵĳ�ʼ����״̬


/*
********************************************************************************
  *@  name      : CAN_init
  *@  function  : Initialization for CAN
  *@  input     : CANx      CAN1 or CAN2
  *@			  			PPr       TIM7����ռ���ȼ�
  *@              SPr       TIM7�Ĵ����ȼ�
  *@  output    : 0	        ��ʼ���ɹ�
  *@              1         ��ʼ��ʧ��
********************************************************************************
*/
u32 Elmo_Init(CAN_TypeDef* CANx, uint8_t PPr, uint8_t SPr)
{  
	u8 i = 0;
	int temp = 0;
	/* Ӳ����ȫ�ֱ�����ʼ�� */ 
	CAN_init( CANx );
	TIM7_init( PPr, SPr);	

	/*���������ʼ��*/
	Variate_init();

	/* ��elmo����ڵ�ID */
	for(i=0; i <= ELMO_NUM; i++)					
	{
		elmo[i].NodeID = i;			
	}

	/* ��elmo������ID */
	elmogroup.NodeID = 126;

	/* ��ȫ��ڵ����ͨ�Ÿ�λ */
	for(i=1; i <= ELMO_NUM; i++)				
	{
		NMTCmd(&elmo[i], NMT_RESET_COMMUNICATION);			
		Elmo_Delay100us(50);					//��Ϻ���Elmo_SendCmd(void)������ܿ�����ν����ʱ����ô�����										
	}
	
	/* �Լ칦�ܺ�����CAN��ʼ���ɹ���������ֵ0 */
	temp = Self_test();
	if( temp )
	{
		return temp;		
	}
	

	//	/* �ȴ�Elmo�������,�����յ�Boot up���� */
	//	Elmo_Delay100us(50);

	/* CANOpenͨ�Ų�����ʼ�� */
	/* RPDO1->0x6040,ָ����,2�ֽ�,�첽���� */
	// ������Ĭ��ӳ��,����Ҫ�޸� //

	/* RPDO2->0x2012,�����Ʊ�������,4�ֽ�,�첽���� */
	// ������Ĭ��ӳ��,����Ҫ�޸� //

	/* ����TPDO,Debugʱ����,������ʱ��ùر� */
	RSDO(&elmo[0], 0x1A00, 0x00, 0);
	Elmo_Delay100us(150);
	RSDO(&elmo[0], 0x1A01, 0x00, 0);
	Elmo_Delay100us(150);

	/* ����NMT����״̬ */
	Elmo_Delay100us(40);
	NMTCmd(&elmo[0], NMT_ENTER_OPERATIONAL);													//����ELMO������������״̬
	Elmo_Delay100us(40);

	/* �ر����� */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);		//����ELMO  MO=0		ʧ������
	Elmo_Delay100us(80);

	/* ��ʼ�����ٶ� */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"PM", 0, TYPE_INTEGER, 0x01);			//����ELMO  PM=1			PMΪ1��������AC��DC
	Elmo_Delay100us(40);	
	RPDO2_Cmd_data(&elmo[0], (u8 *)"AC", 0, TYPE_INTEGER, 100000);		//����ELMO  AC=100000		���ٶ�
	Elmo_Delay100us(40);
	RPDO2_Cmd_data(&elmo[0], (u8 *)"DC", 0, TYPE_INTEGER, 100000);		//����ELMO  DC=100000		���ٶ�
	Elmo_Delay100us(40);

	/* Enter in SCM */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);		//����ELMO  UM=2  �ٶ�ģʽ
	Elmo_Delay100us(40);
	elmogroup.CurOPMode = UM_SCM;								//��¼����ELMO��ģʽ(����ELMOģʽһ��ʱ��ģʽ)��ÿ��ELMO��ģʽ		
	for(i=0;i<=ELMO_NUM;i++)
	{
		elmo[i].CurOPMode = UM_SCM;			
	}

	/* ʹ������ */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);			//����ELMO  MO=1		ʹ������
	Elmo_Delay100us(250);
	Elmo_Delay100us(250);
	Elmo_Delay100us(50);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_PTM
  *@  function  : ��������ģʽ����
  *@  input     : elmoID    ȡelmo�ڵ�ID,�����ڵ��̿����е���elmo[1]~elmo[4]
  *@ 			  			torque    Ŀ��ת��(A)
  *@  output    : 0         �������óɹ�
  *@              1         ��������ʧ��
********************************************************************************
*/
u8 Elmo_PTM(u8 elmoID, float torque)
{
    u8 i = 0;

	/* ����ʼ���Ƿ�ɹ������ʧ�ܣ��������� */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	
	/* ���ʹ�ù㲥����, ��ǰģʽ��Ϊ����ģʽ,�л�Ϊ����ģʽ*/
	if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_TCM)  
	{
		if( elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(100);
		}		
		
		/* ������״̬������ֵΪTCM */
		elmogroup.CurOPMode = UM_TCM;			
		for(i=0;i<=ELMO_NUM;i++)
		{
			elmo[i].CurOPMode = UM_TCM;			
		}
		
		RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_TCM);
		Elmo_Delay100us(10);
		
		RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
		Elmo_Delay100us(30);
	}  
	/* ʹ�õ���ELMO����,��ǰģʽ��Ϊ����ģʽ,�л�Ϊ����ģʽ */
 	else if( elmo[elmoID].CurOPMode != UM_TCM)         
	{
		if( elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(100);
		}
		elmo[elmoID].CurOPMode = UM_TCM;
		RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_TCM);
		Elmo_Delay100us(10);

		RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
		Elmo_Delay100us(30);
		
        /* ���ELMOֻ������1����������ô�����ģʽ��elmo[0]��ģʽ����һ�� */		
		if(ELMO_NUM == 1)
		{
			elmo[0].CurOPMode = UM_TCM;
		}	
		/* �����ж��Ƿ����е��ģʽ��ͬ���Ӷ�ȷ��elmo[0]��ģʽ */
		else
		{
			for(i=1;i<ELMO_NUM;i++)  
			{
				if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
				{
					elmo[0].CurOPMode = UM_TCM;
				}
				else
				{
					elmo[0].CurOPMode = UM_UNC;
					break;
				}
			}			
		}
	}
		
	/* ����Ŀ��ת�ز����е���ģʽ */
	RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"TC", 0, TYPE_FLOAT, f2h(torque));
	Elmo_Delay100us(10);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_PVM
  *@  function  : �����ٶ�ģʽ����
  *@  input     : elmoID   ȡelmo�ڵ�ID
  *@			  			speed    Ŀ���ٶ�(cnt/s)
  *@  output    : 0         �������óɹ�
  *@              1         ��������ʧ��
********************************************************************************
*/
u8 Elmo_PVM(u8 elmoID, s32 speed)
{
	 u8 i = 0;
	
	/* ����ʼ���Ƿ�ɹ������ʧ�ܣ��������� */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	/* ���ʹ�ù㲥����,��ǰģʽ��Ϊ�ٶ�ģʽ,�л�Ϊ�ٶ�ģʽ */
	if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_SCM)
	{
		if(elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(100);
		}	
		
		/* ������״̬������ֵΪSCM */
		elmogroup.CurOPMode = UM_SCM;			
		for(i=0;i<=ELMO_NUM;i++)
		{
			elmo[i].CurOPMode = UM_SCM;			
		}

		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);
		Elmo_Delay100us(10);

	    RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
		Elmo_Delay100us(30);
		
	}  
	/* ʹ�õ���ELMO����,��ǰģʽ��Ϊ�ٶ�ģʽ,�л�Ϊ�ٶ�ģʽ*/
	else if(elmo[elmoID].CurOPMode != UM_SCM)
	{
		if(elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(100);
		}

		elmo[elmoID].CurOPMode = UM_SCM;
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);
		Elmo_Delay100us(10);

	    RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
		Elmo_Delay100us(30);
	
        /* ���ELMOֻ������1����������ô�����ģʽ��elmo[0]��ģʽ����һ�� */				
		if(ELMO_NUM == 1)       
		{
			elmo[0].CurOPMode = UM_SCM;
		}	
		/* �����ж��Ƿ����е��ģʽ��ͬ���Ӷ�ȷ��elmo[0]��ģʽ */
		else
		{
			for(i=1;i<ELMO_NUM;i++) 
			{
				if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
				{
					elmo[0].CurOPMode = UM_SCM;
				}
				else
				{
					elmo[0].CurOPMode = UM_UNC;
					break;
				}
			}				
		}
	}

	/* ����Ŀ���ٶ� */
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"JV", 0, TYPE_INTEGER, speed);
	Elmo_Delay100us(10);

	/* �����ٶ�ģʽ */
	RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
	Elmo_Delay100us(10);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_RunPPM
  *@  function  : ����ƽ���ٶȵ�λ��ģʽ
  *@  input     : elmoID    ȡelmo�ڵ�ID
  *@              speed     �ٶ�(cnt/s)
  *@              position  Ŀ��λ��(cnt)
  *@              PPMmode   ����ģʽ
  *@				    POS_ABS // PPM���з�ʽ:����λ��
  *@				    POS_REL // PPM���з�ʽ:���λ��
  *@  output    : 0         �������óɹ�
  *@              1         ��������ʧ��
********************************************************************************
*/
u8 Elmo_PPM(u8 elmoID, u32 speed, s32 position, u8 PPMmode)
{
	u8 i = 0;
	/* ����ʼ���Ƿ�ɹ������ʧ�ܣ��������� */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	/* ���ʹ�ù㲥����,��ǰģʽ��Ϊλ��ģʽ,�л�Ϊλ��ģʽ */
	if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_PCM)
	{
		if(elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(90);
		}	
		/* ������״̬������ֵΪPCM */		
		elmogroup.CurOPMode = UM_PCM;			
		for(i=0;i<=ELMO_NUM;i++)
		{
			elmo[i].CurOPMode = UM_PCM;			
		}

		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_PCM);
		Elmo_Delay100us(20);
		
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
		Elmo_Delay100us(30);
	}  
	/* ʹ�õ���ELMO����,��ǰģʽ��Ϊλ��ģʽ,�л�Ϊλ��ģʽ */
	else if(elmo[elmoID].CurOPMode != UM_PCM)
	{
		if(elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(90);
		}

		elmo[elmoID].CurOPMode = UM_PCM;
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_PCM);
		Elmo_Delay100us(20);

		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
		Elmo_Delay100us(30);


        /* ���ELMOֻ������1����������ô�����ģʽ��elmo[0]��ģʽ����һ�� */				
		if(ELMO_NUM == 1)      
		{
			elmo[0].CurOPMode = UM_PCM;
		}		
		/* �����ж��Ƿ����е��ģʽ��ͬ���Ӷ�ȷ��elmo[0]��ģʽ */
		else 
		{
			for(i=1;i<ELMO_NUM;i++) 
			{
				if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
				{
					elmo[0].CurOPMode = UM_PCM;
				}
				else
				{
					elmo[0].CurOPMode = UM_UNC;
					break;
				}
			}			
		}
	}

	/* ����Ŀ���ٶ� */
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"SP", 0, TYPE_INTEGER, speed);
	Elmo_Delay100us(20);

	/* ��������ģʽ����λ�� */
	if(PPMmode)
	{
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"PA", 0, TYPE_INTEGER, position);
		Elmo_Delay100us(20);
	}
	else
	{
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"PR", 0, TYPE_INTEGER, position);
		Elmo_Delay100us(20);
	}
	
	/* ����λ��ģʽ */
	RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
	Elmo_Delay100us(10);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_Close
  *@  function  : ��������رգ���������Լ�����ʻ
  *@  input     : elmoID    ȡelmo�ڵ�ID,�����ڵ��̿����е���elmo[1]~elmo[4]        
  *@  output    : 0         �������óɹ�
  *@              1         ��������ʧ��
********************************************************************************
*/
u8 Elmo_Close(u8 elmoID)
{
	u8 i = 0;
	/* ����ʼ���Ƿ�ɹ������ʧ�ܣ��������� */	
  if( CAN_Error == 1)
	{
		return 1;		
	}
	
    /* ���ʹ�ù㲥����,������ELMOʧ�� */
	if(elmoID == 0)
	{
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
		Elmo_Delay100us(100);
		
		/* ������״̬������ֵΪIDLE */		
		elmogroup.CurOPMode = UM_IDLE;			
		for(i=0;i<=ELMO_NUM;i++)
		{
			elmo[i].CurOPMode = UM_IDLE;			
		}	    
	}
    /* ʹ�õ���ELMO���� */
	else 
	{
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
		Elmo_Delay100us(100);
		elmo[elmoID].CurOPMode = UM_IDLE;		

        /* ���ELMOֻ������1����������ô�����ģʽ��elmo[0]��ģʽ����һ�� */			
		if(ELMO_NUM == 1)       
		{
			elmo[0].CurOPMode = UM_IDLE;
		}		
		/* �����ж��Ƿ����е��ģʽ��ͬ���Ӷ�ȷ��elmo[0]��ģʽ */
		else 
		{
			for(i=1;i<ELMO_NUM;i++)  
			{
				if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
				{
					elmo[0].CurOPMode = UM_IDLE;
				}
				else
				{
					elmo[0].CurOPMode = UM_UNC;
					break;
				}
			}			
		}
	}
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_Stop
  *@  function  : ɲ�����������
  *@  input     : elmoID      ȡelmo�ڵ�ID,�����ڵ��̿����е���elmo[1]~elmo[4]        
  *@  output    : 0         �������óɹ�
  *@              1         ��������ʧ��
********************************************************************************
*/
u8 Elmo_Stop(u8 elmoID)
{
	u8 i = 0;
	/* ����ʼ���Ƿ�ɹ������ʧ�ܣ��������� */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	/* ���CAN������������Ŀ���ģʽ����ͬ���ҷ����㲥ָ����ιر� */
	if(elmoID == 0 && elmo[elmoID].CurOPMode == UM_UNC)  
	{
		/* ѭ���жϸ��������״̬�����ر�ÿһ����� */
		for(i=1;i<=ELMO_NUM;i++)            
		{		
			/* ��ǰģʽΪ�ͷŵ��,�ȴ򿪵�����ٱ��� */		
			if (elmo[i].CurOPMode == UM_IDLE) 
			{
				RPDO2_Cmd_data(&elmo[i], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
				Elmo_Delay100us(30);				
			}
			/* ��ǰģʽΪ����ģʽ,���л�Ϊ�ٶ�ģʽ���ٹر� */
			else if(elmo[i].CurOPMode == UM_TCM)
			{
				RPDO2_Cmd_data(&elmo[i], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);			
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);			
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);	
				Elmo_Delay100us(200);			

				elmo[i].CurOPMode = UM_SCM;			

				RPDO2_Cmd_data(&elmo[i], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);
				Elmo_Delay100us(10);

				RPDO2_Cmd_data(&elmo[i], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
				Elmo_Delay100us(30);

				/* ����Ŀ���ٶ� */
				RPDO2_Cmd_data(&elmo[i], (u8 *)"JV", 0, TYPE_INTEGER, 0);
				Elmo_Delay100us(10);

				/* �����ٶ�ģʽ */
				RPDO2_Cmd_string(&elmo[i], (u8 *)"BG");
				Elmo_Delay100us(10);
			}	
				
			RPDO2_Cmd_string(&elmo[i], (u8 *)"ST");
			Elmo_Delay100us(10);
		}	
		
		/* �����ж��Ƿ����е��ģʽ��ͬ���Ӷ�ȷ��elmo[0]��ģʽ,�ܹ��������if�Ĳ���������CAN����ֻ�е��� */
		for(i=1;i<ELMO_NUM;i++)  
		{
			if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
			{
				elmo[0].CurOPMode = UM_SCM;         //�����STOPģʽ������ģʽͳһ�ˣ�ֻ�п�����SCMģʽ
			}
			else
			{
				elmo[0].CurOPMode = UM_UNC;
				break;
			}
		}											
	}
	/* �����㲥ָ����������϶���Ŀ���ģʽ����ͬ����ʱ�����һ��ر� */
    else if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_UNC)  
	{
		/* ��ǰģʽΪ�ͷŵ��,�ȴ򿪵�����ٱ��� */		
		if (elmo[elmoID].CurOPMode == UM_IDLE) 
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);				
		}
		/* ��ǰģʽΪ����ģʽ,���л�Ϊ�ٶ�ģʽ���ٹر� */
		else if(elmo[elmoID].CurOPMode == UM_TCM)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);			
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);			
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);			

			/* �㲥ģʽ�£������ٶ�ģʽ����ΪSCM */
			for(i=0;i<=ELMO_NUM;i++) 
			{
				elmo[i].CurOPMode = UM_SCM;			
			}
		
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);
			Elmo_Delay100us(10);

			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);

			/* ����Ŀ���ٶ� */
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"JV", 0, TYPE_INTEGER, 0);
			Elmo_Delay100us(10);

			/* �����ٶ�ģʽ */
			RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
			Elmo_Delay100us(10);
		}	
			
		RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"ST");
		Elmo_Delay100us(10);	
        
    }
	/* ʹ�õ���ELMO���� */
	else    
	{
		/* ��ǰģʽΪ�ͷŵ��,�ȴ򿪵�����ٱ��� */		
		if (elmo[elmoID].CurOPMode == UM_IDLE) 
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);				
		}
		/* ��ǰģʽΪ����ģʽ,���л�Ϊ�ٶ�ģʽ���ٹر� */
		else if(elmo[elmoID].CurOPMode == UM_TCM)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);			
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);			
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);	
			Elmo_Delay100us(200);			

			elmo[elmoID].CurOPMode = UM_SCM;			

			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);
			Elmo_Delay100us(10);

			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);

			/* ����Ŀ���ٶ� */
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"JV", 0, TYPE_INTEGER, 0);
			Elmo_Delay100us(10);

			/* �����ٶ�ģʽ */
			RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
			Elmo_Delay100us(10);

            /* ���ELMOֻ������1����������ô�����ģʽ��elmo[0]��ģʽ����һ�� */			
			for(i=1;i<ELMO_NUM;i++)  //�����ж��Ƿ����е��ģʽ��ͬ���Ӷ�ȷ��elmo[0]��ģʽ
			{
				if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
				{
					elmo[0].CurOPMode = UM_SCM;    //�����STOPģʽ������ģʽͳһ�ˣ�ֻ�п�����SCMģʽ
				}
				else
				{
					elmo[0].CurOPMode = UM_UNC;
					break;
				}
			}				
		}	
			
		RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"ST");
		Elmo_Delay100us(10);		
	}
	return 0;		
}


/*
********************************************************************************
  *@  name      : Elmo_SetAcc(u8 elmoID, u32 acc, u32 dec)
  *@  function  : �����ٶ�ģʽ��λ��ģʽ�ĵ���Ӽ���
  *@  input     : elmoID     ȡelmo�Ľڵ�ID
  *@                 acc        ���ٶ�,���ٶ�����ܳ���1000000000,ͬʱӦ���ǵ������
  *@                 dec        ���ٶ�,���ٶ�����ܳ���1000000000,ͬʱӦ���ǵ������
  *@  output    : 0         �������óɹ�
  *@              1         ��������ʧ��
********************************************************************************
*/
u8 Elmo_SetAcc(u8 elmoID, u32 acc, u32 dec)
{ 
	/* ����ʼ���Ƿ�ɹ������ʧ�ܣ��������� */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
	Elmo_Delay100us(30);	
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"PM", 0, TYPE_INTEGER, 0x01);
	Elmo_Delay100us(10);	
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"AC", 0, TYPE_INTEGER, acc);
	Elmo_Delay100us(10);
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"DC", 0, TYPE_INTEGER, dec);
	Elmo_Delay100us(10);
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
	Elmo_Delay100us(100);
	return 0;
}


/*
********************************************************************************
  *@  name      : NMTCmd
  *@  function  : ����CANOPEN��NMT״̬����
  *@  input     : elmo     ȡelmo�Ľڵ�ID
                  MNTCmd   NMTָ��,NMT_xxx
  *@  output    : None
********************************************************************************
*/
static void NMTCmd(Elmo *elmo, u8 MNTCmd)
{
	u16 tmp_rear;

	/* �жϻ������Ƿ����� */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* ���������� */
		return;
	}

	/* ��仺���� */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   =  COBID_NMT_SERVICE;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     =  2;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] =  MNTCmd;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] =  elmo->NodeID;

	/* ��Ч���ݼ�1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : RSDO
  *@  function  : ʹ������SDO����ָ���
  *@  input     : elmo      ȡelmo�ڵ�ID
									Index     ����
                  SubIndex  ������
                  Data      ����
  *@  output    : None
********************************************************************************
*/
static void RSDO(Elmo *elmo, u16 Index, u8 SubIndex, u32 Data)
{
	u16 tmp_rear;

	/* �жϻ������Ƿ����� */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* ���������� */
		return;
	}

	/* ��仺���� */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = COBID_RSDO + elmo->NodeID;  // COBID
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 8;                          // DLC
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = 0x22;                       // CS,������δȷ��
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] = (Index&0xFF);               // Index
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[2] = (Index&0xFF00)>>8;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[3] = (SubIndex);                 // SubIndex
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[4] = (Data&0xFF);                // Data
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[5] = (Data&0xFF00)>>8;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[6] = (Data&0xFF0000)>>16;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[7] = (Data&0xFF000000)>>24;

	/* ��Ч���ݼ�1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : RPDO2_Cmd_data
  *@  function  : ʹ�ö����Ʊ����ELMO��������ָ��
                  CANopen RPDO2 -> 0x2012 ����������-���ù���
  *@  input     : elmo   ȡelmo�ڵ�ID
                  Cmd    ����,���ַ�����ʽ����
                  Index  ������±�           
                  Type   ��������
                  Data   ����
  *@  output    : None
********************************************************************************
*/
static void RPDO2_Cmd_data(Elmo *elmo, u8 *Cmd, u8 Index, u8 Type, u32 Data)
{
	u16 tmp_rear;

	/* �жϻ������Ƿ����� */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* ���������� */
		return;
	}


	/* ��仺���� */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = COBID_RPDO2 + elmo->NodeID;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 8;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = (*Cmd++);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] = (*Cmd);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[2] = (Index);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[3] = (Type<<7);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[4] = (Data&0xFF);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[5] = (Data&0xFF00)>>8;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[6] = (Data&0xFF0000)>>16;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[7] = (Data&0xFF000000)>>24;

	/* ��Ч���ݼ�1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : RPDO2_Cmd_string
  *@  function  : ʹ�ö����Ʊ����ELMO�����ַ���ָ��
                  CANopen RPDO2 -> 0x2012 ����������-ִ�й���
  *@  input     : elmo   ȡelmo�ڵ�ID
									cmd    ����,���ַ�����ʽ����
  *@  output    : None
********************************************************************************
*/
static void RPDO2_Cmd_string(Elmo *elmo, u8 *Cmd)
{
	u16 tmp_rear;

	/* �жϻ������Ƿ����� */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* ���������� */
		return;
	}

	/* ��仺���� */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = COBID_RPDO2 + elmo->NodeID;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 4;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = (*Cmd++);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] = (*Cmd);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[2] = 0x00;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[3] = 0x00;

	/* ��Ч���ݼ�1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : CAN_init
  *@  function  : Initialization for CAN
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void CAN_init(CAN_TypeDef* CANx)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	CAN_InitTypeDef          CAN_InitStructure;
	CAN_FilterInitTypeDef    CAN_FilterInitStructure;      
	NVIC_InitTypeDef         NVIC_InitStructure;


	if( CANx == CAN1 )
	{  
		can = CAN1;				//Ϊ�ײ㷢�ͱ���ѡ��can��
		/* Enable GPIO clock */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		/* Enable CAN clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

		/* Configure CAN RX and TX pins */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* Connect CAN pins to AF9 */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);			
	}
	else if( CANx == CAN2 )
	{  
		can = CAN2;				//Ϊ�ײ㷢�ͱ���ѡ��can��
		/* Enable GPIO clock */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		/* Enable CAN clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2, ENABLE);

		/* Configure CAN RX and TX pins */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* Connect CAN pins to AF9 */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);			
	}

	/* CAN register init */
	CAN_DeInit(CANx);
	CAN_StructInit(&CAN_InitStructure);	 

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;    
	CAN_InitStructure.CAN_ABOM = DISABLE;    
	CAN_InitStructure.CAN_AWUM = DISABLE;  
	CAN_InitStructure.CAN_NART = DISABLE;    
	CAN_InitStructure.CAN_RFLM = DISABLE;  
	CAN_InitStructure.CAN_TXFP = ENABLE;    
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;

	/* Baudrate = 1Mbps (CAN clocked at 42 MHz) */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
	CAN_InitStructure.CAN_Prescaler = 3;     //CAN������42/(1+9+4)/3=1Mbps
	CAN_Init(CANx, &CAN_InitStructure);

	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;                        
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;      
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;     
	//ERROR CONTROL ��ID��Χ700-77f
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0700<<5;               
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;                     
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0700<<5;           
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0006;               
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;               
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	if( CANx == CAN1 )//�����Լ�
	{  
		/* CAN FIFO0 message pending interrupt enable */ 
		CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);

		/* Enable the CAN1 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if( CANx == CAN2 )
	{
		/* CAN FIFO0 message pending interrupt enable */ 
		CAN_ITConfig(CAN2,CAN_IT_FMP0, ENABLE);

		/* Enable the CAN2 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	
	}
}


/*
********************************************************************************
  *@  name      : CAN1_RX0_IRQHandler
  *@  function  : �жϴ�����
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
//void CAN1_RX0_IRQHandler()
//{
//  CanRxMsg RxMsg;
//	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
//	{
//		CAN_Receive(CAN1, CAN_FIFO0, &RxMsg);
//		Elmo_Init_Flag |= (1<<((RxMsg.StdId&0x0F)-1));
//		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
//	}
//}


//void CAN2_RX0_IRQHandler()
//{
//   CanRxMsg RxMsg;
//   CAN_Receive(CAN2, CAN_FIFO0, &RxMsg);
//   
//   Elmo_Init_Flag |= (1<<((RxMsg.StdId&0x0F)-1));
//}


/*
********************************************************************************
  *@  name      : TIM7_init
  *@  function  : TIM7��ʼ����ʹCAN����ÿ100us����һ��
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void TIM7_init(uint8_t PPr, uint8_t SPr)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	NVIC_InitTypeDef          NVIC_InitStructure;

	/* TIM7 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);

	/* Enable the TIM7 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PPr;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SPr;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Time base configuration (TIM7 clocked at 84 MHz)*/
	TIM_TimeBaseStructure.TIM_Period = 840;
	TIM_TimeBaseStructure.TIM_Prescaler = 10-1;                
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;           

	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 

	/* TIM7 IT enable */
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM7, TIM_FLAG_Update); 

	/* TIM7 enable counter */
	TIM_Cmd(TIM7, ENABLE);
}


/*
********************************************************************************
  *@  name      : TIM7_IRQHandler
  *@  function  : TIM7�жϴ�������ÿ100us��������CAN����
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
void TIM7_IRQHandler(void)
{
	/* 100us */
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	Elmo_SendCmd();
}


/*
********************************************************************************
  *@  name      : Self_test
  *@  function  : Elmo�ϵ��Լ�
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
int Self_test(void)
{
	u32 cnt_delay = 0x3FFF;                                            
	
	do
	{
	   __nop();
	}
  while( --cnt_delay );
  if( CAN_Error == 1) //�����ʼ��ʧ�ܣ��ر�TIM7���жϺ�TIM7
	{
		TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM7, DISABLE);		
		return 0x80000000;		
	}
	
	Elmo_software_delay_ms(500);
	
	while((Elmo_Init_Flag & ((1<<ELMO_NUM) - 1)) != ((1<<ELMO_NUM) - 1))		//CAN�����ж��и���Elmo_Init_Flag
	{
		return Elmo_Init_Flag;
	}
	 
	return 0;
}


/*
********************************************************************************
  *@  name      : Variate_init
  *@  function  : ������ʼ��
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Variate_init(void)
{
	memset (&QUEUE_CAN, 0, sizeof(QUEUE_CAN));
	memset (elmo, 0, sizeof(Elmo)*(ELMO_NUM + 1));
	memset (&elmogroup, 0, sizeof(Elmo));
	QUEUE_CAN.Front = 0;
	QUEUE_CAN.Rear  = 0;
}


/*
********************************************************************************
  *@  name      : Elmo_SendCmd
  *@  function  : ��������п�����CAN���ģ�Ҳ�п������ӳٱ���
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Elmo_SendCmd(void)
{
	/* �жϻ������Ƿ������� */
	if(QUEUE_CAN.Rear != QUEUE_CAN.Front)
	{
		/* ������,�ж��Ƿ�����ʱ���� */
		if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].COBID == CAN_ID_DELAY)
		{
			/* ����ʱָ��,�ж��Ƿ���ʱ��� */
			if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].DATA[0] > 1) //����һ��BUG������Ч���úܶ�
			{
				/* ��ʱδ��,��ʱʱ���1 */
				QUEUE_CAN.CANBUF[QUEUE_CAN.Front].DATA[0]--;
			}
			else
			{
				/* ��ʱ���,���׼�1 */      
				QUEUE_CAN.Front++;
				if( QUEUE_CAN.Front >= CAN_BUF_NUM)
				{
					QUEUE_CAN.Front = 0;
				}
			}
		}
		else
		{
			/* ������ʱָ��,����CAN���� */
			Elmo_CANSend( &QUEUE_CAN.CANBUF[QUEUE_CAN.Front] );

			/*���׼�1*/   
			QUEUE_CAN.Front++;
			if( QUEUE_CAN.Front >= CAN_BUF_NUM)
			{
				QUEUE_CAN.Front = 0;
			}
		}
	}
	else
	{
		/* ����Ϊ�� */ 
		return;   
	}
}


/*
********************************************************************************
  *@  name      : Elmo_CANSend
  *@  function  : �ײ㷢��CAN����
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Elmo_CANSend(CANDATA *pCANDATA)
{
	u8 i, TransmitMailbox;
	u32 cnt_delay;
	CanTxMsg elmoCAN;

	elmoCAN.IDE    =  CAN_ID_STD;                          // ��׼֡
	elmoCAN.RTR    =  CAN_RTR_DATA;                        // ����֡
	elmoCAN.StdId  =  pCANDATA->COBID;                     // COBID
	elmoCAN.DLC    =  pCANDATA->DLC;                       // DLC
	for(i=0;i<elmoCAN.DLC;i++)                             // Data
	{
		elmoCAN.Data[i] = pCANDATA->DATA[i];		
	}
	
	TransmitMailbox = CAN_Transmit(can, &elmoCAN);                          // ���÷��ͱ��ĺ���   
	
	cnt_delay = 0x2FFF;
	do
	{
	   __nop();
	}
    while((CAN_TransmitStatus(can,TransmitMailbox) != CANTXOK) && (--cnt_delay));
	
	if (cnt_delay <= 0x01 )
		CAN_Error = 1;
    else
		CAN_Error = 0;
	
}


/*
********************************************************************************
  *@  name      : Elmo_Delay100us
  *@  function  : �ӳٱ��������ӳ���һ�����ĵķ��ͣ���߷��ͱ��ĵ��ȶ���
                  N���Ϊ255��N��100us��
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Elmo_Delay100us(u8 N100us)
{
	uint16_t tmp_rear;

	/* �жϻ������Ƿ����� */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Rear)                                  
	{
		/* ���������� */
		return ;
	}

	/* ��仺���� */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = CAN_ID_DELAY;        // ��ʱ�õ�COBID 
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 1;                   // DLCΪ1r 
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = N100us;              // ��ʱ,��¼ʱ�� 

	/* ��Ч���ݼ�1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : Elmo_software_delay_ms
  *@  function  : Elmo�����ʱ
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
void Elmo_software_delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a = 41580; //at 168MHz 41580 is ok
 		while(a--);
	}
}


/*
********************************************************************************
  *@  name      : f2h
  *@  function  : ��������ת��Ϊ8�ֽ�ʮ��������(IEEE754)
  *@  input     : x   ������ 
  *@  output    : None
********************************************************************************
*/
static u32 f2h(float x)
{
	u32 *p = (u32 *)&x;
	return ((u32)*p);
}





