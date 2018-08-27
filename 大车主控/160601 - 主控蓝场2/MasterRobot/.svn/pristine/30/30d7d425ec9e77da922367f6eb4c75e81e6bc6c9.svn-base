#include "led.h"
#include "stm32f4xx.h"

/*
****************************************
* Name : Led_configuration
* Describe : ≥ı ºªØledµ∆
* Input : None
* Output : None
* Return : None
****************************************
*/
void LED_Configuration(void)
{
		GPIO_InitTypeDef gpio;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
		GPIO_DeInit(GPIOF);
		GPIO_DeInit(GPIOA);
		GPIO_DeInit(GPIOC);
		GPIO_DeInit(GPIOE);
		
		gpio.GPIO_Mode=GPIO_Mode_OUT;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin=GPIO_Pin_2 | GPIO_Pin_4;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		GPIO_Init(GPIOF,&gpio);
	
		gpio.GPIO_Pin=GPIO_Pin_15;
		GPIO_Init(GPIOA,&gpio);
	
		gpio.GPIO_Pin=GPIO_Pin_14;
		GPIO_Init(GPIOC,&gpio);
		
		gpio.GPIO_Pin=GPIO_Pin_6;
		GPIO_Init(GPIOE,&gpio);
		
		LED_BlueOff;
		LED_PowerOff;
		LED_GreenOff;
		LED_YellowOff;
		LED_RedOff;
		
}

