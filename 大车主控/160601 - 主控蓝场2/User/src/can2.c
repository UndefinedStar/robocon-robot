#include "can2.h"

MOTORPOSITION MotorRealPosition={0,0,0};
MOTORPOSITION MotorRealPositionOld={0,0,0};
MOTORCURRENT MotorRealCurrent;
MOTORSPEED MotorRealSpeed;


u8 CylinderState=0;
u8 MagneticSwitchState=0;
float CameraDistance=0;
float CameraDistanceValue=0;
float CameraDistanceOld[3]={0,0,0};
u32 n=0;
float CameraDistance0 = 0,CameraDistance1 = 0,CameraDistance2 = 0;
u8 DT50_flag = 0;

Can_queue QUEUE_CAN;
Can_queue QUEUE_CAN1;

#if Switch_CanReturn
   Can_Information CanHaveSend[16];
   Can_Information_NoSend *NoSendCan[16];
	 Can_Information_NoSend *c;
#endif

//static u8 CAN_Error = 0;         //如果CAN发送失败，CAN_Error置1


void Can2_Configuration(void)
{
		CAN_InitTypeDef can2;
		CAN_FilterInitTypeDef  can_filter;
		GPIO_InitTypeDef       gpio;
		NVIC_InitTypeDef       nvic;
	
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5,GPIO_AF_CAN2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6,GPIO_AF_CAN2);
	
		gpio.GPIO_Mode=GPIO_Mode_AF;
		gpio.GPIO_Pin=GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_Init(GPIOB, &gpio);
	
		nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority =4;
		nvic.NVIC_IRQChannelSubPriority = 4;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);
				
		CAN_DeInit(CAN2);
		CAN_StructInit(&can2);
		
		can2.CAN_TTCM = DISABLE;
		can2.CAN_ABOM = DISABLE;
		can2.CAN_AWUM = DISABLE;
		can2.CAN_NART = DISABLE;
		can2.CAN_RFLM = DISABLE;
		can2.CAN_TXFP = ENABLE;
		can2.CAN_Mode = CAN_Mode_Normal;
		can2.CAN_SJW  = CAN_SJW_1tq;
		can2.CAN_BS1 = CAN_BS1_9tq;
		can2.CAN_BS2 = CAN_BS2_4tq;
		can2.CAN_Prescaler = 3;        //CAN BaudRate 42/(1+9+4)/3=1Mbps
		CAN_Init(CAN2, &can2);

		can_filter.CAN_FilterNumber=15;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000000<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000000<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xFFFF;
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
	
		can_filter.CAN_FilterFIFOAssignment=0;			//过滤后的数据给fifo0
		can_filter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=16;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000250<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000250<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xE0FF;
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
		
		can_filter.CAN_FilterFIFOAssignment=0;			//过滤后的数据给fifo0
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=17;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000300<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000300<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xFFFF;
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
		
		can_filter.CAN_FilterFIFOAssignment=0;			//过滤后的数据给fifo0
		CAN_FilterInit(&can_filter);
		
		can_filter.CAN_FilterNumber=19;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000221<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000221<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xFFFF;
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
		
		can_filter.CAN_FilterFIFOAssignment=0;			//过滤后的数据给fifo0
		CAN_FilterInit(&can_filter);
		
		
		can_filter.CAN_FilterNumber=20;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000241<<21)&0xffff0000)>>16;
		can_filter.CAN_FilterIdLow=((0x00000241<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
		can_filter.CAN_FilterMaskIdHigh=0xFF9F;
		can_filter.CAN_FilterMaskIdLow=0xFFFF;	
		
		can_filter.CAN_FilterFIFOAssignment=0;			//过滤后的数据给fifo0
		CAN_FilterInit(&can_filter);
		
		
		CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);			//使能接收fifo0中断
		
}

void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	#if Switch_CanReturn
	Can_Information caninformation={0};
	u8 a,i;
	#endif
	u8 type=100;
	CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	CAN_ClearFlag(CAN2, CAN_IT_FMP0);
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET) 
	{
		CAN_Receive(CAN2, CAN_FIFO0, &rx_message);	
		switch(rx_message.StdId)
		{
			case 0x000:	//自检
			if(rx_message.Data[0]=='1' && rx_message.Data[2]=='0')
			{
					if('0'<=rx_message.Data[1] && rx_message.Data[1]<='9')
						Canself=OSFlagPost(CanSelfCheck,0x0001<<(rx_message.Data[1]-48),OS_FLAG_SET,ErrorCanSelfCheck);
					else
						Canself=OSFlagPost(CanSelfCheck,0x0001<<(rx_message.Data[1]-55),OS_FLAG_SET,ErrorCanSelfCheck);
			}
			break;
			case 0x200:	//DT50
				if(rx_message.Data[0]=='D' && rx_message.Data[1]=='S')
				{
						DecodeFloatData(&CameraDistance,&rx_message.Data[2]);
						if(CameraDistance < 150)
							DT50_flag = 1;
						if(DT50_flag)
						{
							CameraDistance0 = CameraDistance;
							if(CameraDistance0 - CameraDistance1 > 20 && CameraDistance2)
								CameraDistance0 = CameraDistance1 - (float)0.1*(CameraDistance1 - CameraDistance2);
							CameraDistance2 = CameraDistance1;
							CameraDistance1 = CameraDistance0;
						}
//						if(CameraDistance>1000)
//							Flag[DT50Error]++;
//						else
//							Flag[DT50Error]=0;
				}
			break;
				case 0x221:	
				if(rx_message.Data[0]=='F' && rx_message.Data[1]=='A' && rx_message.Data[2]=='N')
					type=TypeFan;
			break;
			case 0x241:	
				if(rx_message.Data[0]=='O' && rx_message.Data[1]=='K')
				{
					if(Flag[ClimbStop]==1 && PlacePart==RightPart)
					{
						Flag[SunSwitchOn]=1;
					}
				}				
			break;
			case 0x242:	
				if(rx_message.Data[0]=='L' && rx_message.Data[1]=='E' && rx_message.Data[2]=='F')
				{
					type=TypeStteringEngineLeft;
				}
			break;
			case 0x243:	
				if(rx_message.Data[0]=='R' && rx_message.Data[1]=='H' && rx_message.Data[2]=='T')
				{
					type=TypeStteringEngineRight;
				}
			break;
			case 0x250:  //气缸状态
				if(rx_message.DLC==3)
					type=TypeCylinder;
				else
				{
					CylinderState=rx_message.Data[0];
					MagneticSwitchState=rx_message.Data[1];
				}
				break;
			case 0x280:  //爪子定心机构
				if(rx_message.Data[0]=='O' && rx_message.Data[1]=='K')
				{
					LED_GreenOn;
					type=TypeMotorZero;
					ReturnSearchZero(MotorHeartHand);
					if(Flag[HeartHandSearchZero]==1)
					{
						MotorStop(MotorHeartHand);
					}
					else
					{
						switch (KeyNumber & 0x07)
						{
							case 0x00:
							case 0x01:
							case 0x02:
							case 0x03:
							case 0x04:
							case 0x06:
							case 0x07:
									MotorPosition(MotorHeartHand,3500,-46533);	//-44075
							break;
							case 0x05:
								  MotorPosition(MotorHeartHand,3500,-37533);
							default:break;
						}
				  }
				}
				else if(rx_message.Data[0]=='K' && rx_message.Data[1]=='O')
				{
					if(Flag[ClimbStop]==1 && PlacePart==LeftPart)
					{
						Flag[SunSwitchOn]=1;
						BeepOn;
					}
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='P')
				{
				    DecodeS32Data(&MotorRealPosition.HeartHand,&rx_message.Data[2]);
						if(MotorRealPosition.HeartHand==0)
							MotorRealPosition.HeartHand=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='S')
				{
				    DecodeS16Data(&MotorRealSpeed.HeartHand,&rx_message.Data[2]);
						if(MotorRealSpeed.HeartHand==0)
							MotorRealSpeed.HeartHand=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='C')
				{
				    DecodeFloatData(&MotorRealCurrent.HeartHand,&rx_message.Data[2]);
						if(MotorRealCurrent.HeartHand==0)
							MotorRealCurrent.HeartHand=1;
				}
				else if(rx_message.Data[0]=='M' && rx_message.Data[1]=='C')
				{
				    type=TypeMotorMode;
				}
				else if(rx_message.Data[0]=='C' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorPWM;
				}
				else if(rx_message.Data[0]=='S' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorSetPosition;
				}
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='W')
				{
				    type=TypeMotorSetPWM;
				}
			break;
			case 0x290:  //涵道风扇上下
				if(rx_message.Data[0]=='O' && rx_message.Data[1]=='K')
				{
					LED_RedOn;
					type=TypeMotorZero;
					ReturnSearchZero(MotorFanHight);
					switch (KeyNumber & 0x07)
					{
						case 0x00:
						case 0x07:	
						case 0x06:
						case 0x05:
							  MotorPosition(MotorFanHight,5000,-2500);   //54				  	
						break;
						case 0x01:	
							MotorPosition(MotorFanHight,5000,-72000);
						break;
						case 0x02:
 							MotorPosition(MotorFanHight,5000,-145000);
						break;
						case 0x04:
							OSSemPost(ArmStart);
						break;
						case 0x03:
							MotorPosition(MotorFanHight,3000,-190000);     // 原来为-10000
						break;
				
						default:break;
					}
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='P')
				{
				    DecodeS32Data(&MotorRealPosition.FanHight,&rx_message.Data[2]);
						if(MotorRealPosition.FanHight==0)
							MotorRealPosition.FanHight=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='S')
				{
				    DecodeS16Data(&MotorRealSpeed.FanHight,&rx_message.Data[2]);
						if(MotorRealSpeed.FanHight==0)
							MotorRealSpeed.FanHight=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='C')
				{
				    DecodeFloatData(&MotorRealCurrent.FanHight,&rx_message.Data[2]);
						if(MotorRealCurrent.FanHight==0)
							MotorRealCurrent.FanHight=1;
				}
				else if(rx_message.Data[0]=='K' && rx_message.Data[1]=='O')
				{
						if(Flag[HeartHandSearchZero]==1)
						{
							Flag[ClimbSpeedDown]=1;
						}
				}
				else if(rx_message.Data[0]=='M' && rx_message.Data[1]=='C')
				{
				    type=TypeMotorMode;
				}
				else if(rx_message.Data[0]=='C' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorPWM;
				}
				else if(rx_message.Data[0]=='S' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorSetPosition;
				}
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='W')
				{
				    type=TypeMotorSetPWM;
				}
				break;
			case 0x2A0:  //涵道风扇旋转
				if(rx_message.Data[0]=='R' && rx_message.Data[1]=='P')
				{
				    DecodeS32Data(&MotorRealPosition.FanCircle,&rx_message.Data[2]);
						ArmAngle = (float)MotorRealPosition.FanCircle/(float)111.111111;
						if(MotorRealPosition.FanCircle==0)
							MotorRealPosition.FanCircle=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='S')
				{
				    DecodeS16Data(&MotorRealSpeed.FanCircle,&rx_message.Data[2]);
						if(MotorRealSpeed.FanCircle==0)
							MotorRealSpeed.FanCircle=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='C')
				{
				    DecodeFloatData(&MotorRealCurrent.FanCircle,&rx_message.Data[2]);
						if(MotorRealCurrent.FanCircle==0)
							MotorRealCurrent.FanCircle=1;
				}
				else if(rx_message.Data[0]=='M' && rx_message.Data[1]=='C')
				{
				    type=TypeMotorMode;
				}
				else if(rx_message.Data[0]=='C' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorPWM;
				}
				else if(rx_message.Data[0]=='S' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorSetPosition;
				}
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='W')
				{
				    type=TypeMotorSetPWM;
				}
				break;
			case 0x2B0:  //定心
				if(rx_message.Data[0]=='R' && rx_message.Data[1]=='P')
				{
				    DecodeS32Data(&MotorRealPosition.SetHeart,&rx_message.Data[2]);
						if(MotorRealPosition.SetHeart==0)
							MotorRealPosition.SetHeart=1;
				}
				else if(rx_message.Data[0]=='O' && rx_message.Data[1]=='K')
				{
				  	type=TypeMotorZero;
				  	ReturnSearchZero(MotorSetHeart);
						if(Flag[ClimbStop]==1)
					  	OSFlagPost(Flag_Pend,SetHeartFinish,OS_FLAG_SET,ErrorFlabellumFinish);		
				}
				else if(rx_message.Data[0]=='K' && rx_message.Data[1]=='O')
				{
//				  	if(Flag[HeartHandSearchZero]==1)
//						{
//							Flag[ClimbStop]=1;
//						}
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='S')
				{
				    DecodeS16Data(&MotorRealSpeed.SetHeart,&rx_message.Data[2]);
						if(MotorRealSpeed.SetHeart==0)
							MotorRealSpeed.SetHeart=1;
				}
				else if(rx_message.Data[0]=='R' && rx_message.Data[1]=='C')
				{
				    DecodeFloatData(&MotorRealCurrent.SetHeart,&rx_message.Data[2]);
						if(MotorRealCurrent.SetHeart==0)
							MotorRealCurrent.SetHeart=1;
				}
				else if(rx_message.Data[0]=='M' && rx_message.Data[1]=='C')
				{
				    type=TypeMotorMode;
				}
				else if(rx_message.Data[0]=='C' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorPWM;
				}
				else if(rx_message.Data[0]=='S' && rx_message.Data[1]=='P')
				{
				    type=TypeMotorSetPosition;
				}
				else if(rx_message.Data[0]=='P' && rx_message.Data[1]=='W')
				{
				    type=TypeMotorSetPWM;
				}
				break;
				default:break;	
			}
			#if Switch_CanReturn
					a=GetFromId(rx_message.StdId);
					if(CanHaveSend[a].Type==type)
					{
						CanGroup&=(~(0x01<<a));
						CanGroupTime&=(~(0x01<<a));
						CanHaveSend[a].Type=0;
						if(NoSendCan[a]!=NULL)
						{
							c=NoSendCan[a];
							caninformation.DLC=NoSendCan[a]->DLC;
							caninformation.StdId=NoSendCan[a]->StdId;
							caninformation.Type=NoSendCan[a]->Type;
							for(i=0;i<8;i++)
							  caninformation.Data[i]=NoSendCan[a]->Data[i];
							Can_PutToQueue(&caninformation);
							NoSendCan[a]=NoSendCan[a]->Next;
							free(c);
						}
					}
			#else
					type=type;
			#endif
	 }
}


/*
**********************************************
* Name : MotorPosition
* Describe : 电机位置模式
* Input : ID       : 报文ID号
					position ：脉冲数
					speed    ：达到位置的速度
* Output : None
* Return : None
**********************************************
*/
void MotorPosition(u16 ID,s16 speed,float position)
{
	Can_Information tx_message={0};
	s32 pulse=0;
	
	#if Switch_CanReturn
	  u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(ID);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
	  tx_message.Type=TypeMotorSetPosition;
	#endif
		
	pulse=position;
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数

	
	tx_message.Data[0]='S';
	tx_message.Data[1]='P';
	EncodeS16Data(&speed,tx_message.Data+2);
	EncodeS32Data(&pulse,tx_message.Data+4);
	
		
	#if Switch_CanReturn
	if(b==1)
	{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL && i<6)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i++;
		}
		if(i>=6)
			return;
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
	Can_PutToQueue(&tx_message);
}


/*
**********************************************
* Name : MotorSpeed
* Describe : 电机速度模式
* Input : ID       : 报文ID号
					speed    ：想要达到的速度
* Output : None
* Return : None
**********************************************
*/
void MotorSpeed(u16 ID,s16 speed)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x04;								//数据字节数
	
	tx_message.Data[0]='S';
	tx_message.Data[1]='S';
	EncodeS16Data(&speed,tx_message.Data+2);
	
	Can_PutToQueue(&tx_message);
}

/*
**********************************************
* Name : MotorSearchZero
* Describe : 电机寻零
* Input : ID       : 报文ID号
					speed    ：想要达到的速度
* Output : None
* Return : None
**********************************************
*/
void MotorSearchZero(u16 ID,s16 speed)
{
	Can_Information tx_message={0};
	
  #if Switch_CanReturn
	  u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(ID);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
	  tx_message.Type=TypeMotorZero;
	#endif
	
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x04;								//数据字节数
	
	tx_message.Data[0]='S';
	tx_message.Data[1]='Z';
	EncodeS16Data(&speed,tx_message.Data+2);
	
	#if Switch_CanReturn
	if(b==1)
	{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
	  Can_PutToQueue(&tx_message);
}


/*
**********************************************
* Name : AskForMotorPosition
* Describe : 获取电机位置
* Input : ID       : 报文ID号
* Output : None
* Return : None
**********************************************
*/
void AskForMotorPosition(u16 ID)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='R';
	tx_message.Data[1]='P';
	
	Can_PutToQueue(&tx_message);
}


/*
**********************************************
* Name : MotorPWM
* Describe : 电机PWM模式
* Input : ID       : 报文ID号
					pwm    ：
* Output : None
* Return : None
**********************************************
*/
void MotorPWM(u16 ID,s16 pwm)
{
	Can_Information tx_message={0};
	
	 #if Switch_CanReturn
	  u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(ID);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
	  tx_message.Type=TypeMotorSetPWM;
	#endif
		
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x04;								//数据字节数
	
	tx_message.Data[0]='P';
	tx_message.Data[1]='W';
	EncodeS16Data(&pwm,tx_message.Data+2);
	
		
		#if Switch_CanReturn
	if(b==1)
	{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
	Can_PutToQueue(&tx_message);
}

/*
**********************************************
* Name : AskForMotorSpeed
* Describe : 获取电机速度
* Input : ID       : 报文ID号
* Output : None
* Return : None
**********************************************
*/
void AskForMotorSpeed(u16 ID)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='R';
	tx_message.Data[1]='S';
	
	Can_PutToQueue(&tx_message);
}



/*
**********************************************
* Name : AskForMotorCurrent
* Describe : 获取电机电流
* Input : ID       : 报文ID号
* Output : None
* Return : None
**********************************************
*/
void AskForMotorCurrent(u16 ID)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='R';
	tx_message.Data[1]='C';
	
  Can_PutToQueue(&tx_message);
}



/*
**********************************************
* Name : AskForMotorCurrent
* Describe : 改变电机电流上限
* Input : ID       : 报文ID号
* Output : None
* Return : None
**********************************************
*/
void ChangeMotorPWMLimit(u16 ID,u16 pwm)
{
	Can_Information tx_message={0};
	
	#if Switch_CanReturn
		u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(ID);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
	  tx_message.Type=TypeMotorPWM;
	#endif
		
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x04;								//数据字节数
	
	tx_message.Data[0]='C';
	tx_message.Data[1]='P';
	
	if(pwm>4500)
		pwm=4500;
	
	EncodeU16Data(&pwm,&tx_message.Data[2]);
	
	#if Switch_CanReturn
	if(b==1)
		{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
  Can_PutToQueue(&tx_message);
}



/*
**********************************************
* Name :MotorStop
* Describe : 电机急停
* Input : ID       : 报文ID号
					speed    ：想要达到的速度
* Output : None
* Return : None
**********************************************
*/
void MotorStop(u16 ID)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='S';
	tx_message.Data[1]='T';
	
	Can_PutToQueue(&tx_message);
}


/*
**********************************************
* Name :MotorChangeMode
* Describe : 
* Input : ID       : 报文ID号
					mode    ：想要设定的模式
* Output : None
* Return : None
**********************************************
*/
void MotorChangeMode(u16 ID,u8 mode)
{
	Can_Information tx_message={0};
	
	#if Switch_CanReturn
		u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(ID);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
		tx_message.Type=TypeMotorMode;
	#endif
		
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x03;								//数据字节数
	
	tx_message.Data[0]='M';
	tx_message.Data[1]='C';
	tx_message.Data[2]=mode;
	
	#if Switch_CanReturn
	if(b==1)
	{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
	Can_PutToQueue(&tx_message);
}

/*
**********************************************
* Name :Cylinder
* Describe : 控制气缸
* Input :  state    ：想要达到的状态
* Output : None
* Return : None
**********************************************
*/
void Cylinder(u8 state,u8 action,char f)    
{
	Can_Information tx_message={0};
	
	#if Switch_CanReturn
		u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(0x150);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
		tx_message.Type=TypeCylinder;
	#endif
	tx_message.StdId = 0x150;							//报文ID号
	tx_message.DLC = 0x03;								//数据字节数
	
	tx_message.Data[0]=f;
	tx_message.Data[1]=state;
	tx_message.Data[2]=action;
	
	#if Switch_CanReturn
	if(b==1)
	{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
	Can_PutToQueue(&tx_message);
}

/*
**********************************************
* Name :AskForCylinderState
* Describe : 获取气缸状态
* Input :  state    ：想要达到的状态
* Output : None
* Return : None
**********************************************
*/
void AskForCylinderState(void)       
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x150;							//报文ID号
	tx_message.DLC = 0x01;								//数据字节数
	
	tx_message.Data[0]='R';
	
	Can_PutToQueue(&tx_message);
}



/*
**********************************************
* Name : Start
* Describe : 开始信号
* Input : ID号
* Output : None
* Return : None
**********************************************
*/
void StartFan(float speed)
{
	Can_Information tx_message={0};
	
	#if Switch_CanReturn
	  u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(0x121);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
	  tx_message.Type=TypeFan;
	#endif
		
	tx_message.StdId = 0x121;							//报文ID号
	tx_message.DLC = 0x05;								//数据字节数
	
	if(speed>900)
		speed=900;
	else if(speed<0)
		speed=0;
	
	tx_message.Data[0]='S';
	EncodeFloatData(&speed,&tx_message.Data[1]);
	
	
	#if Switch_CanReturn
	if(b==1)
		{
		c=NoSendCan[a];
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;
	}
	else
	#endif
	if(!FanStopFlag)
		Can_PutToQueue(&tx_message);
}


/*
**********************************************
* Name : Start
* Describe : 开始信号
* Input : ID号
* Output : None
* Return : None
**********************************************
*/
void StartStteringEngine(u16 ID,float pulse)
{
	Can_Information tx_message={0};
	
	#if Switch_CanReturn
	  u8 b=0,i;
		Can_Information_NoSend *c,*d,*e;
		u8 a=GetFromId(ID);
		if((CanGroup&(1<<a))!=0)
		  b=1;
		CanGroup|=(1<<a);
		if(ID==StteringEngineRed)
	     tx_message.Type=TypeStteringEngineLeft;
		else
			 tx_message.Type=TypeStteringEngineRight;
	#endif
		
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x05;								//数据字节数
	
	
	tx_message.Data[0]='S';
	EncodeFloatData(&pulse,&tx_message.Data[1]);
	
		#if Switch_CanReturn
	if(b==1)
		{
		c=NoSendCan[a];                   
		d=malloc(sizeof(Can_Information_NoSend));
		d->DLC=tx_message.DLC;
		d->Next=NULL;
		d->StdId=tx_message.StdId;
		d->Type=tx_message.Type;
		d->Next=NULL;
		for(i=0;i<8;i++)
		{
			d->Data[i]=tx_message.Data[i];		
		}
		i=0;
		while(c!=NULL)
		{
			e=c;
			c=c->Next;  //这里还需要加入检查错误，防止can2出错的时候无限存入
			i=1;
		}
		if(i==0)
		  NoSendCan[a]=d;
		else
			e->Next=d;	
	}
	else
	#endif
	Can_PutToQueue(&tx_message);
}



void Can2_VS4Channal_Send(int16_t n_dataCH1, int16_t n_dataCH2, int16_t n_dataCH3, int16_t n_dataCH4)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x310;//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	EncodeS16Data(&n_dataCH1,&tx_message.Data[0]);
	EncodeS16Data(&n_dataCH2,&tx_message.Data[2]);
	EncodeS16Data(&n_dataCH3,&tx_message.Data[4]);
	EncodeS16Data(&n_dataCH4,&tx_message.Data[6]);
	
	Can_PutToQueue(&tx_message);
}



/*
**********************************************
* Name :MotorDeletePosition
* Describe : 清除脉冲
* Input : ID       : 报文ID号
* Output : None
* Return : None
**********************************************
*/
void MotorDeletePosition(u16 ID)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='D';
	tx_message.Data[1]='P';
	
	Can_PutToQueue(&tx_message);
}


void DT50_VS4Channal_Send(int16_t n_dataCH1, int16_t n_dataCH2, int16_t n_dataCH3, int16_t n_dataCH4)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x320;//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	
	EncodeS16Data(&n_dataCH1,&tx_message.Data[0]);
	EncodeS16Data(&n_dataCH2,&tx_message.Data[2]);
	EncodeS16Data(&n_dataCH3,&tx_message.Data[4]);
	EncodeS16Data(&n_dataCH4,&tx_message.Data[6]);
	
	Can_PutToQueue(&tx_message);
}

void ReturnSearchZero(u16 ID)
{
	Can_Information tx_message={0};
	tx_message.StdId = ID;							//报文ID号
	tx_message.DLC = 0x02;								//数据字节数
	
	tx_message.Data[0]='O';
	tx_message.Data[1]='K';
	
	Can_PutToQueue(&tx_message);
}




u8 GetFromId(u16 id)
{
	id=id>>4;
	return (u8)(id & 0x0f);
}

u16 GetIdFrom(u16 id)
{
	return ((u16)(id<<4)+0x100);
}


void Variate_init(void)
{
	memset (&QUEUE_CAN, 0, sizeof(QUEUE_CAN));
	QUEUE_CAN.Front = 0;
	QUEUE_CAN.Rear  = 0;
}


int Can_PutToQueue(Can_Information *temp_message)
{
	u16 temp_rear;

	/*判断缓冲区是否已满*/
	temp_rear=QUEUE_CAN.Rear+1;
	if(temp_rear>=CAN_BUF_NUM)
	{
		temp_rear=0;
	}
	if(temp_rear==QUEUE_CAN.Front)
	{
		/*缓冲区已满*/
		return 1;
	}
	
	/*填充缓冲区*/
	memcpy(&QUEUE_CAN.CANBUF[QUEUE_CAN.Rear],temp_message,sizeof(Can_Information));
	

	/* 有效数据个数加1 */
	QUEUE_CAN.Rear++;
	if(QUEUE_CAN.Rear >= CAN_BUF_NUM)
	{
		QUEUE_CAN.Rear = 0;
	}
	return 0;
}

 void TIM7_init(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	NVIC_InitTypeDef          NVIC_InitStructure;

	/* TIM7 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);

	/* Enable the TIM7 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Time base configuration (TIM7 clocked at 84 MHz)*/
	
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; 
	TIM_TimeBaseStructure.TIM_Period = 100;            
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


static void Send_CanCmd(void)
{
		/* 判断缓冲区是否有数据 */
	if(QUEUE_CAN.Rear != QUEUE_CAN.Front)
	{
		/* 有数据,判断是否是延时命令 */
		if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].StdId == Can_delay)
		{
			/* 是延时指令,判断是否延时完毕 */
			if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].Data[0] > 1) //发现一个BUG，改了效果好很多？？
			{
				/* 延时未完,延时时间减1 */  //延时时间为多少?
				QUEUE_CAN.CANBUF[QUEUE_CAN.Front].Data[0]--;
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
			if((CAN2->TSR & CAN_TSR_TME) != 0)
			{
				/* 不是延时指令,发送CAN报文 */
				Send_Can( &QUEUE_CAN.CANBUF[QUEUE_CAN.Front],CAN2);
				#if Switch_CanReturn
				if(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].Type!=0)
           memcpy(&CanHaveSend[GetFromId(QUEUE_CAN.CANBUF[QUEUE_CAN.Front].StdId)],&QUEUE_CAN.CANBUF[QUEUE_CAN.Front],sizeof(Can_Information));
				#endif
				/*队首加1*/   
				QUEUE_CAN.Front++;
				if( QUEUE_CAN.Front >= CAN_BUF_NUM)
				{
					QUEUE_CAN.Front = 0;
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


int can_delay(void)
{
	Can_Information tx_message={0};
	tx_message.StdId=Can_delay;
	tx_message.DLC = 8;
	tx_message.Data[0]=0x10;
	
	return (Can_PutToQueue(&tx_message));
}


void Send_Can(Can_Information *pCan_Information,CAN_TypeDef* CANx)
{
	u8 i;
//	u8 TransmitMailbox;
//	u32 cnt_delay; 
	CanTxMsg tx_message={0};
	tx_message.IDE = CAN_ID_STD;
	tx_message.RTR = CAN_RTR_DATA;
	tx_message.StdId = pCan_Information->StdId;
	tx_message.DLC =pCan_Information->DLC;
	for(i=0;i<pCan_Information->DLC;i++)
	{
		tx_message.Data[i]=pCan_Information->Data[i];
	}
	

	   CAN_Transmit(CANx, &tx_message);

	
//		TransmitMailbox = CAN_Transmit(CAN2, &tx_message);                          // 调用发送报文函数   
	
//	cnt_delay = 0x2FFF;
//	do
//	{
//		 __nop();
//	}
//		while((CAN_TransmitStatus(CAN2,TransmitMailbox) != CANTXOK) && (--cnt_delay));

//	if (cnt_delay <= 0x01 )
//		CAN_Error = 1;
//		else
//		CAN_Error = 0;
}


void TIM7_IRQHandler(void)
{
	/* 100us */
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
	{
		TIM_ClearFlag(TIM7,TIM_FLAG_Update);
		Flagu16[OverTime]++;
		if(Flagu16[OverTime]>10000)
			Flagu16[OverTime]=0;
		Send_CanCmd();
	  Send_Can1Cmd();
//		LED_TOGGLE();
	}
}		



void SelfCheckCan2(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x100;							//报文ID号
	tx_message.DLC = 0x03;								//数据字节数
	
	tx_message.Data[0] = 'W';
	tx_message.Data[1] = 'H';
	tx_message.Data[2] = 'U';
		
	Can_PutToQueue(&tx_message);
}


void SelfResetCan2(void)
{
	Can_Information tx_message={0};
	tx_message.StdId = 0x100;							//报文ID号
	tx_message.DLC = 0x03;								//数据字节数
	
	tx_message.Data[0] = 'R';
	tx_message.Data[1] = 'E';
	tx_message.Data[2] = 'S';
	
	Can_PutToQueue(&tx_message);
}


