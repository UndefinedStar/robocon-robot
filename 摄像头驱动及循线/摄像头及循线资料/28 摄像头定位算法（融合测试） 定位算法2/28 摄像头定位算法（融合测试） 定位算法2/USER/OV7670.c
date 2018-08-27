#include "I2C.h"
#include "delay.h"
#include "switch.h"
#include "ov7670.h"
#include "ov7670config.h"

void ov7670_PortConfig()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG| RCC_APB2Periph_AFIO,ENABLE);

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_12;	//����ʹ�õ�I2C��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //����I2C�������������ٶ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	        //����I2CΪ��©���
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG ,ENABLE);
	//RRST WRST

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_5|GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //����I2C�������������ٶ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;	        
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//RCK OE WR

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //����I2C�������������ٶ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	        
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//1λ���ݿ� D2 PD1
}


uint8_t RdCmos7670(uint16_t star_addr,uint8_t *recv_buf)
{
  Multiple_read( star_addr,8,OV7670_DEVICE_WRITE_ADDRESS, recv_buf);
	return 1;
}

uint8_t WrCmos7670(uint16_t adress,uint16_t data)
{
Single_Write(OV7670_DEVICE_WRITE_ADDRESS,adress,data);
		delay_us(100);
	return 1;
}



void set7670ToRGB_QVGA(void)
{	 
	uint16_t i;
   for(i=0;i<(sizeof(ov7670_Normal)/sizeof(ov7670_Normal[2])/2);i++)
	{
		WrCmos7670(ov7670_Normal[i][0],ov7670_Normal[i][1]);
	}
	
}

void set7670ToYUV_QVGA(void)
{
	uint16_t i;
   for(i=0;i<(sizeof(ov7670_YUV)/sizeof(ov7670_YUV[2])/2);i++)
	{
		WrCmos7670(ov7670_YUV[i][0],ov7670_YUV[i][1]);
	}
}


void Mode_RGB_QICF()//ת����ʽ
{
    	WrCmos7670(0x12, 0x0C); //QICF��ͷֱ���
}

/***************************************************************************
��    �ƣ�unsigned char Cmos7670_init(void)
��    �ܣ�CMOS��ʼ��
��ڲ�������
���ڲ�����1 ��ʼ���ɹ�
          0 ��ʼ��ʧ��
˵    ����
���÷�����m=Cmos7670_init();
***************************************************************************/
unsigned char Cmos7670_init(void)
{
	unsigned char mmm;	
	mmm=0x80;
	if(0==WrCmos7670(0x12, mmm)) 
	{
		return 0 ;
	}
	delay_ms(10);

	set7670ToYUV_QVGA();
		  Mode_RGB_QICF();

	return 1; 
} 

//�����ֱ��ʵĺ��� 
//startx : ͼ��ʼX����
//starty : ͼ��ʼY����
//width  : �������ͼ��鵽�Ŀ��
//height : �߶�
void OV7670_config_window(u16 startx,u16 starty,u16 width,u16 height)
{
	u8 x_reg,y_reg;u8 state,temp;
		u16 endx=(startx+width*2)%784;
		u16 endy=(starty+height*2); 

		state=RdCmos7670(0x32,&x_reg);
		x_reg&=0xC0;
		state=RdCmos7670(0x03,&y_reg);
		y_reg&=0xF0;
		//����HREF
		temp=x_reg|((endx&0x7)<<3)|(startx&0x7);state=WrCmos7670(0x32,temp);temp=(startx&0x7F8)>>3;
		state=WrCmos7670(0x17,temp);
		temp=(endx&0x7F8)>>3;
		state=WrCmos7670(0x18,temp);
		//����VREF
		temp=y_reg|((endy&0x3)<<2)|(starty&0x3);
		state=WrCmos7670(0x03,temp);
		temp=(starty&0x3FC)>>2;
		state=WrCmos7670(0x19,temp);
		temp=(endy&0x3FC)>>2;
		state=WrCmos7670(0x1A,temp);
}
