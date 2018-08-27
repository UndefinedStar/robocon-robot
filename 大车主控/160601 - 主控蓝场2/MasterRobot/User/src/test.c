#include "test.h"

ROBOTARM	RobotArm = {0};		//��е�۵���Ϣ
POSITION	DTPosition = {0};	//DT50 ��λ��
u8 arm_flag = 1;

/***********************************************************************
******************************* ֱ���ܷ� *******************************
***********************************************************************/
void RunPoint_test(
									float 				Vstart,					//��ʼ�ٶ�
									float 				Vwant,					//������Ҫ�ﵽ���ٶ�
									float 				Xwant,					//��Ҫ�ﵽ�� X ����
									float 				Ywant,					//��Ҫ�ﵽ�� Y ����
									float 				Anglewant,			//��Ҫ�ﵽ�ĽǶ�
									float 				updis)					//���پ���
{
		YGoal							= Ywant;
    CurrentV 					= VStart;                  //���ٶȸ���ֵ
    SpeedWantSet.Vw 	= 0.0;
    Flag[KeepRun] 		= 1;
    LockPoint.angle  	= Anglewant;  //������̬�ǲ���
		
    Flag[LockPointOn] = 0;              //�ر�λ������
    FREE_ALL_MOTOR;
    Flag[AutoRun] = 0;                  //��PID����
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
	* Describe : ��е����ת
	* Input  	 :
			speed    : ��ת�ٶ�
			angle	 ����Ҫ�ﵽ�ĽǶ�
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
	
	angle *= (float)105.51;	//���ռ��ٱȺ͹�դ����
	if(angle <= (float)-9500)
		angle = (float)-9500;
	else if(angle >= 19000)
		angle = 19000;
	
//	MotorPosition(ArmRotate, speed, angle);
}

/***********************************************
	* Name 	 	 : robot_arm_rotate_limit
	* Describe : ��е����ת����
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

/********** ���������ĳ��� **********/
float CountCoord(COORD *vector)
{
	float distance_count = 0;
	distance_count = sqrt((vector->x)*(vector->x) + (vector->y)*(vector->y));
	return distance_count;
}

/********** ���������ķ��� **********/
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
