
#include "led.h"


void LED_GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		//����һ���ṹ��ָ�룬ָ���װ�ļĴ����׵�ַ
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		//����������APB2�ϵ�GPIOCʱ������ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		//ѡ�����õ�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//����Ϊ�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		//ѡ������ٶ�
	
	  //�����ָ�ֵ���
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		//�ѿ����ֽ�ֱ��д���Ӧ�Ĵ����׵�ַ  ʹ���Ƕ���Ŀ�������Ч  ��һ������ʱ Ҫ���õ��Ķ˿� �ڶ����Ǵ�ſ����ֵĽṹָ��
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	  //�⺯���и������������ߵ�ƽ�Ŀ⺯��
	  //�͵�ƽ�Ŀ⺯����ӦΪ GPIO_ResetBits��һ������������Ƕ˿ں� �ڶ������������Ǹö˿ںŵľ�������
		//�ر����е�


		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);
		//����������APB2�ϵ�GPIOCʱ������ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		//ѡ�����õ�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//����Ϊ�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		//ѡ������ٶ�
	
	  //�����ָ�ֵ���
		GPIO_Init(GPIOC,&GPIO_InitStructure);
		//�ѿ����ֽ�ֱ��д���Ӧ�Ĵ����׵�ַ  ʹ���Ƕ���Ŀ�������Ч  ��һ������ʱ Ҫ���õ��Ķ˿� �ڶ����Ǵ�ſ����ֵĽṹָ��
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
}