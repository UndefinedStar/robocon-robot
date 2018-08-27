#ifndef _TIM_H
#define _TIM_H

#include "stm32f4xx.h"
#include "can2.h"


void Tim2Configuration(void);

extern u16 CanGroup;
extern u16 CanGroupTime;


#define Switch_CanReturn 1
#define Switch_Exti      0
#define Switch_Test      1

#endif

