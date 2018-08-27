#ifndef _PID_H
#define _PID_H

#include "math.h"
#include "can1.h"
#include "image.h"
#include "delay.h"
extern float P,I,D;
extern int sc_test;

//extern float *Pparameter[];

void CameraPid(void);

extern float message;

extern float message2;

extern float Angle,BigCarWaitingDistance;
extern int hd0to1_flag,XpScTime,XpScFlag,PulseLockPoint;
extern u8  HandFanleafFlag;
extern float translation_angle;

#endif

