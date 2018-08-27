#ifndef ILI9325_32_H
#define ILI9325_32_H

#include "stm32f10x.h"



//根据芯片资料定义
#define WINDOW_XADDR_START	0x0050 // 水平方向开始写入的地址设置
#define WINDOW_XADDR_END	0x0051 //水平方向结束写入的地址设置
#define WINDOW_YADDR_START	0x0052 // 垂直方向开始写入的地址设置
#define WINDOW_YADDR_END	0x0053 // 垂直方向结束写入的地址设置
#define GRAM_XADDR		0x0020 // GRAM 水平地址设置
#define GRAM_YADDR		0x0021 // GRAM 垂直地址设置
#define GRAMWR 			0x0022 // memory write
#define GUI_LCM_YMAX  319     //常数，320*240点阵，水平方向上240列点
#define GUI_LCM_XMAX  239     //常数，320*240点阵，垂直方向上320行点


#define ILI9325_LN	320
#define ILI9325_COL	240

#define Data_Port GPIOF   //GPIOD十六位位作为数据口
#define Crt_Port GPIOE    //GPIOA作为控制端口
//控制端口定义


#define Crt_Port_Clock   RCC_APB2Periph_GPIOE
#define Data_Port_Clock  RCC_APB2Periph_GPIOF
#define TFT_RS  GPIO_Pin_10
#define TFT_RW  GPIO_Pin_11
#define TFT_RD  GPIO_Pin_12
#define TFT_CS  GPIO_Pin_13
#define TFT_RST GPIO_Pin_14
//定义引脚

#define TFT_RS_1  GPIO_SetBits(GPIOE,TFT_RS)    //数据/命令选择  p3.0
#define TFT_RS_0  GPIO_ResetBits(Crt_Port,TFT_RS)    

#define TFT_WR_1  GPIO_SetBits(Crt_Port,TFT_RW)	//写p3.1引脚，根据实际硬件需要更改
#define TFT_WR_0  GPIO_ResetBits(Crt_Port,TFT_RW)

#define TFT_RD_1  GPIO_SetBits(Crt_Port,TFT_RD)	//读p3.2引脚，根据实际硬件需要更改
#define TFT_RD_0  GPIO_ResetBits(Crt_Port,TFT_RD)

#define TFT_CS_1  GPIO_SetBits(Crt_Port,TFT_CS)	//片选p3.3引脚，根据实际硬件需要更改
#define TFT_CS_0  GPIO_ResetBits(Crt_Port,TFT_CS)

#define TFT_RST_1 GPIO_SetBits(Crt_Port,TFT_RST)	//复位p3.4引脚，根据实际硬件需要更改
#define TFT_RST_0 GPIO_ResetBits(Crt_Port,TFT_RST)


//函数声明
void ILI9325_initial(void);//TFT初始化
void write_cmd(unsigned char CH,unsigned char CL);//写命令
void write_data(unsigned char DH,unsigned char DL);//写数据
void write_data_u16(unsigned int dat);//写16位数据
void write_cmd_data (unsigned char cmd,unsigned int dat);//写命令数据
void LCD_WriteRAM_Prepare(void);//准备好写入TFTRAM中
void LCD_WriteRAM(u16 RGB_Code);//把Code的数据显示到TFT中去，必须为RGB格式
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1);//设置窗口
void LCD_setxy(unsigned char x,unsigned int y);//设定当前显示坐标
void LCD_test(void);//彩条、单色自测程序
void Write_RRR(void);
void Write_GGG(void);
uint16_t LCD_ReadDat(void);

#endif




//花费很多时间的教训
/*

给GPIO端口写数据不能通过GPIO_write 来设定，而是通过BSR BSRR 两个寄存器来实现
GPIOx_BSRR的高16位中每一位对应端口x的每个位，对高16位中的某位置'1'则端口x的对应位被清'0'；寄存器中的位置'0'，则对它对应的位不起作用。

GPIOx_BSRR的低16位中每一位也对应端口x的每个位，对低16位中的某位置'1'则它对应的端口位被置'1'；寄存器中的位置'0'，则对它对应的端口不起作用。

BSRR的低十六位对应的是 引脚的低十六位  BSRR的低十六位全部置1 则对应引脚全部置1   高十六位没怎么用到
BSR的低十六位与对应引脚的低十六位 取反相互对应
*/
