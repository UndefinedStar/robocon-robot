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
	dma.DMA_Priority =DMA_Priority_VeryHigh;//以下为f4特有
	dma.DMA_FIFOMode =DMA_FIFOMode_Disable;
	dma.DMA_FIFOThreshold =DMA_FIFOThreshold_HalfFull;
	dma.DMA_PeripheralBurst =DMA_PeripheralBurst_Single;
	dma.DMA_MemoryBurst =DMA_MemoryBurst_Single;
	
	DMA_Init(DMA2_Stream7,&dma);
	DMA_ClearFlag (DMA2_Stream7,DMA_IT_TCIF7);					//清除中断标志
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

void usart_txhander(void)       //检查队列中是否有待发送的数据，如果有，将其发送出去
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
 // 	DMA_Cmd(DMA2_Stream7, DISABLE); 							//F4中不需要，中断处理函数中不需要，但是其他地方一定需要
		DMA_SetCurrDataCounter(DMA2_Stream7,j);
		DMA_Cmd(DMA2_Stream7, ENABLE);
	}
}

void USART1_sendData(u8 *a,u8 count)
{
	uint8_t i = 0,j = 0,data;
	for (i = 0; i < count; i++)
	{
		EnQueue(&TxBuffer_UART1,a[i]);									//把a[i]里面的数据给&TxBuffer_UART2
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
//		DMA_Cmd(DMA2_Stream7, DISABLE); 							//F4中不需要
		DMA_SetCurrDataCounter(DMA2_Stream7,j);
		DMA_Cmd(DMA2_Stream7, ENABLE);  
	}
}

void DMA2_Stream7_IRQHandler(void)               //数据传输完成，产生中断，检查是否还有没有传输的数据，继续传输
{
	if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7)==SET)
	{
		DMA_ClearFlag (DMA2_Stream7,DMA_IT_TCIF7);					//清除中断标志
		DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7);
		usart_txhander();
	}
}


u8 USART1_RX_BUF[32];     //接收缓冲,最大32个字节.
//接收状态
//bit7，接收完成标志
//bit6，接收开始标志
//bit4~0，接收到的有效字节数目
u8 USART1_RX_STA=0;

/*
*************************************************
* Name :USART1_IRQHandler
* Describe : 串口接收中断函数
* Input :  None
* Output : 置位对应输入的标志位
* Return : None
*************************************************
*/
void USART1_IRQHandler(void)
{
		u8 temp;
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)	//接收寄存器非空
		{
				USART_ClearFlag(USART1,USART_IT_RXNE);			//清除中断标志
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);

				temp = USART_ReceiveData(USART1);
				if((USART1_RX_STA&0x40)!=0)//接收已经开始
				{			
						if((USART1_RX_STA&0x80)==0)//接收未完成
						{
								if(temp=='*')			
										USART1_RX_STA|=0x80;	//接收完成了														
								else //还没收到*
								{	
										USART1_RX_BUF[USART1_RX_STA&0X3F]=temp;
										USART1_RX_STA++;								  
										if((USART1_RX_STA&0X3F)>31)
												USART1_RX_STA=0;//接收数据错误，重新开始接收 
								}		 
						}
				}  		
				else if(temp=='#')		//接收到包头
						USART1_RX_STA|=0x40;	
		
				if((USART1_RX_STA&0x80)!=0)			//接收已经完成，立即处理命令
				{
						USART1_Judge();
						USART1_RX_STA=0;
				}
	  
		}
}





/*
*************************************************
* Name : USART1_Judge
* Describe : 对串口输入的数据进行处理，相应的置位
						 标志位
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


/*printf函数的 配置函数*/
int fputc(int ch,FILE*f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_SendData(USART1,(uint8_t)ch);
	return ch;
		
}



