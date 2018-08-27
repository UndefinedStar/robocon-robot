
#include "led.h"


void LED_GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		//定义一个结构体指针，指向封装的寄存器首地址
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		//开启挂载在APB2上的GPIOC时钟外设时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		//选择配置的引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//设置为推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		//选择输出速度
	
	  //控制字赋值完毕
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		//把控制字节直接写入对应寄存器首地址  使我们定义的控制字生效  第一个参数时 要设置到的端口 第二个是存放控制字的结构指针
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	  //库函数中给出的用来拉高电平的库函数
	  //低电平的库函数对应为 GPIO_ResetBits第一个参数输入的是端口号 第二个参数给的是该端口号的具体引脚
		//关闭所有灯


		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);
		//开启挂载在APB2上的GPIOC时钟外设时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		//选择配置的引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//设置为推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		//选择输出速度
	
	  //控制字赋值完毕
		GPIO_Init(GPIOC,&GPIO_InitStructure);
		//把控制字节直接写入对应寄存器首地址  使我们定义的控制字生效  第一个参数时 要设置到的端口 第二个是存放控制字的结构指针
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
}