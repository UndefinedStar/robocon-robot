#ifndef __LED_H
#define __LEd_H
//±‹√‚÷ÿ∏¥∂®“Â
#include "stm32f10x.h"
#define ON 1
#define OFF 0
#define LED1(a) 			if(a)\
											GPIO_SetBits(GPIOB,GPIO_Pin_0);\
											else GPIO_ResetBits(GPIOB,GPIO_Pin_0) 

#define LED2(a) 			if(a)\
											GPIO_SetBits(GPIOC,GPIO_Pin_0);\
											else GPIO_ResetBits(GPIOC,GPIO_Pin_0) 
												
//#define LED3(a) 			if(a)\
										//	GPIO_SetBits(GPIOC,GPIO_Pin_5);\
										//	else GPIO_ResetBits(GPIOC,GPIO_Pin_5) 
											
void LED_GPIO_Config(void);


#endif/*__LED_H*/
