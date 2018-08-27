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

typedef struct coord	//����
{
		float x;
		float y;
}COORD;

typedef struct robotarm_
{
	float height;				//�߶�
	float height_set;		//��Ҫ�ﵽ�ĸ߶�
	float height_min;		//��С�߶�
	float height_max;		//���߶�
	float angle;				//�Ƕ�
	float angle_set;		//��Ҫ�ﵽ�ĽǶ�
	float angle_min;		//��С�Ƕ�
	float angle_max;		//���Ƕ�
	
}ROBOTARM;

extern ROBOTARM	RobotArm;	//��е�۵���Ϣ

void RunPoint_test(float Vstart,float Vwant,float Xwant,float Ywant,float Anglewant,float updis);
float CountCoord(COORD *vector);
float CountDirect(COORD *vector);

#endif
