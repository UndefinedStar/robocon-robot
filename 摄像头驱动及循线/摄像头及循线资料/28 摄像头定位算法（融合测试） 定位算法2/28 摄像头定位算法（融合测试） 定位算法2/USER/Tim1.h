#ifndef HCSR04_H
#define HCSR04_H

#include "stm32f10x.h"
#include <math.h>
#include "delay.h"

void TIM1_Init(void);
void TIM1_NVIC_Configuration(void);
void TIM_Configuration(void);
extern int overflow;
#endif

