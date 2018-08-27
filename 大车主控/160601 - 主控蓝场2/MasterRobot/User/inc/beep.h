#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f4xx.h"
#include "delay.h"

#define BeepOff     GPIO_ResetBits(GPIOD,GPIO_Pin_11);
#define BeepOn      GPIO_SetBits(GPIOD,GPIO_Pin_11);
#define BEEP_TOGGLE	GPIO_ToggleBits(GPIOD, GPIO_Pin_11)

void Beep_Configuration(void);
void beep_show(u8 num);

#endif

