#include "filter.h"

second_order_struct second_order_flt_X = {0};
second_order_struct second_order_flt_Y = {0};
second_order_struct second_order_flt_Vx = {0};
second_order_struct second_order_flt_Vy = {0};
second_order_struct second_order_flt_DT50 = {0};
second_order_struct second_order_flt_Rotate = {0};

void kalman_init(KALMAN_filter* kalman)
{
    kalman->x_last=1;
    kalman->p_last=5;     //这两个数值初始化无所谓，但P不要为0
    
//    kalman->Q=0.001;     //过程噪声
//    kalman->R=0.03; 			//观测噪声,即原始速度数据的方差？？？？
    kalman->Q=0.003;     //过程噪声
    kalman->R=0.05; 			//观测噪声,即原始速度数据的方差？？？？
    kalman->A=1;         //简化单模型
    kalman->H=1;
}

double KAL_filter(KALMAN_filter *kalman,double input)
{
    kalman->x_last=kalman->A*kalman->x_last;                //根据上一次的值预测本次的值    
    kalman->p_last=kalman->p_last+kalman->Q;                //根据上一次的协方差计算本次的协方差    
    kalman->kg=kalman->p_last/(kalman->p_last+kalman->R);   //根据本次的协方差计算kalman增益    
    kalman->x_last=kalman->x_last+kalman->kg*(input-kalman->H*kalman->x_last);//求出本次的最有值    
    kalman->p_last=(1-kalman->kg)*kalman->p_last;           //求出本次的协方差	
	kalman->best=kalman->x_last;    
    return kalman->best;
}

void second_order_init2(second_order_struct* second_struct, unsigned int f0)	//二阶低通滤波器初始化
{
	second_struct->fs = 1000;
	second_struct->f0 = f0;
	second_struct->den = (second_struct->fs)*(second_struct->fs) + 6*PI*(second_struct->f0)*(second_struct->fs) + 4*PI*PI*(second_struct->f0)*(second_struct->f0);
	second_struct->a 	= 4*PI*PI*(second_struct->f0)*(second_struct->f0)/(second_struct->den);
	second_struct->b 	= (2*(second_struct->fs)*(second_struct->fs) + 6*PI*(second_struct->fs)*(second_struct->f0))/(second_struct->den);
	second_struct->c 	= (second_struct->fs)*(second_struct->fs)/(second_struct->den);
}

double second_order_filter2(second_order_struct* second_struct,double input)	//二阶低通滤波 -- 运行 44.58us
{
	second_struct->current_output = (second_struct->a)*input + (second_struct->b)*(second_struct->last_output) - (second_struct->c)*(second_struct->last_last_output);	//计算出本次滤波输出
	second_struct->last_last_output = second_struct->last_output;	//更新上上次输出
	second_struct->last_output = second_struct->current_output;		//更新上次输出
	return second_struct->current_output;	//返回本次滤波输出
}
