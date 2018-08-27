#include "main.h"

u8 UpdataTFT_flag = 0;


int main()
{

	SystemInit();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Led_Config();
	ili9320_Initializtion();
	Can1_Configuration();
	while(OV_Init()==1)			
	{
		LED_TOGLE();
		delay_ms(50);
	}												//OV7725初始化
	LED_OFF();
	delay_ms(200);
	OV_Start();

	while(1)
	{

		if(UpdataTFT_flag != 0)
		{

			Transfer1Gray(Image, Gray_Image_Buffer);		//  YUV422格式转化为灰度图，或亮度图							
      Picture_Display();                                //显示图像
			
			SendPulse(Pulse);                                 //小车偏右白线中点位置偏小，偏左则偏大
			UpdataTFT_flag--;                                 //清除标志位

		}

  }	

}


//一张图片传输完成，场中断
void DMA2_Stream1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1))
  {
		DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1);
    DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);
		DCMI_CaptureCmd(DISABLE);			
		UpdataTFT_flag++;
		DCMI_CaptureCmd(ENABLE); 				//中断只负责标志位的管理，处理函数放到中断外面
	}
}

void Picture_Display(void)
{
	
	int i,j,k;
	ili9320_SetCursor(0,0);
	LCD->LCD_REG = R34; 
	for(i = 0 ; i < Row ; i++)
	{
		
		for(j = 0 ;j < Column ; j++)
		{
			LCD->LCD_RAM = *((uint8_t *)Gray_Image_Buffer + i*Column + (Column - j));
		}
		
		for(k = Column ; k < IMAGE_COLUMN ; k++)
		{
			LCD->LCD_RAM = Red;
		}

	}
	
}





