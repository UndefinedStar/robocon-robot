#include "hcsr04.h"
#include "delay.h"
#include "GUI_32.h"

extern uint16_t Time;
int overflow=0;  //用于检测是否定时器已经溢出
#define ECHO_PIN GPIO_Pin_0
#define ECHO_GPIO GPIOA,GPIO_Pin_0

#define TRIG_PIN GPIO_Pin_5
#define TRIG_GPIO GPIOA,GPIO_Pin_5

void Hcsr04_Init(void)
{
  
  Hcsr04_GPIO_Configuration();
  TIM_Configuration();
	Hcsr04_NVIC_Configuration();
}

float Read_hcs04()
{
  float result=0;
	result=Sensor_using();
	if(result>=object_distance)
	{
	  GPIO_SetBits(ECHO_GPIO);
	  GPIO_ResetBits(TRIG_GPIO);
	}
	else if (result<object_distance && result!=0.0)
	{
	  GPIO_SetBits(TRIG_GPIO);
	  GPIO_ResetBits(ECHO_GPIO);
	}
	else
	{
	  GPIO_ResetBits(ECHO_GPIO);
	  GPIO_ResetBits(TRIG_GPIO);
	}
  return result;
}


void Hcsr04_NVIC_Configuration(void)
{
  /*CAN receive interrupt enable*/
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Hcsr04_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  /*Echo pin define*/
  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /*Trigle pin define*/
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
}

void TIM_Configuration(void)
{
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  TIM_DeInit(TIM1);

  TIM_TimeBaseStructure.TIM_Period=0xffff;
  TIM_TimeBaseStructure.TIM_Prescaler=0;
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_PrescalerConfig(TIM1,7219,TIM_PSCReloadMode_Immediate);//时钟频率为72MHz/(359+1)=200000
  TIM_ARRPreloadConfig(TIM1, DISABLE);
  //TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
  TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
  TIM_Cmd(TIM1, DISABLE);
}

/*毫米级*/
float Sensor_using(void)
{
  float distance=0;
  u16 TIM=0;
  
  GPIO_SetBits(TRIG_GPIO);
  delay_us(12);
  GPIO_ResetBits(TRIG_GPIO);
	
	GPIO_ResetBits(ECHO_GPIO);
  
  TIM_Cmd(TIM1, ENABLE);
  while(!GPIO_ReadInputDataBit(ECHO_GPIO)&& overflow==0 );
  TIM1->CNT=0;
  while(GPIO_ReadInputDataBit(ECHO_GPIO)&& overflow==0 );
  TIM_Cmd(TIM1, DISABLE);
  
  if(overflow!=0)
  {
	overflow=0;
	return 0.0;
  }
  TIM=TIM_GetCounter(TIM1);
  distance=(float)sqrt((TIM/20.0*17)*(TIM/20.0*17)-module_interval*module_interval/4.0)+12.0; //12.0为误差补偿
  
  return(distance);
}

void delay_t(void)
{
  u32 i;
  i=100000;
  while(i--);
}

void Time_Start()
{
	  TIM_Cmd(TIM1, ENABLE);
   Time=TIM1->CNT;
}

void Time_Stop()
{
	//		TIM_Cmd(TIM1, DISABLE);
		Time=TIM1->CNT-Time;
		EXTI->IMR&=~(1<<4);	 //静止外部中断
		EXTI->EMR&=~(1<<4);
		GUI_clearscreen(0XFFFF);
		while(1)
		{
			GUI_wrul(100,100,Time,0x0000,0xffff);
  	}
}