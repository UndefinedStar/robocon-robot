#ifndef __FIFO_H
#define __FIFO_H

#include "stm32f10x.h"
#include "sys.h"

void fifo_init(void);//��дָ���ʼ��
void fifo_wrst(void);
void fifo_rrst(void);
#endif
