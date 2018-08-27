#ifndef __PRIVATE_USART_H
#define __PRIVATE_USART_H

#include "stm32f10x.h"
//#include <stdio.h>

void USART1_Init(uint32_t BR_num);	

void USART1_IRQ(void);
//中断缓冲器式发送
void USART1_Put_String(unsigned char *Str);
void USART1_Put_Buf(unsigned char *DataToSend , uint16_t data_num);
//int fputc(int ch, FILE *f);
//以下是非中断发送
void USART1_Send_Char(unsigned char DataToSend);
void USART1_Send_String(unsigned char *Str);
void USART_Send_Buf(unsigned char *buf , uint16_t num);
#endif

