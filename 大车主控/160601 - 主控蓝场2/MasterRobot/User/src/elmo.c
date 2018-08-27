/*
**********************************************************************************************************
	*@  file: elmo.c
	*@  author: Kevin
	*@  data: 03/17/2014
	*@  version: v1.6（测试版）
	*@  brief: 加入了ELMO的自检功能，更改了底层代码，修复了一个发送时间的BUG，使得发送有100us的误差的错误消除
	*...............................................................................
	*@ Notes1: (1)初始化函数：       
	*@              name      : Elmo_Init(CAN_TypeDef* CANx, uint8_t PPr, uint8_t SPr)
	*@              function  : 调用初始化函数即可使用CAN通信模块，入参为CAN1或CAN2，用来选择
	*@			                CAN口，确保物理通信层正确，通信速度为1Mbps，同时选择TIM7的中断
	*@	     		            优先级，为底层报文发送提供时序	
	*@              input     : CANx      CAN1 or CAN2
	*@						    					PPr       TIM7的抢占优先级
	*@                          SPr       TIM7的从优先级
	*@              output    : 0	        初始化成功
	*@                          0x80000000  主控没有连上CAN总线
	*@ 													其他        对应的ELMO的ID位没有置1
	*@	
	*@         (2)力矩模式函数：        		
	*@  		    name      : Elmo_PTM(u8 elmoID, float torque);
	*@  		    function  : 单轴力矩控制函数，维持电机力矩恒定,支持模式切换  
	*@              input     : elmoID    取elmo节点ID     
	*@			    			orque     目标转矩(A)
	*@  			output    : 0         函数调用成功
	*@                          1         函数调用失败
	*@ 	
	*@         (3)速度模式函数：  
	*@              name      : Elmo_PVM(u8 elmoID, s32 speed);      
	*@ 			    function  : 单轴速度控制函数,支持模式切换 ，支持连续调用，elmo 
	*@                          将以最大加速度或减速度使电 机转速达到设定值
	*@              input     : elmoID    取elmo节点ID      
	*@					        speed     目标速度(cnt/s)
	*@  			output    : 0         函数调用成功
	*@                          1         函数调用失败
	*@
	*@         (4)位置模式函数：   
	*@              name      : Elmo_PPM(u8 elmoID, u32 speed, s32 position, u8 PPMmode);
	*@              function  : 单轴速度控制函数，支持模式切换，支持连续调用，对于POS_ABS模式
	*@ 						    终是指最终电机的位置相对于上电后的电机的位置，也就是电机 中，目    
	*@ 						    标位置始的绝对位置。对于POS_REL模式中，最终电机的位置是现在elmo
	*@ 				            绝对位置寄存器中的绝对位置加上目标位置，绝对位置寄存器在CAN_init 
	*@                          后默认为0
	*@						     例子1：
	*@						     Elmo_PPM(1, 50000, 500000, POS_ABS);
	*@						     while(position != 500000);
	*@					   	     Elmo_PPM(1, 50000, 250000, POS_REL);		
	*@                             电机位置在750000处		
	*@						     例子2：
	*@						     Elmo_PPM(1, 50000, 500000, POS_ABS);
	*@						     while(position != 500000);
	*@						     Elmo_PPM(1, 50000, 250000, POS_ABS);			
	*@						       电机位置在250000处		
	*@						     例子3：
	*@						     Elmo_PPM(1, 50000, 500000, POS_ABS);
	*@						     while(position <= 250000);
	*@						     Elmo_PPM(1, 50000, 250000, POS_REL);			
	*@					           电机位置在750000处		
	*@              input     : elmoID      取elmo节点ID,请勿在底盘控制中调用1--4        
	*@ 						    speed       速度(cnt/s)
	*@ 					        position    目标位置(cnt)
	*@ 						    PPMmode     运行模式
	*@ 						    POS_ABS    // PPM运行方式:绝对位置
	*@ 		   			        POS_REL    // PPM运行方式:相对位置
	*@  			output    : 0         函数调用成功
	*@                          1         函数调用失败
	*@
	*@         (5)电机释放函数：   
	*@              name      : Elmo_Close(u8 elmoID);
	*@              function  : 驱动输出关闭，电机靠惯性继续行驶,支持连续调用，支持联合调用（能
	*@						    够在各种elmo函数前后调用），不会影响其他函数的功能实现和elmo稳
	*@						    定性														
	*@              input     : elmoID      取elmo节点ID     
	*@  						output    : 0         函数调用成功
	*@                          1         函数调用失败
	*@         
	*@         (6)电机抱死函数：
	*@              name      : Elmo_Stop(u8 elmoID);
	*@              function  : 电机抱死，维持电机当前位置不变，支持连续调用，支持联合调用（能
	*@ 						    够在各种elmo函数前后调用），不会影响其他函数的功能实现和elmo稳
	*@ 						    定性	
	*@              input     : elmoID      取elmo节点ID     
	*@  						output    : 0         函数调用成功
	*@                          1         函数调用失败
	*@	
	*@         (7)加速度设置函数：	
	*@  			 name      : Elmo_SetAcc(u8 elmoID, u32 acc, u32 dec)
	*@               function  : 设置速度模式和位置模式的电机加减速，如果没有在函数中调用，初始化
	*@	                         后加速度默认为1000000000，减速度默认为1000000000
	*@			     input     : elmoID      取elmo的节点ID
	*@                           acc         加速度,加速度最大不能超过1000000000,同时应考虑电机性能
	*@                           dec         减速度,减速度最大不能超过1000000000,同时应考虑电机性能
	*@  			output    : 0         函数调用成功
	*@                          1         函数调用失败
	*@   
	*...............................................................................
	*@ Notes2: (1)、CAN口引脚 
	*@			     CAN1 RX -> PB8     CAN1 TX -> PB9
	*@               CAN2 RX -> PB5     CAN2 TX -> PB6
	*@         (2)、修改宏定义CAN_BUF_NUM的值修改缓冲数目
	*@         (3)、修改TIM7_Configuration()中TIM7更新中断优先级
	*@         (4)、注意CAN时钟为42MHz,TIM7时钟为42MHz
	*@ 	       (5)、注意写优先级分组函数
	*...............................................................................
	*@ Notes3: (1)、没有写节点ID和组ID的分配函数
	*@	       (2)、没有加反馈报文机制 
	*@		   (3)、没有加平滑因子设置函数	    
	*@		   (4)、Elmo_Stop()对Elmo_PTM()的响应时间太长，需要优化			
	*@         (5)、没有加节点保护函数和总线心跳报文				 
	*@    	   (6)、Elmo_Delay100us()可以改进，提高效率    
	*@         (7)、GroupID占时不能用了	
**********************************************************************************************************
*/
#include "elmo.h"
#include "stdio.h"

static CANQUEUE QUEUE_CAN;       //CAN2底层发送报文队列
static Elmo elmo[ELMO_NUM + 1];
static Elmo elmogroup;
static CAN_TypeDef* can;         //初始化选择CANx的接口变量
static u8 CAN_Error = 0;         //如果CAN发送失败，CAN_Error置1
static u32 Elmo_Init_Flag = 0;   //用来记录ELMO实际的初始化的状态


/*
********************************************************************************
  *@  name      : CAN_init
  *@  function  : Initialization for CAN
  *@  input     : CANx      CAN1 or CAN2
  *@			  			PPr       TIM7的抢占优先级
  *@              SPr       TIM7的从优先级
  *@  output    : 0	        初始化成功
  *@              1         初始化失败
********************************************************************************
*/
u32 Elmo_Init(CAN_TypeDef* CANx, uint8_t PPr, uint8_t SPr)
{  
	u8 i = 0;
	int temp = 0;
	/* 硬件及全局变量初始化 */ 
	CAN_init( CANx );
	TIM7_init( PPr, SPr);	

	/*定义变量初始化*/
	Variate_init();

	/* 对elmo分配节点ID */
	for(i=0; i <= ELMO_NUM; i++)					
	{
		elmo[i].NodeID = i;			
	}

	/* 对elmo分配组ID */
	elmogroup.NodeID = 126;

	/* 对全体节点进行通信复位 */
	for(i=1; i <= ELMO_NUM; i++)				
	{
		NMTCmd(&elmo[i], NMT_RESET_COMMUNICATION);			
		Elmo_Delay100us(50);					//结合函数Elmo_SendCmd(void)，你就能看懂所谓的延时是怎么搞的了										
	}
	
	/* 自检功能函数，CAN初始化成功，返回数值0 */
	temp = Self_test();
	if( temp )
	{
		return temp;		
	}
	

	//	/* 等待Elmo启动完毕,即接收到Boot up报文 */
	//	Elmo_Delay100us(50);

	/* CANOpen通信参数初始化 */
	/* RPDO1->0x6040,指令字,2字节,异步传输 */
	// 驱动器默认映射,不需要修改 //

	/* RPDO2->0x2012,二进制编译输入,4字节,异步传输 */
	// 驱动器默认映射,不需要修改 //

	/* 禁用TPDO,Debug时开启,电流环时最好关闭 */
	RSDO(&elmo[0], 0x1A00, 0x00, 0);
	Elmo_Delay100us(150);
	RSDO(&elmo[0], 0x1A01, 0x00, 0);
	Elmo_Delay100us(150);

	/* 进入NMT操作状态 */
	Elmo_Delay100us(40);
	NMTCmd(&elmo[0], NMT_ENTER_OPERATIONAL);													//所有ELMO进入组网操作状态
	Elmo_Delay100us(40);

	/* 关闭驱动 */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);		//所有ELMO  MO=0		失能驱动
	Elmo_Delay100us(80);

	/* 初始化加速度 */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"PM", 0, TYPE_INTEGER, 0x01);			//所有ELMO  PM=1			PM为1才能设置AC，DC
	Elmo_Delay100us(40);	
	RPDO2_Cmd_data(&elmo[0], (u8 *)"AC", 0, TYPE_INTEGER, 100000);		//所有ELMO  AC=100000		加速度
	Elmo_Delay100us(40);
	RPDO2_Cmd_data(&elmo[0], (u8 *)"DC", 0, TYPE_INTEGER, 100000);		//所有ELMO  DC=100000		减速度
	Elmo_Delay100us(40);

	/* Enter in SCM */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);		//所有ELMO  UM=2  速度模式
	Elmo_Delay100us(40);
	elmogroup.CurOPMode = UM_SCM;								//记录底盘ELMO组模式(所有ELMO模式一致时的模式)和每个ELMO的模式		
	for(i=0;i<=ELMO_NUM;i++)
	{
		elmo[i].CurOPMode = UM_SCM;			
	}

	/* 使能驱动 */
	RPDO2_Cmd_data(&elmo[0], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);			//所有ELMO  MO=1		使能驱动
	Elmo_Delay100us(250);
	Elmo_Delay100us(250);
	Elmo_Delay100us(50);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_PTM
  *@  function  : 单轴力矩模式函数
  *@  input     : elmoID    取elmo节点ID,请勿在底盘控制中调用elmo[1]~elmo[4]
  *@ 			  			torque    目标转矩(A)
  *@  output    : 0         函数调用成功
  *@              1         函数调用失败
********************************************************************************
*/
u8 Elmo_PTM(u8 elmoID, float torque)
{
    u8 i = 0;

	/* 检测初始化是否成功，如果失败，跳出函数 */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	
	/* 如果使用广播控制, 当前模式不为电流模式,切换为电流模式*/
	if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_TCM)  
	{
		if( elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(100);
		}		
		
		/* 将所有状态变量赋值为TCM */
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
	/* 使用单个ELMO控制,当前模式不为电流模式,切换为电流模式 */
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
		
        /* 如果ELMO只挂载了1个，不管怎么改其的模式，elmo[0]的模式和它一样 */		
		if(ELMO_NUM == 1)
		{
			elmo[0].CurOPMode = UM_TCM;
		}	
		/* 用来判断是否所有电机模式相同，从而确定elmo[0]的模式 */
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
		
	/* 设置目标转矩并运行电流模式 */
	RPDO2_Cmd_data( &elmo[elmoID], (u8 *)"TC", 0, TYPE_FLOAT, f2h(torque));
	Elmo_Delay100us(10);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_PVM
  *@  function  : 单轴速度模式函数
  *@  input     : elmoID   取elmo节点ID
  *@			  			speed    目标速度(cnt/s)
  *@  output    : 0         函数调用成功
  *@              1         函数调用失败
********************************************************************************
*/
u8 Elmo_PVM(u8 elmoID, s32 speed)
{
	 u8 i = 0;
	
	/* 检测初始化是否成功，如果失败，跳出函数 */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	/* 如果使用广播控制,当前模式不为速度模式,切换为速度模式 */
	if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_SCM)
	{
		if(elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(100);
		}	
		
		/* 将所有状态变量赋值为SCM */
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
	/* 使用单个ELMO控制,当前模式不为速度模式,切换为速度模式*/
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
	
        /* 如果ELMO只挂载了1个，不管怎么改其的模式，elmo[0]的模式和它一样 */				
		if(ELMO_NUM == 1)       
		{
			elmo[0].CurOPMode = UM_SCM;
		}	
		/* 用来判断是否所有电机模式相同，从而确定elmo[0]的模式 */
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

	/* 设置目标速度 */
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"JV", 0, TYPE_INTEGER, speed);
	Elmo_Delay100us(10);

	/* 运行速度模式 */
	RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
	Elmo_Delay100us(10);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_RunPPM
  *@  function  : 单轴平滑速度的位置模式
  *@  input     : elmoID    取elmo节点ID
  *@              speed     速度(cnt/s)
  *@              position  目标位置(cnt)
  *@              PPMmode   运行模式
  *@				    POS_ABS // PPM运行方式:绝对位置
  *@				    POS_REL // PPM运行方式:相对位置
  *@  output    : 0         函数调用成功
  *@              1         函数调用失败
********************************************************************************
*/
u8 Elmo_PPM(u8 elmoID, u32 speed, s32 position, u8 PPMmode)
{
	u8 i = 0;
	/* 检测初始化是否成功，如果失败，跳出函数 */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	/* 如果使用广播控制,当前模式不为位置模式,切换为位置模式 */
	if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_PCM)
	{
		if(elmo[elmoID].CurOPMode != UM_IDLE)
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
			Elmo_Delay100us(90);
		}	
		/* 将所有状态变量赋值为PCM */		
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
	/* 使用单个ELMO控制,当前模式不为位置模式,切换为位置模式 */
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


        /* 如果ELMO只挂载了1个，不管怎么改其的模式，elmo[0]的模式和它一样 */				
		if(ELMO_NUM == 1)      
		{
			elmo[0].CurOPMode = UM_PCM;
		}		
		/* 用来判断是否所有电机模式相同，从而确定elmo[0]的模式 */
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

	/* 设置目标速度 */
	RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"SP", 0, TYPE_INTEGER, speed);
	Elmo_Delay100us(20);

	/* 根据运行模式设置位置 */
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
	
	/* 运行位置模式 */
	RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
	Elmo_Delay100us(10);
	return 0;
}


/*
********************************************************************************
  *@  name      : Elmo_Close
  *@  function  : 驱动输出关闭，电机靠惯性继续行驶
  *@  input     : elmoID    取elmo节点ID,请勿在底盘控制中调用elmo[1]~elmo[4]        
  *@  output    : 0         函数调用成功
  *@              1         函数调用失败
********************************************************************************
*/
u8 Elmo_Close(u8 elmoID)
{
	u8 i = 0;
	/* 检测初始化是否成功，如果失败，跳出函数 */	
  if( CAN_Error == 1)
	{
		return 1;		
	}
	
    /* 如果使用广播控制,将所有ELMO失能 */
	if(elmoID == 0)
	{
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
		Elmo_Delay100us(100);
		
		/* 将所有状态变量赋值为IDLE */		
		elmogroup.CurOPMode = UM_IDLE;			
		for(i=0;i<=ELMO_NUM;i++)
		{
			elmo[i].CurOPMode = UM_IDLE;			
		}	    
	}
    /* 使用单个ELMO控制 */
	else 
	{
		RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_OFF);
		Elmo_Delay100us(100);
		elmo[elmoID].CurOPMode = UM_IDLE;		

        /* 如果ELMO只挂载了1个，不管怎么改其的模式，elmo[0]的模式和它一样 */			
		if(ELMO_NUM == 1)       
		{
			elmo[0].CurOPMode = UM_IDLE;
		}		
		/* 用来判断是否所有电机模式相同，从而确定elmo[0]的模式 */
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
  *@  function  : 刹车，电机抱死
  *@  input     : elmoID      取elmo节点ID,请勿在底盘控制中调用elmo[1]~elmo[4]        
  *@  output    : 0         函数调用成功
  *@              1         函数调用失败
********************************************************************************
*/
u8 Elmo_Stop(u8 elmoID)
{
	u8 i = 0;
	/* 检测初始化是否成功，如果失败，跳出函数 */	
    if( CAN_Error == 1)
	{
		return 1;		
	}
	
	/* 如果CAN总线上轴与轴的控制模式不相同，且发出广播指令，依次关闭 */
	if(elmoID == 0 && elmo[elmoID].CurOPMode == UM_UNC)  
	{
		/* 循环判断个个电机的状态，并关闭每一个电机 */
		for(i=1;i<=ELMO_NUM;i++)            
		{		
			/* 当前模式为释放电机,先打开电机，再抱死 */		
			if (elmo[i].CurOPMode == UM_IDLE) 
			{
				RPDO2_Cmd_data(&elmo[i], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
				Elmo_Delay100us(30);				
			}
			/* 当前模式为力矩模式,先切换为速度模式，再关闭 */
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

				/* 设置目标速度 */
				RPDO2_Cmd_data(&elmo[i], (u8 *)"JV", 0, TYPE_INTEGER, 0);
				Elmo_Delay100us(10);

				/* 运行速度模式 */
				RPDO2_Cmd_string(&elmo[i], (u8 *)"BG");
				Elmo_Delay100us(10);
			}	
				
			RPDO2_Cmd_string(&elmo[i], (u8 *)"ST");
			Elmo_Delay100us(10);
		}	
		
		/* 用来判断是否所有电机模式相同，从而确定elmo[0]的模式,能够进入这个if的不可能是在CAN线上只有单轴 */
		for(i=1;i<ELMO_NUM;i++)  
		{
			if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
			{
				elmo[0].CurOPMode = UM_SCM;         //如果在STOP模式里面电机模式统一了，只有可能是SCM模式
			}
			else
			{
				elmo[0].CurOPMode = UM_UNC;
				break;
			}
		}											
	}
	/* 发出广播指令，但是总线上多轴的控制模式都相同，这时候可以一起关闭 */
    else if(elmoID == 0 && elmo[elmoID].CurOPMode != UM_UNC)  
	{
		/* 当前模式为释放电机,先打开电机，再抱死 */		
		if (elmo[elmoID].CurOPMode == UM_IDLE) 
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);				
		}
		/* 当前模式为力矩模式,先切换为速度模式，再关闭 */
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

			/* 广播模式下，所有速度模式都改为SCM */
			for(i=0;i<=ELMO_NUM;i++) 
			{
				elmo[i].CurOPMode = UM_SCM;			
			}
		
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"UM", 0, TYPE_INTEGER, UM_SCM);
			Elmo_Delay100us(10);

			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);

			/* 设置目标速度 */
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"JV", 0, TYPE_INTEGER, 0);
			Elmo_Delay100us(10);

			/* 运行速度模式 */
			RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
			Elmo_Delay100us(10);
		}	
			
		RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"ST");
		Elmo_Delay100us(10);	
        
    }
	/* 使用单个ELMO控制 */
	else    
	{
		/* 当前模式为释放电机,先打开电机，再抱死 */		
		if (elmo[elmoID].CurOPMode == UM_IDLE) 
		{
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"MO", 0, TYPE_INTEGER, MO_ON);
			Elmo_Delay100us(30);				
		}
		/* 当前模式为力矩模式,先切换为速度模式，再关闭 */
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

			/* 设置目标速度 */
			RPDO2_Cmd_data(&elmo[elmoID], (u8 *)"JV", 0, TYPE_INTEGER, 0);
			Elmo_Delay100us(10);

			/* 运行速度模式 */
			RPDO2_Cmd_string(&elmo[elmoID], (u8 *)"BG");
			Elmo_Delay100us(10);

            /* 如果ELMO只挂载了1个，不管怎么改其的模式，elmo[0]的模式和它一样 */			
			for(i=1;i<ELMO_NUM;i++)  //用来判断是否所有电机模式相同，从而确定elmo[0]的模式
			{
				if( elmo[i].CurOPMode == elmo[i+1].CurOPMode )
				{
					elmo[0].CurOPMode = UM_SCM;    //如果在STOP模式里面电机模式统一了，只有可能是SCM模式
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
  *@  function  : 设置速度模式和位置模式的电机加减速
  *@  input     : elmoID     取elmo的节点ID
  *@                 acc        加速度,加速度最大不能超过1000000000,同时应考虑电机性能
  *@                 dec        减速度,减速度最大不能超过1000000000,同时应考虑电机性能
  *@  output    : 0         函数调用成功
  *@              1         函数调用失败
********************************************************************************
*/
u8 Elmo_SetAcc(u8 elmoID, u32 acc, u32 dec)
{ 
	/* 检测初始化是否成功，如果失败，跳出函数 */	
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
  *@  function  : 对于CANOPEN的NMT状态设置
  *@  input     : elmo     取elmo的节点ID
                  MNTCmd   NMT指令,NMT_xxx
  *@  output    : None
********************************************************************************
*/
static void NMTCmd(Elmo *elmo, u8 MNTCmd)
{
	u16 tmp_rear;

	/* 判断缓冲区是否已满 */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* 缓冲区已满 */
		return;
	}

	/* 填充缓冲区 */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   =  COBID_NMT_SERVICE;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     =  2;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] =  MNTCmd;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] =  elmo->NodeID;

	/* 有效数据加1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : RSDO
  *@  function  : 使用下载SDO进行指令发送
  *@  input     : elmo      取elmo节点ID
									Index     索引
                  SubIndex  子索引
                  Data      数据
  *@  output    : None
********************************************************************************
*/
static void RSDO(Elmo *elmo, u16 Index, u8 SubIndex, u32 Data)
{
	u16 tmp_rear;

	/* 判断缓冲区是否已满 */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* 缓冲区已满 */
		return;
	}

	/* 填充缓冲区 */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = COBID_RSDO + elmo->NodeID;  // COBID
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 8;                          // DLC
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = 0x22;                       // CS,传输量未确认
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] = (Index&0xFF);               // Index
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[2] = (Index&0xFF00)>>8;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[3] = (SubIndex);                 // SubIndex
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[4] = (Data&0xFF);                // Data
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[5] = (Data&0xFF00)>>8;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[6] = (Data&0xFF0000)>>16;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[7] = (Data&0xFF000000)>>24;

	/* 有效数据加1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : RPDO2_Cmd_data
  *@  function  : 使用二进制编码对ELMO发送数据指令
                  CANopen RPDO2 -> 0x2012 二进制输入-设置功能
  *@  input     : elmo   取elmo节点ID
                  Cmd    命令,以字符串形式输入
                  Index  命令的下标           
                  Type   数据类型
                  Data   数据
  *@  output    : None
********************************************************************************
*/
static void RPDO2_Cmd_data(Elmo *elmo, u8 *Cmd, u8 Index, u8 Type, u32 Data)
{
	u16 tmp_rear;

	/* 判断缓冲区是否已满 */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* 缓冲区已满 */
		return;
	}


	/* 填充缓冲区 */
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

	/* 有效数据加1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : RPDO2_Cmd_string
  *@  function  : 使用二进制编码对ELMO发送字符串指令
                  CANopen RPDO2 -> 0x2012 二进制输入-执行功能
  *@  input     : elmo   取elmo节点ID
									cmd    命令,以字符串形式输入
  *@  output    : None
********************************************************************************
*/
static void RPDO2_Cmd_string(Elmo *elmo, u8 *Cmd)
{
	u16 tmp_rear;

	/* 判断缓冲区是否已满 */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Front)
	{
		/* 缓冲区已满 */
		return;
	}

	/* 填充缓冲区 */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = COBID_RPDO2 + elmo->NodeID;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 4;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = (*Cmd++);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[1] = (*Cmd);
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[2] = 0x00;
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[3] = 0x00;

	/* 有效数据加1 */
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
		can = CAN1;				//为底层发送报文选择can口
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
		can = CAN2;				//为底层发送报文选择can口
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
	CAN_InitStructure.CAN_Prescaler = 3;     //CAN波特率42/(1+9+4)/3=1Mbps
	CAN_Init(CANx, &CAN_InitStructure);

	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;                        
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;      
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;     
	//ERROR CONTROL 的ID范围700-77f
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0700<<5;               
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;                     
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0700<<5;           
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0006;               
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;               
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	if( CANx == CAN1 )//用来自检
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
  *@  function  : 中断处理函数
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
  *@  function  : TIM7初始化，使CAN报文每100us发送一次
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
  *@  function  : TIM7中断处理函数，每100us用来发送CAN报文
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
  *@  function  : Elmo上电自检
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
  if( CAN_Error == 1) //如果初始化失败，关闭TIM7的中断和TIM7
	{
		TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM7, DISABLE);		
		return 0x80000000;		
	}
	
	Elmo_software_delay_ms(500);
	
	while((Elmo_Init_Flag & ((1<<ELMO_NUM) - 1)) != ((1<<ELMO_NUM) - 1))		//CAN接收中断中更新Elmo_Init_Flag
	{
		return Elmo_Init_Flag;
	}
	 
	return 0;
}


/*
********************************************************************************
  *@  name      : Variate_init
  *@  function  : 参数初始化
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
  *@  function  : 发送命令，有可能是CAN报文，也有可能是延迟报文
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Elmo_SendCmd(void)
{
	/* 判断缓冲区是否有数据 */
	if(QUEUE_CAN.Rear != QUEUE_CAN.Front)
	{
		/* 有数据,判断是否是延时命令 */
		if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].COBID == CAN_ID_DELAY)
		{
			/* 是延时指令,判断是否延时完毕 */
			if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].DATA[0] > 1) //发现一个BUG，改了效果好很多
			{
				/* 延时未完,延时时间减1 */
				QUEUE_CAN.CANBUF[QUEUE_CAN.Front].DATA[0]--;
			}
			else
			{
				/* 延时完毕,队首加1 */      
				QUEUE_CAN.Front++;
				if( QUEUE_CAN.Front >= CAN_BUF_NUM)
				{
					QUEUE_CAN.Front = 0;
				}
			}
		}
		else
		{
			/* 不是延时指令,发送CAN报文 */
			Elmo_CANSend( &QUEUE_CAN.CANBUF[QUEUE_CAN.Front] );

			/*队首加1*/   
			QUEUE_CAN.Front++;
			if( QUEUE_CAN.Front >= CAN_BUF_NUM)
			{
				QUEUE_CAN.Front = 0;
			}
		}
	}
	else
	{
		/* 队列为空 */ 
		return;   
	}
}


/*
********************************************************************************
  *@  name      : Elmo_CANSend
  *@  function  : 底层发送CAN报文
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Elmo_CANSend(CANDATA *pCANDATA)
{
	u8 i, TransmitMailbox;
	u32 cnt_delay;
	CanTxMsg elmoCAN;

	elmoCAN.IDE    =  CAN_ID_STD;                          // 标准帧
	elmoCAN.RTR    =  CAN_RTR_DATA;                        // 数据帧
	elmoCAN.StdId  =  pCANDATA->COBID;                     // COBID
	elmoCAN.DLC    =  pCANDATA->DLC;                       // DLC
	for(i=0;i<elmoCAN.DLC;i++)                             // Data
	{
		elmoCAN.Data[i] = pCANDATA->DATA[i];		
	}
	
	TransmitMailbox = CAN_Transmit(can, &elmoCAN);                          // 调用发送报文函数   
	
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
  *@  function  : 延迟报文用来延迟下一个报文的发送，提高发送报文的稳定性
                  N最大为255（N次100us）
  *@  input     : None
  *@  output    : None
********************************************************************************
*/
static void Elmo_Delay100us(u8 N100us)
{
	uint16_t tmp_rear;

	/* 判断缓冲区是否已满 */
	tmp_rear = QUEUE_CAN.Rear + 1;
	if(tmp_rear >= CAN_BUF_NUM)
	{
		tmp_rear = 0;
	}
	if(tmp_rear == QUEUE_CAN.Rear)                                  
	{
		/* 缓冲区已满 */
		return ;
	}

	/* 填充缓冲区 */
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].COBID   = CAN_ID_DELAY;        // 延时用的COBID 
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DLC     = 1;                   // DLC为1r 
	QUEUE_CAN.CANBUF[QUEUE_CAN.Rear].DATA[0] = N100us;              // 延时,记录时长 

	/* 有效数据加1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
}


/*
********************************************************************************
  *@  name      : Elmo_software_delay_ms
  *@  function  : Elmo软件延时
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
  *@  function  : 将浮点数转化为8字节十六进制数(IEEE754)
  *@  input     : x   浮点数 
  *@  output    : None
********************************************************************************
*/
static u32 f2h(float x)
{
	u32 *p = (u32 *)&x;
	return ((u32)*p);
}





