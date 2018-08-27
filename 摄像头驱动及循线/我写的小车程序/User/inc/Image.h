#ifndef _IMAGE_H
#define _IMAGE_H

#include "stm32f4xx.h"

#include "math.h"

#define IMAGE_COLUMN 320
#define IMAGE_ROW    200

#define Column 80
#define Row 50

#define FirstRow_StandardStation 80



u8 Fabs(u8 Pixel);
void Transfer3Gray(uint16_t * image,uint8_t  * gray_image,uint32_t image_size);
void Transfer2Gray(uint16_t *image,uint8_t  *gray_image);
void Transfer1Gray(uint16_t *image,uint8_t  *gray_image);

void Common_Two_ValuedProcessing(uint8_t *Gray_Image_Buffer);

void Remove_Disturbs(uint8_t *Gray_Image_Buffer , int i , int j );
void Find_FirstRow_WhiteMid(uint8_t *Gray_Image_Buffer );
void Find_SecondRow_WhiteMid (  uint8_t *Gray_Image_Buffer );
void Find_ThirdRow_WhiteMid (  uint8_t *Gray_Image_Buffer );
void Find_BehindRow_WhiteMid (  uint8_t *Gray_Image_Buffer );

void Turn_Right(  uint8_t *Gray_Image_Buffer );
void Find_White(  uint8_t *Gray_Image_Buffer);

void Through_the_Triangle( uint8_t *Gray_Image_Buffer );
	
extern int FirstRow_WhiteMid_Station ;
extern int SecondRow_WhiteMid_Station ;
extern int ThirdRow_WhiteMid_Station ;
extern int BehindRow_WhiteMid_Station  ;
extern int lost_image_flag ;
extern int WhiteLine  ;
extern int Triangle_Right_Flag ;
#endif


























