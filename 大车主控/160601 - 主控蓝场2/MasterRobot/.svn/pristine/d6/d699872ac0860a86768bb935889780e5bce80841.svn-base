#include "usb.h"

/*
****************************************
* Name : USB_Configuration
* Describe : ≥ı ºªØledµ∆
* Input : None
* Output : None
* Return : None
****************************************
*/
void USB_Configuration(void)
{
		GPIO_InitTypeDef gpio;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
		GPIO_DeInit(GPIOG);
		
		gpio.GPIO_Mode=GPIO_Mode_OUT;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin=GPIO_Pin_10;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOG,&gpio);
	
	  GPIO_ResetBits(GPIOG,GPIO_Pin_10);
		
}