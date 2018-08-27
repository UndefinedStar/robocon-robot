#include "stm32f10x.h"
#include "Nvic_Exit.h"
#include "ov7670.h"
#include "I2C.h"
#include "ILI9325_32.h"
#include "GUI_32.h"
#include "delay.h"
#include "led.h"
#include "data_conf.h"
#include "PictureAnalyse.h"
#include "Tim1.h"

/*
�õ���ģ��
1��IIC ��Ӧ�˿ڳ�ʼ��
2��OV7670�Ĵ�����ʼ��+�˿ڳ�ʼ��
3�����FIFO.C�����˿ڳ�ʼ�����������RRST()��WRST()������ʼ������
4���ⲿ�жϳ�ʼ��
5��LEDָʾ�Ƴ�ʼ��
6����ʱ��ʼ��
7: ���ڳ�ʼ�� ������

�����߼�

*/
extern Picture_Control PictureContorl;
int main()
{ 
	  LED_GPIO_Config();//ָʾ�Ƴ�ʼ��
	  delay_init(72);//��ʱ��ʼ��   
	  ILI9325_initial();//TFT�˿ڳ�ʼ��
	  Anal_I2C_Init();//IIC��ʼ��
    ov7670_PortConfig();//����ͷģ�����ų�ʼ��//��RCK,WR,OE,WRST,RRST�����˶˿�����	
	  Cmos7670_init();//���üĴ�
	  GUI_clearscreen(0xffff);//���� 
    GUI_sprintf_string(50, 100,"TFT Init Successful !", 0x0000,0xffff);	//��ʾ��ʼ��
	  GUI_clearscreen(0xffff);//���� 
		Exit_Init(GPIOC, GPIO_Pin_12, GPIO_Mode_IPU, EXTI_Trigger_Falling, 0, 0);	//VSYNC //�ⲿ�жϳ�ʼ��
  //	TakeVerfPhoto();
	  TIM1_Init();
		GUI_sprintf_string(10,50,"ERROR:",0x0000,0xffff);
	  GUI_sprintf_string(10,100,"ERROR_Verf:",0x0000,0xffff);
		GUI_sprintf_string(10,150,"+offset:",0x0000,0xffff);
		GUI_sprintf_string(10,200,"-offset:",0x0000,0xffff);
	  GUI_sprintf_string(10,250,"RunTime:",0x0000,0xffff);
    while(1)
		{

      	GUI_wrul(200,50,PictureContorl.Control_Value,0x0000,0xffff); //ˢ�¿����
			GUI_wrul(200,100,PictureContorl.Control_Value_Verf,0x0000,0xffff); //ˢ�¿�����
		  if(PictureContorl.Control_Value-PictureContorl.Control_Value_Verf>0)
			
				GUI_wrul(200,150,(PictureContorl.Control_Value-PictureContorl.Control_Value_Verf),0x0000,0xffff); //ˢ�¿�����
			else
        GUI_wrul(200,200,(PictureContorl.Control_Value_Verf-PictureContorl.Control_Value),0x0000,0xffff); //ˢ�¿�����
				GUI_wrul(200,250,PictureContorl.Control_Value,0x0000,0xffff); //ˢ�¿����
			
		}
}

