#include "ILI9325_32.h"
#include "delay.h"
#include "ILI9325REG.H"
unsigned int color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};
//颜色定义  红 绿 蓝 黄 黑 白 天蓝 紫

//初始化TFT所需引脚
void TFT_GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure; 
		
  RCC_APB2PeriphClockCmd( Crt_Port_Clock , ENABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(Crt_Port, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( Data_Port_Clock ,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; ;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(Data_Port, &GPIO_InitStructure);
}

//初始化程序，设定相应寄存器
void ILI9325_initial(void)
{ 
  TFT_GPIO_Config();
	TFT_CS_1;
	delay_us(5000);
	TFT_RST_0;
	delay_us(5000);
	TFT_RST_1;
	delay_us(20000);//可以适当调整延时，保障稳定显示
	

//	write_cmd_data(0x0001,0x0100); //源扫描设置SS=0, 输出的移动方向是从S1到S720
//	//（源扫描设置SS=1, 输出的移动方向是从S720到S1）
//	//SM=0，逐行扫描（SM=1，隔行扫描）

//	write_cmd_data(0x0002,0x0700); //B/C=1、EOR=1：行倒置（B/C=0：帧/场倒置）
//	write_cmd_data(0x0003,0x1030); //AM=0，地址在水平方向自动加1
//	//I/D[1:0] = 11：水平垂直方向均增加
//	//BGR=1:采用BGR格式
//	//TRI=0、DFM=*：8位机、两次数据传送
//	write_cmd_data(0x0004,0x0000); //比例缩放设置：不缩放
//	
//	//显示控制
//	write_cmd_data(0x0008,0x0207); //设置后边沿和前沿 
//	write_cmd_data(0x0009,0x0000);//设置非显示区时间间隔ISC[3:0]
//	write_cmd_data(0x000A,0x0000); //帧标记功能

//	write_cmd_data(0x000C,0x0000);//RGB显示接口控制1
//	write_cmd_data(0x000D,0x0000);//帧标记位置
//	write_cmd_data(0x000F,0x0000);//RGB显示接口控制2
//	
//	//电源配置
//	write_cmd_data(0x0010,0x0000);   
//	write_cmd_data(0x0011,0x0007);  
//	write_cmd_data(0x0012,0x0000);  
//	write_cmd_data(0x0013,0x0000); 
//	//vgh 
//	write_cmd_data(0x0010,0x1290);   
//	write_cmd_data(0x0011,0x0227);
//	//delayms(100);
//	//vregiout 
//	write_cmd_data(0x0012,0x001d); //0x001b
//	//delayms(100); 
//	//vom amplitude
//	write_cmd_data(0x0013,0x1500);
//	//delayms(100); 
//	//vom H
//	write_cmd_data(0x0029,0x0018); 
//	write_cmd_data(0x002B,0x000D); 
//	
//	//伽马校正
//	write_cmd_data(0x0030,0x0004);
//	write_cmd_data(0x0031,0x0307);
//	write_cmd_data(0x0032,0x0002);//0006
//	write_cmd_data(0x0035,0x0206);
//	write_cmd_data(0x0036,0x0408);
//	write_cmd_data(0x0037,0x0507); 
//	write_cmd_data(0x0038,0x0204);//0200
//	write_cmd_data(0x0039,0x0707); 
//	write_cmd_data(0x003C,0x0405);//0504
//	write_cmd_data(0x003D,0x0F02); 
//	
//	//窗口设置
//	write_cmd_data(0x0050,0x0000);//水平起始位置
//	write_cmd_data(0x0051,0x00EF);//水平终止位置
//	write_cmd_data(0x0052,0x0000);//垂直起始位置
//	write_cmd_data(0x0053,0x013F);//垂直终止位置

//	write_cmd_data(0x0060,0xA700);//门扫描设置，GS=1：从G320扫描到G1，320线
//	write_cmd_data(0x0061,0x0001); 
//	write_cmd_data(0x006A,0x0000);
//	//
//	write_cmd_data(0x0080,0x0000); 
//	write_cmd_data(0x0081,0x0000); 
//	write_cmd_data(0x0082,0x0000); 
//	write_cmd_data(0x0083,0x0000); 
//	write_cmd_data(0x0084,0x0000); 
//	write_cmd_data(0x0085,0x0000); 
//	//
//	write_cmd_data(0x0090,0x0010); 
//	write_cmd_data(0x0092,0x0600); 
//	write_cmd_data(0x0093,0x0003); 
//	write_cmd_data(0x0095,0x0110); 
//	write_cmd_data(0x0097,0x0000); 
//	write_cmd_data(0x0098,0x0000);
//	write_cmd_data(0x0007,0x0133);
		  write_cmd_data(0x00e7,0x0010);      
    write_cmd_data(0x0000,0x0001);
    write_cmd_data(0x0001,0x0100);     
    write_cmd_data(0x0002,0x0700); 
    write_cmd_data(0x0003,(1<<12)|(3<<4)|(0<<3) );   
    write_cmd_data(0x0004,0x0000);                                   
    write_cmd_data(0x0008,0x0207);	           
    write_cmd_data(0x0009,0x0000);         
    write_cmd_data(0x000a,0x0000);        
    write_cmd_data(0x000c,0x0001);         
    write_cmd_data(0x000d,0x0000);         
    write_cmd_data(0x000f,0x0000);

    write_cmd_data(0x0010,0x0000);   
    write_cmd_data(0x0011,0x0007);
    write_cmd_data(0x0012,0x0000);                                                                 
    write_cmd_data(0x0013,0x0000);                 
    delay_ms(50); 
    write_cmd_data(0x0010,0x1590);   
    write_cmd_data(0x0011,0x0227);
    delay_ms(50); 
    write_cmd_data(0x0012,0x009c);                  
    delay_ms(50); 
    write_cmd_data(0x0013,0x1900);   
    write_cmd_data(0x0029,0x0023);
    write_cmd_data(0x002b,0x000e);
    delay_ms(50); 
    write_cmd_data(0x0020,0x0000);                                                            
    write_cmd_data(0x0021,0x013f);           
	delay_ms(50); 

    write_cmd_data(0x0030,0x0007); 
    write_cmd_data(0x0031,0x0707);   
    write_cmd_data(0x0032,0x0006);
    write_cmd_data(0x0035,0x0704);
    write_cmd_data(0x0036,0x1f04); 
    write_cmd_data(0x0037,0x0004);
    write_cmd_data(0x0038,0x0000);        
    write_cmd_data(0x0039,0x0706);     
    write_cmd_data(0x003c,0x0701);
    write_cmd_data(0x003d,0x000f);
    delay_ms(50); 
    write_cmd_data(0x0050,0x0000);
    write_cmd_data(0x0051,0x00ef);                   
    write_cmd_data(0x0052,0x0000);                    
    write_cmd_data(0x0053,0x013f);   
    
    write_cmd_data(0x0060,0xa700);        
    write_cmd_data(0x0061,0x0001); 
    write_cmd_data(0x006a,0x0000);
    write_cmd_data(0x0080,0x0000);
    write_cmd_data(0x0081,0x0000);
    write_cmd_data(0x0082,0x0000);
    write_cmd_data(0x0083,0x0000);
    write_cmd_data(0x0084,0x0000);
    write_cmd_data(0x0085,0x0000);
  
    write_cmd_data(0x0090,0x0010);     
    write_cmd_data(0x0092,0x0000);  
    write_cmd_data(0x0093,0x0003);
    write_cmd_data(0x0095,0x0110);
    write_cmd_data(0x0097,0x0000);        
    write_cmd_data(0x0098,0x0000);  
    //¿ªÆôÏÔÊ¾ÉèÖÃ    
    write_cmd_data(0x0007,0x0133);   
    write_cmd_data(0x0020,0x0000);                                                            
    write_cmd_data(0x0021,0x013f);  
}

//写十六位命令
void write_cmd(unsigned char CH,unsigned char CL)
{
 
	TFT_RD_1;// 读控制命令，"0"为读有效，写时一直为高电平
	TFT_CS_0; //低电平有效，片选
	TFT_RS_0;//"0"为命令，"1"为数据
	//确定是写命令还是写数据
	
	Data_Port->BSRR=CH&0xff;  //传输的数据，高8位
	Data_Port->BRR = ~CH & 0xff;
	
	TFT_WR_0;//低电平到高电平变化完成命令传输
	TFT_WR_1;//
	//把数据输入到端口，然后启动传输
	
	Data_Port->BSRR=CL&0xff;  //传输的数据，高8位
	Data_Port->BRR = ~CL & 0xff;
	TFT_WR_0;
	TFT_WR_1;//低电平到高电平变化完成数据传输
	//再发一次低八位
	TFT_CS_1;//高电平无效，结束片选	
}

//写十六位数据
void write_data(unsigned char DH,unsigned char DL)
{
	TFT_RD_1;  // 读控制命令，"0"为读有效
    TFT_CS_0;  //低电平有效，片选
	TFT_RS_1;  //"1"为数据，"0"为命令
	//RD决定是读还是写 写的话一直置高
	//RS决定读的是READ SELECT 选择读数据还是命令 1 为数据 0 为命令
	
	Data_Port->BSRR=DH&0xff;  //传输的数据，高8位
	Data_Port->BRR = ~DH & 0xff;
	TFT_WR_0;  // 低电平
	TFT_WR_1;  //变化到高电平，启动传输
	
	Data_Port->BSRR=DL&0xff;  //传输的数据，高8位
	Data_Port->BRR = ~DL & 0xff;
	
	TFT_WR_0;  // 低电平
	TFT_WR_1; // 低电平
	TFT_CS_1;//高电平无效，结束片选
}

//整合十六位数据
void write_data_u16(unsigned int dat)
{
	unsigned char m,n;  
	m=dat>>8;   //高8位，右移8位
	n=dat;     //低8位
	write_data(m,n);
}


//发送地址和数据
void write_cmd_data (unsigned char cmd,unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_cmd(0x00,cmd);  //写命令，命令的高8位为0x00,低字节为命令
	write_data(m,n); //写命令数据
}


void LCD_WriteRAM_Prepare(void)
{
	write_cmd(0x00,0x22);
}	 

void LCD_WriteRAM(u16 RGB_Code)
{							    
	write_data_u16(RGB_Code);
}




//===============================================================
//设置窗口
//入口参数: x0 y0,为显示窗口左上角坐标；x1,y1为显示窗口右下角坐标。
//出口参数: 无
//说明：该函数设置TFT模块的显示窗口。
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1)
{
	write_cmd_data(WINDOW_XADDR_START,x0);//水平起始位置
	write_cmd_data(WINDOW_XADDR_END,x1);//水平终止位置
	write_cmd_data(WINDOW_YADDR_START,y0);//垂直起始位置
	write_cmd_data(WINDOW_YADDR_END,y1);//垂直终止位置
	write_cmd_data(GRAM_XADDR,x0);//设置X坐标位置
	write_cmd_data(GRAM_YADDR,y0);//设置Y坐标位置
	write_cmd(0x00,0x22);//LCD_WriteCMD(GRAMWR);
}

void Write_RRR()
{
  write_cmd_data(0x0003, 0x10B8);
}
void Write_GGG()
{
  write_cmd_data(0x0003, 0x1030);
}

//===============================================================
//设定当前显示坐标
//入口参数: x,y为当前显示坐标。
//出口参数: 无
//说明：本函数实际上是LCD_setwindow函数的一个特例，显示窗口为最小，仅是一个像素点。
void LCD_setxy(unsigned char x,unsigned int y)
{
	LCD_setwindow(x,y,x,y);	
}


//===============================================================
//彩条、单色自测程序
//入口参数: 无。
//出口参数: 无
//说明：在TFT屏上轮流显示彩条和各种颜色的单色屏幕。
void LCD_test()
{
	unsigned int temp,num;
	unsigned char n,c;

	//显示彩条	
	LCD_setwindow(0,0,239,319); //x方向0~239行，Y方向0~239行
	for(n=0;n<8;n++)
	{
	   temp=color[n];/*颜色数值:红色，绿色，蓝色，黄色，黑色，白色，天蓝色，紫色*/									
		for(num=40*240;num>0;num--)
	   	write_data_u16(temp);
	}
	delay_us(1000);

	//显示单色彩色
	for(c=0;c<8;c++)
	{
		temp = color[c];
		LCD_setwindow(0,0,239,319);
		for(n=0;n<240;n++)
		{
			for(num=0;num<320;num++)
			  write_data_u16(temp);
	 	}
   	delay_us(1000);
	}
}

