#ifndef _KEY_H
#define _KEY_H

#include "stm32f4xx.h"
#include "pwm.h"

#define RowIn        GPIOD->MODER&=0xF0FFFFFF;GPIOG->MODER&=0xFFFFC3FF;  
#define RowOut       GPIOD->MODER|=0x05000000;GPIOG->MODER|=0x00001400; 
#define CoulumIn     GPIOC->MODER&=0xFFFF0FFF;GPIOG->MODER&=0xFFFC3FFF;
#define CoulumOut    GPIOC->MODER|=0x00005000;GPIOG->MODER|=0x00014000;

#define RowLow       GPIO_ResetBits(GPIOG,GPIO_Pin_5 | GPIO_Pin_6);GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13);
#define RowHigh      GPIO_SetBits(GPIOG,GPIO_Pin_5 | GPIO_Pin_6);GPIO_SetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13);
void Key_Configuration(void);

#endif

