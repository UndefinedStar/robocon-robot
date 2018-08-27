#ifndef FILTER_H_
#define FILTER_H_
/*
* 		头文件包含
*/
#include "includes.h"
#include "rundriver.h"
#include <stdio.h>

/*复合滤波结构体定义,去掉极值求平均*/

typedef struct KALMAN
{
    double Q;       //过程噪声的协方差
    double R;       //观测噪声的协方差
    
    double x_last;  //上次的最优值，本次测量值，本次最优值
    double p_last;  //上次协方差，本次预测协方差，本次协方差
    
    double kg;      //kalman增益
    
    double A;       //系统转移矩阵，
    double H;       //观测转移矩阵   
		
    double best;

}KALMAN_filter;


/*二阶低通滤波器结构体*/
typedef struct tag_second_order
{
	unsigned int fs;				//采样频率(Hz)
	unsigned int f0;				//截止频率,注意要乘2才是实际的截止频(Hz)
	float den;
	float a;								//x[n]系数
	float b;								//y[n-1]系数
	float c;								//y[n-2]系数
	float current_output;		//y[n]
	float last_output;			//y[n-1]
	float last_last_output;	//y[n-2]
}second_order_struct;

extern second_order_struct second_order_flt_X;
extern second_order_struct second_order_flt_Y;
extern second_order_struct second_order_flt_Vx;
extern second_order_struct second_order_flt_Vy;
extern second_order_struct second_order_flt_DT50;
extern second_order_struct second_order_flt_Rotate;

void  kalman_init(KALMAN_filter* kalman);
double KAL_filter(KALMAN_filter *kalman,double input);
void second_order_init2(second_order_struct* second_struct, unsigned int f0);	//二阶低通滤波器初始化
double second_order_filter2(second_order_struct* second_struct,double input);	//二阶低通滤波 -- 运行 44.58us

#endif


