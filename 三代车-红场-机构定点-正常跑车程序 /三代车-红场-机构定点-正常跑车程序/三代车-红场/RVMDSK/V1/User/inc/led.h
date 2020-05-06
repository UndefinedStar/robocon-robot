#ifndef _LED_H
#define _LED_H

#include "stm32f4xx.h"

#define LED_ON()				GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define LED_OFF()				GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define LED_TOGGLE()		GPIO_ToggleBits(GPIOA, GPIO_Pin_15)

#define BEEP_ON()   GPIO_SetBits(GPIOF, GPIO_Pin_6)
#define BEEP_OFF()   GPIO_ResetBits(GPIOF, GPIO_Pin_6)

void led_configuration(void);
void Systic_Configuration(void);

#endif

