#include "exti.h"


void EXTI9_5_IRQHandler(void)
{
    delay_ms(10);   //消抖
    if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6))
    {
        BREAK_All_MOTOR;
        MotorStop(MotorHeartHand);
        MotorStop(MotorFanHight);
        MotorStop(MotorFanCircle);
        MotorStop(MotorSetHeart);
        StartFan(0);
        OSTaskSuspend(5);
        Vmax = 0;
    }
    EXTI_ClearITPendingBit(EXTI_Line6);
    EXTI_ClearFlag(EXTI_Line6);
}


void EXTI15_10_IRQHandler(void)
{
    delay_ms(10);   //消抖
    if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
    {
        BREAK_All_MOTOR;
        Cylinder(CylinderClimbTwoMotor | CylinderClimbOneMotor,
                 CylinderClimbTwoClose | CylinderClimbOneClose, 'W');
        StartFan(0);
        OSTaskSuspend(15);
    }
    EXTI_ClearITPendingBit(EXTI_Line10);//清除LINE2上的中断标志位
    EXTI_ClearFlag(EXTI_Line10);
}

//外部中断初始化程序
//初始化 PG2 为中断输入.
void exti_init(void)
{
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
    EXTI_InitTypeDef  exti;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //使能 GPIOG 时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //使能 GPIOG 时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //使能 GPIOG 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能 SYSCFG 时钟

    gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_2;                  //KEY0 对应引脚
    gpio.GPIO_Mode = GPIO_Mode_IN;                //普通输入模式
    gpio.GPIO_Speed = GPIO_Speed_100MHz;  //100M
    gpio.GPIO_PuPd = GPIO_PuPd_UP;                //上拉
    GPIO_Init(GPIOG, &gpio);                          //初始化GPIOG2

    gpio.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOF, &gpio);

    gpio.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &gpio);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);
    /* 配置EXTI_Line2 */
    exti.EXTI_Line = EXTI_Line4;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
    exti.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
    exti.EXTI_LineCmd = ENABLE;//中断线使能
    EXTI_Init(&exti);//配置

    exti.EXTI_Line = EXTI_Line2;
    EXTI_Init(&exti);//配置

    exti.EXTI_Line = EXTI_Line6;
    EXTI_Init(&exti);//配置

    exti.EXTI_Line = EXTI_Line10;
    EXTI_Init(&exti);//配置

    nvic.NVIC_IRQChannel = EXTI4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 3;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);//配置

    nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&nvic);//配置

    nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&nvic);//配置
//
    nvic.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
    NVIC_Init(&nvic);//配置
}
