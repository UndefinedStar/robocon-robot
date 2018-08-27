#ifndef __TEST_H__
#define __TEST_H__

#include "led.h"
#include "led8.h"
#include "beep.h"
#include "delay.h"
#include "pwm.h"
#include "run.h"
#include "rundriver.h"
#include "pid.h"
#include "includes.h"
#include "can1.h"
#include "visual_scope.h"
#include "stm32f4xx.h"
#include "stdarg.h"
#include "stdio.h"
#include "ili9320_api.h"
#include "ili9320.h"
#include "string.h"
#include "usart1.h"
#include "key.h"
#include "can2.h"
#include "usart2.h"
#include "lcd.h"
#include "motor.h"
#include "flash.h"
#include "tim.h"
#include "MyMath.h"
#include "filter.h"
#include "exti.h"

typedef struct coord	//向量
{
		float x;
		float y;
}COORD;

typedef struct robotarm_
{
	float height;				//高度
	float height_set;		//想要达到的高度
	float height_min;		//最小高度
	float height_max;		//最大高度
	float angle;				//角度
	float angle_set;		//想要达到的角度
	float angle_min;		//最小角度
	float angle_max;		//最大角度
	
}ROBOTARM;

extern ROBOTARM	RobotArm;	//机械臂的信息

void RunPoint_test(float Vstart,float Vwant,float Xwant,float Ywant,float Anglewant,float updis);
float CountCoord(COORD *vector);
float CountDirect(COORD *vector);

#endif
