#include "usart4.h"

s16 ErrorCameraHeight=500;
s16 ErrorCameraWidth=500;
s16 ErrorCameraHeight1=500;
s16 ErrorCameraWidth1=500;

void USART4_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE); 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);			//�����ж�
	
	//����NVIC
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;          
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           
	NVIC_Init(&NVIC_InitStructure);   

	//ʹ��USART
	USART_Cmd(UART4, ENABLE);
}



u8 USART4_RX_BUF[32];     //���ջ���,���32���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����տ�ʼ��־
//bit4~0�����յ�����Ч�ֽ���Ŀ
u8 USART4_RX_STA=0;       //����״̬���
	
void UART4_IRQHandler(void)
{
	u8 temp;
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)	//���ռĴ����ǿ�
	{
		USART_ClearFlag (UART4,USART_IT_RXNE);			//����жϱ�־
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);

		temp = USART_ReceiveData(UART4);
		if((USART4_RX_STA&0x40)!=0)//�����Ѿ���ʼ
		{
			if((USART4_RX_STA&0x80)==0)//����δ���
			{
				if(temp=='*')
					USART4_RX_STA|=0x80;	//���������
				else //��û�յ�*
				{
					USART4_RX_BUF[USART4_RX_STA&0X3f]=temp;
					USART4_RX_STA++;								   //�ѱ��ҸĶ�
					if((USART4_RX_STA&0X3F)>31)USART4_RX_STA=0;//�������ݴ���,���¿�ʼ����
				}
			}
		}
		else if(temp=='#')		//���յ���ͷ
			USART4_RX_STA|=0x40;
		
		if((USART4_RX_STA&0x80)!=0)			//�����Ѿ���ɣ���������ָ��
		{
			if(USART4_RX_BUF[0]=='R' && USART4_RX_BUF[1]=='C')
			{
				UsartErrorTme=0;
				DecodeS16Data(&ErrorCameraWidth,&USART4_RX_BUF[2]);
				DecodeS16Data(&ErrorCameraHeight,&USART4_RX_BUF[4]);			
				ErrorCameraHeight1 = ErrorCameraHeight;
				ErrorCameraWidth1 = ErrorCameraWidth;
//				if(ErrorCameraWidth == 500)
//				{
//					ErrorCameraWidth = 0;
//					ErrorCameraHeight = 0;
//				}
				if(USART4_RX_BUF[4]==0)
					Flag[LostPicture]=0;
				else if(USART4_RX_BUF[4]==1)
					Flag[LostPicture]++;
			}
			if(USART4_RX_BUF[0]=='S' && USART4_RX_BUF[1]=='T')
			{
				if(PositionNow.x>245)
				{
//					OSSemPost(ArmStart);
//					BeepOn;
				}
			}                                           //127,472   60,800
			
			USART4_RX_STA=0;
		}
	}
}


