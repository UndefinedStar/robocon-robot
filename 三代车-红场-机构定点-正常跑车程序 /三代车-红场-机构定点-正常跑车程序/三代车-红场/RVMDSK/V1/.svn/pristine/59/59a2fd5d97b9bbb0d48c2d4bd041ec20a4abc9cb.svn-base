#ifndef _USART_H
#define _USART_H

#include "stm32f4xx.h"
#include "misc.h"
#include "delay.h"
#include "queue.h"


void USART_GPIO_Config(void);
void send_picture(uint8_t * a,int array_size);
void delay(int t);
void USART2_sendData(u8 *a,u8 count);
void send_big_data(s16 a);
extern u16 HandKey_Receive;
extern u16 HandRock_left_Receive;
extern u16 HandRock_right_Receive;
extern unsigned char HandMode_Receive;
extern u8 USART2_TX_BUF[32];			//·¢ËÍ»º³å

#endif
