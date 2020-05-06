#ifndef _PS2_H
#define _PS2_H

#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"


#define SET_PS2_ATT()			GPIOF->BSRRL = GPIO_Pin_11
#define RESET_PS2_ATT()		GPIOF->BSRRH = GPIO_Pin_11
#define SET_PS2_CLK()			GPIOF->BSRRL = GPIO_Pin_12
#define RESET_PS2_CLK()		GPIOF->BSRRH = GPIO_Pin_12
#define SET_PS2_CMD()			GPIOF->BSRRL = GPIO_Pin_14
#define RESET_PS2_CMD()		GPIOF->BSRRH = GPIO_Pin_14

extern u16 HandKey;
extern u16 HandKey_old;
extern u16 HandRock_left;
extern u16 HandRock_left_old;
extern u16 HandRock_right;
extern u16	HandRock_right_old;
extern unsigned char HandMode;	//手柄模式，1-按键模式，2-摇杆模式
extern int send_picture_flag;

void PS2_Configuration(void);
void ReadHand(void);
void BlueHand(void);	//读取蓝牙手柄

#endif
