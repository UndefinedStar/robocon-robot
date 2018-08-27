#include "motor.h"

void MotorInit(void)
{
    MotorChangeMode(MotorFanHight, ModeSpeed);
    MotorChangeMode(MotorFanHight, ModePosition);
    MotorSearchZero(MotorFanHight, 500);
    MotorChangeMode(MotorSetHeart, ModePWM);
    MotorChangeMode(MotorHeartHand, ModePosition);


    MotorChangeMode(MotorFanCircle, ModePosition);

//    MotorSearchZero(MotorHeartHand, 3000*PlacePart);
    MotorPWM(MotorSetHeart, 1500);

    switch (KeyNumber & 0x07)
    {
        case 0x00:
            MotorPositionSet.FanHight = -2500;
            MotorPositionSetOld.FanHight = -2500;
            break;
        case 0x01:
            MotorPosition(MotorFanCircle, 7000, -111 * 30 * PlacePart);
            MotorPositionSet.FanCircle = -111 * 30 * PlacePart;
            MotorPositionSetOld.FanCircle = -111 * 30 * PlacePart;
            MotorPositionSet.FanHight = -72000;
            MotorPositionSetOld.FanHight = -72000;
            break;
        case 0x02:
            MotorPosition(MotorFanCircle, 7000, -111 * 15 * PlacePart);
//            MotorPositionSet.FanCircle = -111 * 15 * PlacePart;
//            MotorPositionSetOld.FanCircle = -111 * 15 * PlacePart;
            MotorPositionSet.FanHight = -145000;
            MotorPositionSetOld.FanHight = -145000;
            break;
        case 0x03:
            MotorPosition(MotorFanCircle, 7000, 111 * 35 * PlacePart);
            MotorPositionSet.FanCircle = 111 * 35 * PlacePart;
            MotorPositionSetOld.FanCircle = 111 * 35 * PlacePart;
            MotorPositionSet.FanHight = -190000;
            MotorPositionSetOld.FanHight = -190000;
            break;
        case 0x04:
            MotorPosition(MotorFanCircle, 7000, -111 * 35 * PlacePart);
            MotorPositionSet.FanCircle = -111 * 35 * PlacePart;
            MotorPositionSetOld.FanCircle = -111 * 35 * PlacePart;
            break;
        default:
            break;
    }
    AskForMotorPosition(MotorFanCircle);
    OSTimeDly(20);
    Flagu16[OverTime] = 0;
    while(fabs(MotorRealPosition.FanCircle - MotorPositionSet.FanCircle) > 300 &&
          Flagu16[OverTime] < 200)
    {
        MotorPosition(MotorFanCircle, 7000, MotorPositionSet.FanCircle);
        AskForMotorPosition(MotorFanCircle);
        OSTimeDly(100);
    }
    MotorChangeMode(MotorFanCircle, ModeSpeed);
}


void MotorInitFive(void)
{
    MotorChangeMode(MotorSetHeart, ModePWM);

    MotorChangeMode(MotorHeartHand, ModePosition);

    MotorChangeMode(MotorFanHight, ModePosition);
    MotorChangeMode(MotorFanCircle, ModePosition);

    ChangeMotorPWMLimit(MotorSetHeart, 1500);

    MotorSearchZero(MotorHeartHand, 3000*PlacePart);
    MotorSearchZero(MotorFanHight, 3000);
    MotorPWM(MotorSetHeart, 1500);

}


void ClimbPole(void)
{
		u8 Once = 0;
    u8 time = 0;
    switch (KeyNumber & 0x07)
    {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:

        case 0x05:
            BREAK_All_MOTOR;
            ChangeMotor(0x160, ClimbMotor);
            OSTimeDly(100);
            Elmo_StartMotor();
            Led8DisData(10);

            while(Flag[GetFanSucess] == 0)
                OSTimeDly(100);

			
#if (PlacePart==BluePart)
            OSTimeDly(20);
            Flagu16[OverTime] = 0;
            while((MotorRealPosition.HeartHand > -41500 && Flagu16[OverTime] < 10000) ||
                  Once == 0)
            {
                Once = 1;
                time++;
                if(time == 3)
                    Cylinder(CylinderSetHeart, CylinderSetHeartClose, 'W');
                AskForCylinderState();
                OSTimeDly(100);
            }
            Led8DisData(11);
#else
            Flag[HeartHandSearchZero] = 1;
            Flagu16[OverTime] = 0;
            OSTimeDly(20);
            while((MotorRealPosition.HeartHand < -16000 && Flagu16[OverTime] < 10000)  || Once == 0)
            {
                Once = 1;
                time++;
                if(time == 3)
                    Cylinder(CylinderSetHeart, CylinderSetHeartClose, 'W');
                AskForCylinderState();
                OSTimeDly(100);
            }
            Led8DisData(11);


#endif
						while(!Switch_Climb)
				      OSTimeDly(100);
            break;



        case 0x06:
					  OSTimeDly(2000);
            Cylinder(CylinderClimbOneMotor, CylinderClimbOneOpen, 'W');
            OSTimeDly(20);
            ChangeMotor(0x160, ClimbMotor);
            OSTimeDly(100);
            Elmo_StartMotor();
            Led8DisData(10);
        case 0x07:
            Flag[HeartHandSearchZero] = 1;
		    		Flag[GetFanSucess]=1;
            break;
        default:
            break;
    }

		
			
    FREE_ALL_MOTOR;
    Flagu16[OverTime] = 0;
    while(GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_6) && Flagu16[OverTime] < 100)
        OSTimeDly(10);
		#if (PlacePart==RedPart)
    Elmo_SetDC(2000000);
		#else
		Elmo_SetDC(4000000);
		#endif
    Elmo_SetSpeed(2, -5500);
    Elmo_SetSpeed(3, 5500);
    Elmo_SetSpeed(4, -5500 / 1000 * 512);
    Elmo_SetSpeed(1, 0);
		
		Cylinder(CylinderSetHeart, CylinderSetHeartOpen, 'W');
		
    StartFan(0);
    Elmo_Begin();
    OSTimeDly(100);
    Flagu16[OverTime] = 0;
    while((MotorRealSpeed.MotorTwo > -200 || MotorRealSpeed.MotorThree < 200 ||
           MotorRealSpeed.MotorFour > -200) && Flagu16[OverTime] < 1000)
    {
        Elmo_SetSpeed(2, -5500);
        Elmo_SetSpeed(3, 5500);
        Elmo_SetSpeed(4, -5500 / 1000 * 512);
        Elmo_SetSpeed(1, 0);
        Elmo_Begin();

        OSTimeDly(100);
    }


    OSSemPost(RunStart);

    OSTimeDly(1000);
    while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_2) == 1 &&
          (Flag[ClimbSpeedDown] == 0 || !Switch_ClimbDown) &&
          Flagu16[ClimbTime] < ClimbTimeLimit)
    {
        Flagu16[ClimbTime]++;
        if(PositionNow.angle < -181.5)
            MotorPosition(MotorFanCircle, 5000, -111 * 180 * PlacePart);
        else if(PositionNow.angle > -178.5)
            MotorPosition(MotorFanCircle, 5000, -111 * 0 * PlacePart);

        if(fabs(PositionNow.angle + 180) > 2)
            StartFan(150);
        else
            StartFan(0);
        OSTimeDly(100);
    }

    StartFan(0);

    Elmo_SetSpeed(2, -2000);
    Elmo_SetSpeed(3, 2000);
    Elmo_SetSpeed(4, -2000 / 1000 * 512);
    Elmo_Begin();

    while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_2) == 1 && Flagu16[ClimbSpeedDownTime] < ClimbDownLimit)
    {
        Flagu16[ClimbSpeedDownTime]++;
        OSTimeDly(50);
    }

		Cylinder(CylinderSetHeart, CylinderSetHeartClose, 'W');
    Flag[ClimbStop] = 1;
    BREAK_All_MOTOR;


    MotorChangeMode(MotorSetHeart, ModePosition);
    ChangeMotorPWMLimit(MotorSetHeart, 3000);
    MotorSearchZero(MotorSetHeart, 5000);
#if (PlacePart==BluePart)
    StartStteringEngine(StteringEngineBlue, StteringEngineBlueUp);
#else
    StartStteringEngine(StteringEngineRed, StteringEngineRedUp);
#endif

    AskForCylinderState();
    OSFlagPend(Flag_Pend, SetHeartFinish, OS_FLAG_WAIT_SET_ALL | OS_FLAG_CONSUME, 0,
               ErrorFlabellumFinish);    //定心结束，放扇叶

    MotorChangeMode(MotorHeartHand, ModePosition);
    ChangeMotorPWMLimit(MotorHeartHand, 3000);
    MotorSearchZero(MotorHeartHand, PlacePart * Flagu16[MotorPutFanSpeedBlue]);
    Flag[HeartHandSearchZero] = 2;



//#if (PlacePart==BluePart)

//    if((MagneticSwitchState & 0x17) != 17)
//    {
//        while(Flagu16[PutFanTime] < PutFanLimit - 25)
//        {
//            Flagu16[PutFanTime]++;
//            OSTimeDly(10);
//        }
//        Cylinder(CylinderHand, CylinderHandOpen, 'W');
//        OSTimeDly(250);
//        Cylinder(CylinderHand, CylinderHandClose, 'W');
//    }
//    else
//    {
        while(Flagu16[PutFanTime] < PutFanLimit)
        {
            Flagu16[PutFanTime]++;
            OSTimeDly(10);
        }
//    }

//#else
//    if((MagneticSwitchState & 0x06) != 6)
//    {
//        while(Flagu16[PutFanTime] < PutFanLimit - 25)
//        {
//            Flagu16[PutFanTime]++;
//            OSTimeDly(10);
//        }
//        Cylinder(CylinderHand, CylinderHandOpen, 'W');
//        OSTimeDly(250);
//        Cylinder(CylinderHand, CylinderHandClose, 'W');
//    }
//    else
//    {
//        while(Flagu16[PutFanTime] < PutFanLimit)
//        {
//            Flagu16[PutFanTime]++;
//            OSTimeDly(10);
//        }
//    }
//#endif
    OSTimeDly(1000);
    Cylinder(CylinderHand, CylinderHandOpen,
             'W');                                     //放完扇叶松开爪子

    OSTimeDly(1500);
//    MotorChangeMode(MotorHeartHand, ModePosition);
#if (PlacePart==BluePart)
    StartStteringEngine(StteringEngineBlue, StteringEngineBlueDown);
    StartStteringEngine(StteringEngineRed, StteringEngineRedUp);
//   MotorPosition(MotorHeartHand, 3500, -35000);
#else
    StartStteringEngine(StteringEngineBlue, StteringEngineBlueUp);
    StartStteringEngine(StteringEngineRed, StteringEngineRedDown);
//   MotorPosition(MotorHeartHand, 3500, -45000);
#endif





    MotorChangeMode(MotorSetHeart, ModePWM);
    OSTimeDly(4000);
    MotorPWM(MotorSetHeart, -1500);
		Elmo_RelieveMotor(0x304);
    FREE_ALL_MOTOR;
    Elmo_SetSpeed(2, 1000);
    Elmo_SetSpeed(3, -1000);
    Elmo_SetSpeed(4, 1000 / 1000 * 512);
    Elmo_Begin();

    OSTimeDly(100);
    Flagu16[OverTime] = 0;
    while((fabs(MotorRealSpeed.MotorTwo) < 100 ||
           fabs(MotorRealSpeed.MotorThree) < 100 ||
           fabs(MotorRealSpeed.MotorFour) < 100) && Flagu16[OverTime] < 1000)
    {
        Elmo_SetSpeed(2, 1000);
        Elmo_SetSpeed(3, -1000);
        Elmo_SetSpeed(4, 1000 / 1000 * 512);
        Elmo_Begin();
        OSTimeDly(100);
    }

    OSTimeDly(7500);
		Elmo_StartMotor();
    BREAK_All_MOTOR;
    OSTaskSuspend(57);

}

s32 GetMotorHightPosition(float x)
{
    return 189200*sin(0.004109f*x+2.562f) +  67060*sin(0.008668f*x-1.883f) + 18090*sin(0.01453f*x-1.153) + 
                    4793*sin( 0.03088f*x-0.9818f) + 63520*sin(0.06416f*x+0.6726f) -6341*sin(0.04178f*x-5.666f) + 
                    3985*sin(0.05581f*x-2.506f) + 63570*sin(0.06411f*x+3.842);
}

s32 GetMotorCirclePositionOne(float x)
{
    return  1667*sin(0.1956f*x+2.85f) + 426.5*sin(0.3686f*x+3.235f) + 184.1f*sin(0.8673f*x+4.368f) + 
                    111.9f*sin(0.9939f*x+19.29f);
}

s32 GetMotorCirclePositionTwo(float x)
{
    return  4185*sin( 0.0105f*x-0.8225f) + 2258*sin(0.01886f*x+0.5757f) + 443.8f*sin(0.03086f*x+1.219f) + 
                    78.75f*sin(0.06149f*x-2.063f) + 41.59f*sin(0.07089f*x+ 5.469f) + 10.53f*sin(0.122f*x+0.7533f);
}

s32 GetMotorCirclePositionThree(float x)
{
    return  2127*sin(0.006997f*x+3.848f) + 2250  *sin(0.0166f*x+ 2.145f) + 125.1f*sin(0.04179f*x-1.226f) + 
                    123.2f*sin(0.05299f*x+1.01f) + 90.81f*sin(0.07071f*x+0.4778f) + 62.58f*sin(0.08544f*x+7.948f);
}

s32 GetMotorCirclePositionFour(float x)
{
    return  9566*sin(0.01595f*x+16.56f) + 4278*sin(0.05162f*x+13.15f) + 1091*sin(0.1697f*x+35.48f) + 
                    1412*sin(0.1272f*x+12.48f) + 107.8f*sin(0.3036f*x+39.77f) + 37.17f*sin(0.3622f*x+ 51.39f) + 
                    444.1f*sin(0.2209f*x+52.12);
}


void ArmChangeByPosition(void)
{
    if(PositionNow.y < 50)
        return;
    if(PositionNow.y < 65)
        MotorPositionSet.FanCircle = GetMotorCirclePositionOne(PositionNow.y);                                 
    else if(PositionNow.y<372)
        MotorPositionSet.FanCircle = GetMotorCirclePositionTwo(PositionNow.y);
    else if(PositionNow.y<671)         
				MotorPositionSet.FanCircle = GetMotorCirclePositionThree(PositionNow.y);
		else       
				MotorPositionSet.FanCircle = GetMotorCirclePositionFour(PositionNow.y);

    MotorPosition(MotorFanCircle, 5000, MotorPositionSet.FanCircle);

    if(Flag[HeightChangeByCar] == 1)
    {
        MotorPositionSet.FanHight = GetMotorHightPosition(PositionNow.y);

        if(PositionNow.y < 550)
        {
            if(PositionNow.y > 410 && MotorPositionSet.FanHight > -145000)
            {
                MotorPositionSet.FanHight = -145000;
            }
            else if(PositionNow.y > 280 && MotorPositionSet.FanHight > -72000)
            {
                MotorPositionSet.FanHight = -72000;
            }
        }
        else
        {
            MotorPositionSet.FanHight = -185000;

        }
        if( MotorPositionSet.FanHight > -2000)
            MotorPositionSet.FanHight = -2000;
        MotorPosition(MotorFanHight, 6200, MotorPositionSet.FanHight);
    }
}


void FanSpeedChangeByPosition(float x)
{
    if(x <= 300)
        FanSpeed = 550;
    else if(x<=455)
        FanSpeed = 100;
		else if(x<=540)
			  FanSpeed=512.2f*sin(0.1155f*x+12.54f) + 206.2f*sin(0.214f*x+23.26f) + 18.63f*sin(0.8083f*x+3.161f) + 
                    14.36f*sin(1.178f*x+57.81);
		else if(x<=600)
				FanSpeed=420;
		else if(x<=667)
			  FanSpeed=200;
		else
				FanSpeed=750;
    StartFan(FanSpeed);
//    if(PositionNow.y > 600)
//        Flag[SpeedChange] = 1;
}
