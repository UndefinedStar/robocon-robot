#ifndef _USER_TYPEDEF_H
#define _USER_TYPEDEF_H

//定义结构体数据类型
typedef struct pot
{
	float X;				//机器人自身坐标系原点在场地坐标系中的X坐标，cm
	float Y;				//机器人自身坐标系原点在场地坐标系中的Y坐标，cm
	float AngleDeg;	//机器人的姿态角(场地坐标系X轴转向自身坐标系X轴)，角度制，顺负逆正
	float Sum_Encoder1;//码盘1走过的路程
	float Sum_Encoder2;//码盘2走过的路程
}POSITION;

typedef struct spd
{
	float Vx;				//机器人在场地坐标系X轴方向的分速度，cm/s
	float Vy;				//机器人在场地坐标系Y轴方向的分速度，cm/s
	float Vw;				//机器人角速度，度/s,顺负逆正
}ABSOLUTE_SPEED;

#endif
