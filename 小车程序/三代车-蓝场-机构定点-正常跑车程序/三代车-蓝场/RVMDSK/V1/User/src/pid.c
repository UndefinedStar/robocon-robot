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
float translation_angle = 1.3; // ƽ�ƽǶȣ����ڽ�����е���
void CameraPid(void)
{
/* �ֶε���PID������Ĭ��ֵΪ���²��� */
/* ����Ƕ���Ϣ,���Ҹ���*/
Ek1=message;
	
// PD����
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
		P=0.5;// ����ɲ��Ư�ƣ�����P��һ��0.46
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

	// �����Ϣ����
	Angle=P*Ek1+I*Ek3+D*(Ek1-Ek3)+translation_angle;

	/* �Ƕȵ��� */
	
	// ���²��֣�ֱ��ǰ���������ƽ��
	if(sp_flag==1&&HuorDistance>ZjClearDistance)
		Angle+=1;
	
	// �ӵ����֣�������ֱ��ʱ���御���������ൺ���м�
	if(hd_flag==1&&hd_stage_flag>=3)
		Angle-=1.8;//+0.36 

	// ���²��֣����ӳ���ƽ��
//	if(img_stop_flag==3)
//		Angle-=0.5;
	
	// ���²���
	// ��������������ֱ�ӽ����������һ���׶�
	if(hand_restart==1)
	{
		img_stop_flag = 6;
		stop_angle = translation_angle;
		stop_time = 0;
		hand_restart = 2;
	}

	// ���Ӵ򶨽�
//	if(img_stop_flag>=6)
//	{
//		if(stop_angle!=0)
//			Angle = stop_angle;    //���¶���ƽ��//+3
//	}
//	if(img_stop_flag>=4)
//	{	
//		if(stop_angle==0&&fabs(race)<0.14&&whitelost_left==0&&nu>32)
//			stop_angle = 0.8*Angle;
//		if(stop_angle!=0)
//			Angle = stop_angle;
//	}
	// �Ƕ��޷�
	if(fabs(Angle)>30)
		Angle = 30*Angle/fabs(Angle);				// �޶���Ƿ�Χ

	Ek3 = Ek2;
	Ek2=Ek1;
	
	// �������壬����Ϊʵ�ʷ���ֵ
	PulseDirection=(int)(((double)Angle/90+1.5)*1000);	
	PulseCutDown = 1600;
	PulseLockPoint = 1000;

	/* ɲ������ */
	
	// ֱ�ǲ���ɲ��
	// ֱ�ǲ���ɲ��
	if(late_cut_down==1&&zj_sc_count==0)
	{
		if(speed_now<=5)
			zj_sc_count = 2;		// �趨ÿ��ɲ��������ʱ��
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
	// ֱ��ɲ��
	if(zj_sc_count>0)
		PulseCutDown = 2200;
	
	// �ӵ�����ɲ��
	// ���ӵ�ɲ������ֹ�ٶȹ�������ӵ�
	if((speed_now>9&&hd_stage_flag==3)||(img_stop_flag==0&&xp_flag==1&&speed_now>=7)||(hd_flag==1&&hd_stage_flag>=5&&speed_now>=9))  //7
		PulseCutDown = 2200;
	
	// ���²���ɲ��
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

	// ����ɲ��
	if(hand_restart==2)
	{
		PulseLockPoint = 440;
	}
	
//	// ����֮���ֹС������������������ɲ��
//	if(DirectionFlag==1&&img_stop_flag>=4&&speed_back==0&&HandFanleafFlag==1)
//		speed_back = HuorDistance;
//	if(HuorDistance-speed_back>6&&speed_back>0&&speed_now>=1&&back_flag==0&&DirectionFlag==1)
//		back_flag = 1;
//	if(back_flag==1)
//		PulseCutDown = 2200;

	
	// ������Ϣ
	SendPulse(PulseCutDown,PulseDirection);
	SendPulseBeep(beep_count,PulseLockPoint);
}
