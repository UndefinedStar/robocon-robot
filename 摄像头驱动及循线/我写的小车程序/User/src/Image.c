#include "Image.h"
#include "OV7725.h"

u8 Fabs(u8 Pixel)
{
	if(Pixel < 0)
	{
		Pixel = -Pixel;
	}
	else
	{
		Pixel = Pixel;
	}
}

/****************************************************************************
*函数名称: void Transfer2Gray(uint16_t * image,uint8_t  * ccm_image)
*函数功能：YUV422提取8位Y分量，获取灰度图，亮度图
*输入参数：原始图像信息*image,*gray_image用来存储当前图像
****************************************************************************/

void Transfer1Gray(uint16_t *image , uint8_t  *gray_image)
{
	uint32_t i = 0;
	uint32_t j = 0;
	
	for(i = 0 ; i < Row ; i++)
	{
		
		for(j = 0 ; j < Column ; j++)
		{			
			
			*((uint8_t *)gray_image + i*Column + j) = (uint8_t)((*((uint16_t *)image + i*4*IMAGE_COLUMN + j*4)) >> 8);
			
		}
		
 	}			 
	
}


//void Transfer3Gray(uint16_t * image,uint8_t  * gray_image,uint32_t image_size)          //最大输出RGB格式时使用
//{
//    uint16_t image_selection = 0xff;
//    uint8_t  image_shift = 0;
//    uint32_t i = 0;
//		image_selection = 0xff00;
//		image_shift = 8;	
//		for (i= 0; i < image_size; i++)				//提取出8位的Y通道值，即为灰度图
//		{   
//				*((uint8_t *)gray_image + i) = (uint8_t)((*((uint16_t *)image + i) & image_selection) >> image_shift);
//		}

//}

void Twovalue_Processing(u8 *Gray_Image_Buffer)
{
	uint32_t i = 0;
	uint32_t j = 0;
  int err1 = 0 , err2 = 0;
	int leftvalue = 0;
	int rightvalue = 0;
	
	for(i = 0 ; i < Row ; i++)
	{
		
		for(j = 1 ; j < Column ; j++)
		{			
			
			err1 = Gray_Image_Buffer[i*Column + j] - Gray_Image_Buffer[i*Column + j - 2] ;
			if(err1 >= 20)
			{
				leftvalue = Gray_Image_Buffer[i*Column + j - 2] + 5;
			}
			
			err2 = Gray_Image_Buffer[i*Column + j] - Gray_Image_Buffer[i*Column + j - 2] ;
			if(err2 <= -20)
			{
				rightvalue = Gray_Image_Buffer[i*Column + j] ;
			}
			
		}
		
	}
		
}






