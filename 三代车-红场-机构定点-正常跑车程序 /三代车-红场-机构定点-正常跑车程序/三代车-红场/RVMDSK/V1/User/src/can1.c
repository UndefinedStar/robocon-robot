#include "can1.h"
#include "image.h"
#include "visual_scope.h"

s16 HuorDistance=0,HuorDistance2=0,DirectionFlag = 3;
float UltrosonicDistance = 0;
s32 Distance = 0;
float Fdistance = 0;
int last_position,now_position;
s16 KeyCommandFlag = 0;

u16 ID_Electromagnet=0x0146;    //电磁铁

void Can1_Configuration(void)
{
		CAN_InitTypeDef can1;
		GPIO_InitTypeDef       gpio;
		CAN_FilterInitTypeDef  can_filter;
		NVIC_InitTypeDef       nvic;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource11,GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource12,GPIO_AF_CAN1);
	
		gpio.GPIO_Mode=GPIO_Mode_AF;
		gpio.GPIO_Pin=GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_Init(GPIOA, &gpio);
	
		nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority =3;
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
		can1.CAN_Prescaler = 3;        
		CAN_Init(CAN1, &can1);
		
		can_filter.CAN_FilterNumber=0;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=((0x00000101<<21)&0xffff0000)>>16;
	  can_filter.CAN_FilterIdLow=((0x00000101<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
	  can_filter.CAN_FilterMaskIdHigh=0x0000;
	  can_filter.CAN_FilterMaskIdLow=0x0000;	
		can_filter.CAN_FilterFIFOAssignment=0;		
		can_filter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&can_filter);
			
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);	
}


void SendPulse(s32 data1,s32 data2)
{
	CanTxMsg tx_message;
	tx_message.StdId = 0x145;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	tx_message.RTR = CAN_RTR_Data;				//数据帧
	tx_message.IDE = CAN_Id_Standard;			//标准ID
	
	//前四位,转向
	EncodeS32Data(&data1,&tx_message.Data[0]);
	//后四位，刹车
	EncodeS32Data(&data2,&tx_message.Data[4]);
	
	CAN_Transmit(CAN1,&tx_message);
}
void SendPulseBeep(s16 data1,s32 data2)
{
	CanTxMsg tx_message;
	tx_message.StdId = 0x0147;							//报文ID号
	tx_message.DLC = 0x08;								//数据字节数
	tx_message.RTR = CAN_RTR_Data;				//数据帧
	tx_message.IDE = CAN_Id_Standard;			//标准ID
	
	//前四位,转向
	EncodeS16Data(&data1,&tx_message.Data[0]);
	EncodeS32Data(&data2,&tx_message.Data[2]);
	CAN_Transmit(CAN1,&tx_message);
}
void SendHandKey_3(u16 ID,char a,u8 state_up,u8 state_back)
{
	CanTxMsg tx_message;
	tx_message.StdId = ID;
	tx_message.DLC = 0x03;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.IDE = CAN_Id_Standard;
	
	tx_message.Data[0] = a;	
	tx_message.Data[1] = state_up;
	tx_message.Data[2] = state_back;			//速度模式
	
	CAN_Transmit(CAN1,&tx_message);
}

void SendElectromagnet(char i)
{
	CanTxMsg tx_message;
	tx_message.StdId = ID_Electromagnet;
	tx_message.DLC=0x01;
	tx_message.RTR=CAN_RTR_Data;
	tx_message.IDE = CAN_Id_Standard;
	
	tx_message.Data[0]=i;
	
	CAN_Transmit(CAN1,&tx_message);
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
int m = 0;
void CAN1_RX0_IRQHandler(void)
{
	int i = 0;
	CanRxMsg rx_message;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);	
		switch(rx_message.StdId)
		{
			case 0x0101:
				{				
					DecodeS16Data(&(HuorDistance),&rx_message.Data[0]);
					DecodeS16Data(&(DirectionFlag),&rx_message.Data[2]);
					DecodeFloatData(&(UltrosonicDistance),&rx_message.Data[4]);
					break;
				}

			case 0x0120:
				{				
					if(rx_message.Data[0]=='1'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='7')
					{
						ZjBigAngleRow += 1;
					}
					else if(rx_message.Data[0]=='1'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='8')
					{
						ZjBigAngleRow-=1;
					}
					else if(rx_message.Data[0]=='1'&&rx_message.Data[1]=='5'&&rx_message.Data[2]=='7')
					{
						ZjScSpeed += 1;
					}
					else if(rx_message.Data[0]=='1'&&rx_message.Data[1]=='5'&&rx_message.Data[2]=='8')
					{
						ZjScSpeed -= 1;
					}
					else if(rx_message.Data[0]=='2'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='7')
					{
						HdAngle+=0.5;
					}
					else if(rx_message.Data[0]=='2'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='8')
					{
						HdAngle-=0.5;
					}
					else if(rx_message.Data[0]=='2'&&rx_message.Data[1]=='5'&&rx_message.Data[2]=='7')
					{
						HdScSpeed+=1;
					}
					else if(rx_message.Data[0]=='2'&&rx_message.Data[1]=='5'&&rx_message.Data[2]=='8')
					{
						HdScSpeed-=1;
					}
					else if(rx_message.Data[0]=='3'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='7')
					{
						xpp1+=0.02;
//						xpp2+=0.05;
//						xpp3+=0.01;
					}
					else if(rx_message.Data[0]=='3'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='8')
					{
						xpp1-=0.02;
//						xpp2-=0.05;
//						xpp3-=0.01;
					}
					else if(rx_message.Data[0]=='3'&&rx_message.Data[1]=='5'&&rx_message.Data[2]=='7')
					{
						xpp2+=0.05;
					}
					else if(rx_message.Data[0]=='3'&&rx_message.Data[1]=='5'&&rx_message.Data[2]=='8')
					{
						xpp2-=0.05;
					}		
					else if(rx_message.Data[0]=='3'&&rx_message.Data[1]=='6'&&rx_message.Data[2]=='7')
					{
						XpScSpeed+=2;
					}
					else if(rx_message.Data[0]=='3'&&rx_message.Data[1]=='6'&&rx_message.Data[2]=='8')
					{
						XpScSpeed-=2;
					}	
					else if(rx_message.Data[0]=='A'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='7')
					{
						translation_angle+=0.3;
					}
					else if(rx_message.Data[0]=='A'&&rx_message.Data[1]=='4'&&rx_message.Data[2]=='8')
					{
						translation_angle-=0.3;
					}
					break;
				}
			default:break;
		}
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_ClearFlag(CAN1, CAN_IT_FMP0);		
	}
}
