#ifndef _USART_H
#define _USART_H

#include "stm32f4xx.h"
#include "can1.h"
#include "can2.h"
#include "pwm.h"
#include "motor.h"

extern u8 FanStopFlag;

void USART2_Configuration(void);

#endif
