/*
 * User_EEPROM.c
 *
 *  Created on: 2014-2-23
 *      Author: John
 */


#include "EEPROM.h"

unsigned char CharTempData[4];
unsigned int  IntTempData[2];

//用两个IO口模拟IIC通信协议
//其他参数不能写在这里，否则会出问题


/*
*****************************************
* Name : Init24C256
* Describe : 初始化24c256的IO口，模拟IIC
* Input : None
* Output : None
* Return : None
*****************************************
*/
void Init24C256(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_DeInit(GPIOE);
	
	gpio.GPIO_Mode=GPIO_Mode_OUT;
	gpio.GPIO_OType=GPIO_OType_OD;
	gpio.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
	gpio.GPIO_PuPd=GPIO_PuPd_UP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&gpio);
	
	DataHigh;
	CLKHigh;
	
	delay(IIC_DELAY_TIME*IIC_DELAY_TIME);
}




/*
*****************************************
* Name : iic_start
* Describe : 启动信号
* Input : None
* Output : None
* Return : None
*****************************************
*/
void iic_start(void)
{
	DataOut;   												 //SDA作输出
	DataHigh;   											 //数据线拉高
	delay(IIC_DELAY_TIME/10);          //稍微延时，等待稳定
	CLKHigh; 													 //时钟拉高
	delay(IIC_DELAY_TIME);
	DataLow;												   //数据线拉低，发送启动标志
	delay(IIC_DELAY_TIME);
	CLKLow;													   //时钟拉低
	delay(IIC_DELAY_TIME/10);
	return;
}




/*
*****************************************
* Name : iic_stop
* Describe : 结束信号
* Input : None
* Output : None
* Return : None
*****************************************
*/
void iic_stop(void)
{
	DataOut;   												 //SDA作输出
	DataLow;  												 //数据线拉低
	delay(IIC_DELAY_TIME/10);
	CLKHigh;   												 //时钟拉高
	delay(IIC_DELAY_TIME);
	DataHigh;													 //数据线拉高，作为停止标志
	delay(IIC_DELAY_TIME);
	return;
}



/*
*****************************************
* Name : iic_ack
* Describe : 主器件发送应答信号
* Input : dat ：0为成功应答，1为非应答
* Output : None
* Return : None
*****************************************
*/
void iic_ack(unsigned char dat) 		 
{
	DataOut;
	if(dat&0x01)
	{
		DataHigh;
	}
	else
		DataLow;
	delay(IIC_DELAY_TIME);
	CLKHigh;
	delay(IIC_DELAY_TIME);
	CLKLow;
	delay(IIC_DELAY_TIME/10);
	return;
}



/*
**************************************************
* Name : IicSendByte
* Describe : 主机向从器件发送一个字节的数据
* Input : wdata ：想要发送的数据
* Output : None
* Return : 从机应答信号，1为没有应答，0为应答成功
**************************************************
*/
unsigned char IicSendByte(unsigned char wdata) 
{
	unsigned char bit_cnt;
	DataOut; 																		 //数据线作为输出
	for(bit_cnt=0;bit_cnt<8;bit_cnt++)					 //从高位开始发送
	{
		if((wdata<<bit_cnt)&0x80)
		{
			DataHigh;
		}
		else DataLow;
		delay(IIC_DELAY_TIME);
		CLKHigh;
		delay(IIC_DELAY_TIME);
		CLKLow;
	}
	delay(IIC_DELAY_TIME);
	DataIn;																		  //重新配置为输入
	CLKHigh;  																	//发送完一个字节之后，检测从机应答信号
	delay(IIC_DELAY_TIME);
	if(DataRead)
	{
			bit_cnt=1;
	}									 													//从器件没有应答，则返回1
	else
	{		
			bit_cnt=0;   														//从器件成功应答，则返回0
	}
	CLKLow;  																		//拉低时钟
	return bit_cnt;
}


/*
*****************************************
* Name : IicRevByte
* Describe : 主机接受一个字节
* Input : None
* Output : None
* Return : 接收到的字节
*****************************************
*/
unsigned char IicRevByte(void) 						   
{
	unsigned char bit_cnt,rdata=0x00;
	DataIn;  																		//设为输入
	for(bit_cnt=0;bit_cnt<8;bit_cnt++)
	{
		CLKLow;
		delay(IIC_DELAY_TIME);
		CLKHigh;
		delay(IIC_DELAY_TIME);
		rdata<<=1;
		if(DataRead)rdata|=1;
		delay(IIC_DELAY_TIME/10);
	}
	CLKLow;
	return rdata;
}


/*
写入EEPROM，地址add_s开始处的连续写入num个字节数据num的最大值为？
add_s范围：0x0000-0x7FFF;共32K字节数据
若add_s+num超过0x7fff，则转到地址0x0000处继续连续写入剩余字节
*/
void _24C256_WriteStr(unsigned char add,unsigned int add_s,unsigned char *s,unsigned char num)
{
	unsigned char i;
	iic_start();  												//通信开始
	if(IicSendByte(add))return;  				  //发送从机地址
	if(IicSendByte(add_s>>8))return;  		//发送从机写地址高八位
	if(IicSendByte(add_s))return;	 			  //发送从机写地址低八位
	for(i=0;i<num;i++)
	{
	   if(IicSendByte(*s))return;  //发送数据
	   s++;
	}
	iic_stop();  									 //通信结束
	delay(50000); 								 //延时，等待数据完全写进EEPROM
	return;
}
/*
读取EEPROM，地址add_s开始处连续读出的num个字节数据 num的最大值为？
add_s范围：0x0000-0x7FFF;共32K字节数据
若add_s+num超过0x7fff，则转到地址0x0000处继续连续读取
*/
void _24C256_ReadStr(unsigned char add,unsigned int add_s,unsigned char *s,unsigned char num)
{
	unsigned char i;
	iic_start();  										//启动通信
	if(IicSendByte(add))return;   		//发送伪指令写
	if(IicSendByte(add_s>>8))return;
	if(IicSendByte(add_s))return;
	iic_start();  										//重新启动通信
	if(IicSendByte(add+1))return;			//发送读指令
	for(i=0;i<num-1;i++)
	{
	   *s=IicRevByte();
	   iic_ack(0);   									//主器件向从器件发送应答位
	   s++;
	}
	*s=IicRevByte();
	iic_ack(1);		 										//主器件发送非应答位
	iic_stop();     								  //通信结束
	return;
}



/*
*****************************************
* Name : _24C256_SaveFloatData
* Describe : 发送浮点型数据，占用四个字节
* Input : add_s：起始地址
					dat  ：想要存入的浮点型数据
* Output : None
* Return : None
*****************************************
*/
void _24C256_SaveFloatData(unsigned int add_s,float dat)
{
	EncodeFloatData(&dat, CharTempData);
	_24C256_WriteStr(0xa0,add_s,CharTempData,4);
}


/*
*****************************************
* Name : _24C256_ReadFloatData
* Describe : 读指定地址的浮点型数据
* Input : add_s：起始地址
* Output : None
* Return : 读到的数据
*****************************************
*/
float _24C256_ReadFloatData(unsigned int add_s)
{
	float revdata;
	_24C256_ReadStr(0xa0,add_s,CharTempData,4);
	DecodeFloatData(&revdata,CharTempData);
	return revdata;
}


/*
********************************************
* Name : _24C256_SaveIntData
* Describe : 存储整型数据
* Input : add_s：起始地址
					dat  ：想要存入的数据，占两个字节
* Output : None
* Return : None
********************************************
*/
void _24C256_SaveIntData(unsigned int add_s,int dat)
{
	IntTempData[0] = dat;
	CharTempData[0]=IntTempData[0]&0x00ff;
	CharTempData[1]=(IntTempData[0]&0xff00)>>8;
	_24C256_WriteStr(0xa0,add_s,CharTempData,2);
}


/*
*****************************************
* Name : _24C256_ReadIntData
* Describe : 读取整型数据
* Input : add_s：起始地址
* Output : None
* Return : 读取的整型数据
*****************************************
*/
int _24C256_ReadIntData(unsigned int add_s)
{
	_24C256_ReadStr(0xa0,add_s,CharTempData,2);
	IntTempData[0]=(CharTempData[0]&0x00ff)|((CharTempData[1]<<8)&0xff00);
	return IntTempData[0];
}



/*
*****************************************
* Name : _24C256_SaveLongData
* Describe : 存储长整型数据，占4个字节
* Input :  add_s：起始地址
					 dat  ：想要存入的长整型数据
* Output : None
* Return : None
*****************************************
*/
void  _24C256_SaveLongData(unsigned int add_s,long dat)
{
	*( long* )IntTempData = dat;
	CharTempData[0]=IntTempData[0]&0x00ff;
	CharTempData[1]=(IntTempData[0]&0xff00)>>8;
	CharTempData[2]=IntTempData[1]&0x00ff;
	CharTempData[3]=(IntTempData[1]&0xff00)>>8;
	_24C256_WriteStr(0xa0,add_s,CharTempData,4);
}


/*
*****************************************
* Name : _24C256_ReadLongData
* Describe : 读取长整型数据
* Input : add_s：起始地址
* Output : None
* Return : 读取的长整型数据
*****************************************
*/
long  _24C256_ReadLongData(unsigned int add_s)
{
	long revdata;
	_24C256_ReadStr(0xa0,add_s,CharTempData,4);
	IntTempData[0]=(CharTempData[0]&0x00ff)|((CharTempData[1]<<8)&0xff00);
	IntTempData[1]=(CharTempData[2]&0x00ff)|((CharTempData[3]<<8)&0xff00);
	revdata = *( long* )IntTempData;
	return revdata;
}


/*
*****************************************
* Name : _24C256_ReadFloatDataStr
* Describe : 读取一连串浮点型数据
* Input : add_start：起始地址
					num：      要读取的数据的个数
* Output : None
* Return : None
*****************************************
*/
//void _24C256_ReadFloatDataStr(unsigned int add_start,unsigned char num)
//{
//		vu8 i;
//		for(i=0;i<num;i++)
//		{
//				add_start=add_start+i*4;
//				*Pparameter[i]=_24C256_ReadFloatData(add_start);
//		}
//}
























