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
  float desired;     //�趨ֵ
  float error;        // error
  float prevError;    //�ϴ� error
  float integ;        //������
  float deriv;        //΢����
  float kp;           //P��ϵ��
  float ki;           //I��ϵ��
  float kd;           //D��ϵ��
  float outP;         //
  float outI;         //
  float outD;         //
  float iLimit;      //
} PidObject;
*/
typedef struct
{
  float desired;     //�趨ֵ
  float error;        // error
  float prevError;    //�ϴ� error
  float integ;        //������
  float deriv;        //΢����
	
  float kp_0;           //Pϸ�ֶε�ϵ��
  float ki_0;           //Iϸ�ֶε�ϵ��
  float kd_0;           //Dϸ�ֶε�ϵ��
	
	float kp_1;           //P�ֶַε�ϵ��
  float ki_1;           //I�ֶַε�ϵ��
  float kd_1;           //D�ֶַε�ϵ��
	
  float outP;         //
  float outI;         //
  float outD;         //
  float iLimit;      //
	float Error_Critical; //PID�ֶε�
} PidObject;

extern __IO int16_t   Motor_M1,Motor_M2,Motor_M3,Motor_M4,Motor_M5,Motor_M6,Motor_M7,Motor_M8;//������ bs motor
extern T_int16_xyz 		Acc,Gyr;	//�����ۺϺ�Ĵ��������� ������ main
extern T_float_angle 	Angle;	//ATT�������������̬�� ������ main
extern T_int16_xyz		GYRO_OFFSET,ACC_OFFSET;					
extern T_RC_Data 		  RC_D;	//���յ�ң������ ������ main
extern PidObject           pid_pitch,pid_roll,pid_yaw,PID_ALT,PID_POS; //������ PID
extern PidObject            PID_1,PID_2,PID_3,PID_4,PID_5,PID_6,PID_7,PID_8,PID_9,PID_10,PID_11,PID_12; //������ PID
extern vs32           Alt; //δ֪����
extern MotorObject   Motor;//��ŵ���ĸ�ֵ
extern float 	AngleOffset_Rol,AngleOffset_Pit;
#endif
//extern PidObject            PID_ROL,PID_PIT,PID_YAW,PID_ALT,PID_POS; //������ PID -���ļ�
