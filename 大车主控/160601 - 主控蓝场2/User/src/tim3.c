#include "tim3.h"

void Tim3Configuration(void)
{
		TIM_TimeBaseInitTypeDef  tim;
	  NVIC_InitTypeDef         nvic;
		
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    nvic.NVIC_IRQChannel = TIM2_IRQn;
	  nvic.NVIC_IRQChannelPreemptionPriority = 1;
   	nvic.NVIC_IRQChannelSubPriority = 1;
  	nvic.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&nvic);	
	
		tim.TIM_Prescaler = 336-1;                               //84MHZ
	  tim.TIM_Period = 25;	 				
	  tim.TIM_ClockDivision = 0;
	  tim.TIM_CounterMode = TIM_CounterMode_Up;
	  TIM_TimeBaseInit(TIM3,&tim);
	
	  TIM_ARRPreloadConfig(TIM3, ENABLE);
  	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	  TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
	  TIM_Cmd(TIM3, ENABLE);	 	
}




void TIM3_IRQHandler(void)
{
	  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) 
		{
			 TIM_ClearFlag(TIM3, TIM_FLAG_Update);		
			 
		}
}
