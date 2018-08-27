#include "stm32f10x.h"
#include "private_usart.h"
/**************************************************************
 ** �������� :USART1_Init
 ** ����˵�� :USART1��ʼ����GPIO��USART1��USART1ʱ�ӡ�NVIC��
 ** ������� :BR_num  ʹ�õĲ�����
 ** ������� :��
 ** ���ز��� :��
 ** ע    �� :NVICĬ��δ���ã�������ȥ��ע�� �������ʹ��NVIC�ļ�ͳһ���������ж����ȼ�
***************************************************************/
void USART1_Init(uint32_t BR_num)
{	
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;  
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct; //ͬ������USARTʱ������
	//����USART1,GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	//����PA9��ΪUSART1��Tx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	//����PA10��ΪUSART1��Rx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	//����USART1
	USART_InitStructure.USART_BaudRate = BR_num;       //�����ʿ�������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��
	//����ͬ������USART1ʱ��-��ע�͵�ʹ��Ĭ��ֵ
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK������ʱ������ļ���->�͵�ƽ
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //ʱ�ӵڶ������ؽ������ݲ���
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //���һλ���ݵ�ʱ�����岻��SCLK���
	
	

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	         //��4
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		 //USART1ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�����Ա������ⲿ�жϵ���Ƕ���ж�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		 //��Ӧ���ȼ�1 �ⲿ�ж�ʱ��ʹ����ж� �ⲿ�ж�����Ӧ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 //ʹ��USART1ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStruct);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE); 	
}
/**************************************************************
 ** ������ :USART1_IRQ
 ** ����   :�жϺ����������ڽ��յ��ĺ���ֱ�ӴӴ��ڴ�ӡ����
 ** ����   :��
 ** ���   :��
 ** ����   :��
 ** ע��   :��Ҫ��misc�е��ã�ʹ��ǰ�����ú�NVIC���ȼ�
***************************************************************/
uint8_t TxBuffer[50];//2^8��ջ
uint8_t TxCount=0;            //����ָ��
uint8_t count=0;                //������������
static uint8_t RxBuffer[50];
static uint8_t RxState = 0;
void USART1_IRQ(void)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//�������BUGʱ����
    {   //������BUG
        USART_ClearFlag(USART1,USART_FLAG_ORE);   //��SR 
		USART_ReceiveData(USART1);           //��DR		
    }	
	//�����ж�
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))//����ÿ⺯����if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
	{
		USART1->DR = TxBuffer[TxCount++]; //дDR����жϱ�־          
		if(TxCount == count)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�//����ÿ⺯����USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
			count=0;TxCount=0; //���������С�ڻ����256��ȡ����ע��
		}
	}
}

/**************************************************************
 ** ������ :USART1_Put_Char
 ** ����   :��DataToSend���ݴ�ӡ������
 ** ����   :unsigned char
 ** ���   :��
 ** ����   :��
 ** ע��   :��
***************************************************************/
static void USART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}
/**************************************************************
 ** ������ :USART1_Put_String
 ** ����   :��*Strָ������ݴ�ӡ������
 ** ����   :��
 ** ���   :��
 ** ����   :��
 ** ע��   :��
***************************************************************/
void USART1_Put_String(unsigned char *Str)
{
	//�ж�Strָ��������Ƿ���Ч.
	while(*Str)
	{
	//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
	if(*Str=='\r')USART1_Put_Char(0x0d);
		else if(*Str=='\n')USART1_Put_Char(0x0a);
			else USART1_Put_Char(*Str);
	//ָ��++ ָ����һ���ֽ�.
	Str++;
	}
}
/**************************************************************
 ** ������ :USART1_Put_buf
 ** ����   :���������ݴ�ӡ������
 ** ����   :unsigned char *DataToSend , uint8_t data_num
 ** ���   :��
 ** ����   :��
 ** ע��   :��
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
 ** ������ :fputc
 ** ����   :�ض���c�⺯��printf��USART
 ** ����   :��
 ** ���   :��
 ** ����   :��
 ** ע��   :��printf���ã��������ض���
***************************************************************/
/*
int fputc(int ch, FILE *f)	//��ʵ������
{
   // ��Printf���ݷ������� 
   USART_SendData(USART1, (unsigned char) ch);
   // �ȴ����ͽ��� 
   while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
   return (ch);
}
*/
//���жϷ���
void USART1_Send_Char(unsigned char DataToSend) //����һ���ַ�
{
  USART_SendData(USART1,DataToSend);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		//�ȴ�ֱ���������
}
void USART1_Send_String(unsigned char *Str)		//����һ��ָ�����ȵ��ַ���
{
   while(*Str)
	{	
	if(*Str=='\r')USART1_Send_Char(0x0d);//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
		else if(*Str=='\n')USART1_Send_Char(0x0a);
			else USART1_Send_Char(*Str);
	Str++;//ָ��++ ָ����һ���ֽ�.
	}
}
void USART_Send_Buf(unsigned char *buf , uint16_t num)
{
	uint16_t i;
	for(i=0;i<num;i++)
	{
	USART1_Send_Char(*buf);
	buf++;//ָ��++ ָ����һ���ֽ�.
	}
}
