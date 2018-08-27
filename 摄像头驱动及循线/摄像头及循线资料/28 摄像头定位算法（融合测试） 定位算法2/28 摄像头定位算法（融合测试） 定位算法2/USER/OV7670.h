#include "sys.h"
#ifndef OV7670_H
#define OV7670_H

#define Mode_QICF   // QICF模式
#define Model_RGB    //RGB输出模式
#define TFT_OutPut   //看TFT输出

#define OV7670_DEVICE_WRITE_ADDRESS    0x42
#define OV7670_DEVICE_READ_ADDRESS     0x43

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

//d3 rck D5 WR OE D7 WRRST G12 WRST G10
/*OV7670FIFO模块控制引脚定义*/
//#define FIFO_PWDN  PAout(0)			//功耗设定端口，正常使用接地
//#define FIFO_RST   PAout(1)			//7670复位端口，不用时接高
#define FIFO_RCK   PDout(3)			//读数据端口时钟，一个时钟周期读八个字节数据
#define FIFO_WR    PDout(5)			//写控制端 1：允许CMOS写入FIFO 0 禁止 
#define FIFO_OE	   PDout(7)			//关断FIFO的使能端 1：关断FIFO 0 使能FIFO
#define FIFO_WRST  PGout(10)			//写指针复位端口，执行写指针复位
#define FIFO_RRST  PGout(12)			//读指针复位端口，与RCK配合时序完成读指针复位操作
//#define FIFO_STR   PAout(7)			//闪光灯端口，不用的时候悬空
//再会用到一个VSYNC作为一个中断信号接在PC4上面

void set_Cmos7670reg(void);	
unsigned char Cmos7670_init(void);
void ov7670_PortConfig(void);
#endif

/*
模块引脚作用SIOC SIOD ： IIC通信引脚
VSYNC ： 帧同步引脚，一次中断传送一帧数据，是沿信号
HREF : 像素始终信号 ，一次高电平接收一行像素信号，是电平信号，高电平允许数据位变化
总的看起来，VSYNC出现下降沿中断，则开始一帧传输，每一帧通过HREF信号来一行一行输出
RST:复位
PWDN:直接接地了（战舰的做法）
D[0：7]: FIFO的数据输出口
STROBE:悬空什么都不接（战舰的做法）
RCK:读FIFO数据时钟
WEN:FIFI写数据时能，WE与HREF与非门输出信号 OE
//深刻理解，WE代表FIFO写使能，HREF代表7670读使能，两者与非，说明不能两个同时使能
//必须等7670读完了，FIFO再写进缓存里，FIFO写完了7670开始读，此时开启输出OE，所以是与非门

OE：FIFO输出使能
WR: FIFO模块写使能，个人理解应该是WRITE/READ 转换 为1的时候写使能

WRST: 写指针复位，7670写到FIFO里的指针
RRST：读指针复位，MCU读取FIFO数据的指针

OV7670摄像头模块存储图像数据的过程为（即FIFO读取7670图像并储存在缓存中的步骤）：
1：等待OV7670同步信号（等待VSYNC的沿信号，利用中断）?
2：FIFO写指针复位（接下来开始写进缓存，所以写指针复位，操作WRST）
3：FIFO写使能 （表明已经可以开始写了，操作WR写使能）
4：等待第二个OV7670同步信号（再等待一次中断）?
5：FIFO写禁止。（操作WR取消写使能（7670写到fifo里），变为读使能（单片机读fifo），读写转换）
通过以上5个步骤，我们就完成了1帧图像数据的存储。



//数据处理

在存储完一帧图像以后，我们就可以开始读取图像数据了。读取过程为
1：FIFO读指针复位
2: 给FIFO读时钟（FIFO_RCLK）?读取第一个像素高字节
3: 给FIFO读时钟?			  读取第一个像素低字节?
4：给FIFO读时钟?             读取第二个像素高字节?循环至结束。


//失败了很多次的教训
1：抓清楚问题所在，在行动之前仔细分析，哪里出现问题的可能性最大，不要到处测试，到处找问题，这次就是因为IIC通信出现问题
就把各种各样的问题全部 分析了一边，没有意识到是寄存器配置有问题，以后拿到了一个器件，先读他的ID，确定通信正常之后，再
继续下一步的指令。
2：寄存器暂且先相信网上的设定，毕竟人家正确跑过，当自己熟悉了之后，在自己设定寄存器。
以后就多了一个模块供我驱使了哈哈，VO7670的知识很关键，很好，摄像头可以算是入门了以上都是宝贵的驱动资料
*/
