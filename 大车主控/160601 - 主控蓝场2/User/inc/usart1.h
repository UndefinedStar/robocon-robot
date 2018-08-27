#ifndef _USART1_H
#define _USART1_H

#include "queue.h"
#include "stm32f4xx.h"
#include "stdarg.h"
#include "stdio.h"
#include "led.h"
#include <stdlib.h>
#include "includes.h"
#include "flash.h"
#include "can2.h"
#include "Usart2.h"
#include "Usart4.h"

extern INT8U *Pflagserr1;
extern OS_EVENT *Pevent2;
extern OS_FLAG_GRP *Pgrp1;
extern INT8U *Peventerr2;

void USART1_sendData(u8 *a,u8 count);
void usart_config(void);


#endif


