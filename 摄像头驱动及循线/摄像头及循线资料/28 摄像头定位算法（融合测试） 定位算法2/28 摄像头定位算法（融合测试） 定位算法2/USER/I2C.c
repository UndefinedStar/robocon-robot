//封装IIC的驱动程序
#include "I2C.h"

void Anal_I2C_delay(uint32_t time)
{
	while(--time);	//time=100: 8.75us; time=1000: 85.58 us (SYSCLK=72MHz)不准确，未测量
}

void Anal_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin = Anal_I2C_SDA;	//配置使用的I2C口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;            //设置I2C口最大允许输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	        //设置I2C为开漏输出
	GPIO_Init(Anal_I2C_PORT_D, &GPIO_InitStructure);

	
		GPIO_InitStructure.GPIO_Pin = Anal_I2C_SCL;	//配置使用的I2C口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;            //设置I2C口最大允许输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	        //设置I2C为开漏输出
	GPIO_Init(Anal_I2C_PORT_C, &GPIO_InitStructure);
	
	//时钟线全置高，总线空闲
	Anal_I2C_SCL_1;
	Anal_I2C_SDA_1;
	Anal_I2C_WAIT;
}

uint8_t Anal_I2C_START(void)//SCL一直高，接受沿信号
{
	Anal_I2C_SDA_1;//为SDA下降沿做准备
	Anal_I2C_NOP;

	Anal_I2C_SCL_1;//确保SCL一直是高
	Anal_I2C_NOP;

	if(!Anal_I2C_SDA_STATE) return Anal_I2C_BUS_BUSY;
	//SDA如果没有被拉高，说明总线忙被其他IIC设备占用，忙

	Anal_I2C_SDA_0;//进行了下降沿操作
	Anal_I2C_NOP;
    //完成了开始的沿信号
	Anal_I2C_SCL_0;
	Anal_I2C_NOP;
    //把总线设做空闲模式，以便下一次沿操作或电平操作
	if(Anal_I2C_SDA_STATE) return Anal_I2C_BUS_ERROR;
	//如果我把它拉低了，他还没有拉低，则说明错误

	return Anal_I2C_READY;
	//程序能进行到这一步说明一切正常
}
void Anal_I2C_STOP(void)//SCL一直高，接受上升沿的沿信号停止
{
	Anal_I2C_SDA_0;   //为上升沿做准备
	Anal_I2C_NOP;

	Anal_I2C_SCL_1;   //满足条件1
	Anal_I2C_NOP;

	Anal_I2C_SDA_1;   //进行上升沿操作
	Anal_I2C_NOP;
}

void Anal_I2C_SendACK(void)//应答：发送器发完一个字节后，表示从机已经收到了主机的信号
{
	Anal_I2C_SDA_0;//SDA保持低电平
	Anal_I2C_NOP;

	Anal_I2C_SCL_1;
	Anal_I2C_NOP;

	Anal_I2C_SCL_0;
	Anal_I2C_NOP;
	//模拟第九个时钟周期
}
//方法：八个数据接收完了之后，第九个时钟周期让SDA保持低电平
//主控器为接收器的时候，应答信号时发给从机接收器的，表明自己是否正确的接收了数据
//主控器为发送器的时候，非应答信号有用，说明发完了，接下来可以停止了
//结论：主控器都是对外输出应答或非应答信号

void Anal_I2C_SendNACK(void)//MCU是作为发送机的，非应答信号用来提醒接收机发送已经结束了
{
	Anal_I2C_SDA_1;//DA拉高
	Anal_I2C_NOP;

	Anal_I2C_SCL_1;
	Anal_I2C_NOP;

	Anal_I2C_SCL_0;
	Anal_I2C_NOP;
	//模拟第九个时钟周期
}

uint8_t Anal_I2C_SendByte(uint8_t i2c_data)//单字节发送数据
{
	uint8_t i;
	Anal_I2C_SCL_0;//SCL低的时候才可以改变DA，SCL低的时候接受电平信号
	for(i=0; i<8; i++)
		{
			if(i2c_data&0x80) 
			     Anal_I2C_SDA_1;//如果最高位是1，则DA高否则低
			else Anal_I2C_SDA_0;

			i2c_data<<=1; //抹去最高位，发送次高位
			Anal_I2C_NOP;

			Anal_I2C_SCL_1;//模拟SCL时钟
			Anal_I2C_NOP;
			Anal_I2C_SCL_0;
			Anal_I2C_NOP;
		}
	//结论：一个时钟发送一位的数据，SCL用来模拟时钟
	
	Anal_I2C_SDA_1;
	Anal_I2C_NOP;
	Anal_I2C_SCL_1;
	Anal_I2C_NOP;
	//闲置总线，检测当前运行状态
	if(Anal_I2C_SDA_STATE)//数据发送完了，等待从机给应答信号，从机如果给低 则应答，否则非应答
		{
			Anal_I2C_SCL_0;//接受电平信号
			return Anal_I2C_NACK;//返回0
		}
	else 
		{
			Anal_I2C_SCL_0;
			return Anal_I2C_ACK;
		}
}
uint8_t Anal_I2C_ReceiveByte(void)//单字节读取数据，此时MCU为接收机
{
	uint8_t i,i2c_data;

	Anal_I2C_SDA_1;
	Anal_I2C_SCL_0;//接受电平信号，数据可以变化
	i2c_data=0;

	for(i=0; i<8; i++)
		{
			Anal_I2C_SCL_1;//模拟时钟信号，高
			Anal_I2C_NOP;
			i2c_data<<=1;//移位读取

			if(Anal_I2C_SDA_STATE)	i2c_data|=0x01;//如果此时总线上是高则此为为高
			Anal_I2C_SCL_0;//模拟时钟低
			Anal_I2C_NOP;
		}
		//一个周期读取一个数据
	//Anal_I2C_SendACK();//第九个周期发送应答信号，作为接收机，应答信号代表了接受成功
	//主要用在和可以收发的智能主控芯片互联数据，读得懂应答信号的
	return i2c_data;
}
uint8_t Anal_I2C_ReceiveByte_WithACK(void)//多了个ACK，和一般的IC通信，人家也不懂是否有应答
{
	uint8_t i,i2c_data;

	Anal_I2C_SDA_1;
	Anal_I2C_SCL_0;
	i2c_data=0;

	for(i=0; i<8; i++)
		{
			Anal_I2C_SCL_1;
			Anal_I2C_NOP;
			i2c_data<<=1;

			if(Anal_I2C_SDA_STATE)	i2c_data|=0x01;
			Anal_I2C_SCL_0;
			Anal_I2C_NOP;
		}
	Anal_I2C_SendACK();
	return i2c_data;
}

void Anal_I2C_ReceiveBuf(uint8_t *i2c_data_buffer,uint8_t num)//一次性多读几次数据
{
	uint8_t i,j;
	uint8_t i2c_data;

	for(j=0; j<num-1; j++)
		{
			Anal_I2C_SDA_1;
			Anal_I2C_SCL_0;
			i2c_data=0;

			for(i=0; i<8; i++)
				{
					Anal_I2C_SCL_1;
					Anal_I2C_NOP;
					i2c_data<<=1;

					if(Anal_I2C_SDA_STATE)	i2c_data|=0x01;

					Anal_I2C_SCL_0;
					Anal_I2C_NOP;
				}
			i2c_data_buffer[j]=i2c_data;
			Anal_I2C_SendACK();//表明已经收到了数据
		}
	Anal_I2C_SDA_1;
	Anal_I2C_SCL_0;
	i2c_data=0;
	for(i=0; i<8; i++)
		{
			Anal_I2C_SCL_1;
			Anal_I2C_NOP;
			i2c_data<<=1;

			if(Anal_I2C_SDA_STATE)	i2c_data|=0x01;
			Anal_I2C_SCL_0;
			Anal_I2C_NOP;
		}
	i2c_data_buffer[num-1]=i2c_data;
	Anal_I2C_SendNACK();
}

//单字节读IIC器件寄存器
//Device_Adress ： 设备地址
//REG_Address： 要读取的寄存器地址
unsigned char Single_Read(unsigned char DeviceAddress,unsigned char REG_Address )
{  unsigned char REG_data;
   Anal_I2C_START();                          //开始
    Anal_I2C_SendByte(DeviceAddress);           //发送总线上IIC设备地址，查手册
    Anal_I2C_SendByte(REG_Address);                   //对应设备的寄存器地址，手册
    Anal_I2C_START();                          //开始
   Anal_I2C_SendByte(DeviceAddress+1);         //要读取数据的地址
    REG_data=Anal_I2C_ReceiveByte();              //读取一个字节
	Anal_I2C_SendACK();   					//作为接收机，发送已经读完八个数据应答
	 Anal_I2C_STOP();                           //停止
    return REG_data; 
}

//多字节读取寄存器数据
//star_addr : 第一个要读的寄存器地址
//num ： 要读的寄存器数量
//SlaveAdress ： 设备地址
//recv_buf ： 要储存数据的数组
void Multiple_read(unsigned char star_addr,unsigned char num,unsigned char SlaveAddress,unsigned char* recv_buf)
{
	Anal_I2C_START();
	Anal_I2C_SendByte(SlaveAddress);			//????????
	Anal_I2C_SendByte(star_addr);     //??????????
	Anal_I2C_START();
	Anal_I2C_SendByte(0x3d);      	//????????
	Anal_I2C_ReceiveBuf(recv_buf,num);	//?????????
	Anal_I2C_STOP();
}

//写寄存器函数，用来配置IIC器件的寄存器
//SlaveAddress : 设备地址
// adress : IIC器件要写的寄存器地址
//data: 写到该地址的数据
uint8_t Single_Write(uint16_t SlaveAdress,uint16_t adress,uint16_t data)
{
		Anal_I2C_START();
		Anal_I2C_SendByte(SlaveAdress);//??????+???
		Anal_I2C_SendByte(adress);//???????
	    Anal_I2C_SendByte(data);
      	Anal_I2C_STOP();
  	return 1;	

}
