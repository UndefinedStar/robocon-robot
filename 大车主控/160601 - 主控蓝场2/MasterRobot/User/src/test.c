#include "test.h"

ROBOTARM	RobotArm = {0};		//机械臂的信息
POSITION	DTPosition = {0};	//DT50 的位置
u8 arm_flag = 1;

/***********************************************************************
******************************* 直线跑法 *******************************
***********************************************************************/
void RunPoint_test(
									float 				Vstart,					//起始速度
									float 				Vwant,					//行走想要达到的速度
									float 				Xwant,					//想要达到的 X 坐标
									float 				Ywant,					//想要达到的 Y 坐标
									float 				Anglewant,			//想要达到的角度
									float 				updis)					//加速距离
{
		YGoal							= Ywant;
    CurrentV 					= VStart;                  //把速度赋初值
    SpeedWantSet.Vw 	= 0.0;
    Flag[KeepRun] 		= 1;
    LockPoint.angle  	= Anglewant;  //保持姿态角不变
		
    Flag[LockPointOn] = 0;              //关闭位置锁定
    FREE_ALL_MOTOR;
    Flag[AutoRun] = 0;                  //打开PID调节
    while(PositionNow.x < updis)
    {
				if(PositionNow.x > 50 && PositionNow.x < 80)
				{
						StartFan(900);
				}
				CurrentV = Vstart;
				PidLockAngle(Anglewant);
				PidLockY(YGoal);
				CalculateWheelSpeedAbsolute(SpeedWantSet);
				OSTimeDly(50);
    }
    while(PositionNow.x < Xwant)
    {
				CurrentV = Vwant;
				PidLockAngle(Anglewant);
				PidLockY(YGoal);
				CalculateWheelSpeedAbsolute(SpeedWantSet);
				OSTimeDly(50);
    }
		BREAK_All_MOTOR;
		LockPoint.x 		= PositionNow.x;
		LockPoint.y 		= PositionNow.y;
		LockPoint.angle = PositionNow.angle;
}

/***********************************************
	* Name 	 	 : robot_arm_rotate
	* Describe : 机械臂旋转
	* Input  	 :
			speed    : 旋转速度
			angle	 ：想要达到的角度
	* Output 	 : None
	* Return 	 : None
***********************************************/
void robot_arm_rotate(s16 speed, float angle)
{
//	robot_arm_rotate_limit();
	if(angle <= -45)
		angle = -45;
	else if(angle >= 225)
		angle = 225;
	
	angle *= (float)105.51;	//按照减速比和光栅计算
	if(angle <= (float)-9500)
		angle = (float)-9500;
	else if(angle >= 19000)
		angle = 19000;
	
//	MotorPosition(ArmRotate, speed, angle);
}

/***********************************************
	* Name 	 	 : robot_arm_rotate_limit
	* Describe : 机械臂旋转限制
	* Input  	 : None
	* Output 	 : None
	* Return 	 : None
***********************************************/
void robot_arm_rotate_limit(void)
{
	float angle;
	float temp,temp_cos,temp_sin;
	float x1,y1,x2,y2;
	COORD Line = {0};

	angle = PositionNow.angle * (float)(0.017453292);
	DTPosition.x = PositionNow.x + 52.8*cos(angle);
	DTPosition.y = PositionNow.y + 52.8*sin(angle);
	if(DTPosition.y < 700)
	{
		x1 = 275;
		y1 = 695;
		x2 = 120;
		y2 = 725;
	}
	else if(DTPosition.y < 750)
	{
		x1 = 275;
		y1 = 695;
		x2 = 330;
		y2 = 800;
	}
	else if(DTPosition.y < 900)
	{
		x1 = 275;
		y1 = 695;
		x2 = 510;
		y2 = 810;
	}
//	Line.x = x1 - DTPosition.x;
//	Line.y = y1 - DTPosition.y;
	RobotArm.angle_min = PositionNow.angle+CountDirect(x1, y1)-90;
//	Line.x = x2 - DTPosition.x;
//	Line.y = y2 - DTPosition.y;
	RobotArm.angle_max = PositionNow.angle+CountDirect(x2, y2)-90;

	if(RobotArm.angle_min <= -90)
		RobotArm.angle_min = -90;
	if(RobotArm.angle_max >= 180)
		RobotArm.angle_max = 180;
}

/********** 计算向量的长度 **********/
float CountCoord(COORD *vector)
{
	float distance_count = 0;
	distance_count = sqrt((vector->x)*(vector->x) + (vector->y)*(vector->y));
	return distance_count;
}

/********** 计算向量的方向 **********/
float CountDirect(float x, float y)
{
	float angle;
	float temp,temp_cos,temp_sin;
	COORD  vector = {0};
	
	angle = PositionNow.angle * (0.017453292);
	DTPosition.x = PositionNow.x + 52.8*cos(angle);
	DTPosition.y = PositionNow.y + 52.8*sin(angle);
	vector.x = x - DTPosition.x;
	vector.y = y - DTPosition.y;
	
	temp					= CountCoord(&vector);
	temp_cos 			= vector.x/temp;
	temp_sin 			= vector.y/temp;
	
	if(temp_sin  >= 0)
		angle 			=  acos(temp_cos)*57.2957795;
	else
		angle 			=  360 - acos(temp_cos)*57.2957795;
	
	return angle;
}
