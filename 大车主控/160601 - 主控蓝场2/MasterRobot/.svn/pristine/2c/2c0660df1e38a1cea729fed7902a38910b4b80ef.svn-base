#ifndef _PWM_H
#define _PWM_H

#include "stm32f4xx.h"
#include "math.h"



/****************************************/
//#define BREAK_All_MOTOR  Elmo_Stop();
//#define FREE_ALL_MOTOR	 Elmo_StartMotor();
#define BREAK_All_MOTOR  GPIO_SetBits(GPIOC, GPIO_Pin_2);
#define FREE_ALL_MOTOR	 Elmo_StartMotor();GPIO_ResetBits(GPIOC, GPIO_Pin_2);
#define BREAK_CHANNEL4	 GPIO_ResetBits(GPIOG, GPIO_Pin_7);
#define BREAK_CHANNEL3	 GPIO_ResetBits(GPIOG, GPIO_Pin_8);
#define BREAK_CHANNEL1	 GPIO_ResetBits(GPIOG, GPIO_Pin_6);
#define BREAK_CHANNEL2	 GPIO_ResetBits(GPIOG, GPIO_Pin_5);
#define FREE_CHANNEL4	   GPIO_SetBits(GPIOG, GPIO_Pin_7);
#define FREE_CHANNEL3	   GPIO_SetBits(GPIOG, GPIO_Pin_8);
#define FREE_CHANNEL1	   GPIO_SetBits(GPIOG, GPIO_Pin_6);
#define FREE_CHANNEL2	   GPIO_SetBits(GPIOG, GPIO_Pin_5);

/****************************************/

void PWM_configuration(void);
void PWM_set(u8 PWM_channel,u16 give_pulse);
void BreakIO_configuration(void);
#endif
