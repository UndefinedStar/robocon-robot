#ifndef FILTER_H_
#define FILTER_H_
/*
* 		头文件包含
*/
#include "stm32f4xx.h"
#include <math.h>
#include <stdio.h>
/*
* 		通用宏定义
*/
#define			SAMP_RATE					1000							//采样频率(Hz)
#define			CUTOFF_RATE				100							//截止频率,实际截止频率为100Hz
#define			pi							3.15159265
#define			SAMP_TIME					0.0010						/*采样周期*/
#define 		abs(num)  					(((num)>0)?(num):-(num))
#define			SCALE						0.0127						/*(1000*5)/(65535*6)*(N-ZERO_POinT)*/
#define			POS_SCALE			0.012540060//0.012535880//0.012528916					/*陀螺仪正向转的积分系数*/
#define			NEG_SCALE			0.012543174  				/*陀螺仪反向转的积分系数*/
#define			MAX_NUM						10								/*冒泡排序处理数据的数目*/
#define			MAX_ZP_SAMPLE				2000
#define			ZERO_THREDHOLD				(float)(16.5)//(16.58)					/*如果前后两次采样的绝对值小于阈值，则用此数据更新零点*/
#define			THETA						0.65					/*一阶低通滤波系数*/
/*一阶kalman 结构体定义*/
typedef struct tag_k_filter
{
	int32_t	A;				/*系统状态转移矩阵*/
//	float B;						/*噪声输入矩阵，列矩阵*/
	int32_t H;					/*观测矩阵，行矩阵*/
									/*前三个矩阵为系统的参数矩阵，计算过程已经将矩阵直接代入，程序运算过程不用此矩阵，仅作记录用*/

	float Ck;					/*预测过程协方差矩阵     C(k|k)  */
	float C_last;				/*上次预测过程协方差矩阵 C(k|k-1)*/
	float Q;						/*过程噪声*/
	float Rk;						/*观测噪声*/

	float X;						/*系统状态滤波输出矩阵，列矩阵*/
	float X_last;				/*系统状态预测矩阵，列矩阵*/
	float kg;					/*卡尔曼增益，列矩阵*/
	float zero_point;		/*kalman filter zero_point*/					
	float input;					/*量测值，即Z(k)*/
}
k_filter;
/*复合滤波结构体定义*/
typedef struct tag_comb_filter
{
	uint16_t max;
	uint16_t min;
	float average;
	float sum;
	unsigned char comb_filter_flag;
	uint16_t data[MAX_NUM];
}
comb_filter;


/*二阶低通滤波器结构体*/
typedef struct tag_second_order
{
	unsigned int fs;				//采样频率(Hz)
	unsigned int f0;				//截止频率,注意要乘2才是实际的截止频(Hz)
	float den;
	float a;						//x[n]系数
	float b;						//y[n-1]系数
	float c;						//y[n-2]系数
	float current_output;			//y[n]
	float last_output;				//y[n-1]
	float last_last_output;			//y[n-2]
}
second_order_struct;



extern k_filter kal_filter; 
extern comb_filter comb_flt;
extern second_order_struct second_order_flt;

/*
* 		滤波函数定义
*/

/*
* 		kalman滤波器初始化
*		k1_flt: 一阶kalman指针
*/
extern void kal_flt_init(k_filter* k_flt);
/*
* 		kalman滤波器初始化
*		k1_flt: 一阶kalman指针
*/
extern float kalman_filter(k_filter* k_flt , float input);
/*
* 		组合滤波器
*		comb_flt: comb_filter 指针
*/
extern float combination_filter(comb_filter* comb_flt);
/*
* 		second_order滤波器初始化
*		second_struct: 二阶滤波指针
*/
extern void second_order_init(second_order_struct* second_struct);
/*
* 		second_order滤波器
*		second_struct: 二阶滤波指针，input---输入
*/
extern float second_order_filter(second_order_struct* second_struct,float input);
#endif/*FILTER_H_*/
//--------------------------end of line------------------------------------
