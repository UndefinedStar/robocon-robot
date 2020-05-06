#include "Kalman.h"

k_filter kal_filter = {0};
comb_filter comb_flt = {0};
second_order_struct second_order_flt = {0};
/*
*
* 		kalman结构体初始化
*
*/
void kal_flt_init(k_filter* k_flt)
{
	k_flt->A = 1;
	k_flt->H = 1;

	k_flt->C_last = 1;			/*过程协方差*/
	k_flt->X_last = 200;	/*系统初始值*/
	k_flt->Q = 0.0001;	   	/*过程噪声*/
	k_flt->Rk = 0.3;				/*量测噪声*/

	k_flt->input = 0;				/*初始输入为0*/
}
/*
*
* 		kalman filter 的实现
*
*/
float kalman_filter(k_filter* k_flt, float input)    
{
	/*量测方程的更新，3组方程*/
	k_flt->input = input;
	k_flt->kg = (k_flt->C_last)/(k_flt->C_last + k_flt->Rk);			/*kg(k) = C(k|k-1)*H(转置)/[H*C(k|k-1)*H(转置)+R] */
	k_flt->X  = k_flt->X_last + k_flt->kg * (k_flt->input - k_flt->X_last);
																	/*X(k|k) = X(k|k-1)+kg(k)*[Z(k)-H*X(k|k-1)]*/
	k_flt->Ck =  (1-k_flt->kg)*(k_flt->C_last);						/*C(k|k) = [I-kg(k)*H]*C(k|k-1) */
	/*积分得角度*/
//	k_flt->output = k_flt->output + k_flt->X*SAMP_TIME;
	/*时间更新方程，2组方程*/
	k_flt->X_last = k_flt->X;										/*X(k+1|k) = A*X(k|k)*/
	k_flt->C_last = k_flt->Ck + k_flt->Q;							/* C(k+1|k) = A*C(k|k)*A(转置)+B*Q*B(转置)*/

	return k_flt->X;

}
/*
*
* 		复合滤波的实现：融合低通滤波和限幅滤波，剔除最大值和最小值，剩余值求平均
*
*/
float combination_filter(comb_filter* comb_flt)
{
	int i=0;
	comb_flt->sum = 0;
	comb_flt->max = comb_flt->data[0];
	comb_flt->min = comb_flt->data[0];
	for (i=1; i<MAX_NUM; i++)
	{
		if (comb_flt->max < comb_flt->data[i])
		{
			comb_flt->max = comb_flt->data[i];
		} 
 		if (comb_flt->min > comb_flt->data[i])
		{
			comb_flt->min = comb_flt->data[i];
 		}

	}
	for (i=0 ;i< MAX_NUM; i++)
	{
		comb_flt->sum += comb_flt->data[i];
	}
	comb_flt->sum = comb_flt->sum - comb_flt->max - comb_flt->min;
	comb_flt->average = (float)(comb_flt->sum/(MAX_NUM-2));
	comb_flt->comb_filter_flag = 1;
	return 	comb_flt->average;	
}
/*
* 		second_order滤波器初始化
*		second_struct: 滤波器结构体
*/
void second_order_init(second_order_struct* second_struct)
{
	second_struct->fs = SAMP_RATE;
	second_struct->f0 = CUTOFF_RATE;
	second_struct->den = (second_struct->fs)*(second_struct->fs) + 6*pi*(second_struct->f0)*(second_struct->fs) + 4*pi*pi*(second_struct->f0)*(second_struct->f0);
	second_struct->a = 4*pi*pi*(second_struct->f0)*(second_struct->f0)/(second_struct->den);
	second_struct->b = (2*(second_struct->fs)*(second_struct->fs) + 6*pi*(second_struct->fs)*(second_struct->f0))/(second_struct->den);
	second_struct->c = (second_struct->fs)*(second_struct->fs)/(second_struct->den);
	second_struct->last_output = 0.1;
	second_struct->last_last_output = 0;
}
/*
* 		second_order实现函数
*		second_struct: 二阶结构体,input---当前输入的数据
*/
float second_order_filter(second_order_struct* second_struct,float input)
{
	second_struct->current_output = (second_struct->a)*input + (second_struct->b)*(second_struct->last_output) - (second_struct->c)*(second_struct->last_last_output);	
	second_struct->last_last_output = second_struct->last_output;
	second_struct->last_output = second_struct->current_output;
	return second_struct->current_output;
}

