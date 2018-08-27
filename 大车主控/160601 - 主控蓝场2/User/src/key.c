#include "key.h"

void Key_Configuration(void)
{
		GPIO_InitTypeDef gpio;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
		GPIO_DeInit(GPIOG);
		
		gpio.GPIO_Mode=GPIO_Mode_IN;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin= GPIO_Pin_5;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOG,&gpio);
	
		#if (Switch_Exti==0)
			gpio.GPIO_Mode=GPIO_Mode_IN;
			gpio.GPIO_OType=GPIO_OType_PP;
			gpio.GPIO_Pin= GPIO_Pin_2 | GPIO_Pin_4;
			gpio.GPIO_Speed=GPIO_Speed_2MHz;
			gpio.GPIO_PuPd=GPIO_PuPd_UP;
			GPIO_Init(GPIOG,&gpio);
	
			
	  #endif
		
		gpio.GPIO_Pin=GPIO_Pin_3;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOG,&gpio);
	
  	gpio.GPIO_Mode=GPIO_Mode_OUT;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin=GPIO_Pin_10;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOG,&gpio);

		
	  GPIO_ResetBits(GPIOG,GPIO_Pin_10);
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);       //ÊÖ±úI/O¿Ú
		
		GPIO_DeInit(GPIOF);
		
		gpio.GPIO_Mode=GPIO_Mode_IN;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOF,&gpio);
	
		GPIO_SetBits(GPIOF,GPIO_Pin_6);
	  GPIO_SetBits(GPIOF,GPIO_Pin_11);
		GPIO_SetBits(GPIOF,GPIO_Pin_12);
		GPIO_SetBits(GPIOF,GPIO_Pin_13);
		GPIO_SetBits(GPIOF,GPIO_Pin_14);
		
		/*¾ØÕó¼üÅÌ³õÊ¼»¯*/
		gpio.GPIO_Mode=GPIO_Mode_OUT;
		gpio.GPIO_OType=GPIO_OType_OD;
		gpio.GPIO_Pin=GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		gpio.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOG,&gpio);
		
//		GPIO_DeInit(GPIOC);
//	  GPIO_DeInit(GPIOD);
		
		gpio.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13;
		GPIO_Init(GPIOD,&gpio);
		
		gpio.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOC,&gpio);
		
		RowOut;
		RowLow;
		CoulumIn;
		
		/*¼±Í£*/
		gpio.GPIO_Mode=GPIO_Mode_OUT;
		gpio.GPIO_OType=GPIO_OType_PP;
		gpio.GPIO_Pin= GPIO_Pin_2;
		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		gpio.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOC,&gpio);
		
		BREAK_All_MOTOR;
		
}

