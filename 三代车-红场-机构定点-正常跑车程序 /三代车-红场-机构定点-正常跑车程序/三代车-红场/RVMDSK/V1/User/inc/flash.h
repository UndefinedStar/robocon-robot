#ifndef __FLASH_H__
#define __FLASH_H__

#include "stm32f4xx.h"
#include "usart2.h"
#include "stm32f4xx_flash.h"

void Flash_Write_Word(uint32_t Address,uint32_t Data);
void Flash_Write_HalfWord(uint32_t Address,uint16_t Data);
void Flash_Erase_Page(uint16_t FLASH_Sector);
	uint16_t Flash_Read_HalfWord(uint32_t Address);		 // 为我所改动 原为	uint32_t

void Flash_Write_check(void);
void Flash_Write_all(void);
void Flash_Write(void);

void Flash_Read_check(void);
void Flash_Read_all(void);
void Flash_Read(void);

extern u8 flash_first_flag;


#endif




