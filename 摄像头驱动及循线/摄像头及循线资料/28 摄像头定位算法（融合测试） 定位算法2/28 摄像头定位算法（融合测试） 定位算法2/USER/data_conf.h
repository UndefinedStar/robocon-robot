#ifndef _DATA_CONF_H_
#define _DATA_CONF_H_

#include "stm32f10x.h"
typedef struct{
				float rol;
				float pit;
				float yaw;}T_float_angle;
typedef struct{
				float X;
				float Y;
				float Z;}T_float_xyz;
typedef struct{
				int16_t X;
				int16_t Y;
				int16_t Z;}T_int16_xyz;
typedef struct int16_rcget{
				int16_t ROLL;
				int16_t PITCH;
				int16_t THROTTLE;
				int16_t YAW;
				int16_t AUX1;
				int16_t AUX2;
				int16_t AUX3;
				int16_t AUX4;
				int16_t AUX5;
				int16_t AUX6;}T_RC_Data;
typedef struct{
				u8	ARMED;}T_RC_Control;
typedef struct
{
	uint16_t M1;
	uint16_t M2;
	uint16_t M3;
	uint16_t M4;

	uint16_t M1_R;
	uint16_t M2_R;
	uint16_t M3_R;
	uint16_t M4_R;
}MotorObject;

typedef struct{
		uint16_t Control_Value;
	  uint16_t Control_Value_Verf;
	  uint8_t LeftOrRight;
	  uint8_t LeftDegree;
	  uint8_t RightDegree;
	  uint8_t TakeVerf;
	}Picture_Control;
/*
typedef struct PID{
					float P;
					float I;
					float D;}PID;

typedef struct
{
  float desired;     //设定值
  float error;        // error
  float prevError;    //上次 error
  float integ;        //积分项
  float deriv;        //微分项
  float kp;           //P的系数
  float ki;           //I的系数
  float kd;           //D的系数
  float outP;         //
  float outI;         //
  float outD;         //
  float iLimit;      //
} PidObject;
*/
typedef struct
{
  float desired;     //设定值
  float error;        // error
  float prevError;    //上次 error
  float integ;        //积分项
  float deriv;        //微分项
	
  float kp_0;           //P细分段的系数
  float ki_0;           //I细分段的系数
  float kd_0;           //D细分段的系数
	
	float kp_1;           //P粗分段的系数
  float ki_1;           //I粗分段的系数
  float kd_1;           //D粗分段的系数
	
  float outP;         //
  float outI;         //
  float outD;         //
  float iLimit;      //
	float Error_Critical; //PID分段点
} PidObject;

extern __IO int16_t   Motor_M1,Motor_M2,Motor_M3,Motor_M4,Motor_M5,Motor_M6,Motor_M7,Motor_M8;//定义在 bs motor
extern T_int16_xyz 		Acc,Gyr;	//两次综合后的传感器数据 定义在 main
extern T_float_angle 	Angle;	//ATT函数计算出的姿态角 定义在 main
extern T_int16_xyz		GYRO_OFFSET,ACC_OFFSET;					
extern T_RC_Data 		  RC_D;	//接收的遥控数据 定义在 main
extern PidObject           pid_pitch,pid_roll,pid_yaw,PID_ALT,PID_POS; //定义在 PID
extern PidObject            PID_1,PID_2,PID_3,PID_4,PID_5,PID_6,PID_7,PID_8,PID_9,PID_10,PID_11,PID_12; //定义在 PID
extern vs32           Alt; //未知功能
extern MotorObject   Motor;//存放电机四个值
extern float 	AngleOffset_Rol,AngleOffset_Pit;
#endif
//extern PidObject            PID_ROL,PID_PIT,PID_YAW,PID_ALT,PID_POS; //定义在 PID -旧文件
