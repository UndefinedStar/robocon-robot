#include "exti.h"


void EXTI9_5_IRQHandler(void)
{
    delay_ms(10);   //����
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
    delay_ms(10);   //����
    if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
    {
        BREAK_All_MOTOR;
        Cylinder(CylinderClimbTwoMotor | CylinderClimbOneMotor,
                 CylinderClimbTwoClose | CylinderClimbOneClose, 'W');
        StartFan(0);
        OSTaskSuspend(15);
    }
    EXTI_ClearITPendingBit(EXTI_Line10);//���LINE2�ϵ��жϱ�־λ
    EXTI_ClearFlag(EXTI_Line10);
}

//�ⲿ�жϳ�ʼ������
//��ʼ�� PG2 Ϊ�ж�����.
void exti_init(void)
{
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
    EXTI_InitTypeDef  exti;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //ʹ�� GPIOG ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //ʹ�� GPIOG ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //ʹ�� GPIOG ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ�� SYSCFG ʱ��

    gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_2;                  //KEY0 ��Ӧ����
    gpio.GPIO_Mode = GPIO_Mode_IN;                //��ͨ����ģʽ
    gpio.GPIO_Speed = GPIO_Speed_100MHz;  //100M
    gpio.GPIO_PuPd = GPIO_PuPd_UP;                //����
    GPIO_Init(GPIOG, &gpio);                          //��ʼ��GPIOG2

    gpio.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOF, &gpio);

    gpio.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &gpio);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);
    /* ����EXTI_Line2 */
    exti.EXTI_Line = EXTI_Line4;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
    exti.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
    exti.EXTI_LineCmd = ENABLE;//�ж���ʹ��
    EXTI_Init(&exti);//����

    exti.EXTI_Line = EXTI_Line2;
    EXTI_Init(&exti);//����

    exti.EXTI_Line = EXTI_Line6;
    EXTI_Init(&exti);//����

    exti.EXTI_Line = EXTI_Line10;
    EXTI_Init(&exti);//����

    nvic.NVIC_IRQChannel = EXTI4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 3;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);//����

    nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&nvic);//����

    nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&nvic);//����
//
    nvic.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
    NVIC_Init(&nvic);//����
}
