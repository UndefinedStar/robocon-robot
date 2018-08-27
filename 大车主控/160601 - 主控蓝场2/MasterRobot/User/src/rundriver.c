#include "rundriver.h"


#define RatSpeedPwm   ((float)(15.9155))	//2.6		//根据轮径和铭朗设置的最高转速进行折算     新铭朗：2.16638

#if (PlacePart==RedPart)
POSITION PositionWheel[4]={{-23.7185,27.7185,5*PI/4},{-23.7185,-27.7185,7*PI/4},{23.7185,-27.7185,PI/4},{23.7185,27.7185,3*PI/4}};
#else
POSITION PositionWheel[4]={{-23.7185,-27.7185,3*PI/4},{-23.7185,27.7185,PI/4},{23.7185,27.7185,-PI/4},{23.7185,-27.7185,-3*PI/4}};
#endif
void SetWheelSpeed(float wheelspeed[4]);




/*
****************************************************
* Name : CalculateWheelSpeed
* Describe : 根据想要达到的相对对速度来设置轮子速度
* Input : speedwantset 想要设置的速度
* Output : None
* Return : None
****************************************************
*/
void CalculateWheelSpeedOpposite(SPEED speedwantset,POSITION positionnow)
{
		float WheelSpeed[4];
	  vu8 i;
		for(i=0;i<4;i++)
		{
				WheelSpeed[i]=(speedwantset.Vx+speedwantset.Vw*PI/180*(-PositionWheel[i].y))*cos(PositionWheel[i].angle)
											+(speedwantset.Vy+speedwantset.Vw*PI/180*(PositionWheel[i].x))*cos(PositionWheel[i].angle-PI/2);
		}
		SetWheelSpeed(WheelSpeed);
}


/*
***************************************************
* Name : CalculateWheelSpeedAbsolute
* Describe : 根据想要达到的绝对速度来设置轮子速度
* Input : speedwantset 想要设置的速度
* Output : None
* Return : None
***************************************************
*/
void CalculateWheelSpeedAbsolute(SPEED speedwantset)
{
		float WheelSpeed[4];

	  
		vu8 i;
	  speedwantset.Vw*=PlacePart;
		for(i=0;i<4;i++)
		{	
				WheelSpeed[i]=(speedwantset.Vx*cos(PositionNow.angle*PI/180)+speedwantset.Vy*sin(PositionNow.angle*PI/180)
											+speedwantset.Vw*PI/180*(-PositionWheel[i].y*PlacePart))*cos(PositionWheel[i].angle)
											+(-speedwantset.Vx*sin(PositionNow.angle*PI/180)+speedwantset.Vy*cos(PositionNow.angle*PI/180)
											+speedwantset.Vw*PI/180*(PositionWheel[i].x*PlacePart))*cos(PositionWheel[i].angle-PI/2);
		}
	SetWheelSpeed(WheelSpeed);
}

/*
***************************************************
* Name : SetWheelSpeed
* Describe : 根据计算得到的轮子的速度来设置PWM波
* Input : wheelspeed[4]  计算得到的轮子的速度
* Output : None
* Return : None
***************************************************
*/
int PWM1,PWM2,PWM3,PWM4;
void SetWheelSpeed(float wheelspeed[4])
{
		int MAX_PWM;
		float temp;
		int temp1;
		PWM1=-wheelspeed[0]*RatSpeedPwm;
		PWM2=-wheelspeed[1]*RatSpeedPwm;
		PWM3=-wheelspeed[2]*RatSpeedPwm;
		PWM4=-wheelspeed[3]*RatSpeedPwm;
	
	  MAX_PWM=fabs(PWM1)>fabs(PWM2)?fabs(PWM1):fabs(PWM2);
		temp1=fabs(PWM3)>fabs(PWM4)?fabs(PWM3):fabs(PWM4);
		MAX_PWM=MAX_PWM>temp1?MAX_PWM:temp1;
	
		if(MAX_PWM>7200)                           //控制占空比在5%-95%之间，限幅
		{
				temp=7200/(float)MAX_PWM;
				PWM1=(int)((PWM1)*temp);
				PWM2=(int)((PWM2)*temp);
				PWM3=(int)((PWM3)*temp);
				PWM4=(int)((PWM4)*temp);
		}
		Elmo_SetSpeed(2,PWM1);
		Elmo_SetSpeed(3,PWM2);
		Elmo_SetSpeed(4,PWM3);
		Elmo_SetSpeed(1,PWM4);
		Elmo_Begin();
}
