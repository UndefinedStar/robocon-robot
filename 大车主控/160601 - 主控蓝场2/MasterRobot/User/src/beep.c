#include "beep.h"

void Beep_Configuration(void)
{
		GPIO_InitTypeDef gpio;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		
		GPIO_DeInit(GPIOD);
		
		gpio.GPIO_Mode=GPIO_Mode_OUT;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin=GPIO_Pin_11;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		
		GPIO_Init(GPIOD,&gpio);
	
		BeepOff;
}

void beep_show(u8 num)
{
	u8 i;
	for(i=0; i<num; i++)
	{
		BeepOn;
		delay_ms(100);
		BeepOff;
		delay_ms(100);
	}
}
