#ifndef HCSR04_H
#define HCSR04_H

#include "stm32f10x.h"
#include <math.h>
//#include "private_delay.h"
#define module_interval 25    //定义超声波模块接收发射端间距(单位:mm)
#define object_distance 100.0   //检测物理的距离
void Hcsr04_Init(void);
void Hcsr04_NVIC_Configuration(void);
void TIM_Configuration(void);
void Hcsr04_GPIO_Configuration(void);
float Sensor_using(void);
void delay_t(void);
float Read_hcs04(void);
void Time_Start(void);
void Time_Stop(void);
extern int overflow;
#endif

