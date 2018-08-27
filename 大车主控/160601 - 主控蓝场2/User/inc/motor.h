#ifndef _MOTOR_H
#define _MOTOR_H

#include "can2.h" 
#include "lcd.h"


extern void MotorInit(void);
extern void MotorInitFive(void);
extern void ClimbPole(void);
void ML_CorrectError(void);
void ArmChangeByPosition(void);
extern u32 aaa;
#endif

