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
ÓÃµ½µÄÄ£¿é
1£ºIIC ¶ÔÓ¦¶Ë¿Ú³õÊ¼»¯
2£ºOV7670¼Ä´æÆ÷³õÊ¼»¯+¶Ë¿Ú³õÊ¼»¯
3£ºÌí¼ÓFIFO.C¸¨Öú¶Ë¿Ú³õÊ¼»¯£¬²¢ÇÒÌí¼ÓRRST()ºÍWRST()Á½¸ö³õÊ¼»¯º¯Êý
4£ºÍâ²¿ÖÐ¶Ï³õÊ¼»¯
5£ºLEDÖ¸Ê¾µÆ³õÊ¼»¯
6£ºÑÓÊ±³õÊ¼»¯
7: ´®¿Ú³õÊ¼»¯ ²âÊÔÓÃ

³ÌÐòÂß¼­

*/
extern Picture_Control PictureContorl;
int main()
{ 
	  LED_GPIO_Config();//Ö¸Ê¾µÆ³õÊ¼»¯
	  delay_init(72);//ÑÓÊ±³õÊ¼»¯   
	  ILI9325_initial();//TFT¶Ë¿Ú³õÊ¼»¯
	  Anal_I2C_Init();//IIC³õÊ¼»¯
    ov7670_PortConfig();//ÉãÏñÍ·Ä£¿éÒý½Å³õÊ¼»¯//¶ÔRCK,WR,OE,WRST,RRST½øÐÐÁË¶Ë¿ÚÉèÖÃ	
	  Cmos7670_init();//ÅäÖÃ¼Ä´æ
	  GUI_clearscreen(0xffff);//ÇåÆÁ 
    GUI_sprintf_string(50, 100,"TFT Init Successful !", 0x0000,0xffff);	//ÏÔÊ¾³õÊ¼»¯
	  GUI_clearscreen(0xffff);//ÇåÆÁ 
		Exit_Init(GPIOC, GPIO_Pin_12, GPIO_Mode_IPU, EXTI_Trigger_Falling, 0, 0);	//VSYNC //Íâ²¿ÖÐ¶Ï³õÊ¼»¯
  //	TakeVerfPhoto();
	  TIM1_Init();
		GUI_sprintf_string(10,50,"ERROR:",0x0000,0xffff);
	  GUI_sprintf_string(10,100,"ERROR_Verf:",0x0000,0xffff);
		GUI_sprintf_string(10,150,"+offset:",0x0000,0xffff);
		GUI_sprintf_string(10,200,"-offset:",0x0000,0xffff);
	  GUI_sprintf_string(10,250,"RunTime:",0x0000,0xffff);
    while(1)
		{

      	GUI_wrul(200,50,PictureContorl.Control_Value,0x0000,0xffff); //Ë¢ÐÂ¿ØÖÆÁ
			GUI_wrul(200,100,PictureContorl.Control_Value_Verf,0x0000,0xffff); //Ë¢ÐÂ¿ØÖÆÁ¿
		  if(PictureContorl.Control_Value-PictureContorl.Control_Value_Verf>0)
			
				GUI_wrul(200,150,(PictureContorl.Control_Value-PictureContorl.Control_Value_Verf),0x0000,0xffff); //Ë¢ÐÂ¿ØÖÆÁ¿
			else
        GUI_wrul(200,200,(PictureContorl.Control_Value_Verf-PictureContorl.Control_Value),0x0000,0xffff); //Ë¢ÐÂ¿ØÖÆÁ¿
				GUI_wrul(200,250,PictureContorl.Control_Value,0x0000,0xffff); //Ë¢ÐÂ¿ØÖÆÁ
			
		}
}

