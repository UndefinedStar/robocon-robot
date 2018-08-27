#ifndef _RUNDRIVER_H
#define _RUNDRIVER_H


#define RightPart    -1              
#define LeftPart     1

#include "stm32f4xx.h"
#include "math.h"
#include "pwm.h"

#define BeginX       36.135            //29.76        //37.8
#define BeginY       39.7            //41.05        //54.6
#define BeginSixX    90
#define BeginSixY    1330


#define CAN_BUF_NUM         50                            //缓冲指令条数

extern s32 PlacePart;

//结构体声明
typedef struct position
{
		float x;
		float y;
		float angle;              //角度制
}POSITION;

typedef struct speed
{
		float Vx;
		float Vy;
		float Vw;
}SPEED;

typedef struct pointonbezier
{
		float x;
		float y;
		float t;
}POINTONBEZIER;

typedef struct posi
{
		float x;
		float y;
}POSI;

typedef struct motorposition
{
	s32 FanHight;
	s32 FanCircle;
	s32 HeartHand;
	s32 SetHeart;
	s32 MotorOne;
	s32 MotorTwo;
	s32 MotorThree;
	s32 MotorFour;
}MOTORPOSITION;

typedef struct motorspeed
{
	s16 FanHight;
	s16 FanCircle;
	s16 HeartHand;
	s16 SetHeart;
	s16 MotorOne;
	s16 MotorTwo;
	s16 MotorThree;
	s16 MotorFour;
}MOTORSPEED;

typedef struct motorcurrent
{
	float FanHight;
	float FanCircle;
	float HeartHand;
	float SetHeart;
	float ClimbPositive;
	float ClimbNegative;
}MOTORCURRENT;


/*******bezier曲线描述结构体**********/
typedef struct bezierdescribe
{
	POSI P0;			//用户
	POSI P1;			//算出
	POSI P2;			//算出
	POSI P3;			//用户
	float bezier_startangle;		//用户
	float bezier_endangle;			//用户
	float length1;					//用户
	float length2;					//用户
	float x_t3;				//算出
	float x_t2;				//算出
	float x_t1;				//算出
	float x_t0;				//算出
	float y_t3;				//算出
	float y_t2;				//算出
	float y_t1;				//算出
	float y_t0;				//算出
}BEZIER;


typedef struct TypedefPID
{
		float Kp;
		float Ki;
		float Kd; 
		float Esum;
		float E[3];
}PID;

typedef struct Camera
{
		s16   errorcameraline;
		float positionnowy;
}CAMERA;


/* CAN循环队列元素 */ 
typedef struct _Can_Information
{
	u16 StdId;
	u8  DLC;
	u8  Data[8];
	u8  Type;
} Can_Information;


/* CAN待存入发送队列循环队列元素 */ 
typedef struct _Can_Information_NoSend Can_Information_NoSend;
typedef struct _Can_Information_NoSend
{
	u16 StdId;
	u8  DLC;
	u8  Data[8];
	u8  Type;
	Can_Information_NoSend *Next;
} Can_Information_NoSend;

typedef struct __Can_queue
{
   u16 Front;        
   u16 Rear;
   Can_Information CANBUF[CAN_BUF_NUM];
} Can_queue;

//结构体变量声明

extern POSITION PositionNow;
extern POSITION LockPoint;

extern POINTONBEZIER BPoint1;
extern POINTONBEZIER BPoint2;

extern SPEED SpeedNow;
extern SPEED SpeedStart;
extern SPEED SpeedEnd;
extern SPEED SpeedWantSet;
extern SPEED SpeedWantSetOld;
extern SPEED SpeedAbsolute;

extern POSI VectorPosition;
extern POSI VectorError;

extern float DeltaT;

void CalculateWheelSpeedOpposite(SPEED speedwantset,POSITION positionnow);
void CalculateWheelSpeedAbsolute(SPEED speedwantset);

#include "visual_scope.h"

#endif

