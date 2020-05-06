#ifndef _OV7725_H
#define _OV7725_H

#include "ili9325.h"
#include "delay.h"
#include "stm32f4xx_dcmi.h"
#include "image.h"
#include "sccb.h"
#include "OV_Config.h"
#define OV7725YUV


extern u16 image[IMAGE_COLUMN * IMAGE_ROW];
extern uint8_t * Gray_Image_Buffer;

u8 OV_Init(void);
u8 OV_Init2(void);
void OV_Start(void);
void OV_Stop(void);
void OV_DCMI_DMA_Init(uint32_t address, uint16_t buffer_size);

#endif

