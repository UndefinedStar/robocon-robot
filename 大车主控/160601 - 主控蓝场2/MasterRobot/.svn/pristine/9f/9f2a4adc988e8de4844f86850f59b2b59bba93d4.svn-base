#include "MyMath.h"

POSITION DTPosition = {0};
POSITION CarPosition = {0};
POSITION CarPositionLsat = {0};
float ArmAngle = 0;
SPEED CarSpeeds = {0};
SPEED CarSpeedsLast = {0};
float time = 0,time_last = 0;
float DT50distance = 0;
float CameraRotate = 0;
u8 posi_flag = 0;
u8 speed_flag = 0;
/*
 * 函数名: fsign
 * 描  述: 取出浮点数的符号位
 * 输  入: 浮点数a
 * 输  出: int型的符号
 * 调  用: 外部调用
 */
int fsign(float a)
{
	if(a>0)
		return 1;
	else if(a<0)
		return -1;
	else return 0;
}


void car_position(void)
{
	float angle;
	float time_det;
	
	time = (float)OSTimeGet()/10000;
	time_det = time - time_last;
	time_last = time;
	
	if(posi_flag)
	{
		angle = PositionNow.angle*PI/180;
		DTPosition.x = PositionNow.x + 52.8*cos(angle);
		DTPosition.y = PositionNow.y - 52.8*sin(angle);
		DTPosition.angle = PositionNow.angle + ArmAngle;

		angle = DTPosition.angle*PI/180;
		DT50distance = second_order_filter2(&second_order_flt_DT50, CameraDistance0);
		CameraRotate = second_order_filter2(&second_order_flt_Rotate, ErrorCameraWidth1);
		CarPosition.x = second_order_filter2(&second_order_flt_X, DTPosition.x + DT50distance*sin(angle) - CameraRotate);
		CarPosition.y = second_order_filter2(&second_order_flt_Y, DTPosition.y + DT50distance*cos(angle));
		
		if(CarPositionLsat.x)
		{
			if(speed_flag)
			{
				CarSpeeds.Vx = second_order_filter2(&second_order_flt_Vx, (CarPosition.x - CarPositionLsat.x)/time_det);
				CarSpeeds.Vy = second_order_filter2(&second_order_flt_Vy, (CarPosition.y - CarPositionLsat.y)/time_det);
			}
			else
			{
				CarSpeeds.Vx = (CarPosition.x - CarPositionLsat.x)/time_det;
				CarSpeeds.Vy = (CarPosition.y - CarPositionLsat.y)/time_det;
				speed_flag = 1;
			}
		}
	}
//	else
//	{
//		CarPosition.x += CarSpeeds.Vx*time_det;
//		CarPosition.y += CarSpeeds.Vy*time_det;
//	}
	if(ErrorCameraHeight1 < 8 && ErrorCameraHeight1 > -13 && ErrorCameraWidth1 < 15 && ErrorCameraWidth1 > -25)
		posi_flag = 1;
	CarPositionLsat.x = CarPosition.x;
	CarPositionLsat.y = CarPosition.y;
}
