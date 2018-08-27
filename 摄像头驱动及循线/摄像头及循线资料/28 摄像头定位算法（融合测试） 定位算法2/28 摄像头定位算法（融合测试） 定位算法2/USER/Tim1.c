#include "Tim1.h"

int overflow=0;  //���ڼ���Ƿ�ʱ���Ѿ����

void TIM1_Init(void)
{
  
  TIM_Configuration();
	//TIM1_NVIC_Configuration(); ��ʱ����Ҫ
}



void TIM1_NVIC_Configuration(void)
{
  /*CAN receive interrupt enable*/
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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
	
  TIM_PrescalerConfig(TIM1,359,TIM_PSCReloadMode_Immediate);//ʱ��Ƶ��Ϊ72MHz/(359+1)=200000
  TIM_ARRPreloadConfig(TIM1, ENABLE);
  //TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
  //TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}
