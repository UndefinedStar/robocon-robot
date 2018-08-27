#include "PictureAnalyse.h" 
#include "data_conf.h"
#include "OV7670.h"
#include "GUI_32.h"
uint16_t Control_Value;  //�������� ����ӿ�
uint8_t VSYNCCnt = 0;    //�жϼ�����
uint16_t yBuf[500];//��ű�ѡ�е����ص㵱�б�ɺڵ������
uint16_t p=0;//ָ�����v
uint16_t Time;
Picture_Control PictureContorl;
void PictureAnalyse(void)
{
uint16_t x=0,y=0;
		uint16_t average=0;

uint16_t t1=0,t2=0,temp=0;   //ѭ������ת��  

EXTI_ClearITPendingBit(EXTI_Line4);  	
	 //��ָ�븴λ
	LED1(ON);
	LED2(OFF);
   VSYNCCnt++;
	/*
	1:�ȴ�OV7670ͬ���źţ������жϺ���˵�����ź�����
	*/
	if(VSYNCCnt==1)    //FIFOдָ�븴λ
	{
	  FIFO_WRST=1;
		for(x=0;x<5;x++);
		FIFO_WRST=0;
 		for(x=0;x<100;x++);
		FIFO_WRST=1;      	//дָ�븴λ
		FIFO_WR=1;	  //дʹ�ܣ�дָ�븴λֻ��Ϳ��Կ�ʼд��	   
	}

	/*
	2&3:FIFOдָ�븴λ�������ֲ��ϵ�ʱ�򣬸�λ���
	*/
	
	/*
	4:���������������˵���ڶ��ν��յ������ź�
	*/
	if(VSYNCCnt==2)
	{
	 	FIFO_WR=0;     //��ֹCMOS����д��FIFO
	/*
	5:��ֹFIFOд�����������ݣ���дʹ��ת����һ֡���ݴ������
	*/
/////////////////////��ȡ�������///////////////////////////////////

		EXTI->IMR&=~(1<<4);	 //��ֹ�ⲿ�ж�
		EXTI->EMR&=~(1<<4);
	   
			FIFO_RRST =0;				//��ָ�븴λ										
			for(x=0;x<10;x++)		
			{
				FIFO_RCK =0;				//������Ҫһ��ʱ�����ڵ�������ܸ�λ
				FIFO_RCK =1;
			}
			FIFO_RRST =1;
      /*
		1��FIFO��ָ�븴λ������ɣ����ն�ָ�븴λʱ��
	  */

		write_cmd_data(0x0003,0x1018);
		write_cmd_data(0x0050,0x0000); 
		write_cmd_data(0x0051,0x00ef);
		write_cmd_data(0x0052,0x0000);
		write_cmd_data(0x0053,0x013f);
		write_cmd_data(0x0020,0x0000);
		write_cmd_data(0x0021,0x013f);   
		//����TFT��ʾģʽ��Ϊ��̬��ʾ
			
		LCD_WriteRAM_Prepare();
		FIFO_OE=0;			  //����FIFO����������ʱ��
			

		for(x = 1; x <= Windows_X; x ++)	 
		 {	
			 	LED1(OFF);
				LED2(ON);			
		 	for(y = 1; y <= Windows_Y; y ++)
			{			
				FIFO_RCK=0;					
				FIFO_RCK=1;				//ģ���ʱ�ӣ���ȡ�߰�λ�ֽ�
				
				//��ȡT1��ʱ���  �Ͱ�λ

				
				FIFO_RCK=0;						
				FIFO_RCK=1;	//ģ���ʱ�ӣ���ȡ�ڰ�λ
				
				//���߰�λ YUV����߰�λ��Ч
				//�����㷨 ȡ27*27�������㣬��������Ϊ�ڵ���Ѹõ�ĺ��������Buf���������
			   if(0x0002&GPIOD->IDR)  //��������������Ч   &&x%6==0&&y%8==0
				{
						t1=0xff;  //��λ���ֽڣ�λ1�ֽ�FF λ0 �ֽ�00
					  //yBuf[p]=x; //˵���ò������Ǻ�ɫ��
					 // PictureContorl.Control_Value+=yBuf[p];//��ͺڵ������
					//  p++;//�ڵ�ָ���
				}
				else
				{
						t1=0x00;  
				}
				#ifdef TFT_OutPut
			  temp=(t1<<8)|t2;	//����	
				write_data_u16(temp);//��������+��ʾ��TFT��	
				#endif
			}
		}
		  p=0; 

		 		PictureContorl.Control_Value=PictureContorl.Control_Value/p;	//ȡƽ��
		  if(PictureContorl.TakeVerf==1)//ץ�Ĳο�ֵ
			{
				PictureContorl.Control_Value_Verf=PictureContorl.Control_Value;
				PictureContorl.TakeVerf=0;
			}
				 TIM_Cmd(TIM1, DISABLE);
		//	while(1)
				//				GUI_wrul(200,250,TIM1->CNT,0x0000,0xffff); //ˢ�¿����
		/*
		2&3&4 : ��ȡһ�����ݽ���
		*/	

		FIFO_OE=1;		 	  //��ֹFIFO���
		VSYNCCnt = 0;	      //���������־
		EXTI->IMR|=(1<<4);	  //�����ⲿ�жϣ��Ա������֡ͼ������
		EXTI->EMR|=(1<<4);
   }
 }

 void TakeVerfPhoto()
 {
	 PictureContorl.TakeVerf=1;
 }
 
