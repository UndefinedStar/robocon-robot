#include "stm32f10x.h"
#include "private_usart.h"
/**************************************************************
 ** 函数名称 :USART1_Init
 ** 功能说明 :USART1初始化（GPIO、USART1、USART1时钟、NVIC）
 ** 输入参数 :BR_num  使用的波特率
 ** 输出参数 :无
 ** 返回参数 :无
 ** 注    意 :NVIC默认未配置，配置需去除注释 建议独立使用NVIC文件统一配置所有中断优先级
***************************************************************/
void USART1_Init(uint32_t BR_num)
{	
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;  
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct; //同步串口USART时钟配置
	//开启USART1,GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	//配置PA9作为USART1　Tx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	//配置PA10作为USART1　Rx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	//配置USART1
	USART_InitStructure.USART_BaudRate = BR_num;       //波特率可以配置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //在帧结尾传输1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;    //禁用奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //发送、接收使能
	//配置同步串口USART1时钟-可注释掉使用默认值
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //时钟低电平活动
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK引脚上时钟输出的极性->低电平
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //时钟第二个边沿进行数据捕获
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //最后一位数据的时钟脉冲不从SCLK输出
	
	

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	         //组4
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		 //USART1全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级最高以便于在外部中断当中嵌套中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		 //响应优先级1 外部中断时间和串口中断 外部中断先相应
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 //使能USART1通道
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStruct);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE); 	
}
/**************************************************************
 ** 函数名 :USART1_IRQ
 ** 功能   :中断函数，将串口接收到的函数直接从串口打印出来
 ** 输入   :无
 ** 输出   :无
 ** 返回   :无
 ** 注意   :需要在misc中调用，使用前需配置好NVIC优先级
***************************************************************/
uint8_t TxBuffer[50];//2^8堆栈
uint8_t TxCount=0;            //发送指针
uint8_t count=0;                //缓存器计数器
static uint8_t RxBuffer[50];
static uint8_t RxState = 0;
void USART1_IRQ(void)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//发生溢出BUG时处理
    {   //清除溢出BUG
        USART_ClearFlag(USART1,USART_FLAG_ORE);   //读SR 
		USART_ReceiveData(USART1);           //读DR		
    }	
	//发送中断
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))//如果用库函数：if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
	{
		USART1->DR = TxBuffer[TxCount++]; //写DR清除中断标志          
		if(TxCount == count)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE中断//如果用库函数：USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
			count=0;TxCount=0; //如果缓冲器小于或大于256，取消该注释
		}
	}
}

/**************************************************************
 ** 函数名 :USART1_Put_Char
 ** 功能   :将DataToSend内容打印到串口
 ** 输入   :unsigned char
 ** 输出   :无
 ** 返回   :无
 ** 注意   :无
***************************************************************/
static void USART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}
/**************************************************************
 ** 函数名 :USART1_Put_String
 ** 功能   :将*Str指向的内容打印到串口
 ** 输入   :无
 ** 输出   :无
 ** 返回   :无
 ** 注意   :无
***************************************************************/
void USART1_Put_String(unsigned char *Str)
{
	//判断Str指向的数据是否有效.
	while(*Str)
	{
	//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
	if(*Str=='\r')USART1_Put_Char(0x0d);
		else if(*Str=='\n')USART1_Put_Char(0x0a);
			else USART1_Put_Char(*Str);
	//指针++ 指向下一个字节.
	Str++;
	}
}
/**************************************************************
 ** 函数名 :USART1_Put_buf
 ** 功能   :将数组内容打印到串口
 ** 输入   :unsigned char *DataToSend , uint8_t data_num
 ** 输出   :无
 ** 返回   :无
 ** 注意   :无
***************************************************************/
void USART1_Put_Buf(unsigned char *DataToSend,uint16_t data_num)
{	  
    uint16_t i=0;
	for(;i<data_num;i++)
		TxBuffer[count++] = *(DataToSend+i);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}
/**************************************************************
 ** 函数名 :fputc
 ** 功能   :重定向c库函数printf到USART
 ** 输入   :无
 ** 输出   :无
 ** 返回   :无
 ** 注意   :由printf调用，需配置重定义
***************************************************************/
/*
int fputc(int ch, FILE *f)	//无实用意义
{
   // 将Printf内容发往串口 
   USART_SendData(USART1, (unsigned char) ch);
   // 等待发送结束 
   while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
   return (ch);
}
*/
//非中断发送
void USART1_Send_Char(unsigned char DataToSend) //发送一个字符
{
  USART_SendData(USART1,DataToSend);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		//等待直到发送完成
}
void USART1_Send_String(unsigned char *Str)		//发送一个指定长度的字符串
{
   while(*Str)
	{	
	if(*Str=='\r')USART1_Send_Char(0x0d);//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
		else if(*Str=='\n')USART1_Send_Char(0x0a);
			else USART1_Send_Char(*Str);
	Str++;//指针++ 指向下一个字节.
	}
}
void USART_Send_Buf(unsigned char *buf , uint16_t num)
{
	uint16_t i;
	for(i=0;i<num;i++)
	{
	USART1_Send_Char(*buf);
	buf++;//指针++ 指向下一个字节.
	}
}
