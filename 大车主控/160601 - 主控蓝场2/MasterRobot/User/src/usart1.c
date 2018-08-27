#include "usart1.h"

QueueTypeDef 	  TxBuffer_UART1;
uint8_t   aTxBuffer_UART1[51]={0};

void USART1_Judge(void);

OS_EVENT *Pevent2;
INT8U *Peventerr2;


void usart_config(void)
{
	USART_InitTypeDef usart;
	GPIO_InitTypeDef  gpio;
	NVIC_InitTypeDef  nvic;
	DMA_InitTypeDef 	dma;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 
	
	gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_AF;
  gpio.GPIO_OType = GPIO_OType_PP;
  gpio.GPIO_Speed = GPIO_Speed_100MHz;
  gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpio);
	
	usart.USART_BaudRate = 115200;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&usart);
	
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	USART_ClearFlag (USART1,USART_IT_RXNE);			
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	
	nvic.NVIC_IRQChannel =USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 3;
	nvic.NVIC_IRQChannelSubPriority = 4;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	DMA_DeInit(DMA2_Stream7);
	dma.DMA_Channel =DMA_Channel_4;
	dma.DMA_BufferSize =0;
	dma.DMA_DIR =DMA_DIR_MemoryToPeripheral;
	dma.DMA_Memory0BaseAddr =(uint32_t)(aTxBuffer_UART1);
	dma.DMA_PeripheralBaseAddr =(uint32_t)(&USART1->DR);
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
	
	DMA_Init(DMA2_Stream7,&dma);
	DMA_ClearFlag (DMA2_Stream7,DMA_IT_TCIF7);					//����жϱ�־
	DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7);
	DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE);
	
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	
	nvic.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 2;
	nvic.NVIC_IRQChannelSubPriority = 4;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	USART_Cmd(USART1,ENABLE);
	
}

void usart_txhander(void)       //���������Ƿ��д����͵����ݣ�����У����䷢�ͳ�ȥ
{
	uint8_t i = 0,j = 0,data;
	if (DMA_GetCurrDataCounter(DMA2_Stream7) == 0)
	{
		j = GetQueueLength(&TxBuffer_UART1);
		if(j==0)
			return;
		if (j > 50) j = 50;
		for (i = 0; i < j; i++)
		{
				DeQueue(&TxBuffer_UART1,&data);
				aTxBuffer_UART1[i] = data;
		}
 // 	DMA_Cmd(DMA2_Stream7, DISABLE); 							//F4�в���Ҫ���жϴ������в���Ҫ�����������ط�һ����Ҫ
		DMA_SetCurrDataCounter(DMA2_Stream7,j);
		DMA_Cmd(DMA2_Stream7, ENABLE);
	}
}

void USART1_sendData(u8 *a,u8 count)
{
	uint8_t i = 0,j = 0,data;
	for (i = 0; i < count; i++)
	{
		EnQueue(&TxBuffer_UART1,a[i]);									//��a[i]��������ݸ�&TxBuffer_UART2
	} 	
	if (DMA_GetCurrDataCounter(DMA2_Stream7) == 0)
	{
		j = GetQueueLength(&TxBuffer_UART1);
		if (j > 50) j = 50;
		for (i = 0; i < j; i++)
		{
				DeQueue(&TxBuffer_UART1,&data);
				aTxBuffer_UART1[i] = data;
		}
//		DMA_Cmd(DMA2_Stream7, DISABLE); 							//F4�в���Ҫ
		DMA_SetCurrDataCounter(DMA2_Stream7,j);
		DMA_Cmd(DMA2_Stream7, ENABLE);  
	}
}

void DMA2_Stream7_IRQHandler(void)               //���ݴ�����ɣ������жϣ�����Ƿ���û�д�������ݣ���������
{
	if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7)==SET)
	{
		DMA_ClearFlag (DMA2_Stream7,DMA_IT_TCIF7);					//����жϱ�־
		DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7);
		usart_txhander();
	}
}


u8 USART1_RX_BUF[32];     //���ջ���,���32���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����տ�ʼ��־
//bit4~0�����յ�����Ч�ֽ���Ŀ
u8 USART1_RX_STA=0;

/*
*************************************************
* Name :USART1_IRQHandler
* Describe : ���ڽ����жϺ���
* Input :  None
* Output : ��λ��Ӧ����ı�־λ
* Return : None
*************************************************
*/
void USART1_IRQHandler(void)
{
		u8 temp;
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)	//���ռĴ����ǿ�
		{
				USART_ClearFlag(USART1,USART_IT_RXNE);			//����жϱ�־
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);

				temp = USART_ReceiveData(USART1);
				if((USART1_RX_STA&0x40)!=0)//�����Ѿ���ʼ
				{			
						if((USART1_RX_STA&0x80)==0)//����δ���
						{
								if(temp=='*')			
										USART1_RX_STA|=0x80;	//���������														
								else //��û�յ�*
								{	
										USART1_RX_BUF[USART1_RX_STA&0X3F]=temp;
										USART1_RX_STA++;								  
										if((USART1_RX_STA&0X3F)>31)
												USART1_RX_STA=0;//�������ݴ������¿�ʼ���� 
								}		 
						}
				}  		
				else if(temp=='#')		//���յ���ͷ
						USART1_RX_STA|=0x40;	
		
				if((USART1_RX_STA&0x80)!=0)			//�����Ѿ���ɣ�������������
				{
						USART1_Judge();
						USART1_RX_STA=0;
				}
	  
		}
}





/*
*************************************************
* Name : USART1_Judge
* Describe : �Դ�����������ݽ��д�����Ӧ����λ
						 ��־λ
* Input :  None
* Output : None
* Return : None
*************************************************
*/
void USART1_Judge(void)
{
		USART1_RX_STA=USART1_RX_STA&0X3F;
		if(USART1_RX_BUF[0] == 'T')
		{
			StartFan(0);
			return;
		}
		
}


/*printf������ ���ú���*/
int fputc(int ch,FILE*f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_SendData(USART1,(uint8_t)ch);
	return ch;
		
}



