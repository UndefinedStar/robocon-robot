#include "stm32f10x.h"
#include "led.h"  //�Ƶ�����
#include "ILI9325_32.h"//��TFT��ʾ��
#include "ov7670.h"//�������Ŷ���
#include "switch.h"
#define Windows_X 176
#define Windows_Y 220//7670ɨ������ط�Χ

#define IntervalLinI  8;
#define IntervalLinJ  8;
//�ָ������к���ɨ������ ������ϡ�軯����Ҫ������ϵ����Խ�ٿ�����Խ��׼�������������ٶ�
void PictureAnalyse(void);//��ȡ���ҷ���ͼƬ����
void TakeVerfPhoto(void);//ץ�Ĳο�ֵ

