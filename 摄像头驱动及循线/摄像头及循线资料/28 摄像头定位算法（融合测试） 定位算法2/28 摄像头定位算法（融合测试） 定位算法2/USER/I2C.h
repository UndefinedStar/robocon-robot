#include "stm32f10x.h"
/*

搭载四旋翼模块引脚
RCK   --- PD3
WR        PD5
OE        PD7
RRST     G12 
WRST      G10

D2        PD1
VSYNC     C12
SIOD      A14
SIOC      C10
*/
#define Anal_I2C_SDA 		GPIO_Pin_14   //A14 SDA C10 SCL
#define Anal_I2C_SCL 		GPIO_Pin_10	 //C10  
#define Anal_I2C_PORT_D       GPIOA
#define Anal_I2C_PORT_C       GPIOC

//定义IIC引脚
#define Anal_I2C_SCL_0 		GPIO_ResetBits(Anal_I2C_PORT_C, Anal_I2C_SCL)
#define Anal_I2C_SCL_1 		GPIO_SetBits(Anal_I2C_PORT_C, Anal_I2C_SCL)
#define Anal_I2C_SDA_0 		GPIO_ResetBits(Anal_I2C_PORT_D, Anal_I2C_SDA)
#define Anal_I2C_SDA_1   	GPIO_SetBits(Anal_I2C_PORT_D, Anal_I2C_SDA)
//定义引脚操作

#define Anal_I2C_SDA_STATE  GPIO_ReadInputDataBit(Anal_I2C_PORT_D, Anal_I2C_SDA)
//读取数据线当前的状态来接受从机的应答信号
#define Anal_I2C_WAIT 		Anal_I2C_delay(100000)
#define Anal_I2C_NOP		Anal_I2C_delay(10) 
//延迟一段时间的定义

#define Anal_I2C_READY			0x00
#define Anal_I2C_BUS_BUSY		0x01	
#define Anal_I2C_BUS_ERROR	0x02

#define Anal_I2C_NACK	  0x00 
#define Anal_I2C_ACK		0x01

void Anal_I2C_delay(uint32_t time);
void Anal_I2C_Init(void);
uint8_t Anal_I2C_START(void);
void Anal_I2C_STOP(void);
void Anal_I2C_SendACK(void);
void Anal_I2C_SendNACK(void);
uint8_t Anal_I2C_SendByte(uint8_t i2c_data);
uint8_t Anal_I2C_ReceiveByte(void);
uint8_t Anal_I2C_ReceiveByte_WithACK(void);
void Anal_I2C_ReceiveBuf(uint8_t *i2c_data_buffer,uint8_t num);

uint8_t Single_Write(uint16_t SlaveAdress,uint16_t adress,uint16_t data);
void Multiple_read(unsigned char star_addr,unsigned char num,unsigned char SlaveAddress,unsigned char* recv_buf);
unsigned char Single_Read(unsigned char DeviceAddress,unsigned char REG_Address );
