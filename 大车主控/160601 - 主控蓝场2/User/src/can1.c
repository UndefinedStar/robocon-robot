#include "can1.h"

SPEED SpeedAbsolute={0,0,0};
CAMERA CameraDate[2]={30,0,30,0};

s16 ErrorCameraLine=0;

OS_FLAG_GRP *MotorResetCheck;
OS_FLAG_GRP *Flag_Pend;
OS_FLAG_GRP *CanSelfCheck;
OS_EVENT *RunStart;
OS_EVENT *ArmStart;
OS_EVENT *Task6Start;
OS_EVENT *FanSpeedChange;
OS_EVENT *ElmoSpeed;
OS_FLAGS Canself=0;
INT8U *ErrorCanSelfCheck;
INT8U *ErrorMotorResetCheck;
INT8U *ErrorFlabellumFinish;
INT8U *ErrorRunStart;
INT8U *ErrorTask6Start;
INT8U *ErrorArmStart;
INT8U *ErrorElmoSpeed;
INT8U *ErrorFanSpeedChange;

void Can1_Configuration(void)
{
		CAN_InitTypeDef can1;
		CAN_FilterInitTypeDef  can_filter;
		GPIO_InitTypeDef       gpio;
		NVIC_InitTypeDef       nvic;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource11,GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource12,GPIO_AF_CAN1);
	
		gpio.GPIO_Mode=GPIO_Mode_AF;
		gpio.GPIO_Pin=GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_Init(GPIOA, &gpio);
	
		nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority =2;
		nvic.NVIC_IRQChannelSubPriority = 4;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);
				
		CAN_DeInit(CAN1);
		CAN_StructInit(&can1);
		
		can1.CAN_TTCM = DISABLE;
		can1.CAN_ABOM = DISABLE;
		can1.CAN_AWUM = DISABLE;
		can1.CAN_NART = DISABLE;
		can1.CAN_RFLM = DISABLE;
		can1.CAN_TXFP = ENABLE;
		can1.CAN_Mode = CAN_Mode_Normal;
		can1.CAN_SJW  = CAN_SJW_1tq;
		can1.CAN_BS1 = CAN_BS1_9tq;
		can1.CAN_BS2 = CAN_BS2_4tq;
		can1.CAN_Prescaler = 3;        //CAN BaudRate 42/(1+9+4)/3=1Mbps
		CAN_Init(CAN1, &can1);

		can_filter.CAN_FilterNumber=0;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	

		can_filter.CAN_FilterIdHigh=((0x00000210<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000210<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xFF9F;                  //可以通过0X210,0X211,0X212,0X213数据来自陀螺仪
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
		
		can_filter.CAN_FilterFIFOAssignment=0;			
		can_filter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=1;
		can_filter.CAN_FilterIdHigh=((0x00000220<<21)&0xffff0000)>>16;
	  can_filter.CAN_FilterIdLow=((0x00000220<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
  	can_filter.CAN_FilterMaskIdHigh=0xFF9F;                  //可以通过0X221,0X222,0X223，数据来自激光雷达1
	  can_filter.CAN_FilterMaskIdLow=0xFFFF;
		can_filter.CAN_FilterFIFOAssignment=0;
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=2;
		can_filter.CAN_FilterIdHigh=((0x00000231<<21)&0xffff0000)>>16;
	  can_filter.CAN_FilterIdLow=((0x00000231<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
  	can_filter.CAN_FilterMaskIdHigh=0xFFFF;                  //可以通过0X231,数据来寻线摄像头
	  can_filter.CAN_FilterMaskIdLow=0xFFFF;
		can_filter.CAN_FilterFIFOAssignment=0;
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=3;
		can_filter.CAN_FilterIdHigh=((0x00000240<<21)&0xffff0000)>>16;
	  can_filter.CAN_FilterIdLow=((0x00000240<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
  	can_filter.CAN_FilterMaskIdHigh=0xFF1F;                  //可以通过0X240~0X247数据来自小板子
	  can_filter.CAN_FilterMaskIdLow=0xFFFF;
		can_filter.CAN_FilterFIFOAssignment=0;
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=4;
		can_filter.CAN_FilterIdHigh=((0x00000000<<21)&0xffff0000)>>16;
	  can_filter.CAN_FilterIdLow=((0x00000000<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
  	can_filter.CAN_FilterMaskIdHigh=0xFFFF;                  //可以通过0X000，用于自检
	  can_filter.CAN_FilterMaskIdLow=0xFFFF;
		can_filter.CAN_FilterFIFOAssignment=0;
		CAN_FilterInit(&can_filter);

    can_filter.CAN_FilterNumber=5;
		can_filter.CAN_FilterIdHigh=((0x00000200<<21)&0xffff0000)>>16;
	  can_filter.CAN_FilterIdLow=((0x00000200<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
  	can_filter.CAN_FilterMaskIdHigh=0xFFFF;                  //可以通过0X000，用于自检
	  can_filter.CAN_FilterMaskIdLow=0xFFFF;
		can_filter.CAN_FilterFIFOAssignment=0;
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=6;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000280<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000280<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xFF10;
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
		
		can_filter.CAN_FilterFIFOAssignment=0;			//过滤后的数据给fifo0
		CAN_FilterInit(&can_filter);
		
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);			//使能接收fifo0中断
}



/*
*******************************************
* Name : CAN1_RX0_IRQHandler
* Describe : 接受来自其他传感器的信号并记录
* Input : None
* Output : None
* Return : None
*******************************************
*/
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);	
		switch(rx_message.StdId)
		{
			case 0x281:
				if(rx_message.Data[0]=='P' && rx_message.Data[1]=='P')
				   Canself = OSFlagPost(CanSelfCheck,0x1000,OS_FLAG_SET,ErrorCanSelfCheck);
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='X')
				{
					 DecodeS32Data(&MotorRealPosition.MotorOne, &rx_message.Data[4]);
					 MotorRealSpeed.MotorOne=(float)(MotorRealPosition.MotorOne-MotorRealPositionOld.MotorOne)/4000*60*0.964f*50;
					 MotorRealPositionOld.MotorOne=MotorRealPosition.MotorOne;
				}
				break;
			case 0x282:
				if(rx_message.Data[0]=='P' && rx_message.Data[1]=='P')
				   Canself=OSFlagPost(CanSelfCheck,0x2000,OS_FLAG_SET,ErrorCanSelfCheck);
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='X')
				{
					 DecodeS32Data(&MotorRealPosition.MotorTwo, &rx_message.Data[4]);
					 MotorRealSpeed.MotorTwo=(float)(MotorRealPosition.MotorTwo-MotorRealPositionOld.MotorTwo)/4000*60*0.964f*50;
					 MotorRealPositionOld.MotorTwo=MotorRealPosition.MotorTwo;
				}
				break;
			case 0x283:
				if(rx_message.Data[0]=='P' && rx_message.Data[1]=='P')
				   Canself=OSFlagPost(CanSelfCheck,0x4000,OS_FLAG_SET,ErrorCanSelfCheck);
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='X')
				{
					 DecodeS32Data(&MotorRealPosition.MotorThree, &rx_message.Data[4]);
					 MotorRealSpeed.MotorThree=(float)(MotorRealPosition.MotorThree-MotorRealPositionOld.MotorThree)/4000*60*0.964f*50;
					 MotorRealPositionOld.MotorThree=MotorRealPosition.MotorThree;
				}
				break;
			case 0x284:
				if(rx_message.Data[0]=='P' && rx_message.Data[1]=='P')
				   Canself=OSFlagPost(CanSelfCheck,0x8000,OS_FLAG_SET,ErrorCanSelfCheck);
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='X')
				{
					 DecodeS32Data(&MotorRealPosition.MotorFour, &rx_message.Data[4]);
					 MotorRealSpeed.MotorFour=(float)(MotorRealPosition.MotorFour-MotorRealPositionOld.MotorFour)/4000*60*0.964f*50;
					 MotorRealPositionOld.MotorFour=MotorRealPosition.MotorFour;
				}
				break;
			case 0x000:
				if(rx_message.Data[0]=='1' && rx_message.Data[2]=='0')
				{
					if('0'<=rx_message.Data[1] && rx_message.Data[1]<='9')
						Canself=OSFlagPost(CanSelfCheck,0x0001<<(rx_message.Data[1]-48),OS_FLAG_SET,ErrorCanSelfCheck);
					else
						Canself=OSFlagPost(CanSelfCheck,0x0001<<(rx_message.Data[1]-55),OS_FLAG_SET,ErrorCanSelfCheck);
				}
			break;
			case 0x210:	//位置包
				PositionNow.x=(double)((s16)(((u16)(rx_message.Data[1])<<8)|rx_message.Data[0])) * 0.1;
				PositionNow.y=PlacePart*(double)((s16)(((u16)(rx_message.Data[3])<<8)|rx_message.Data[2])) * 0.1;
				PositionNow.angle=PlacePart*(double)((s16)(((u16)(rx_message.Data[5])<<8)|rx_message.Data[4])) * 0.1;
		  	Flagu16[PositionTime]=0;
			break;
			case 0x211:	//速度包
				SpeedAbsolute.Vx=(double)((s16)(((u16)(rx_message.Data[1])<<8)|rx_message.Data[0])) * 0.1;
				SpeedAbsolute.Vy=PlacePart*(double)((s16)(((u16)(rx_message.Data[3])<<8)|rx_message.Data[2])) * 0.1;
				SpeedNow.Vw=PlacePart*(double)((s16)(((u16)(rx_message.Data[5])<<8)|rx_message.Data[4])) * 0.1;
				SpeedNow.Vx=SpeedAbsolute.Vx*cos(PositionNow.angle/180*PI)+SpeedAbsolute.Vy*sin(PositionNow.angle/180*PI);
				SpeedNow.Vy=-SpeedAbsolute.Vx*sin(PositionNow.angle/180*PI)+SpeedAbsolute.Vy*cos(PositionNow.angle/180*PI);			
			break;
			case 0x231:	
				DecodeS16Data(&ErrorCameraLine,rx_message.Data);          //摄像头巡线偏差
				ErrorCameraLine=PlacePart*ErrorCameraLine;
				if(fabs(ErrorCameraLine)<18.5)
				{
					CameraDate[1].errorcameraline=CameraDate[0].errorcameraline;
					CameraDate[1].positionnowy=CameraDate[0].positionnowy;
					CameraDate[0].errorcameraline=ErrorCameraLine;
					CameraDate[0].positionnowy=PositionNow.y;
				}
			break;
			default:break;
		}
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_ClearFlag(CAN1, CAN_IT_FMP0);
	}
}


/*
*******************************************
* Name : ResetGyroscope_EN
* Describe : 复位陀螺仪，即会延迟几秒钟
* Input : 想要复位的坐标和位姿
* Output : None
* Return : None
*******************************************
*/
void ResetGyroscope_EN(float x,float y,float angle)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x111;							//报文ID号
	tx_message.DLC = 0x06;								//数据字节数
	
	tx_message.Data[0] = (uint8_t)((int16_t)(x*10));
	tx_message.Data[1] = (uint8_t)((int16_t)(x*10)>>8);
	tx_message.Data[2] = (uint8_t)((int16_t)(y*10));
	tx_message.Data[3] = (uint8_t)((int16_t)(y*10)>>8);
	tx_message.Data[4] = (uint8_t)((int16_t)(angle*10));
	tx_message.Data[5] = (uint8_t)((int16_t)(angle*10)>>8);
	
	Can_PutToQueue1(&tx_message);
}

/*
*******************************************
* Name : ResetPosition_EN
* Describe : 复位陀螺仪坐标，不延迟
* Input : 想要复位的坐标和位姿
* Output : None
* Return : None
*******************************************
*/
void ResetPosition_EN(float x,float y,float angle)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x112;							//报文ID号
	tx_message.DLC = 0x06;								//数据字节数
	
	tx_message.Data[0] = (uint8_t)((int16_t)(x*10));
	tx_message.Data[1] = (uint8_t)((int16_t)(x*10)>>8);
	tx_message.Data[2] = (uint8_t)((int16_t)(y*10));
	tx_message.Data[3] = (uint8_t)((int16_t)(y*10)>>8);
	tx_message.Data[4] = (uint8_t)((int16_t)(angle*10));
	tx_message.Data[5] = (uint8_t)((int16_t)(angle*10)>>8);
	
	Can_PutToQueue1(&tx_message);
}




/*
**********************************************
* Name : SelfCheck
* Describe : 自检
* Input : None
* Output : None
* Return : None
**********************************************
*/
void SelfCheckCan1(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x100;							//报文ID号
	tx_message.DLC = 0x03;								//数据字节数
	
	tx_message.Data[0] = 'W';
	tx_message.Data[1] = 'H';
	tx_message.Data[2] = 'U';
		
	Can_PutToQueue1(&tx_message);
}



/*
**********************************************
* Name : SelfReset
* Describe : 自检
* Input : None
* Output : None
* Return : None
**********************************************
*/
void SelfResetCan1(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x100;							//报文ID号
	tx_message.DLC = 0x03;								//数据字节数
	
	tx_message.Data[0] = 'R';
	tx_message.Data[1] = 'E';
	tx_message.Data[2] = 'S';
	
	
	Can_PutToQueue1(&tx_message);
}






void Can_VS4Channal_Send(int16_t n_dataCH1, int16_t n_dataCH2, int16_t n_dataCH3, int16_t n_dataCH4)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x330;//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	EncodeS16Data(&n_dataCH1,&tx_message.Data[0]);
	EncodeS16Data(&n_dataCH2,&tx_message.Data[2]);
	EncodeS16Data(&n_dataCH3,&tx_message.Data[4]);
	EncodeS16Data(&n_dataCH4,&tx_message.Data[6]);
	
	Can_PutToQueue1(&tx_message);
}


void Elmo_StartMotor(void)
{
	Can_Information tx_message={0};
	s32 a=1;
	tx_message.StdId = 0X300;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]='M';
	tx_message.Data[1]='O';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	EncodeS32Data(&a,&tx_message.Data[4]);
	
	Can_PutToQueue1(&tx_message);
}

void Elmo_RelieveMotor(void)
{
	Can_Information tx_message={0};
	s32 a=0;
	tx_message.StdId = 0X300;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]='M';
	tx_message.Data[1]='O';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	EncodeS32Data(&a,&tx_message.Data[4]);
	
	Can_PutToQueue1(&tx_message);
}

void Elmo_SetSpeed(u8 id,s32 speed)
{
	Can_Information tx_message={0};
	speed=speed*200/3;
	tx_message.StdId = 0X300+id;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]='J';
	tx_message.Data[1]='V';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	EncodeS32Data(&speed,&tx_message.Data[4]);
	
	Can_PutToQueue1(&tx_message);
}

void Elmo_Begin(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0X300;							//报文ID号
	tx_message.DLC = 0x04;								//数据字节数
	
	tx_message.Data[0]='B';
	tx_message.Data[1]='G';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	
	Can_PutToQueue1(&tx_message);
}

void Elmo_Ele(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0X0;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]=1;
	tx_message.Data[1]=0;
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	tx_message.Data[4]=0;
	tx_message.Data[5]=0;
	tx_message.Data[6]=0;
	tx_message.Data[7]=0;
	
	Can_PutToQueue1(&tx_message);
}


void Elmo_Stop(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0X301;							//报文ID号
	tx_message.DLC = 0x04;								//数据字节数
	
	tx_message.Data[0]='S';
	tx_message.Data[1]='T';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	
	
	Can_PutToQueue1(&tx_message);
}

void Elmo_GetId(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0X300;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]='P';
	tx_message.Data[1]='P';
	tx_message.Data[2]=13;
	tx_message.Data[3]=0x40;
	tx_message.Data[4]=0;
	tx_message.Data[5]=0;
	tx_message.Data[6]=0;
	tx_message.Data[7]=0;
	
	Can_PutToQueue1(&tx_message);
}


void Elmo_SetDC(s32 dc)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0X300;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]='D';
	tx_message.Data[1]='C';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0;
	EncodeS32Data(&dc,&tx_message.Data[4]);
	
	Can_PutToQueue1(&tx_message);
}


void Elmo_GetMainPosition(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0X300;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	tx_message.Data[0]='P';
	tx_message.Data[1]='X';
	tx_message.Data[2]=0;
	tx_message.Data[3]=0x40;
	tx_message.Data[4]=0;
	tx_message.Data[5]=0;
	tx_message.Data[6]=0;
	tx_message.Data[7]=0;
	
	Can_PutToQueue1(&tx_message);
}


int Can_PutToQueue1(Can_Information *temp_message)
{
	u16 temp_rear;

	/*判断缓冲区是否已满*/
	temp_rear=QUEUE_CAN1.Rear+1;
	if(temp_rear>=CAN_BUF_NUM)
	{
		temp_rear=0;
	}
	if(temp_rear==QUEUE_CAN1.Front)
	{
		/*缓冲区已满*/
		return 1;
	}
	
	/*填充缓冲区*/
	memcpy(&QUEUE_CAN1.CANBUF[QUEUE_CAN1.Rear],temp_message,sizeof(Can_Information));
	

	/* 有效数据个数加1 */
	QUEUE_CAN1.Rear++;
	if(QUEUE_CAN1.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN1.Rear = 0;
	}
	return 0;
}


void Send_Can1Cmd(void)
{
	/* 判断缓冲区是否有数据 */
	if(QUEUE_CAN1.Rear != QUEUE_CAN1.Front)
	{
		/* 有数据,判断是否是延时命令 */
		if(QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front].StdId == Can_delay)
		{
			/* 是延时指令,判断是否延时完毕 */
			if(QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front].Data[0] > 1) //发现一个BUG，改了效果好很多？？
			{
				/* 延时未完,延时时间减1 */  //延时时间为多少?
				QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front].Data[0]--;
			}
			else
			{
				/* 延时完毕,队首加1 */      
				QUEUE_CAN1.Front++;
				if( QUEUE_CAN1.Front >= CAN_BUF_NUM)
				{
					QUEUE_CAN1.Front = 0;
				}
			}
		}
		else
		{
			if((CAN1->TSR & CAN_TSR_TME) != 0)
			{
				/* 不是延时指令,发送CAN报文 */
				Send_Can( &QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front],CAN1 );
				#if Switch_CanReturn
				if(QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front].Type!=0)
           memcpy(&CanHaveSend[GetFromId(QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front].StdId)],&QUEUE_CAN1.CANBUF[QUEUE_CAN1.Front],sizeof(Can_Information));
				#endif
				/*队首加1*/   
				QUEUE_CAN1.Front++;
				if( QUEUE_CAN1.Front >= CAN_BUF_NUM)
				{
					QUEUE_CAN1.Front = 0;
				}
		  }
		}
	}
	
	else
	{
		/* 队列为空 */ 
		return;   
	}
}


void ChangeMotor(u8 motor)
{
  Can_Information tx_message={0};
	tx_message.StdId = 0x160;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='P';
	tx_message.Data[1]=motor;
	
	Can_PutToQueue1(&tx_message);
}


