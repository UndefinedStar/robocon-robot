#ifndef _PID_H
#define _PID_H

#include "math.h"
#include "can1.h"
#include "image.h"
#include "delay.h"
extern float P,I,D,translation_angle;
extern int sc_test;

//extern float *Pparameter[];

void CameraPid(void);

extern float message;

extern float message2;

extern float Angle;
extern int hd0to1_flag;
extern u8  HandFanleafFlag;
extern int PulseLockPoint;
extern float translation_angle;

#endif

