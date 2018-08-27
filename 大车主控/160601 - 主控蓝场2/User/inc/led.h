#ifndef _LED_H
#define _LED_H

#define LED_BlueOff     GPIO_SetBits(GPIOF, GPIO_Pin_4);
#define LED_PowerOff 		GPIO_SetBits(GPIOA,GPIO_Pin_15);
#define LED_GreenOff  	GPIO_SetBits(GPIOE, GPIO_Pin_6);
#define LED_YellowOff  	GPIO_SetBits(GPIOF, GPIO_Pin_2);
#define LED_RedOff  		GPIO_SetBits(GPIOC, GPIO_Pin_14);

#define LED_BlueOn   		GPIO_ResetBits(GPIOF,GPIO_Pin_4);
#define LED_PowerOn  		GPIO_ResetBits(GPIOA,GPIO_Pin_15);
#define LED_GreenOn   	GPIO_ResetBits(GPIOE,GPIO_Pin_6);
#define LED_YellowOn   	GPIO_ResetBits(GPIOF,GPIO_Pin_2);
#define LED_RedOn   		GPIO_ResetBits(GPIOC,GPIO_Pin_14);

#define LED_TOGGLE					GPIO_ToggleBits(GPIOA, GPIO_Pin_15) 	
#define LED_RED_TOGGLE			GPIO_ToggleBits(GPIOC, GPIO_Pin_14);
#define LED_YELLOW_TOGGLE 	GPIO_ToggleBits(GPIOF, GPIO_Pin_2);	
#define LED_BLUE_TOGGLE			GPIO_ToggleBits(GPIOF, GPIO_Pin_4);
#define LED_GREEN_TOGGLE		GPIO_ToggleBits(GPIOE, GPIO_Pin_6);		

void LED_Configuration(void);

#endif
