#include "run.h"

volatile float CurrentV = 0.0;
volatile float Vmax = 0;
volatile SPEED SpeedWantSet = {0.0, 0.0, 0.0};
volatile SPEED SpeedNow = {0, 0, 0};
volatile POSITION PositionNow = {0.0, 0.0, 0.0};
volatile POSITION LockPoint = {BeginX, BeginY, 0};

POSI Vec_Line;      //当前Bezier上的向量
POSI Vec_Error;     //偏差向量


unsigned char
AutoRunType;                                              //自动行走标志

//初始坐标点与终止坐标点
float XStart = 0.0;
float YStart = 0.0;
float AngleStart = 0.0;

float XGoal = 0.0;
float YGoal = 0.0;
float AngleGoal = 0.0;

//加减速距离与直线行走距离
float UpDis = 0;
float DownDis = 0.0;
float GoalDis = 0.0;

//开始旋转的行走距离与旋转所需的行走距离
float StartTurnDis = 0.0;
float FullTurnDis = 0.0;
//开始旋转时的坐标
float XStartTurn = 0.0;
float YStartTurn = 0.0;

//初始速度与最大速度
float VWant = 0.0;
float VStart = 0.0;
float VStop = 0.0;
//开始刹车时的速度
float VStartBrake = 0.0;


//行走直线的斜率
unsigned char PidLineType = 0; //直线PID调节方式，调X还是调Y
float LineK = 0.0;   //直线斜率
float LineB = 0.0;   //直线截距
float LineKCos = 0.0; //直线倾角余弦值

//Bezier独有
BEZIER GlobalBezier;        //描述Bezier曲线

POINTONBEZIER BPoint1;
POINTONBEZIER BPoint2;

float DeltaT;

float UpT = 0;      //加速到的t值
float DownT = 0.0;  //开始减速时的t值
float StartTurnT = 0.0; //开始旋转的t值
float FullTurnT = 0.0; //旋转所需的t值

u8 LittleCarPosition = 0;

volatile u8  Flag[40] = {0};
volatile u16 Flagu16[10] = {0};

void RunPoint(unsigned char upflag, u8 downflag, unsigned char turnflag,
              unsigned char conflag, float Vwant, float Vstart, float Vstop, 
							float Anglestart,	float Xwant, float Ywant, float Anglewant,
							float updis, float downdis, float startturndis, float fullturndis)
{
		float angle = 0;
    Flag[SpeedUp]      = upflag;
    Flag[SpeedUpVar]   = upflag;
    Flag[SpeedDown]    = downflag;
    Flag[SpeedDownVar] = downflag;
    Flag[Turn]         = turnflag;
    Flag[TurnVar]      = turnflag;
    Flag[RunContinue]  = conflag;

	
    VWant         = Vwant; //速度
    VStart        = Vstart;//起始速度
    VStop         = Vstop; //终止速度

		if(Flag[StartDt50Work]==1 && (KeyNumber & 0x07)==0)
		{
			XStart        = 350+CarBehindStartX;     //起始点
			YStart        = 50;
			AngleStart    = 0;   //改过了			
		}
		else
		{
			XStart        = PositionNow.x;     //起始点
			YStart        = PositionNow.y;
			AngleStart    = Anglestart;   //改过了
		}

//  AngleStart    = 0;

    XGoal         = Xwant; //目标点
    YGoal         = Ywant;
    AngleGoal     = Anglewant;

    UpDis         = updis; //加速距离
    DownDis       = downdis; //减速距离
    GoalDis       = CountDistance(XStart, YStart, XGoal, YGoal); //移动总距离

    StartTurnDis  = startturndis;  //开始旋转的距离
    FullTurnDis   = fullturndis;   //旋转所需的总距离

    //Sum_Distance = 0.0;

    //数据输入有误处理
    if(UpDis + DownDis > GoalDis)       //加减速距离之和大于总距离
    {
        BREAK_All_MOTOR;
        BeepOn;
        OSTaskSuspend(OS_PRIO_SELF);
        return;
    }
    if(StartTurnDis + FullTurnDis >
       GoalDis) //开始旋转时的距离与所需的距离之和大于总距离
    {
        Flag[Turn] = 0;
        Flag[TurnVar] = 0;
        BREAK_All_MOTOR;
        BeepOn;
        OSTaskSuspend(OS_PRIO_SELF);
        return;
    }
//  if(VStart>VWant)                    //如果开始速度大于中间速度
//  {
//      SpeedUpFlag = 0;                //则不需要加速
//      VStart=VWant;
//  }
//  if(VStop>VWant)                     //如果停止点的速度大于中间速度
//  {
//      SpeedDownFlag =0;               //则不需要减速
//      SpeedDownFlagVar =0;        //当前不在减速过程
//  }
//  if(SpeedUpFlag==0)              //如果无加速过程
//  {
//      VStart = VWant;                 //直接给VStart赋值中间速度
//  }

    CurrentV = VStart;                  //把速度赋初值
    SpeedWantSet.Vw = 0.0;
    Flag[KeepRun] = 1;
    LockPoint.angle  = AngleStart;  //保持姿态角不变


    if(fabs(XGoal - XStart) < 0.5)      //直线斜率过大，近似无斜率
    {
        Flag[NoLineK] = 1;              //直线无斜率
        PidLineType = 2;            //直线的PID的类型  以X方向的偏差做调节
    }
    else
    {
        Flag[NoLineK] = 0;
        LineK = (YGoal - YStart) / (XGoal - XStart); //直线斜率
        LineKCos = 1 / sqrt(1 + LineK * LineK); //直线倾角的余弦
        if(fabs(LineK) < 1)   //如果斜率小于1，以Y方向偏差做调节
        {
            PidLineType = 1;
            LineB = YStart - XStart * LineK;
        }
        else                  //否则，以X方向的偏差做调节
        {
            PidLineType = 2;
            LineB = XStart - YStart / LineK;
        }
    }
    Flag[LockPointOn] = 0;              //关闭位置锁定
    AutoRunType = runpoint;
    PidInit();                      //PID初始化
    FREE_ALL_MOTOR;
    Flag[AutoRun] = 1;                  //打开PID调节
    n = 0;
    while((((XGoal - XStart) * (PositionNow.x - XGoal) + (YGoal - YStart) *
            (PositionNow.y - YGoal)) < -0.5))
    {
        OSTimeDly(50);
//      n++;
    }
    if(Flag[RunContinue] == 0)
    {
        Flag[AutoRun] = 0; //关闭PID调节
        if(Flag[KeepRun])//如果是正常退出,即KeepRunFlag未被清零
        {
            SetLockPoint(XGoal, YGoal, AngleGoal);
        }
        Flag[LockPointOn] = 1;
    }
    Flag[AutoRun] = 0;          //只关闭了PID调节，车还是会继续以最后一次的速度运行
}



//Bezier曲线跑法
void RunBezier(unsigned char upflag, unsigned char downflag,
               unsigned char turnflag, unsigned char conflag, float Vwant, float Vstart,
               float Vstop, float Anglewant, float upt, float downt, float startturnt,
               float fullturnt, unsigned char pid_class)
{
    BeepOff;
    CountBezierControlPoint(&GlobalBezier); //计算Bezier中间的两个控制点
    CountBezierFunction(
        &GlobalBezier);     //根据4个控制点坐标计算Bezier参数方程系数
    //估算DeltaT
    DeltaT = (2 / (CountDistance(GlobalBezier.P0.x, GlobalBezier.P0.y,
                                 GlobalBezier.P3.x, GlobalBezier.P3.y)));
    //初始化BPoint1和BPoint2
    BPoint1.t = 0;
    BPoint2.t = DeltaT;
    CountBezierXYbyT(&GlobalBezier,
                     &BPoint1);      //根据BPoint1中的t值计算对应的坐标
    CountBezierXYbyT(&GlobalBezier,
                     &BPoint2);      //根据BPoint2中的t值计算对应的坐标
    //初始化向量Vec_Line
    Vec_Line.x = BPoint2.x - BPoint1.x;
    Vec_Line.y = BPoint2.y - BPoint1.y;
    /*******初始化运动控制参数**************************/
    Flag[SpeedUp]   = upflag;
    Flag[SpeedUpVar] = upflag;
    Flag[SpeedDown] = downflag;
    Flag[SpeedDownVar] = downflag;
    Flag[Turn]      = turnflag;
    Flag[TurnVar]   = turnflag;
    Flag[RunContinue]     = conflag;

    VWant         = Vwant; //目标速度
    VStart        = Vstart;//起始速度
    VStop         = Vstop; //终止速度

    XStart        = PositionNow.x;     //起始点
    YStart        = PositionNow.y;
    AngleStart    = PositionNow.angle;
// AngleStart    = 0;

    XGoal         = GlobalBezier.P3.x;  //目标点
    YGoal         = GlobalBezier.P3.y;
    AngleGoal     = Anglewant;

    UpT = upt;
    DownT = downt;
    StartTurnT = startturnt;
    FullTurnT = fullturnt;

    BezierPIDGroup = pid_class;

    //数据输入有误处理
    if(UpT + DownT > 1)
    {
        BREAK_All_MOTOR;
        BeepOn;
        OSTaskSuspend(OS_PRIO_SELF);
        return;
    }
    if(StartTurnT + FullTurnT > 1)
    {
        BREAK_All_MOTOR;
        BeepOn;
        OSTaskSuspend(OS_PRIO_SELF);
        return;
    }
//  if(VStart>VWant)                    //如果开始速度大于中间速度
//  {
//      SpeedUpFlag = 0;                //则不需要加速
//      VStart=VWant;
//  }
//  if(VStop>VWant)                     //如果停止点的速度大于中间速度
//  {
//      SpeedDownFlag =0;               //则不需要减速
//      SpeedDownFlagVar =0;
//  }
//  if(SpeedUpFlag==0)                  //如果无加速过程
//  {
//          VStart = VWant;             //直接给VStart赋值目标速度
//  }

    CurrentV = VStart;                  //把速度赋初值
    SpeedWantSet.Vw = 0.0;
//    if(BezierPIDGroup == BPidGROUP3)
//        LockPoint.angle  = -180;
//    else
    LockPoint.angle  = AngleStart;    //保持姿态角不变

    Flag[LockPointOn] = 0;              //关闭位置锁定
    AutoRunType = runbezier;
    PidInit();                      //PID初始化
    Flag[KeepRun] = 1;                  //该标志位用于其他线程强制退出
    FREE_ALL_MOTOR;             //使能电机
    Flag[AutoRun] = 1;              //打开PID调节
    //这里要好好研究一下
    while((BPoint1.t < (1 - DeltaT)))
    {
//        if(fabs(fabs(ErrorCameraLine) - 30) > 1 && PositionNow.y > 1300)
//        {
//            MotorPosition(MotorFanHight, 5000, -2000);
//            OSSemPost(Task6Start);
//            return;
//        }
        if( (PositionNow.y > 1250) && (fabs(PositionNow.angle + 180) < 5) &&
            (Dt50ScanDistance < 72 || fabs(fabs(ErrorCameraLine) - 30) > 1) && (Switch_DT50Line==1))
        {
            MotorPosition(MotorFanHight, 5000, -2000);
            OSSemPost(Task6Start);
            return;
        }
				else if(fabs(fabs(ErrorCameraLine) - 30) > 1 && PositionNow.y > 1300 && Switch_DT50Line!=1)
        {
            MotorPosition(MotorFanHight, 5000, -2000);
            OSSemPost(Task6Start);
            return;
        }
        OSTimeDly(50);
    }
    BeepOn;
    if(Flag[RunContinue] == 0)
    {
        Flag[AutoRun] = 0; //关闭轨迹PID调节
        if(Flag[KeepRun])//如果是正常退出，即KeepRunFlag未被清零
        {
            SetLockPoint(XGoal, YGoal, AngleGoal);
        }
        Flag[LockPointOn] =
            1;                      //这里好像有bug，如果是非正常退出，锁点锁的是哪一个点？
        //VExSum=0.0;
    }
    Flag[AutoRun] =
        0;          //只关闭了轨迹PID调节，车还是会继续以最后一次的速度运行
}



void RunCamera(void)
{
    LockPoint.y = 1328;
    LockPoint.angle = -180;
    SpeedWantSet.Vy = 0;
    Flag[RunContinue] = 0;
    CurrentV = 150-20*Switch_SpeedDown;
    Flag[LockPointOn] = 0;              //关闭位置锁定
    AutoRunType = runcamera;
    PidInit();                      //PID初始化
    FREE_ALL_MOTOR;
    Flag[AutoRun] = 1;                  //打开PID调节
    Flag[KeepRun] = 1;
		if((KeyNumber & 0x07) == 6)
		   OSTimeDly(20000);
    while(fabs(SpeedAbsolute.Vx) > 30 &&
          GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_3) == 1 && Flag[InPoleSpeedDown]==0)
    {
        if((Flag[SearchLineSpeedDown] == 1 || PositionNow.x > 520) &&
           CurrentV > 100 )
        {
            CurrentV = 100;
        }
        OSTimeDly(50);
    }
    CurrentV = 50;

    
    MotorChangeMode(MotorFanCircle, ModePosition);
//    MotorPosition(MotorFanCircle, 4000, -111 * (90)*PlacePart);
    OSTimeDly(1000);
    while(fabs(SpeedAbsolute.Vx) > 30)
    {
        OSTimeDly(50);
    }

    if((KeyNumber & 0x07) != 6 || (KeyNumber & 0x07) != 7)
    {
			  OSSemPost(ElmoSpeed);
        Cylinder(CylinderHand | Cylinderbuffer, CylinderHandOpen | CylinderbufferOpen,
                 'W');
#if (PlacePart==BluePart)
        MotorPosition(MotorHeartHand, 6000, -8500);    
#else
        MotorPosition(MotorHeartHand, 6000, -90000);
#endif
    }
    if(Flag[RunContinue] == 0)
    {
        Flag[AutoRun] = 0; //关闭PID调节
        if(Flag[KeepRun])//如果是正常退出,即KeepRunFlag未被清零
        {
            SetLockPoint(PositionNow.x + 1, PositionNow.y, -180);
        }
        Flag[LockPointOn] = 1;
    }
    Flag[AutoRun] = 0;          //只关闭了PID调节，车还是会继续以最后一次的速度运行
}



void RunPointSpeedUp(void)
{
    float temp;
    if(fabs(CurrentV - VWant) > 0.1) //当前速度没有达到目标速度
    {
        temp = CountDistance(XStart, YStart, PositionNow.x, PositionNow.y);
        if(temp < UpDis) //行走距离小于加速距离，安以下算法进行加速
        {
            CurrentV = VStart - (VStart - VWant) * sqrt(temp / UpDis);
        }
        else
        {
            CurrentV = VWant;
            Flag[SpeedUp] = 0;
        }
    }
    else
    {
        CurrentV = VWant;
        Flag[SpeedUp] = 0;
    }
}

void RunPointSpeedDown(void)
{
    if(Flag[SpeedDownVar] == 1 &&
       (CountDistance(PositionNow.x, PositionNow.y, XGoal, YGoal) <= DownDis))
    {
        //存储刚开始减速时的坐标点与速度值
        VStartBrake = CurrentV;
        Flag[SpeedDownVar] = 0;
        Flag[SpeedUp] = 0; //关闭加速
    }
    if(Flag[SpeedDownVar] == 0) //按以下算法进行减速
    {
        CurrentV = VStop - (VStop - VStartBrake) * sqrt(CountDistance(PositionNow.x,
                   PositionNow.y, XGoal, YGoal) / DownDis);
    }
}

void TurnAngle(void)  //边直线行走边旋转的旋转子程序
{
    if(Flag[TurnVar] == 1 &&
       CountDistance(PositionNow.x, PositionNow.y, XStart, YStart) > StartTurnDis)
    {
        //到达旋转点，记录坐标
        XStartTurn = PositionNow.x;
        YStartTurn = PositionNow.y;
        Flag[TurnVar] = 0;
    }
    if(CountDistance(PositionNow.x, PositionNow.y, XStart,
                     YStart) > StartTurnDis + FullTurnDis)
    {
        Flag[Turn] = 0;
        LockPoint.angle = AngleGoal;
        return;
    }
    if(Flag[TurnVar] == 0) //安以下算法进行旋转处理，跟位移呈线性关系
    {
        LockPoint.angle = AngleStart + CountDistance(PositionNow.x, PositionNow.y,
                          XStartTurn, YStartTurn) * (AngleGoal - AngleStart) / FullTurnDis;
    }
}

void SetPointCurrentVBase(void) //设置PID调节之前的原始速度
{
    if(Flag[NoLineK])
    {
        SpeedWantSet.Vx = 0.0;
        if(YGoal > YStart)
        {
            SpeedWantSet.Vy = CurrentV;
        }
        else
        {
            SpeedWantSet.Vy = -CurrentV;
        }
    }
    else
    {
        if(XGoal > XStart)
        {
            SpeedWantSet.Vx = CurrentV * LineKCos;
            SpeedWantSet.Vy = CurrentV * LineKCos * LineK;
        }
        else
        {
            SpeedWantSet.Vx = -CurrentV * LineKCos;
            SpeedWantSet.Vy = -CurrentV * LineKCos * LineK;
        }

    }
}

void RunBezierSpeedUp(void)
{
    if(fabs(CurrentV - VWant) > 0.1) //当前速度没有达到目标速度
    {
        if(BPoint1.t < UpT) //行走距离小于加速距离，按一下算法进行加速
        {
            CurrentV = VStart - (VStart - VWant) * sqrt(BPoint1.t / UpT);
        }
        else
        {
            CurrentV = VWant;
            Flag[SpeedUp] = 0;
        }
    }
    else
    {
        CurrentV = VWant;
        Flag[SpeedUp] = 0;
    }
}

void RunBezierSpeedDown(void)
{
    if(Flag[SpeedDownVar] == 1 && ((1 - BPoint1.t) <= DownT))
    {
        //存储刚开始减速时的速度值
        VStartBrake = CurrentV;
        Flag[SpeedDownVar] = 0;
        Flag[SpeedUp] = 0; //关闭加速

        //计算减速中间变量
        //temp_speeddown2 = VStop*VStop;
        //temp_speeddown1 = temp_speeddown2-VStartBrake*VStartBrake;
    }
    if(Flag[SpeedDownVar] == 0) //匀减速
    {
        CurrentV = VStop - (VStop - VStartBrake) * sqrt((1 - BPoint1.t) / DownT);
        //CurrentV=sqrt(temp_speeddown2-temp_speeddown1 * ((1-BPoint1.t)/DownT));
    }
}

void Bezier_TurnAngle(void)
{
    static float t_StartTurn = 0.0;
    if((Flag[TurnVar] == 1) && (BPoint1.t > StartTurnT))
    {
        //到达旋转点，记录t值
        t_StartTurn = BPoint1.t;
        Flag[TurnVar] = 0;
    }
    if(BPoint1.t > StartTurnT + FullTurnT) //当前t大于转动结束时的t
    {
        Flag[Turn] = 0;
        LockPoint.angle = AngleGoal;
        return;
    }
    if(Flag[TurnVar] == 0) //按以下算法进行旋转处理，跟t呈线性关系
    {
        LockPoint.angle = AngleStart + (BPoint1.t - t_StartTurn) *
                          (AngleGoal - AngleStart) / FullTurnT;
    }
}


//计算中间两个控制点坐标
void CountBezierControlPoint(BEZIER *BezierLine)
{
    float temp1, temp2;
    temp1 = BezierLine->bezier_startangle * PI / 180;
    temp2 = BezierLine->bezier_endangle * PI / 180;
    BezierLine->P1.x = BezierLine->P0.x + BezierLine->length1 * cos(temp1);
    BezierLine->P1.y = BezierLine->P0.y + BezierLine->length1 * sin(temp1);

    BezierLine->P2.x = BezierLine->P3.x - BezierLine->length2 * cos(temp2);
    BezierLine->P2.y = BezierLine->P3.y - BezierLine->length2 * sin(temp2);
}


//简化参数方程系数
void CountBezierFunction(BEZIER *BezierLine)
{
    BezierLine->x_t0 =
        BezierLine->P0.x;                                                                                                                    //x参数方程中的t的0次项系数
    BezierLine->x_t1 = 3 * (BezierLine->P1.x -
                            BezierLine->P0.x);                                                                           //x参数方程中的t的1次项系数
    BezierLine->x_t2 = 3 * (BezierLine->P2.x - BezierLine->P1.x) -
                       BezierLine->x_t1;                              //x参数方程中的t的2次项系数
    BezierLine->x_t3 = BezierLine->P3.x - BezierLine->P0.x - BezierLine->x_t2 -
                       BezierLine->x_t1;   //x参数方程中的t的3次项系数

    BezierLine->y_t0 =
        BezierLine->P0.y;                                                                                                                    //Y参数方程中的t的0次项系数
    BezierLine->y_t1 = 3 * (BezierLine->P1.y -
                            BezierLine->P0.y);                                                                           //Y参数方程中的t的1次项系数
    BezierLine->y_t2 = 3 * (BezierLine->P2.y - BezierLine->P1.y) -
                       BezierLine->y_t1;                              //Y参数方程中的t的2次项系数
    BezierLine->y_t3 = BezierLine->P3.y - BezierLine->P0.y - BezierLine->y_t2 -
                       BezierLine->y_t1;   //Y参数方程中的t的3次项系数
}



void CountBezierXYbyT(BEZIER *BezierLine, POINTONBEZIER *BezierPoint)
{
    float temp1;
    float temp2;
    float temp3;
    temp1 = BezierPoint->t;     //一次方
    temp2 = temp1 * temp1;          //二次方
    temp3 = temp2 * temp1;          //三次方
    BezierPoint->x = BezierLine->x_t3 * temp3 + BezierLine->x_t2 * temp2 +
                     BezierLine->x_t1 * temp1 + BezierLine->x_t0;
    BezierPoint->y = BezierLine->y_t3 * temp3 + BezierLine->y_t2 * temp2 +
                     BezierLine->y_t1 * temp1 + BezierLine->y_t0;
}

//*******************************手动PID*******************************//
void SetCurrentPBase(void) //设置PID调节之前的原始位置
{
    if(Flag[NoLineK])
    {
        SpeedWantSet.Vx = 0.0;
        if(YGoal > YStart)
        {
            SpeedWantSet.Vy = CurrentV;
        }
        else
        {
            SpeedWantSet.Vy = -CurrentV;
        }
    }
    else
    {
        if(XGoal > XStart)
        {
            SpeedWantSet.Vx = CurrentV * LineKCos;
            SpeedWantSet.Vy = CurrentV * LineKCos * LineK;
        }
        else
        {
            SpeedWantSet.Vx = -CurrentV * LineKCos;
            SpeedWantSet.Vy = -CurrentV * LineKCos * LineK;
        }
    }
}


void SetBezier(float p0x, float p0y, float p3x, float p3y, float startangle,
               float endangle, float leng1, float leng2)
{
    GlobalBezier.bezier_endangle = endangle;
    GlobalBezier.bezier_startangle = startangle;
    GlobalBezier.length1 = leng1;
    GlobalBezier.length2 = leng2;
    GlobalBezier.P0.x = p0x;
    GlobalBezier.P0.y = p0y;
    GlobalBezier.P3.x = p3x;
    GlobalBezier.P3.y = p3y;
}



void SpeedChangeByCamera(float CurrentVOld1, float CurrentVOld2)
{
    float VBiggest = 0,Ek=0;
    float temp;
    temp = sqrt(SpeedAbsolute.Vy * SpeedAbsolute.Vy + SpeedAbsolute.Vx *
                SpeedAbsolute.Vx);

    VBiggest = (VWant > VStart) ? VWant : VStart;
    VBiggest = (VBiggest > VStop) ? VBiggest : VStop;

    if(CameraDistanceValue < 400)
    {
				Ek=0.8f * (830 - PositionNow.y) - 0.77f * (380 - CameraDistanceValue);
        CurrentV += Ek* 0.17f;  //850
				if(CurrentV<30 && Distance>400)
					CurrentV=50;
    }
    if(PositionNow.y > 865 && CameraDistanceValue < 380)
        CurrentV = 0;
    if((CameraDistanceValue >= 400 &&
        Flagu16[RiverTime] > RiverTimeDown - 100 * (Switch_Computer - 1) +
        Switch_SpeedDown * 50) ||
       (Flagu16[RiverTime] > RiverTimeLimit - 100 * (Switch_Computer - 1) +
        Switch_SpeedDown * 100 &&
        (KeyNumber & 0x07) != 3))
    {
        if(Flag[FanStop] == 0)
        {
            USART_SendData(UART4, '4');
            StartFan(0);
            Flag[FanStop] = 1;
            Flag[SpeedChange] = 0;
            Vmax = 390 + (Switch_DT50 - 1) * 140;
            Flag[Turn] = 0;
        }
        CurrentV = temp + 150-Switch_SpeedDown*80;
        LockPoint.angle = -90;
				MotorChangeMode(MotorFanCircle, ModePosition);
				MotorStop(MotorFanCircle);
        OSTaskSuspend(25);
				return;
    }
    if(CurrentV > temp + 100)
        CurrentV = temp + 100;

    CurrentV = (CurrentV + CurrentVOld1 + CurrentVOld2) / 3;
    if(CurrentV < 0)
        CurrentV = 0;
    if(CurrentV > VBiggest)
        CurrentV = VBiggest;
		
    if(!Switch_DT50 && Flag[FanStop] == 1)
        CurrentV = 0;
}


float PositionCarOld[5] = {0};
float CarSpeed = 0;
float CarSpeedOld[3] = {0};
float PositionCarOriginal = 0;
float MotorAngle[3];
float GetLittleCarPosition(float distance)
{
    float positiony, angle;
    if(Flag[CameraDistanceValeue] == 0)
        return 1;
    positiony = PositionNow.y + 52.3 * sin(PositionNow.angle / 180 * PI) + distance
                * sin((PositionNow.angle + 90 + MotorRealPosition.FanCircle / 111) / 180 * PI);
    PositionCarOriginal = positiony;

    if(PositionCarOld[0] > 1 && PositionCarOld[1] > 1 && PositionCarOld[2] > 1)
    {
        positiony = (positiony + PositionCarOld[0] + PositionCarOld[1] -
                     PositionCarOld[2]) / 2;
    }


    PositionCarOld[4] = PositionCarOld[3];
    PositionCarOld[3] = PositionCarOld[2];
    PositionCarOld[2] = PositionCarOld[1];
    PositionCarOld[1] = PositionCarOld[0];
    PositionCarOld[0] = positiony;


    if(positiony > 635.0f) //685
    {
        LittleCarPosition = PositionSix;
    }
    else if(positiony > 565)
    {
        LittleCarPosition = PositionFive;
        angle = 15;
    }
    else if(positiony > 449)
    {
        LittleCarPosition = PositionFour;
        angle = 30;
    }
    else if(positiony > 366)
    {
        LittleCarPosition = PositionThree;
        angle = 45;
    }
    else if(positiony > 273)
    {
        LittleCarPosition = PositionTwo;
        angle = 30;
    }
    else if(positiony > 145)
    {
        LittleCarPosition = PositionOne;
        angle = 15;
    }


    if(PositionCarOld[0] > 1 && PositionCarOld[1] > 1)
    {
        CarSpeed = (PositionCarOld[0] - PositionCarOld[4]);
        CarSpeed = CarSpeed / cos(angle / 180 * PI);
//      if(CarSpeed<0)
//          CarSpeed=0;

        if(CarSpeedOld[0] > 1 && CarSpeedOld[1] > 1 && CarSpeedOld[2] > 1)
            CarSpeed = (CarSpeed * 0.5f + CarSpeedOld[0] * 0.25f + CarSpeedOld[1] * 0.15f +
                        CarSpeedOld[2] * 0.1f);

        CarSpeedOld[2] = CarSpeedOld[1];
        CarSpeedOld[1] = CarSpeedOld[0];
        CarSpeedOld[0] = CarSpeed;
    }
    return PositionCarOriginal;
}


//**************************************************************************

//计算两个向量的数量级
float CountTwoVector(POSI *vector1, POSI *vector2)
{
    float temp;
    temp = vector1->x * vector2->x + vector1->y * vector2->y;
    return temp;
}

float CountDistance(float x_from, float y_from, float x_to, float y_to)
{
    float distance_count = 0;
    distance_count = sqrt((x_to - x_from) * (x_to - x_from) + (y_to - y_from) *
                          (y_to - y_from));
    return distance_count;
}
