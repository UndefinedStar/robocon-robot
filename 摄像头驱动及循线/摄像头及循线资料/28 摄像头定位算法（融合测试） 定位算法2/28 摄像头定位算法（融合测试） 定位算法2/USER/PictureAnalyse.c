#include "PictureAnalyse.h" 
#include "data_conf.h"
#include "OV7670.h"
#include "GUI_32.h"
uint16_t Control_Value;  //¿ØÖÆÁ¿£¬ ¶ÔÍâ½Ó¿Ú
uint8_t VSYNCCnt = 0;    //ÖĞ¶Ï¼ÆÊıÁ¿
uint16_t yBuf[500];//´æ·Å±»Ñ¡ÖĞµÄÏñËØµãµ±ÖĞ±ä³ÉºÚµãµÄ×ø±ê
uint16_t p=0;//Ö¸Õë±äÁ¿v
uint16_t Time;
Picture_Control PictureContorl;
void PictureAnalyse(void)
{
uint16_t x=0,y=0;
		uint16_t average=0;

uint16_t t1=0,t2=0,temp=0;   //Ñ­»·Á¿ÖĞ×ªÁ¿  

EXTI_ClearITPendingBit(EXTI_Line4);  	
	 //¸øÖ¸Õë¸´Î»
	LED1(ON);
	LED2(OFF);
   VSYNCCnt++;
	/*
	1:µÈ´ıOV7670Í¬²½ĞÅºÅ£¬½øÈëÖĞ¶Ïº¯ÊıËµÃ÷ÑØĞÅºÅÀ´ÁË
	*/
	if(VSYNCCnt==1)    //FIFOĞ´Ö¸Õë¸´Î»
	{
	  FIFO_WRST=1;
		for(x=0;x<5;x++);
		FIFO_WRST=0;
 		for(x=0;x<100;x++);
		FIFO_WRST=1;      	//Ğ´Ö¸Õë¸´Î»
		FIFO_WR=1;	  //Ğ´Ê¹ÄÜ£¬Ğ´Ö¸Õë¸´Î»Ö»»á¾Í¿ÉÒÔ¿ªÊ¼Ğ´ÁË	   
	}

	/*
	2&3:FIFOĞ´Ö¸Õë¸´Î»£¬°´ÕÕÊÖ²áÉÏµÄÊ±Ğò£¬¸´Î»Íê³É
	*/
	
	/*
	4:½øÈëÏÂÃæÕâ¸öº¯ÊıËµÃ÷µÚ¶ş´Î½ÓÊÕµ½ÁËÑØĞÅºÅ
	*/
	if(VSYNCCnt==2)
	{
	 	FIFO_WR=0;     //½ûÖ¹CMOSÊı¾İĞ´ÈëFIFO
	/*
	5:½ûÖ¹FIFOĞ´£¬»»×ö¶ÁÊı¾İ£¬¶ÁĞ´Ê¹ÄÜ×ª»»£¬Ò»Ö¡Êı¾İ´¢´æÍê±Ï
	*/
/////////////////////¶ÁÈ¡Êı¾İÍê±Ï///////////////////////////////////

		EXTI->IMR&=~(1<<4);	 //¾²Ö¹Íâ²¿ÖĞ¶Ï
		EXTI->EMR&=~(1<<4);
	   
			FIFO_RRST =0;				//¶ÁÖ¸Õë¸´Î»										
			for(x=0;x<10;x++)		
			{
				FIFO_RCK =0;				//ÖÁÉÙĞèÒªÒ»¸öÊ±ÖÓÖÜÆÚµÄÌø±ä²ÅÄÜ¸´Î»
				FIFO_RCK =1;
			}
			FIFO_RRST =1;
      /*
		1£ºFIFO¶ÁÖ¸Õë¸´Î»²Ù×÷Íê³É£¬²ÎÕÕ¶ÁÖ¸Õë¸´Î»Ê±Ğò
	  */

		write_cmd_data(0x0003,0x1018);
		write_cmd_data(0x0050,0x0000); 
		write_cmd_data(0x0051,0x00ef);
		write_cmd_data(0x0052,0x0000);
		write_cmd_data(0x0053,0x013f);
		write_cmd_data(0x0020,0x0000);
		write_cmd_data(0x0021,0x013f);   
		//ÉèÖÃTFTÏÔÊ¾Ä£Ê½£¬Îª¶¯Ì¬ÏÔÊ¾
			
		LCD_WriteRAM_Prepare();
		FIFO_OE=0;			  //ÔÊĞíFIFOÊä³ö£¬´ò¿ªÊä³öÊ±ÄÜ
			

		for(x = 1; x <= Windows_X; x ++)	 
		 {	
			 	LED1(OFF);
				LED2(ON);			
		 	for(y = 1; y <= Windows_Y; y ++)
			{			
				FIFO_RCK=0;					
				FIFO_RCK=1;				//Ä£Äâ¶ÁÊ±ÖÓ£¬¶ÁÈ¡¸ß°ËÎ»×Ö½Ú
				
				//¶ÁÈ¡T1µÄÊ±¼ä¶Î  µÍ°ËÎ»

				
				FIFO_RCK=0;						
				FIFO_RCK=1;	//Ä£Äâ¶ÁÊ±ÖÓ£¬¶ÁÈ¡µÚ°ËÎ»
				
				//¶Á¸ß°ËÎ» YUVÊä³ö¸ß°ËÎ»ÓĞĞ§
				//ºËĞÄËã·¨ È¡27*27¸ö²ÉÑùµã£¬Èô²ÉÑùµãÎªºÚµãÔò°Ñ¸ÃµãµÄºá×ø±ê·ÅÈëBufÖĞ×îÖÕÇóºÍ
			   if(0x0002&GPIOD->IDR)  //µÚÈı¸ùÊı¾İÏßÓĞĞ§   &&x%6==0&&y%8==0
				{
						t1=0xff;  //ÒÔÎ»´ø×Ö½Ú£¬Î»1×Ö½ÚFF Î»0 ×Ö½Ú00
					  //yBuf[p]=x; //ËµÃ÷¸Ã²ÉÑùµãÊÇºÚÉ«µÄ
					 // PictureContorl.Control_Value+=yBuf[p];//ÇóºÍºÚµãºá×ø±ê
					//  p++;//ºÚµãÖ¸Õë¼Ó
				}
				else
				{
						t1=0x00;  
				}
				#ifdef TFT_OutPut
			  temp=(t1<<8)|t2;	//ÕûºÏ	
				write_data_u16(temp);//ÕûºÏÊı¾İ+ÏÔÊ¾ÔÚTFTÉÏ	
				#endif
			}
		}
		  p=0; 

		 		PictureContorl.Control_Value=PictureContorl.Control_Value/p;	//È¡Æ½¾ù
		  if(PictureContorl.TakeVerf==1)//×¥ÅÄ²Î¿¼Öµ
			{
				PictureContorl.Control_Value_Verf=PictureContorl.Control_Value;
				PictureContorl.TakeVerf=0;
			}
				 TIM_Cmd(TIM1, DISABLE);
		//	while(1)
				//				GUI_wrul(200,250,TIM1->CNT,0x0000,0xffff); //Ë¢ĞÂ¿ØÖÆÁ
		/*
		2&3&4 : ¶ÁÈ¡Ò»ÕìÊı¾İ½áÊø
		*/	

		FIFO_OE=1;		 	  //½ûÖ¹FIFOÊä³ö
		VSYNCCnt = 0;	      //Çå³şÊıÁ¿±êÖ¾
		EXTI->IMR|=(1<<4);	  //ÔÊĞíÍâ²¿ÖĞ¶Ï£¬ÒÔ±ã½ÓÊÕÏÂÖ¡Í¼ÏñÊı¾İ
		EXTI->EMR|=(1<<4);
   }
 }

 void TakeVerfPhoto()
 {
	 PictureContorl.TakeVerf=1;
 }
 
