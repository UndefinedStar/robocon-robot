#ifndef FILTER_H_
#define FILTER_H_
/*
* 		ͷ�ļ�����
*/
#include "stm32f4xx.h"
#include <math.h>
#include <stdio.h>
/*
* 		ͨ�ú궨��
*/
#define			SAMP_RATE					1000							//����Ƶ��(Hz)
#define			CUTOFF_RATE				100							//��ֹƵ��,ʵ�ʽ�ֹƵ��Ϊ100Hz
#define			pi							3.15159265
#define			SAMP_TIME					0.0010						/*��������*/
#define 		abs(num)  					(((num)>0)?(num):-(num))
#define			SCALE						0.0127						/*(1000*5)/(65535*6)*(N-ZERO_POinT)*/
#define			POS_SCALE			0.012540060//0.012535880//0.012528916					/*����������ת�Ļ���ϵ��*/
#define			NEG_SCALE			0.012543174  				/*�����Ƿ���ת�Ļ���ϵ��*/
#define			MAX_NUM						10								/*ð�����������ݵ���Ŀ*/
#define			MAX_ZP_SAMPLE				2000
#define			ZERO_THREDHOLD				(float)(16.5)//(16.58)					/*���ǰ�����β����ľ���ֵС����ֵ�����ô����ݸ������*/
#define			THETA						0.65					/*һ�׵�ͨ�˲�ϵ��*/
/*һ��kalman �ṹ�嶨��*/
typedef struct tag_k_filter
{
	int32_t	A;				/*ϵͳ״̬ת�ƾ���*/
//	float B;						/*������������о���*/
	int32_t H;					/*�۲�����о���*/
									/*ǰ��������Ϊϵͳ�Ĳ������󣬼�������Ѿ�������ֱ�Ӵ��룬����������̲��ô˾��󣬽�����¼��*/

	float Ck;					/*Ԥ�����Э�������     C(k|k)  */
	float C_last;				/*�ϴ�Ԥ�����Э������� C(k|k-1)*/
	float Q;						/*��������*/
	float Rk;						/*�۲�����*/

	float X;						/*ϵͳ״̬�˲���������о���*/
	float X_last;				/*ϵͳ״̬Ԥ������о���*/
	float kg;					/*���������棬�о���*/
	float zero_point;		/*kalman filter zero_point*/					
	float input;					/*����ֵ����Z(k)*/
}
k_filter;
/*�����˲��ṹ�嶨��*/
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


/*���׵�ͨ�˲����ṹ��*/
typedef struct tag_second_order
{
	unsigned int fs;				//����Ƶ��(Hz)
	unsigned int f0;				//��ֹƵ��,ע��Ҫ��2����ʵ�ʵĽ�ֹƵ(Hz)
	float den;
	float a;						//x[n]ϵ��
	float b;						//y[n-1]ϵ��
	float c;						//y[n-2]ϵ��
	float current_output;			//y[n]
	float last_output;				//y[n-1]
	float last_last_output;			//y[n-2]
}
second_order_struct;



extern k_filter kal_filter; 
extern comb_filter comb_flt;
extern second_order_struct second_order_flt;

/*
* 		�˲���������
*/

/*
* 		kalman�˲�����ʼ��
*		k1_flt: һ��kalmanָ��
*/
extern void kal_flt_init(k_filter* k_flt);
/*
* 		kalman�˲�����ʼ��
*		k1_flt: һ��kalmanָ��
*/
extern float kalman_filter(k_filter* k_flt , float input);
/*
* 		����˲���
*		comb_flt: comb_filter ָ��
*/
extern float combination_filter(comb_filter* comb_flt);
/*
* 		second_order�˲�����ʼ��
*		second_struct: �����˲�ָ��
*/
extern void second_order_init(second_order_struct* second_struct);
/*
* 		second_order�˲���
*		second_struct: �����˲�ָ�룬input---����
*/
extern float second_order_filter(second_order_struct* second_struct,float input);
#endif/*FILTER_H_*/
//--------------------------end of line------------------------------------
