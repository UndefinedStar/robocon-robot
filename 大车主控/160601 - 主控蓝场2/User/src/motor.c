#include "motor.h"

void MotorInit(void)
{
  MotorChangeMode(MotorFanHight,ModeSpeed);
	MotorChangeMode(MotorFanHight,ModePosition);
	MotorSearchZero(MotorFanHight,3000);
	MotorChangeMode(MotorSetHeart,ModePWM);
	MotorChangeMode(MotorHeartHand,ModePosition);
	
	
	MotorChangeMode(MotorFanCircle,ModePosition);	

  MotorSearchZero(MotorHeartHand,3000);
	MotorPWM(MotorSetHeart,1500);
	
	switch (KeyNumber & 0x07)
	{
		case 0x00:
			MotorPositionSet.FanHight=-2500;
			MotorPositionSetOld.FanHight=-2500;
		break;
		case 0x01:
			MotorPosition(MotorFanCircle,7000,-111*30*PlacePart);
			MotorPositionSet.FanCircle=-111*30*PlacePart;
			MotorPositionSetOld.FanCircle=-111*30*PlacePart;
	  	MotorPositionSet.FanHight=-72000;
			MotorPositionSetOld.FanHight=-72000;
		break;
		case 0x02:
			MotorPosition(MotorFanCircle,7000,-111*15*PlacePart);
			MotorPositionSet.FanCircle=-111*15*PlacePart;
			MotorPositionSetOld.FanCircle=-111*15*PlacePart;
	  	MotorPositionSet.FanHight=-145000;
			MotorPositionSetOld.FanHight=-145000;
		break;
		case 0x03:
			MotorPosition(MotorFanCircle,7000,111*35*PlacePart);
			MotorPositionSet.FanCircle=111*35*PlacePart;
			MotorPositionSetOld.FanCircle=111*35*PlacePart;
	  	MotorPositionSet.FanHight=-190000;
		  MotorPositionSetOld.FanHight=-190000;
		break;
		case 0x04:
			MotorPosition(MotorFanCircle,7000,-111*35*PlacePart);
			MotorPositionSet.FanCircle=-111*35*PlacePart;
			MotorPositionSetOld.FanCircle=-111*35*PlacePart;
		break;
		default:break;
	}
	AskForMotorPosition(MotorFanCircle);
	OSTimeDly(20);
	Flagu16[OverTime]=0;
	while(fabs(MotorRealPosition.FanCircle-MotorPositionSet.FanCircle)>300 && Flagu16[OverTime]<200)
	{
		MotorPosition(MotorFanCircle,7000,MotorPositionSet.FanCircle);
		AskForMotorPosition(MotorFanCircle);
		OSTimeDly(100);
	}
	MotorChangeMode(MotorFanCircle,ModeSpeed);  
}


void MotorInitFive(void)
{
	MotorChangeMode(MotorSetHeart,ModePWM);
	
	MotorChangeMode(MotorHeartHand,ModePosition);
	
	MotorChangeMode(MotorFanHight,ModePosition);
	MotorChangeMode(MotorFanCircle,ModePosition);	
	
	ChangeMotorPWMLimit(MotorSetHeart,1500);

	MotorSearchZero(MotorHeartHand,3000);
	MotorSearchZero(MotorFanHight,3000);
	MotorPWM(MotorSetHeart,1500);
	
}

void ClimbPole(void)
{		
	switch (KeyNumber & 0x07)
	{
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
	  case 0x05:
			
			
			while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)==1)
			{
				Flagu16[ConnectTime]++;
				OSTimeDly(200);
			}
			MotorPosition(MotorFanCircle,4000,-111*(-45)*PlacePart);
      MotorPosition(MotorHeartHand,5000,-45533);			
			BREAK_All_MOTOR;
			ChangeMotor(ClimbMotor);
			OSTimeDly(100);
			Elmo_StartMotor();
			Led8DisData(10);
			
			Cylinder(CylinderHand | CylinderClimbOneMotor,CylinderHandClose | CylinderClimbOneOpen,'W');
	
			OSTimeDly(2000);
			
			MotorPosition(MotorHeartHand,4000,-86304);	    
			

			OSTimeDly(20);
			while(MotorRealPosition.HeartHand+85000>500)       
			{		 
				OSTimeDly(20);
			}
      Led8DisData(11);
			
			break;

		case 0x06:
			Elmo_RelieveMotor();	
			Cylinder(CylinderClimbOneMotor,CylinderClimbOneOpen,'W');
			OSTimeDly(20);
			ChangeMotor(ClimbMotor);
			OSTimeDly(100);
			Elmo_StartMotor();
			Led8DisData(10);
		case 0x07:
			Flag[HeartHandSearchZero]=1;
			break;
		default:
			break;
	}

	FREE_ALL_MOTOR;
	Flagu16[OverTime]=0;
	while(GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_6) && Flagu16[OverTime]<100)
		OSTimeDly(1);
	Elmo_SetDC(2000000);
	Elmo_SetSpeed(2,-5000);
	Elmo_SetSpeed(3,5000);
	Elmo_SetSpeed(4,-5000/1000*512);
	Elmo_SetSpeed(1,0);
	StartFan(0);
	Elmo_Begin();
	OSTimeDly(100);
	Flagu16[OverTime]=0;
	while((MotorRealSpeed.MotorTwo>-200 || MotorRealSpeed.MotorThree<200 || MotorRealSpeed.MotorFour>-200) && Flagu16[OverTime]<1000)
	{
		Elmo_SetSpeed(2,-5000);
		Elmo_SetSpeed(3,5000);
		Elmo_SetSpeed(4,-5000/1000*512);
		Elmo_Begin();
		OSTimeDly(100);
	}
	Flag[GetFanSucess]=1;
	
			
	OSSemPost(RunStart);				       
	
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_2)==1 && Flag[ClimbSpeedDown]==0 && Flagu16[ClimbTime]<ClimbTimeLimit)
	{
		Flagu16[ClimbTime]++;
		if(PositionNow.angle<-181.5)
			MotorPosition(MotorFanCircle,5000,-111*180*PlacePart);
		else if(PositionNow.angle>-178.5)
			MotorPosition(MotorFanCircle,5000,-111*0*PlacePart);
		
		if(fabs(PositionNow.angle+180)>2)
			StartFan(150);
		else
			StartFan(0);
		OSTimeDly(100);
	}

	StartFan(0);
	
	Elmo_SetSpeed(2,-2000);
	Elmo_SetSpeed(3,2000);
	Elmo_SetSpeed(4,-2000/1000*512);
	Elmo_Begin();
	
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_2)==1 && Flagu16[ClimbSpeedDownTime]<ClimbDownLimit)
	{
		Flagu16[ClimbSpeedDownTime]++;
		 OSTimeDly(50);
	}
	
	Flag[ClimbStop]=1;
	BREAK_All_MOTOR;
		
	
	MotorChangeMode(MotorSetHeart,ModePosition);
	ChangeMotorPWMLimit(MotorSetHeart,3000);
	MotorSearchZero(MotorSetHeart,5000);
	StartStteringEngine(StteringEngineBlue,StteringEngineBlueUp);
	

	OSFlagPend(Flag_Pend,SetHeartFinish,OS_FLAG_WAIT_SET_ALL | OS_FLAG_CONSUME,0,ErrorFlabellumFinish);    //定心结束，放扇叶
	
	
	MotorChangeMode(MotorHeartHand,ModeSpeed);		
	ChangeMotorPWMLimit(MotorHeartHand,3000);

	MotorSpeed(MotorHeartHand,-4000);
	

	if(Flag[SunSwitchOn]==1)
		Flag[SunSwitchError]=1;
	while(Flagu16[PutFanTime]<PutFanLimit) 
	{
		Flagu16[PutFanTime]++;
		OSTimeDly(10);
	}
	MotorStop(MotorHeartHand);
	
	
	#if Switch_Test
	Flagu16[OverTime]=0;
	while(Flag[HandleSwitch]==0 && Flagu16[OverTime]<1500)                          
		OSTimeDly(100);
	#endif
	
	Cylinder(CylinderHand,CylinderHandOpen,'W');                                     //放完扇叶松开爪子
	
	OSTimeDly(1500);

	StartStteringEngine(StteringEngineBlue,StteringEngineBlueDown);
	StartStteringEngine(StteringEngineRed,StteringEngineRedUp);
	
	MotorChangeMode(MotorHeartHand,ModePosition);
	MotorPosition(MotorHeartHand,3500,-35000);

	MotorChangeMode(MotorSetHeart,ModePWM);
	OSTimeDly(4000);
	MotorPWM(MotorSetHeart,-1500);
	FREE_ALL_MOTOR;
	Elmo_SetSpeed(2,1000);
	Elmo_SetSpeed(3,-1000);
	Elmo_SetSpeed(4,1000/1000*512);
	Elmo_Begin();
	
	OSTimeDly(100);
	Flagu16[OverTime]=0;
	while((fabs(MotorRealSpeed.MotorTwo)<100 || fabs(MotorRealSpeed.MotorThree)<100 || fabs(MotorRealSpeed.MotorFour)<100) && Flagu16[OverTime]<1000)
	{
		Elmo_SetSpeed(2,1000);
		Elmo_SetSpeed(3,-1000);
		Elmo_SetSpeed(4,1000/1000*512);
		Elmo_Begin();
		OSTimeDly(100);
	}
	
	OSTimeDly(5000);
	
	BREAK_All_MOTOR;
//	StartStteringEngine(StteringEngineRight,StteringEngineRightUp);
	OSTaskSuspend(57);
	
}

s32 GetMotorHightPosition(float x)
{
	return (3476*sin(0.003541f  *x+3.864f) + 3256  *sin(0.004568f*x+ 0.6625f) +  100.9f*sin(0.01236f*x+0.3214f ) + 
                     69.89f*sin( 0.02674f*x+5.926f) +  15.01f*sin( 0.06454f *x-0.4608f  ) + 51.57f*sin(0.04993f*x+ 5.631f));
}

s32 GetMotorCirclePositionOne(float x)
{
	return (145.7f*sin(0.004569f*x+2.413f) + 45.6f*sin(0.01877f*x-2.964f)-271.7f*sin(0.04613f*x-9.704f) + 
                    144.8f*sin( 0.04284f*x-5.425f) + 410.1f*sin(0.04516f*x+3.19f ) + 117*sin(0.009865f*x+2.339f));
}

s32 GetMotorCirclePositionTwo(float x)
{
	return  (176.2f*sin( 0.01317f*x+1.389f) + 94.61f*sin(0.02701f*x+ 2.392f) + 26.73f*sin(0.08104f*x -8.684f) + 
                    18.25f *sin(0.1088f*x -9.857f) + 16.34f*sin(0.1571f*x+-17.4f) + 13.44f*sin(0.1797f*x-8.904f));
}


void ArmChangeByPosition(void)
{
	if(PositionNow.y<50)
		return;
	if(PositionNow.y<550)
		MotorPositionSet.FanCircle=GetMotorCirclePositionOne(PositionNow.y)*10;
	else
		MotorPositionSet.FanCircle=GetMotorCirclePositionTwo(PositionNow.y)*10;
	
	MotorPosition(MotorFanCircle,5000,MotorPositionSet.FanCircle);
	
	if(Flag[HeightChangeByCar]==1)
	{
			MotorPositionSet.FanHight=GetMotorHightPosition(PositionNow.y)*100;
					
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
			}
			else
			{
				  MotorPositionSet.FanHight=-190000;
					
			}
			if( MotorPositionSet.FanHight>-2000)
				MotorPositionSet.FanHight=-2000;
			MotorPosition(MotorFanHight,6200,MotorPositionSet.FanHight);
  }
	VS4Channal_Send(PositionNow.y,MotorPositionSet.FanHight/100,MotorPositionSet.FanCircle/10,0);
}



