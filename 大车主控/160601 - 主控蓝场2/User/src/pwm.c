#include "pwm.h"

/*
****************************************
* Name : PWM_configuration
* Describe : 初始化时钟输出pwm波
* Input : None
* Output : None
* Return : None
****************************************
*/
void PWM_configuration(void)
{
	TIM_TimeBaseInitTypeDef  tim;
	TIM_OCInitTypeDef        oc;
  GPIO_InitTypeDef         gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOC ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM3, ENABLE);	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);                  //复用IO口
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

  gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOD, &gpio);
    
	tim.TIM_Prescaler = 336-1;                               //频率:500hz
	tim.TIM_Period = 2000;	 				
	tim.TIM_ClockDivision = 0;
	tim.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &tim);
	TIM_TimeBaseInit(TIM4, &tim);
	
	oc.TIM_OCMode = TIM_OCMode_PWM2;
  oc.TIM_OutputState = TIM_OutputState_Enable;
  oc.TIM_OutputNState = TIM_OutputNState_Disable;
	oc.TIM_Pulse =1000;
	oc.TIM_OCPolarity = TIM_OCPolarity_Low;
  oc.TIM_OCNPolarity = TIM_OCPolarity_High;
  oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
  oc.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM3, &oc);
	TIM_OC2Init(TIM3, &oc);
	TIM_OC1Init(TIM4, &oc);
	TIM_OC2Init(TIM4, &oc);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_CtrlPWMOutputs(TIM3,ENABLE); 
	TIM_CtrlPWMOutputs(TIM4,ENABLE); 
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

/*
****************************************
* Name : PWM_set
* Describe : 改变四个通道中某一个的pwm
						 波占空比来改变转速
* Input : PWM_Channel  pwm输出通道
					give_pulse   输入捕获通道的设定值
* Output : None
* Return : None
****************************************
*/
void PWM_set(u8 PWM_Channel,u16 give_pulse)
{
	if(give_pulse>1900 && give_pulse<100)
		return;
	switch(PWM_Channel)
	{
		case PWM_Channel_4:
			TIM3->CCR1=give_pulse;
			break;
		case PWM_Channel_3:
			TIM3->CCR2=give_pulse;
			break;
	 	case PWM_Channel_1:
			TIM4->CCR1=give_pulse;
			break;
		case PWM_Channel_2:
			TIM4->CCR2=give_pulse;
			break;
		default:
			break;
  }
}



/*
**********************************************
* Name : BreakIO_configuration
* Describe : 初始化急停功能IO口，低电平有效
* Input : None
* Output : None
* Return : None
**********************************************
*/
void BreakIO_configuration(void)
{
	GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	gpio.GPIO_Pin =GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8 ;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOG,&gpio);
	
	GPIO_ResetBits(GPIOG, GPIO_Pin_5);
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	GPIO_ResetBits(GPIOG, GPIO_Pin_7);
	GPIO_ResetBits(GPIOG, GPIO_Pin_8);
}

