#include "stm32f10x.h"
#include "led.h"  //灯的设置
#include "ILI9325_32.h"//给TFT显示用
#include "ov7670.h"//控制引脚定义
#include "switch.h"
#define Windows_X 176
#define Windows_Y 220//7670扫描的像素范围

#define IntervalLinI  8;
#define IntervalLinJ  8;
//分隔多少行和列扫描数据 是数据稀疏化的重要参数，系数的越少控制量越精准，但是牺牲了速度
void PictureAnalyse(void);//获取并且分析图片数据
void TakeVerfPhoto(void);//抓拍参考值

