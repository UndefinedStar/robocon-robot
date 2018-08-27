/*
 * User_EEPROM.h
 *
 *  Created on: 2014-2-23
 *      Author: John
 */

#ifndef USER_EEPROM_H_
#define USER_EEPROM_H_

#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "pid.h"
#include "MyDataProcess.h"

#define IIC_DELAY_TIME 100 //延时时间可以根据具体情况稍作修改
#define DataHigh    GPIO_SetBits(GPIOE,GPIO_Pin_1)
#define DataLow     GPIO_ResetBits(GPIOE,GPIO_Pin_1)
#define CLKHigh     GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define CLKLow      GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define DataIn	    GPIOE->MODER&=0xFFF3
#define DataOut	    GPIOE->MODER|=0x04
#define DataRead    GPIOE->IDR & GPIO_Pin_1
#define ChipAdress  0xA0

void Init24C256(void);
void iic_start(void);
void iic_stop(void);
void iic_ack(unsigned char dat);
unsigned char IicSendByte(unsigned char wdata);
unsigned char IicRevByte(void);

void _24C256_WriteStr(unsigned char add,unsigned int add_s,unsigned char *s,unsigned char num);
void _24C256_ReadStr(unsigned char add,unsigned int add_s,unsigned char *s,unsigned char num);
void _24C256_SaveFloatData(unsigned int add_s,float dat);
float _24C256_ReadFloatData(unsigned int add_s);
void _24C256_SaveIntData(unsigned int add_s,int dat);
int _24C256_ReadIntData(unsigned int add_s);
void  _24C256_SaveLongData(unsigned int add_s,long dat);
long  _24C256_ReadLongData(unsigned int add_s);
void _24C256_ReadFloatDataStr(unsigned int add_start,unsigned char num);


#endif /* USER_EEPROM_H_ */
