#include "PID.h"

/*存flash参数*/

//直线PID参数
float PKp =3.5;   
float PTi =0.01;
float PTd =0;  

//Bezier曲线PID参数组3分段
float BKp3f = 17;
float BTi3f = 6.5;
float BTd3f = 0;


//涵道风扇旋转电机PID
float Pcircle=10;  //2
float Icircle=0;  //4
float Dcircle=0;



//涵道风扇旋转电机分段PID
float Pcircle1=5;
float Icircle1=0; 
float Dcircle1=0;

float Ecw1=0;
float Ecw2=0;
float Ecw3=0;
float EcwOld=0;

//机械臂PID
float Pheight=0;
float Iheight=350;    //原来为200
float Dheight=0;

float Ech1=0;
float Ech2=0;
float Ech3=0;

//锁点PID参数第一组
float KpX1=4;//原：8
float KdX1=0;//原：0.2
float KpY1=4;//原：8
float KdY1=0;//原：0.2

//锁点PID参数第二组
float KpX2=4.5;//原：3.0
float KdX2=0.005;//原：0.1
float KpY2=4.5;//原：3.0
float KdY2=0.005;//原：0.1

//锁点PID参数第三组
float KpX3=4.5;
float KdX3=0.05;
float KpY3=5;
float KdY3=0.05;

float KpAngle=3.5;     //4.5
float KiAngle=0.015;
float KdAngle=0.0;
float AngleSum=0;


float EkX=0.0,EkY=0.0,EkAngle=0.0;			//this time
float EkX1=0.0,EkY1=0.0,EkAngle1=0.0;		//last time
float EkX2=0.0,EkY2=0.0,EkAngle2=0.0;

float Ek0,Ek1,Ek2;

//巡线PID参数
float CKp = 3.0;      //3.5   
float CTi = 0.00;     //0.12
float CTd = 0.0;  

//PID参数组号,不同的Bezier轨迹使用不同组的PID参数,具体可见PID_Init函数
unsigned char BezierPIDGroup;
//Bezier曲线PID参数组1
float BKp1 = 3.5;
float BTi1 = 0.15;
float BTd1 = 0.01;

//Bezier曲线PID参数组2
float BKp2 = 2.0;
float BTi2 = 0.025;
float BTd2 = 0.0;

//Bezier曲线PID参数组3
float BKp3 = 4.0;
float BTi3 = 0.15;
float BTd3 = 0.0;


float P=0.0;
float I=0.0;
float D=0.0;

float VExSum=0.0;

float Eks1=0,Eks2=0,Eks3=0;

s16 FanSpeed=0;



MOTORPOSITION MotorPositionSet={270000,0};
MOTORPOSITION MotorPositionSetOld={270000,0};
MOTORPOSITION MotorSpeedSet={0};
MOTORPOSITION MotorSpeedSetOld={0};


void PidLockPoint(POSITION* LockPosition);
void PidPoint(void);
void PidBezier(void);
void PidLockAngle(float lockangle);

void PidInit(void)
{
	Ek0 = 0.0;
	Ek1 = 0.0;
	Ek2 = 0.0;
	switch(AutoRunType)
	{
		case runcamera:
			P =CKp;
			I =CTi;
			D =CTd;
			KpAngle=6;
			KiAngle=0.02;
			KdAngle=0;
	  	AngleSum=0;	
			break;
		case runpoint:		
			P =PKp;
			I =PTi;
			D =PTd;
			break;
		case runbezier:
			if (BezierPIDGroup == BPidGROUP1)
			{
				P =BKp1;
				I =BTi1;
				D =BTd1;
			}
			else if (BezierPIDGroup == BPidGROUP2)
			{
				P =BKp2;
				I =BTi2;
				D =BTd2;
				KpAngle=2.7;
				KiAngle=0.025;
				KdAngle=0.01;
			}
			else
			{
				P =BKp3;
				I =BTi3;
				D =BTd3;		
				KpAngle=5;
				KiAngle=0.01;
				KdAngle=0.0;
				AngleSum=0;				
			}
			break;
		
		default:
			break;
	}
	VExSum=0.0; //上次的调节量在PID初始化时清零
}

void Pid(void)//所有的PID调节
{
	//轨迹PID，只有在自动模式下有效
	if(Flag[AutoRun])			//AutoRunFlag有效
	{
		switch(AutoRunType)	//根据行走类型选择PID
		{
			case runpoint:
				PidPoint();	//直线PID
				break;
			case runbezier:
				PidBezier();//bezier曲线PID
				break;
			case runcamera:
				PidCamera();//巡线PID
			default:
				break;
		}
	}
	//锁点PID
	if(Flag[LockPointOn])
	{
		PidLockPoint(&LockPoint);
	}
	
	if(Flag[LockAngle])
		PidLockAngle(LockPoint.angle);
	if(Flag[LockY])
		PidLockY(LockPoint.y);
}



void PidLockPoint(POSITION* LockPosition)
{
	float temp;
	EkX=LockPosition->x-PositionNow.x;
	EkY=LockPosition->y-PositionNow.y;
	EkAngle=LockPosition->angle-PositionNow.angle;
	//PD调节
	if(EkX>(float)(-1)&&EkX<(float)(1))  EkX=0;
	if(EkY>(float)(-1)&&EkY<(float)(1))  EkY=0;
	if(EkAngle>-0.2f&&EkAngle<0.2f)			 EkAngle=0;

	if((EkX==0)&&(EkY==0)&&(EkAngle==0))
	{
		BREAK_All_MOTOR;				//BREAK有效，避免慢速变化引起陀螺仪飘移
	}
	else
	{
		FREE_ALL_MOTOR;
	}
	if(fabs(EkX)<=5)
		SpeedWantSet.Vx=KpX3 * EkX+KdX3*(EkX-EkX1);//X方向第三组参数位置PD控制
	else if(fabs(EkX)<=20)
		SpeedWantSet.Vx=KpX2 * EkX+KdX2*(EkX-EkX1);//X方向第二组参数位置PD控制
	else
		SpeedWantSet.Vx=KpX1 * EkX+KdX1*(EkX-EkX1);//X方向第一组参数位置PD控制
	
	if(fabs(EkY)<=5)
		SpeedWantSet.Vy=KpY3 * EkY+KdY3*(EkY-EkY1);//Y方向第三组参数位置PD控制
	else if(fabs(EkY)<=20)
		SpeedWantSet.Vy=KpY2 * EkY+KdY2*(EkY-EkY1);//Y方向第二组参数位置PD控制
	else
		SpeedWantSet.Vy=KpY1 * EkY+KdY1*(EkY-EkY1);//Y方向第一组参数位置PD控制
	
	SpeedWantSet.Vw=KpAngle * EkAngle+KdAngle*(EkAngle-EkAngle1);
	
	EkX1=EkX;
	EkY1=EkY;
	EkAngle1=EkAngle;
	//限定速度
	temp=sqrt(SpeedWantSet.Vx * SpeedWantSet.Vx + SpeedWantSet.Vy * SpeedWantSet.Vy);
	if(temp>Vmax)
	{
		SpeedWantSet.Vx= SpeedWantSet.Vx*Vmax/temp;
		SpeedWantSet.Vy= SpeedWantSet.Vy*Vmax/temp;
	}
	//限定角速度
	temp=fabs(SpeedWantSet.Vw);
	if(temp>50)
		SpeedWantSet.Vw=SpeedWantSet.Vw*50/temp;
	CalculateWheelSpeedAbsolute(SpeedWantSet);
	temp=sqrt(SpeedAbsolute.Vx*SpeedAbsolute.Vx+SpeedAbsolute.Vy*SpeedAbsolute.Vy);
//	VS4Channal_Send(PositionNow.x,0,SpeedWantSet.Vx,SpeedWantSet.Vy);
}
float CurrentVOld[2];
void PidPoint(void)
{
	float temp;
	if(Flag[SpeedUp] && !Flag[SpeedChange])					//如果加速标志有效，调用加速程序
	{
		RunPointSpeedUp();
	}
	if(Flag[SpeedUp]==0 && Flag[SpeedUpVar]==1)
		CurrentV=VWant;
	else if(Flag[SpeedUp]==0 && Flag[SpeedUpVar]==0)
		CurrentV=VStart;
	if(Flag[SpeedDown] && !Flag[SpeedChange])				//如果减速标志有效，调用减速程序
	{
		RunPointSpeedDown();
	}
	if(Flag[Turn])						//如果旋转标志有效，调用旋转程序
	{
		TurnAngle();
	}
  if(Flag[SpeedChange]==1 && CameraDistanceValue>100)
	{
		SpeedChangeByCamera(CurrentVOld[0],CurrentVOld[1]);
		Flagu16[RiverTime]++;
	}
	if(Flag[FanSpeedChangeByDT50])
	{
		SpeedChangeByMotorAngle();
	}
	
	CurrentVOld[0]=CurrentV;
	CurrentVOld[1]=CurrentVOld[0];
	
	SetPointCurrentVBase();//设置位置PID调节前Vx和Vy基速度
	PidLockAngle(LockPoint.angle);			//对姿态角进行PID

	if(PidLineType==1)		//斜率小于1
	{
		Ek0 = LineK * PositionNow.x + LineB - PositionNow.y;		//计算机器人在Y方向的偏差
	}
	else
	{
		if(Flag[NoLineK])								//斜率近似不存在
		{
			Ek0 = XGoal- PositionNow.x;			//计算X方向偏差
		}
		else												//斜率大于1
		{
			Ek0 = PositionNow.y / LineK + LineB - PositionNow.x;	//计算x方向偏差
		}
	}

	if(fabs(Ek0) >20)			//如果偏差大于10cm,取消积分作用
	{
		VExSum += P*(Ek0-Ek1)+D*(Ek0-2*Ek1+Ek2);
	}
	else						//偏差小于10cm
	{
		VExSum += P*(Ek0-Ek1)+I*Ek0+D*(Ek0-2*Ek1+Ek2);
	}
	
	if(fabs(VExSum)<0.1)            //取消了调节速度的上线，改为限制最后设置速度的上线
	{
		VExSum = 0;
	}

	Ek2 = Ek1;
	Ek1 = Ek0;

	if(PidLineType==1)
	{
		SpeedWantSet.Vy+=VExSum;
	}
	else
	{
		SpeedWantSet.Vx+=VExSum;
	}

	temp=sqrt(SpeedWantSet.Vx*SpeedWantSet.Vx+SpeedWantSet.Vy*SpeedWantSet.Vy);
	if(temp>Vmax)
	{
		SpeedWantSet.Vx=Vmax*SpeedWantSet.Vx/temp;
		SpeedWantSet.Vy=Vmax*SpeedWantSet.Vy/temp;
	}
	CalculateWheelSpeedAbsolute(SpeedWantSet);
	temp=sqrt(SpeedAbsolute.Vx*SpeedAbsolute.Vx+SpeedAbsolute.Vy*SpeedAbsolute.Vy);
  DT50_VS4Channal_Send(CurrentV,Ek0,VExSum,temp);
}

//PID算法:增量式PID&变速积分&抗积分饱和 待完成
void PidBezier(void)
{
	float temp1,temp2,temp;
	/***************************************/
	Vec_Error.x = PositionNow.x - BPoint1.x;		//计算误差向量
	Vec_Error.y = PositionNow.y - BPoint1.y;
	//更新向量的端点对应的t值
	BPoint1.t+=(CountTwoVector(&Vec_Error,&Vec_Line)/(Vec_Line.x*Vec_Line.x+Vec_Line.y*Vec_Line.y))*DeltaT;
	if(BPoint1.t<0)BPoint1.t=0;											//范围限定
	if(BPoint1.t>1-DeltaT)BPoint1.t=1-DeltaT;			//范围限定
	BPoint2.t = BPoint1.t+DeltaT;
	//更新坐标
	CountBezierXYbyT(&GlobalBezier,&BPoint1);
	CountBezierXYbyT(&GlobalBezier,&BPoint2);
	//更新曲线向量和误差向量
	Vec_Error.x = PositionNow.x - BPoint1.x;		//重新计算误差向量
	Vec_Error.y = PositionNow.y - BPoint1.y;
	Vec_Line.x = BPoint2.x - BPoint1.x;	//重新计算误差向量
	Vec_Line.y = BPoint2.y - BPoint1.y;
	//将Vec_Line和Vec_Error同时旋转到Vec_Line指向X轴正方向,计算此时的Vec_Error的y值即为法向偏差
	temp1 = Vec_Line.x/sqrt(Vec_Line.x*Vec_Line.x+Vec_Line.y*Vec_Line.y);
	temp2 = Vec_Line.y/sqrt(Vec_Line.x*Vec_Line.x+Vec_Line.y*Vec_Line.y);
	Ek0 = -(Vec_Error.y*temp1-Vec_Error.x*temp2);

	//PID运算获取新的法向速度
	if(BezierPIDGroup==BPidGROUP3)
	{
		//if(BPoint1.t<0.75f)
			VExSum += P*(Ek0-Ek1)+I*Ek0+D*(Ek0-2*Ek1+Ek2);
//		else
//			VExSum += BKp3f*(Ek0-Ek1)+BTi3f*Ek0+BTd3f*(Ek0-2*Ek1+Ek2);
	}
	else
	{
		if(fabs(Ek0) >30)			//如果偏差大于6cm,去除积分作用,积分分离阀值
		{
			VExSum += P*(Ek0-Ek1)+D*(Ek0-2*Ek1+Ek2);
		}
		else						//偏差小于10cm,加上积分作用
		{
			VExSum += P*(Ek0-Ek1)+I*Ek0+D*(Ek0-2*Ek1+Ek2);
		}
  }
	if(fabs(VExSum)>(300))		//输出限幅,调节速度限制在300cm/s
	{
		VExSum = (300)* VExSum/fabs(VExSum);
	}
	if(fabs(VExSum)<0.1)		//输出死区
	{
		VExSum = 0;
	}

		Ek2 = Ek1;
		Ek1 = Ek0;

	/****************************************/
	if(Flag[SpeedUp] && !Flag[SpeedChange])					//如果加速标志有效，调用加速程序
	{
		RunBezierSpeedUp();		
	}
	if(Flag[SpeedUp]==0 && Flag[SpeedUpVar]==1  && !Flag[SpeedChange])
		CurrentV=VWant;
	else if(Flag[SpeedUp]==0 && Flag[SpeedUpVar]==0  && !Flag[SpeedChange])
		CurrentV=VStart;
	if(Flag[SpeedDown] && !Flag[SpeedChange])				//如果减速标志有效，调用加速程序
	{
		RunBezierSpeedDown();
	}
	if(Flag[Turn])
	{
		Bezier_TurnAngle();
	}
	
	if(Flag[SpeedChange]==1)
	{
		SpeedChangeByCamera(CurrentVOld[0],CurrentVOld[1]);
		Flagu16[RiverTime]++;
	}
	if(Flag[FanSpeedChangeByDT50] && PositionNow.y<670)
	{
		SpeedChangeByMotorAngle();
	}
	if(CurrentV>Vmax)
		CurrentV=Vmax;
	CurrentVOld[0]=CurrentV;
	CurrentVOld[1]=CurrentVOld[0];

	VExSum=VExSum*CurrentV/sqrt(CurrentV*CurrentV+VExSum*VExSum);
	CurrentV=CurrentV*CurrentV/sqrt(CurrentV*CurrentV+VExSum*VExSum);
	
	SpeedWantSet.Vx = CurrentV*temp1;
	SpeedWantSet.Vy = CurrentV*temp2;
	PidLockAngle(LockPoint.angle);			//对姿态角进行PID

	//切向速度与法向速度融合
	SpeedWantSet.Vx=SpeedWantSet.Vx-VExSum*temp2;
	SpeedWantSet.Vy=SpeedWantSet.Vy+VExSum*temp1;

	temp = sqrt(SpeedWantSet.Vx*SpeedWantSet.Vx+SpeedWantSet.Vy*SpeedWantSet.Vy);

	
	
	temp = sqrt(SpeedAbsolute.Vx*SpeedAbsolute.Vx+SpeedAbsolute.Vy*SpeedAbsolute.Vy);

	if(BezierPIDGroup==BPidGROUP3)
	{
		Can2_VS4Channal_Send(BPoint1.t*100,PositionNow.y,SpeedWantSet.Vy,SpeedAbsolute.Vy);
		Can_VS4Channal_Send(PositionNow.x,SpeedWantSet.Vx,SpeedAbsolute.Vx,BPoint1.t*100);
		if(BPoint1.t>0.85f && fabs(SpeedWantSet.Vx)>150)
			SpeedWantSet.Vx=150;
			
	}
  DT50_VS4Channal_Send(CurrentV,Ek0,VExSum,temp);
	CalculateWheelSpeedAbsolute(SpeedWantSet);
}



//#define ZSL
#ifdef ZSL
void PidCamera(void)
{
	float temp;
  Ek0 = ErrorCameraLine;
	ErrorCameraLine=-100;
	if(Flag[StartLockY]==0)
	{
		LockPoint.y = 1335;
		Flag[StartLockY] = 1;
	}
	
	if(Ek0 == 0 && PositionNow.y > 1300)
	{
		LockPoint.y = PositionNow.y;
		Flag[StartLockY]=1;
	}
	else if(PositionNow.y > 1300 && fabs(Ek0) < 20)
	{
		LockPoint.y = PositionNow.y - (float)Ek0*(float)0.705128;
	}
	
	PidLockAngle(LockPoint.angle);
	PidLockY(LockPoint.y);
}
#else
void PidCamera(void)
{
	float temp;
  Ek0=ErrorCameraLine;
	ErrorCameraLine=-100;
	if(Flag[StartLockY]==0)
	{
			if(fabs(Ek0+100)<0.01)
	    {
					Flag[LineCameraLost]++;
					PidLockAngle(LockPoint.angle);			//对姿态角进行PID
					CalculateWheelSpeedAbsolute(SpeedWantSet);
//					VS4Channal_Send(Ek0*10,LockPoint.y,1000,PositionNow.y);
        	DT50_VS4Channal_Send((LockPoint.y-PositionNow.y),VExSum,SpeedWantSet.Vy,SpeedAbsolute.Vy);
        	Can2_VS4Channal_Send(CurrentV,PositionNow.y,PositionNow.angle,SpeedAbsolute.Vy);
        	Can_VS4Channal_Send(PositionNow.x,SpeedAbsolute.Vx,0,SpeedWantSet.Vx);
				
					if(Flag[LineCameraLost]>5)
					{
						Flag[LockPointOn]=0;
						BREAK_All_MOTOR;
						OSTaskSuspend(15);			
						OSTaskSuspend(OS_PRIO_SELF);
					}
					return;
	    }
			else
				  Flag[LineCameraLost]=0;
			
    	if(fabs(fabs(Ek0)-30)<0.01)
    	{
		     PidLockAngle(LockPoint.angle);			//对姿态角进行PID
		     if(Flag[SearchLineLockY]==0)
				 {
			      PidLockY(LockPoint.y);
//					 VExSum=0;
					 return;
				 }
		     else if(Flag[SearchLineLockY]==1 && PositionNow.x<500)
					{
						SpeedWantSet.Vy=VExSum;
						SpeedWantSet.Vx=CurrentV;
						CameraLineSpeedPid();
					}

//					VS4Channal_Send(Ek0*10,LockPoint.y,2000,PositionNow.y);
	        DT50_VS4Channal_Send((LockPoint.y-PositionNow.y),VExSum,SpeedWantSet.Vy,SpeedAbsolute.Vy);
	        Can2_VS4Channal_Send(CurrentV,PositionNow.y,PositionNow.angle,SpeedAbsolute.Vy);
					Can_VS4Channal_Send(PositionNow.x,SpeedAbsolute.Vx,0,SpeedWantSet.Vx);
//					Can_VS4Channal_Send(PositionNow.x, PositionNow.y,LockPoint.y,Flag[RedRayLow]);
		   return;
	    }
			PidLockAngle(LockPoint.angle);
			Flag[SearchLineLockY]=1;
			VExSum = VExSum + P*(Ek0-Ek1)+I*Ek0+D*(Ek0-2*Ek1+Ek2);
			
			if(fabs(VExSum)<0.1)            //取消了调节速度的上线，改为限制最后设置速度的上线
			{
				VExSum = 0;
			}
			
			
			if(fabs(VExSum)>200)            //取消了调节速度的上线，改为限制最后设置速度的上线
			{
				VExSum = 200*VExSum/fabs(VExSum);
			}
			
			Ek2 = Ek1;
			Ek1 = Ek0;

			SpeedWantSet.Vy=VExSum;
			SpeedWantSet.Vx=CurrentV;
			temp=sqrt(SpeedWantSet.Vx*SpeedWantSet.Vx+SpeedWantSet.Vy*SpeedWantSet.Vy);
			if(temp>Vmax)
			{
				SpeedWantSet.Vx=Vmax*SpeedWantSet.Vx/temp;
				SpeedWantSet.Vy=Vmax*SpeedWantSet.Vy/temp;
			}
			CameraLineSpeedPid();
//			VS4Channal_Send(PositionNow.x,PositionNow.y,Ek0*10,LockPoint.y);
//			VS4Channal_Send(LockPoint.x, LockPoint.y, PositionNow.x, PositionNow.y);
//			VS4Channal_Send(Ek0*10,LockPoint.y,3000,PositionNow.y);
			DT50_VS4Channal_Send((LockPoint.y-PositionNow.y),VExSum,SpeedWantSet.Vy,SpeedAbsolute.Vy);
			Can2_VS4Channal_Send(CurrentV,PositionNow.y,PositionNow.angle,SpeedAbsolute.Vy);
			Can_VS4Channal_Send(PositionNow.x,SpeedAbsolute.Vx,0,SpeedWantSet.Vx);
//			Can_VS4Channal_Send(PositionNow.x, PositionNow.y,LockPoint.y,Flag[RedRayLow]);
	}
	else
	{
		if(fabs(Ek0+100)<0.01)
	  {
			Flag[LineCameraLost]++;
		}
		else
			Flag[LineCameraLost]=0;
		if(Flag[LineCameraLost]>5)
		{
			Flag[LockPointOn]=0;
			BREAK_All_MOTOR;
			OSTaskSuspend(15);	//TASK_6_PRIO
			OSTaskSuspend(OS_PRIO_SELF);
			return;
		}
		PidLockAngle(LockPoint.angle);
  	PidLockY(LockPoint.y);
	}
	
	if(fabs(Ek0)<1 && PositionNow.x<520)
	{
		LockPoint.y=PositionNow.y;
		Flag[StartLockY]=1;
	}
	else if(PositionNow.x<520 && CameraDate[0].errorcameraline*CameraDate[1].errorcameraline<=0 && CameraDate[0].errorcameraline*CameraDate[1].errorcameraline>-10)
	{
		LockPoint.y=(CameraDate[0].positionnowy*CameraDate[1].errorcameraline-CameraDate[0].errorcameraline*CameraDate[1].positionnowy)/(float)(CameraDate[1].errorcameraline-CameraDate[0].errorcameraline);
		Flag[StartLockY]=1;
	}
}
#endif

void SetLockPoint(float x,float y,float angle)
{
	LockPoint.x=x;
	LockPoint.y=y;
	LockPoint.angle=angle;
}

void PidLockX(float x)
{
	EkX=x-PositionNow.x;
	if(KpX1>5)
	{
		SpeedWantSet.Vx = 5 * EkX;
	}
	else
	{
		SpeedWantSet.Vx = KpX1 * EkX;
	}
}


void PidLockY(float y)
{
	float temp;
	if(PositionNow.x>505 && CurrentV>100)
	{
		CurrentV=100;
	}
	if(PositionNow.x>525 && CurrentV>850)
	{
		CurrentV=85;
	}
	EkY = y-PositionNow.y;
	if(fabs(EkY)<0.5)
		EkY=0;
	else 
		EkY-=0.5f*EkY/fabs(EkY);
	if(KpY1>2)
	{
		VExSum = 2 * EkY;
	}
	else
	{
		VExSum = 2 * EkY;
	}
	SpeedWantSet.Vx=CurrentV;

	
//	if(Flag[StartLockY]==0)
//	{
//		SpeedWantSet.Vy=VExSum;
//		temp=sqrt(SpeedWantSet.Vy*SpeedWantSet.Vy+SpeedWantSet.Vx*SpeedWantSet.Vx);
//		if(temp>Vmax)
//		{
//			SpeedWantSet.Vy=SpeedWantSet.Vy*Vmax/temp;
//			SpeedWantSet.Vx=SpeedWantSet.Vx*Vmax/temp;
//		}
//	  CalculateWheelSpeedAbsolute(SpeedWantSet);
//	}
//	else
		CameraLineSpeedPid();
//	VS4Channal_Send(SpeedWantSet.Vw,SpeedAbsolute.Vy,PositionNow.angle,SpeedWantSet.Vy);
//	VS4Channal_Send(PositionNow.x,PositionNow.y,Ek0*10,LockPoint.y);
////	VS4Channal_Send(LockPoint.x, LockPoint.y, PositionNow.x, PositionNow.y);
//	DT50_VS4Channal_Send((LockPoint.y-PositionNow.y),VExSum,SpeedWantSet.Vy,SpeedAbsolute.Vy);
//	Can2_VS4Channal_Send(Ek0*10,PositionNow.y,PositionNow.angle,SpeedAbsolute.Vy);
////	Can_VS4Channal_Send(PositionNow.x,SpeedAbsolute.Vx,Flag[RedRayLow]*100,SpeedWantSet.Vx);
//	Can_VS4Channal_Send(PositionNow.x, PositionNow.y,LockPoint.y,Flag[RedRayLow]);
	
//		VS4Channal_Send(Ek0*10,LockPoint.y,0,PositionNow.y);
		DT50_VS4Channal_Send((LockPoint.y-PositionNow.y),VExSum,SpeedWantSet.Vy,SpeedAbsolute.Vy);
		Can2_VS4Channal_Send(CurrentV,PositionNow.y,PositionNow.angle,SpeedAbsolute.Vy);
		Can_VS4Channal_Send(PositionNow.x,SpeedAbsolute.Vx,0,SpeedWantSet.Vx);
}

void PidLockAngle(float lockangle)
{
	float temp;                                                                 //这里肯定要加积分作用
	EkAngle=lockangle-PositionNow.angle;
	if(fabs(EkAngle)<0.1)
		EkAngle=0;
//	AngleSum+=EkAngle;
	SpeedWantSet.Vw=KpAngle*EkAngle+KiAngle*AngleSum+KdAngle*(EkAngle-EkAngle1);
	temp=fabs(SpeedWantSet.Vw);
	EkAngle2=EkAngle1;
	EkAngle1=EkAngle;
	if(temp>100)
		SpeedWantSet.Vw=SpeedWantSet.Vw*100/temp;
	else
		AngleSum+=EkAngle;
}

float sign_float(float num)
{
	if(num>0) return 1.0;
	else if(num<0) return -1.0;
	else return 0.0;
}

u8 UsartErrorTme=0;
void ArmCamera(s16 errorheight,s16 errorwidth)
{
//	float temp;
	UsartErrorTme++;
	if(errorheight==500 && errorwidth==500)
	{
		if(PositionNow.y<550)
  	{
				if(PositionNow.y>410 && MotorPositionSet.FanHight>-145000)
				{
					MotorPositionSet.FanHight=-145000;
				}
				else if(PositionNow.y>280 && MotorPositionSet.FanHight>-72000)
				{
					MotorPositionSet.FanHight=-72000;
				}
				if(MotorPositionSet.FanHight!=MotorPositionSetOld.FanHight && (KeyNumber & 0x07)!=0x04)
				{
						MotorPosition(MotorFanHight,6200,MotorPositionSet.FanHight);			
				}
	  }
		else
		{
				MotorPosition(MotorFanHight,6200,-190000);
		}
		return;
	}
	else
	{
		ErrorCameraHeight=500;
		ErrorCameraWidth=500;
	}
	if(fabs(errorwidth)>400)
	{
		return;
	}
	
//	temp=sqrt(SpeedAbsolute.Vx*SpeedAbsolute.Vx+SpeedAbsolute.Vy*SpeedAbsolute.Vy);
	
	if(fabs(errorwidth)<3)
		errorwidth=0;
	else
		errorwidth-=3*errorwidth/fabs(errorwidth);
	Ecw1=errorwidth;

	MotorSpeedSet.FanCircle=Pcircle*Ecw1+Dcircle*(Ecw1-Ecw2);
	
	Ecw3=Ecw2;
	Ecw2=Ecw1;

	
	if((MotorRealPosition.FanCircle<-15540 &&  MotorSpeedSet.FanCircle<0) || (MotorRealPosition.FanCircle>4400 && MotorSpeedSet.FanCircle>0))
	{
		MotorSpeedSet.FanCircle=0;
		Flag[MotorCircleLimit]=1;
	}
	if(PositionNow.y<100 && MotorSpeedSet.FanCircle<0)
		MotorSpeedSet.FanCircle=0;
 
	
	if(MotorSpeedSet.FanCircle!=MotorSpeedSetOld.FanCircle)
		MotorSpeed(MotorFanCircle,MotorSpeedSet.FanCircle);
  MotorSpeedSetOld.FanCircle=MotorSpeedSet.FanCircle;
	
	
	if(Flag[HeightChangeByCar]==1)
	{
			if(fabs(errorheight)<5)
				errorheight=0;
			else
				errorheight-=5*errorheight/fabs(errorheight);
			Ech1=errorheight;
			MotorPositionSet.FanHight+=Pheight*(Ech1-Ech2)+Iheight*Ech1+Dheight*(Ech1-2*Ech2+Ech3);
			Ech3=Ech2;
			Ech2=Ech1;
			if(MotorPositionSet.FanHight>MotorPositionSetOld.FanHight && PositionNow.y>500)
			{
					MotorPositionSet.FanHight=MotorPositionSetOld.FanHight;
			}
			

			if(MotorPositionSet.FanHight<-190000)
				MotorPositionSet.FanHight=-190000;
			if(MotorPositionSet.FanHight>-2500)
				MotorPositionSet.FanHight=-2500;

			
			if(PositionNow.y<550)
			{
				if(PositionNow.y>410 && MotorPositionSet.FanHight>-145000)
				{
					MotorPositionSet.FanHight=-145000;
				}
				else if(PositionNow.y>280 && MotorPositionSet.FanHight>-72000)
				{
					MotorPositionSet.FanHight=-72000;
				}
				if(MotorPositionSet.FanHight!=MotorPositionSetOld.FanHight && (KeyNumber & 0x07)!=0x04)
				{
						MotorPosition(MotorFanHight,6200,MotorPositionSet.FanHight);			
				}
			}
			else
			{
					MotorPosition(MotorFanHight,6200,-190000);
			}
			MotorPositionSetOld.FanHight=MotorPositionSet.FanHight;
  }
//VS4Channal_Send(PositionNow.y,MotorRealPosition.FanHight,MotorRealPosition.FanCircle,MotorRealSpeed.FanCircle);
	printf("%d\t",(int)PositionNow.y);
	printf("%d\t",(int)(MotorRealPosition.FanHight/100));
	printf("%d\t",(int)(MotorRealPosition.FanCircle/10));
	printf("%d\n",(int)(FanSpeed));
}



float PositionCar=0;
float Distance=0;
float CameraDistanceLastTime=0;                   //DT50实际测得的上一次有效数据
//float rate=0;
void DT50Distance(float distance)
{
//	float temp=0;
	int limit=0;
	int ErrorLimit=0;
	Distance=distance;
	Can_VS4Channal_Send(PositionCar,Flag[DT50Error]*10,distance,CameraDistanceValue);
//	if(Flag[LostPicture]>0)
	if(distance==-500)
	{
		
		Flag[DT50Error]++;
		return;
	}
	else
	{
		Flag[DT50Error]=0;
		CameraDistance=-500;
	}
	
	if(Flag[FanSpeedChangeByDT50]==1)
	{
		ErrorLimit=13;
		limit=350;
	}
	else 
	{
		limit=395;
		ErrorLimit=20;
	}
	
	if( ((KeyNumber & 0x07)==0x03 || (KeyNumber & 0x07)==0x02 || (KeyNumber & 0x07)==0x01 || (KeyNumber & 0x07)==0x00) && (distance<limit || Flag[CameraDistanceValeue]==1))
	{	
		Flag[CameraDistanceValeue]=1;
		if(CameraDistanceLastTime==0)
		  CameraDistanceLastTime=distance;
		if(distance<limit && (distance-CameraDistanceLastTime)<ErrorLimit*(Flag[LostDT50Distance]+1) && (distance-CameraDistanceLastTime)>-ErrorLimit*(Flag[LostDT50Distance]+1))
		{
			MotorRealPositionOld.FanCircle=MotorRealPosition.FanCircle;
			CameraDistanceLastTime=distance;
			CameraDistanceOld[2]=CameraDistanceOld[1];
			CameraDistanceOld[1]=CameraDistanceOld[0];
			CameraDistanceOld[0]=distance;
			CameraDistanceValue=distance;
			Flag[LostDT50Distance]=0;
		}
		else
		{
			Flag[LostDT50Distance]++;
			if(CameraDistanceOld[0]>1 && CameraDistanceOld[1]>1 && CameraDistanceOld[2]>1)
			{
				CameraDistanceValue=CameraDistanceOld[0]+CameraDistanceOld[1]-CameraDistanceOld[2];
				if(Flag[FanSpeedChangeByDT50]==1)
					CameraDistanceValue=(CameraDistanceValue+CameraDistanceOld[0]+CameraDistanceOld[1]+CameraDistanceOld[2])/4;
				if(CameraDistanceValue<50)
					CameraDistanceValue=CameraDistanceLastTime;
				if(distance<CameraDistanceValue)
					CameraDistanceValue=distance;
				if(CameraDistanceValue<CameraDistanceOld[0] && PositionNow.y>690)          //新加的条件
					CameraDistanceValue=CameraDistanceOld[0];
				CameraDistanceOld[2]=CameraDistanceOld[1];
				CameraDistanceOld[1]=CameraDistanceOld[0];
				CameraDistanceOld[0]=CameraDistanceValue;
			}
			else
			{
				distance=70;
				CameraDistanceValue=distance;
				CameraDistanceOld[2]=CameraDistanceOld[1];
				CameraDistanceOld[1]=CameraDistanceOld[0];
				CameraDistanceOld[0]=CameraDistanceValue;
			}
		}
  }
	else
		Flag[LostDT50Distance]++;
	
	
	if(Flag[CameraDistanceValeue]==1)
  	PositionCar = GetLittleCarPosition(CameraDistanceValue);

}

float Ekf1=0,Ekf2=0,SpeedSet=0;
void SpeedChangeByMotorAngle(void)
{		
	switch (LittleCarPosition)
	{
		case PositionFive:
			SpeedSet=13;	//13
		  Vmax=200;
		  break;
		case PositionSix:
			Flag[SpeedChange]=1;
			Flag[FanSpeedChangeByDT50]=0;
		  StartFan(0);
			return;
			break;
		case PositionFour:
			SpeedSet=FanSpeedFour;	//17
		break;
		case PositionThree:	
			SpeedSet=32;	//30
		break;
	  case PositionOne:	
			SpeedSet=25;	//25
		break;
		case PositionTwo:	
			SpeedSet=32;	//30
		break;
		default:break;		
	}
	if((KeyNumber & 0x07)==0x02)
	{
		SpeedSet=27;
	}
	Ekf1 = SpeedSet-CarSpeed;
	FanSpeed = Ekf1*65+(Ekf1-Ekf2)*10;     //13
//	if(LittleCarPosition>=PositionFive)
//	{
//		Ekf1=13-CarSpeed;
//		FanSpeed=Ekf1*40+(Ekf1-Ekf2)*10;     //13
//		if(FanSpeed>450) //300
//			FanSpeed=450;
//	}
//  else if(LittleCarPosition>=PositionFour)
//	{
//		Ekf1=15-CarSpeed;
//		FanSpeed=Ekf1*60+(Ekf1-Ekf2)*5;     //13
//		if(FanSpeed>800)    //550
//			FanSpeed=800;
//	}
	
	Ekf2=Ekf1;
	
//	VS4Channal_Send(FanSpeed,CarSpeed,Ekf1,LittleCarPosition);
	
	if(FanSpeed>900)
		FanSpeed=900;
	else if(FanSpeed<100)
		FanSpeed=100;
//	VS4Channal_Send(FanSpeed, CarSpeed, PositionNow.y, LittleCarPosition);
	StartFan(FanSpeed);
//	DT50_VS4Channal_Send(FanSpeed,CarSpeed,Ekf1,LittleCarPosition);
}


float Ekspeed,Ekspeed1,Ekspeed2;
void CameraLineSpeedPid(void)
{
	Ekspeed=VExSum-SpeedAbsolute.Vy;
	if(fabs(Ekspeed)<3)
		Ekspeed=0;
	else
		Ekspeed-=3*Ekspeed/fabs(Ekspeed);
	SpeedWantSet.Vy+=0.65f*(Ekspeed-Ekspeed1)+0.05f*Ekspeed+0*(Ekspeed-2*Ekspeed1+Ekspeed2);
	
	 if(fabs(SpeedWantSet.Vy)>Vmax)
	  SpeedWantSet.Vy=Vmax*SpeedWantSet.Vy/fabs(SpeedWantSet.Vy);
	
	Ekspeed2=Ekspeed1;
	Ekspeed1=Ekspeed;
	CalculateWheelSpeedAbsolute(SpeedWantSet);
}



