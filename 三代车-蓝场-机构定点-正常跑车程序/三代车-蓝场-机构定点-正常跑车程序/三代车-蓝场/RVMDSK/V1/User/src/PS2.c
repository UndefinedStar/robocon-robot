#include "PS2.h"


u16 HandKey = 0xffff;
u16 HandKey_old = 0xffff;
u16 HandRock_left= 0x7B84;
u16 HandRock_left_old= 0x7B84;
u16 HandRock_right= 0x847B;
u16	HandRock_right_old= 0x847B;
int send_picture_flag = 0;
unsigned char HandMode=0;	//手柄模式，1-按键模式，2-摇杆模式


void BlueHand(void)	//读取蓝牙手柄
{
	//更新蓝牙接收到的键值
	HandKey				=	HandKey_Receive;
	HandRock_left	=	HandRock_left_Receive;
	HandRock_right=	HandRock_right_Receive;
	HandMode			=	HandMode_Receive;
	//清除接收到的键值

//	HandKey_Receive				=	0xFFFF;
//	HandRock_left_Receive	=	0x7B84;
//	HandRock_right_Receive=	0x847B;
//	HandMode_Receive			=	0;
}

void ReadHand(void)
{
	//记录上次键值
	HandKey_old=HandKey;
	HandRock_left_old=HandRock_left;
	HandRock_right_old=HandRock_right;
	if(HandKey_old==0xEFFF)
		send_picture_flag = 1;
	
	BlueHand();
}
