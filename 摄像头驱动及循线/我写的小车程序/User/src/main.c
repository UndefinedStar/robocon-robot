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
	}												//OV7725��ʼ��
	LED_OFF();
	delay_ms(200);
	OV_Start();

	while(1)
	{

		if(UpdataTFT_flag != 0)
		{

			Transfer1Gray(Image, Gray_Image_Buffer);		//  YUV422��ʽת��Ϊ�Ҷ�ͼ��������ͼ							
      Picture_Display();                                //��ʾͼ��
			
			SendPulse(Pulse);                                 //С��ƫ�Ұ����е�λ��ƫС��ƫ����ƫ��
			UpdataTFT_flag--;                                 //�����־λ

		}

  }	

}


//һ��ͼƬ������ɣ����ж�
void DMA2_Stream1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1))
  {
		DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1);
    DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);
		DCMI_CaptureCmd(DISABLE);			
		UpdataTFT_flag++;
		DCMI_CaptureCmd(ENABLE); 				//�ж�ֻ�����־λ�Ĺ����������ŵ��ж�����
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





