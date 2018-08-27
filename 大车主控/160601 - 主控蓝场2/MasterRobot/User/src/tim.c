#include "tim.h"


void Tim2Configuration(void)
{
		TIM_TimeBaseInitTypeDef  tim;
	  NVIC_InitTypeDef         nvic;
		
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    nvic.NVIC_IRQChannel = TIM2_IRQn;
	  nvic.NVIC_IRQChannelPreemptionPriority = 3;
   	nvic.NVIC_IRQChannelSubPriority = 3;
  	nvic.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&nvic);	
	
		tim.TIM_Prescaler = 84-1;                               //84MHZ
	  tim.TIM_Period = 1500;	 				
	  tim.TIM_ClockDivision = 0;
	  tim.TIM_CounterMode = TIM_CounterMode_Up;
	  TIM_TimeBaseInit(TIM2,&tim);
	
	  TIM_ARRPreloadConfig(TIM2, ENABLE);
  	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	  TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	
}


#if Switch_CanReturn
u16 CanGroup;
u16 CanGroupTime;
#endif

void TIM2_IRQHandler(void)
{
		#if Switch_CanReturn
		u16 a=0;
	  u8 i=0;
	  #endif
	  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
		{
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			Flagu16[PositionTime]++;
			if(Flagu16[PositionTime]>10)
			{
				Flagu16[PositionTime]=0;
				BREAK_All_MOTOR;
			}
			#if Switch_CanReturn
			 a=CanGroup;
			 CanGroupTime&=CanGroup;
			 if(a==0)
				 return;
				
			 for(i=0;i<16;i++)
			 {
					 if((a&0x01)!=0)
					 {
						 if((CanGroupTime&(0x01<<i))==0)
							 CanGroupTime|=(0x01<<i);
						 else
						 {
							 Can_PutToQueue(&CanHaveSend[i]);
							 //重新再发一遍报文
							 CanGroupTime&=(~(0x01<<i));
						 }						 
					 }
					 a=a>>1;
		   }			
			#endif	
		}
}



