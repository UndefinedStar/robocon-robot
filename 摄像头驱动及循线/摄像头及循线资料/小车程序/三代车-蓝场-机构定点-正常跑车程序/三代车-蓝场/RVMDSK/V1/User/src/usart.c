#include "usart.h"
QueueTypeDef 	  TxBuffer_UART2;
uint8_t   aTxBuffer_UART2[51]={0};
u8 dbg_show_enable = 1;
u16 HandKey_Receive = 0xFFFF;
u16 HandRock_left_Receive = 0x7B84;
u16 HandRock_right_Receive = 0x847B;
unsigned char HandMode_Receive=0;

void USART_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  nvic;
	DMA_InitTypeDef 	dma;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	
	//PD5-TX,PD6-RX,USART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=115200;                			 	//������115200
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;    		//8λ����λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;          	//һλֹͣλ
	USART_InitStructure.USART_Parity=USART_Parity_No;             	//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;			//��Ӳ��������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;			//���շ��ͷ�ʽ
	USART_Init(USART2,&USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);
	USART_ClearFlag (USART2,USART_IT_RXNE);			
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	
	nvic.NVIC_IRQChannel =USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 3;
	nvic.NVIC_IRQChannelSubPriority = 4;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	DMA_DeInit(DMA1_Stream6);
	dma.DMA_Channel =DMA_Channel_4;
	dma.DMA_BufferSize =0;
	dma.DMA_DIR =DMA_DIR_MemoryToPeripheral;
	dma.DMA_Memory0BaseAddr =(uint32_t)(aTxBuffer_UART2);
	dma.DMA_PeripheralBaseAddr =(uint32_t)(&USART2->DR);
	dma.DMA_MemoryInc =DMA_MemoryInc_Enable;
	dma.DMA_PeripheralInc =DMA_PeripheralInc_Disable;
	dma.DMA_MemoryDataSize =DMA_MemoryDataSize_Byte;
	dma.DMA_PeripheralDataSize =DMA_PeripheralDataSize_Byte;
	dma.DMA_Mode=DMA_Mode_Normal;
	dma.DMA_Priority =DMA_Priority_VeryHigh;//����Ϊf4����
	dma.DMA_FIFOMode =DMA_FIFOMode_Disable;
	dma.DMA_FIFOThreshold =DMA_FIFOThreshold_HalfFull;
	dma.DMA_PeripheralBurst =DMA_PeripheralBurst_Single;
	dma.DMA_MemoryBurst =DMA_MemoryBurst_Single;
	
	DMA_Init(DMA1_Stream6,&dma);
	DMA_ClearFlag (DMA1_Stream6,DMA_IT_TCIF6);					//����жϱ�־
	DMA_ClearITPendingBit(DMA1_Stream6,DMA_IT_TCIF6);
	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);
	
	nvic.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 2;
	nvic.NVIC_IRQChannelSubPriority = 4;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	
	USART_Cmd(USART2,ENABLE); //����2ʹ��
}
void usart_txhander(void)       //���������Ƿ��д����͵����ݣ�����У����䷢�ͳ�ȥ
{
	uint8_t i = 0,j = 0,data;
	if (DMA_GetCurrDataCounter(DMA1_Stream6) == 0)
	{
		j = GetQueueLength(&TxBuffer_UART2);
		if(j==0)
			return;
		if (j > 50) j = 50;
		for (i = 0; i < j; i++)
		{
				DeQueue(&TxBuffer_UART2,&data);
				aTxBuffer_UART2[i] = data;
		}
 // 	DMA_Cmd(DMA2_Stream7, DISABLE); 							//F4�в���Ҫ���жϴ������в���Ҫ�����������ط�һ����Ҫ
		DMA_SetCurrDataCounter(DMA1_Stream6,j);
		DMA_Cmd(DMA1_Stream6, ENABLE);
	}
}

void USART2_sendData(u8 *a,u8 count)
{
	uint8_t i = 0,j = 0,data;
	for (i = 0; i < count; i++)
	{
		EnQueue(&TxBuffer_UART2,a[i]);									//��a[i]��������ݸ�&TxBuffer_UART2
	} 	
	if (DMA_GetCurrDataCounter(DMA1_Stream6) == 0)
	{
		j = GetQueueLength(&TxBuffer_UART2);
		if (j > 50) j = 50;
		for (i = 0; i < j; i++)
		{
				DeQueue(&TxBuffer_UART2,&data);
				aTxBuffer_UART2[i] = data;
		}
//		DMA_Cmd(DMA2_Stream7, DISABLE); 							//F4�в���Ҫ
		DMA_SetCurrDataCounter(DMA1_Stream6,j);
		DMA_Cmd(DMA1_Stream6, ENABLE);  
	}
}
void DMA1_Stream6_IRQHandler(void)               //���ݴ�����ɣ������жϣ�����Ƿ���û�д�������ݣ���������
{
	if(DMA_GetITStatus(DMA1_Stream6,DMA_IT_TCIF6)==SET)
	{
		DMA_ClearFlag (DMA1_Stream6,DMA_IT_TCIF6);					//����жϱ�־
		DMA_ClearITPendingBit(DMA1_Stream6,DMA_IT_TCIF6);
		usart_txhander();
	}
}

u8 USART2_RX_BUF[32];     //���ջ���,���32���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����տ�ʼ��־
//bit4~0�����յ�����Ч�ֽ���Ŀ
u8 USART2_RX_STA=0;
/*
*************************************************
* Name :USART1_IRQHandler
* Describe : ���ڽ����жϺ���
* Input :  None
* Output : ��λ��Ӧ����ı�־λ
* Return : None
*************************************************
*/
//void USART2_IRQHandler(void)
//{
//		u8 temp;
//		if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)	//���ռĴ����ǿ�
//		{
//				USART_ClearFlag(USART2,USART_IT_RXNE);			//����жϱ�־
//				USART_ClearITPendingBit(USART2,USART_IT_RXNE);

//				temp = USART_ReceiveData(USART2);
//				if((USART2_RX_STA&0x40)!=0)//�����Ѿ���ʼ
//				{			
//						if((USART2_RX_STA&0x80)==0)//����δ���
//						{
//								if(temp=='*')			
//										USART2_RX_STA|=0x80;	//���������														
//								else //��û�յ�*
//								{	
//										USART2_RX_BUF[USART2_RX_STA&0X3F]=temp;
//										USART2_RX_STA++;								  
//										if((USART2_RX_STA&0X3F)>31)
//												USART2_RX_STA=0;//�������ݴ������¿�ʼ���� 
//								}		 
//						}
//				}  		
//				else if(temp=='#')		//���յ���ͷ
//						USART2_RX_STA|=0x40;	
//		
//				if((USART2_RX_STA&0x80)!=0)			//�����Ѿ���ɣ�������������
//				{
//						USART2_RX_STA=0;
//				}
//	  
//		}
//}
void send_picture(uint8_t * a,int array_size)
{
	int count=0;
	for(count=0;count<array_size;count++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
		USART_SendData(USART2,a[count]);
	}
}
void delay(int t)
{
	int i,a;
	for(i=0;i<t;i++)
	{
		a = 10300;
		while(a--);
	}
}

void USART2_IRQHandler(void)
{
	u8 temp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)	//���ռĴ����ǿ�
	{
		USART_ClearFlag (USART2,USART_IT_RXNE);			//����жϱ�־
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);

		temp = USART_ReceiveData(USART2);
		if((USART2_RX_STA&0x40)!=0)//�����Ѿ���ʼ
		{			
			if((USART2_RX_STA&0x80)==0)//����δ���
			{
				if(temp=='*')	
					USART2_RX_STA|=0x80;	//���������														
				else //��û�յ�*
				{	
					USART2_RX_BUF[USART2_RX_STA&0X3F]=temp;
					USART2_RX_STA++;								   //�ѱ��ҸĶ�
					if((USART2_RX_STA&0X3F)>31)USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}  		
		else if(temp=='#')		//���յ���ͷ
			USART2_RX_STA|=0x40;	
		
		if((USART2_RX_STA&0x80)!=0)			//�����Ѿ���ɣ���������ָ��
		{																//���͸�ʽΪ#M.H....L....R....E*
			//LED1_ON();										//��20���ַ�,����"."Ϊ�ֱ�����,ռһ���ֽ�
			if(USART2_RX_BUF[0]=='M')
				HandMode_Receive=USART2_RX_BUF[1];
			if(USART2_RX_BUF[2]=='H')
			{
				HandKey_Receive=USART2_RX_BUF[3]|(USART2_RX_BUF[4]<<4)|(USART2_RX_BUF[5]<<8)|(USART2_RX_BUF[6]<<12);
			}
			if(USART2_RX_BUF[7]=='L')
			{
				HandRock_left_Receive=USART2_RX_BUF[8]|(USART2_RX_BUF[9]<<4)|(USART2_RX_BUF[10]<<8)|(USART2_RX_BUF[11]<<12);
			}
			if(USART2_RX_BUF[12]=='R')
			{
				HandRock_right_Receive=USART2_RX_BUF[13]|(USART2_RX_BUF[14]<<4)|(USART2_RX_BUF[15]<<8)|(USART2_RX_BUF[16]<<12);
			}
//			if(USART2_RX_BUF[11]=='F'&&USART2_RX_BUF[16]=='B'&&USART2_RX_BUF[17]=='E')
//			{
//				FunctionType	=	USART2_RX_BUF[12];
////				ServerType		=	USART2_RX_BUF[13];
//				SeverRun			=	USART2_RX_BUF[14];
//				ViewPoint			=	USART2_RX_BUF[15];
//			}
			//LED1_OFF();
			USART2_RX_STA=0;
		}
	}
}
void send_big_data(s16 a)
{
	u8 m = 0;
	u8 n[5] = {0};
	if(a<10)
	{
		n[1] = ' ';
		n[0] = a+48;
		for(m=0;m<1;m++)
		{
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
				USART_SendData(USART2,n[m]);
		}
	}
	else if(a<100&&a>=10)
	{
		n[2] =' ';
		n[1] = a%10+48;
		n[0] = a/10+48;
		for(m=0;m<2;m++)
		{
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
				USART_SendData(USART2,n[m]);
		}
	}
	else if(a<1000&&a>=100)
	{
		n[3] = ' ';
		n[2] = a%10+48;
		n[1] = (a/10)%10+48;
		n[0] = a/100+48;
		for(m=0;m<4;m++)
		{
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
				USART_SendData(USART2,n[m]);
		}
	}
	else
	{
		n[4] = ' ';
		n[3] = a%10+48;
		n[2] = (a/10)%10+48;
		n[1] = (a/100)%10+48;
		n[0] = a/1000+48;
		for(m=0;m<5;m++)
		{
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
				USART_SendData(USART2,n[m]);
		}
	}

}