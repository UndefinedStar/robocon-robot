#include "pid.h"

float Ek1=0,Ek2=0,Ek3=0;
float P=0.16,I=0,D=0.1;
int PulseDirection=0,PulseCutDown=0,PulseLockPoint = 0;
int stop_angle_flag = 0;
int hd0to1_flag = 0;
float stop_angle = 0;
float Angle=0,kp=0;
s16 stop4_flag = 0;
float message2 = 0;
float BigCarWaitingDistance = 0;
u8  HandFanleafFlag = 0;
int sc_test = 0;
u8 back_flag = 0;
float AngleLast = 0;
u8 time_mid_flag = 0;
int speed_back = 0;
int speed_out = 0;
int XpScTime = 0,XpScFlag = 0;
float translation_angle = 1.3; // 平移角度，用于矫正机械误差
void CameraPid(void)
{
/* 分段调整PID参数，默认值为上坡参数 */
/* 计算角度信息,正右负左*/
Ek1=message;
	
// PD调节
if(sp_flag==1)
{
	P =0.4;
	if(right_angle_flag==1)
		P = 0.5;
}
else if(hd_flag==1)
{
	P = 0.22;
	if(hd_stage_flag==5)
	{
		P=0.45;
		if(speed_now>=7)
		{
			P+=0.05;
		}
	}
	else if(hd_stage_flag<=2)
		P = 0.27; 
}
else if(xp_flag==1)
{
	if(img_stop_flag<=1)
	{
		P = 0.45;
	}
	else if(img_stop_flag==2)
	{
		P=0.5;// 下坡刹车漂移，增大P试一下0.46
	}   
	else if(img_stop_flag>=3)
	{
		P = 0.5;
	}
	if(speed_now>4)
		P+=0.06;
}
	if(hd_flag==1)
		D = 0 ;
	else if(xp_flag==1)
		D = 0.1;
	if(sp_flag == 1)
		D = 0.1;
	if(left_angle_flag == 1 || right_angle_flag == 1)
		D=0;

	// 打角信息计算
	Angle=P*Ek1+I*Ek3+D*(Ek1-Ek3)+translation_angle;

	/* 角度调整 */
	
	// 上坡部分，直角前车体向外侧平移
	if(sp_flag==1&&HuorDistance>ZjClearDistance)
		Angle+=1;
	
	// 河道部分，调整过直线时车体尽可能在两侧岛屿中间
	if(hd_flag==1&&hd_stage_flag>=3)
		Angle-=1.8;//+0.36 

	// 下坡部分，交接车体平移
//	if(img_stop_flag==3)
//		Angle-=0.5;
	
	// 下坡部分
	// 发电区，重启，直接进入下坡最后一个阶段
	if(hand_restart==1)
	{
		img_stop_flag = 6;
		stop_angle = translation_angle;
		stop_time = 0;
		hand_restart = 2;
	}

	// 交接打定角
//	if(img_stop_flag>=6)
//	{
//		if(stop_angle!=0)
//			Angle = stop_angle;    //下坡定角平移//+3
//	}
//	if(img_stop_flag>=4)
//	{	
//		if(stop_angle==0&&fabs(race)<0.14&&whitelost_left==0&&nu>32)
//			stop_angle = 0.8*Angle;
//		if(stop_angle!=0)
//			Angle = stop_angle;
//	}
	// 角度限幅
	if(fabs(Angle)>30)
		Angle = 30*Angle/fabs(Angle);				// 限定打角范围

	Ek3 = Ek2;
	Ek2=Ek1;
	
	// 计算脉冲，脉冲为实际发送值
	PulseDirection=(int)(((double)Angle/90+1.5)*1000);	
	PulseCutDown = 1600;
	PulseLockPoint = 1000;

	/* 刹车策略 */
	
	// 直角部分刹车
	// 直角部分刹车
	if(late_cut_down==1&&zj_sc_count==0)
	{
		if(speed_now<=5)
			zj_sc_count = 2;		// 设定每次刹车的作用时间
		else if(speed_now>5&&speed_now<=7)
			zj_sc_count = 3;
		else
			zj_sc_count = 3;
		//zj_speed = speed_now;
		late_cut_down = 0;
	}
//	if(late_cut_down==2&&zj_sc_count==0)
//	{
//		zj_sc_count=4;
//		late_cut_down = 0;
//	}
	// 直角刹车
	if(zj_sc_count>0)
		PulseCutDown = 2200;
	
	// 河道部分刹车
	// 出河道刹车，防止速度过快掉出河道
	if((speed_now>9&&hd_stage_flag==3)||(img_stop_flag==0&&xp_flag==1&&speed_now>=7)||(hd_flag==1&&hd_stage_flag>=5&&speed_now>=9))  //7
		PulseCutDown = 2200;
	
	// 下坡部分刹车
	if(xp_flag==1&&img_stop_flag==1&&speed_now>=8)
		PulseCutDown = 2200;
	else if(xp_flag==1&&img_stop_flag==2&&speed_now>=9)
		PulseCutDown = 2200;
	else if(xp_flag==1&&img_stop_flag>=3&&speed_now>=5)
		PulseCutDown = 2200;
	if(img_cross_flag==2&&speed_now>=3)
		PulseCutDown = 2200;
	if(xp_flag==1&&img_stop_flag>=3)
		PulseLockPoint = 440;

	// 重启刹车
	if(hand_restart==2)
	{
		PulseLockPoint = 440;
	}
	
//	// 交接之后防止小车被吹出风力发电区刹车
//	if(DirectionFlag==1&&img_stop_flag>=4&&speed_back==0&&HandFanleafFlag==1)
//		speed_back = HuorDistance;
//	if(HuorDistance-speed_back>6&&speed_back>0&&speed_now>=1&&back_flag==0&&DirectionFlag==1)
//		back_flag = 1;
//	if(back_flag==1)
//		PulseCutDown = 2200;

	
	// 发送信息
	SendPulse(PulseCutDown,PulseDirection);
	SendPulseBeep(beep_count,PulseLockPoint);
}
