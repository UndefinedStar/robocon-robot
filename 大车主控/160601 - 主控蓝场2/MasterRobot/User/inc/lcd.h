#ifndef _LCD_H
#define _LCD_H

#include "stm32f4xx.h"
#include "ili9320_api.h"
#include "ili9320.h"
#include "can1.h"
#include "can2.h"
#include "key.h"

#define StartRun    0
#define Row         1
#define Coulum      2
#define AdjustKey   3
#define Page        4
#define PageCoulum  5
#define PageOld     6
#define Calculate   7
#define Save        8

#define PageLimit   3

#define AimX 575
#define AimY 1327

extern u8 KeyNumber;
extern u8 ErrorShow;
extern s16 CarBehindPoint;
extern s16 CarBehindStartX;
extern s16 PathPoint;
extern s16 AnglePoint;
extern s16 LineY;
extern u8  RiverTimeLimit;
extern u8  RiverTimeDown;
extern s16  BazierAngle1;
extern s16  BazierLength1;
extern s16  BazierLength2;
extern s16  BazierAngle2;
extern u16  PutFanLimit;
extern u8  FanSpeedFour;
extern u16  ClimbTimeLimit;
extern u8  ClimbDownLimit;
extern int Adjust[10];
extern s8  Switch_ClimbDown;
extern s8  Switch_DT50;
extern s8  Switch_Computer;
extern s8  LineCameraCorrent;
extern s8  DT50LineStandar;
extern s8  Switch_SpeedDown;
extern u16 GyroscopeCoefficientX;
extern u16 GyroscopeCoefficientY;
extern s8  Switch_Magnetic;
extern s8  DT50Speed;
extern s8  Switch_DT50Line;
extern u16  Vbegin;
extern u16  Abegin;
extern u16 FanSpeedDown;
extern s8 Switch_Climb;
void LCDShow(void);
void LCDAdjust(void);

#endif


