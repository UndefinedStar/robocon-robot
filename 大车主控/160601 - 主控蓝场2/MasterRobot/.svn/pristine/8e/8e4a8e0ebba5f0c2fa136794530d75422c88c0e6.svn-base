#ifndef _PID_H
#define _PID_H

#include "rundriver.h"
#include "run.h"
#include "visual_scope.h"
#include "includes.h"
#include "usart1.h"
#include "can1.h"
#include "can2.h"
#include "led8.h"


#define BPidGROUP1 1	
#define BPidGROUP2 2	
#define BPidGROUP3 3



//涵道风扇旋转PID分段
extern float Pcircle; 
extern float Icircle; 
extern float Dcircle;
//直线pid
extern float PKp;   
extern float PTi;
extern float PTd;  

extern float BKp3f;
extern float BTi3f;
extern float BTd3f;

extern unsigned char BezierPIDGroup;
extern MOTORS32 MotorPositionSet;
extern MOTORS32 MotorPositionSetOld;
extern MOTORS32 MotorSpeedSet;

extern float Distance;
extern float CameraDistanceLastTime;
extern float Ecw1;
extern u8 UsartErrorTme;
extern s16 FanSpeed;
extern float PositionCar;

void PidInit(void);
void Pid(void);
void SetLockPoint(float x,float y,float angle);
void PidLockX(float x);
void PidLockY(float y);
void PidLockAngle(float lockangle);
float sign_float(float num);
void PidCamera(void);
void ArmCamera(s16 errorheight,s16 errorwidth);
void SpeedChangeByMotorAngle(void);
void CameraLineSpeedPid(void);
void DT50Distance(float distance);
void BezierSpeedPid(void);
#endif
