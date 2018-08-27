#ifndef _MOTOR_H
#define _MOTOR_H

#include "can2.h" 
#include "lcd.h"
#include "rundriver.h"


extern void MotorInit(void);
extern void MotorInitFive(void);
extern void ClimbPole(void);
void ML_CorrectError(void);
void ArmChangeByPosition(void);
void FanSpeedChangeByPosition(float x);

extern u32 aaa;
#endif

