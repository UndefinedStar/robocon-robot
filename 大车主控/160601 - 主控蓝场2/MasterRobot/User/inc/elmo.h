/*
********************************************************************************
	*@  file: elmo.h
	*@  author: Kevin
	*@  data: 11/14/2013
	*@  version: v1.3
	*@  brief: �����޸ģ���Ҫ�Ҷ�������
	*...............................................................................
	*@
	*@ Notes: (1) �޸�ElMO_NUM��ֵȷ��Elmo����,����Ϊ4��Elmo.
	*@            ��������Elmo,�ڼӺź������.
	*@        (2) �޸ĵ������,�����,��ֵ����,������ת��.
	*@            ��Щ�ǵ��̵ĵ���Ĳ���.����ʹ������Elmo,��ֱ�ӵ��ú���.
	*@            ��������������������Ϊ����5��ID��.
	*@        (3) ***********************************************************
	*@            *  MAXON����ͺ�       �ת��(RPM)  �����(A) ����(W) *
	*@            *  EC-4pole-30-305013  16200          9.21        200     *
	*@            *  RE-40-148867        6930           5.77        150     *
	*@            *  RE-50-370354        5680           10.8        200     *
	*@            *  RE-30-310007        8050           3.44        60      *
	*@            *  RE-25-339152        9620           1.42        20      *
	*@            ***********************************************************
	*@
	               
********************************************************************************
*/

#ifndef _ELMO_H
#define _ELMO_H
#include "stm32f4xx.h"
#include "stdio.h"						   //printf init
#include "stdlib.h"
#include "string.h"



/*******************************************************************************
* �궨�� 
*******************************************************************************/
/* 0:���ٶȿ���ģʽ�������ٶ�ģʽ,��ʱ���ٶ�ʧЧ */ 
/* 1:��λ�ÿ���ģʽ�������ٶ�ģʽ,��ʱ���ٶ���Ч */ 
#define  JV_IN_PCM          0


/* ѭ�����в��� */
#define ELMO_NUM            (3)                             // Elmo����,�����ϸ��չ��ظ�����ELMO���ã����ö����ã�����
#define CAN_BUF_NUM         1000                            //����ָ������
#define CAN_ID_DELAY        0x128                           //��ʱָ��

/* ELMO��ز��� */
#define RATE_CURRENT        10.8                           // �����(A)
#define PEAK_CURRENT        (10.8*2)                       // ��ֵ����(A)
#define MAX_VOLOCITY        5680                           // ������ת��(rpm)

/* ����������ز��� */
#define RATE_CUR            RATE_CURRENT                    // �����(A)          CL[1]
#define MAX_CURRENT         PEAK_CURRENT                    // ��ֵ����(A)          PL[1]
#define MAX_PM_SPEED        (MAX_VOLOCITY*4000/60)          // ���ƽ���ٶ�(cnt/s)  VH[2]
#define MIN_PM_SPEED        (u32)(-MAX_PM_SPEED)            // ��Сƽ���ٶ�(cnt/s)  VL[2]
#define MAX_FB_SPEED        ((MAX_VOLOCITY+1000)*4000/60)   // ������ٶ�(cnt/s)  HL[2]
#define MIN_FB_SPEED        (u32)(-MAX_FB_SPEED)            // ��С�����ٶ�(cnt/s)  LL[2]

/* ƽ���˶���ز��� */ 
#define PM_ACC              3500000                         // ƽ�����ٶ�(cnt/s^2)  AC
#define PM_DEC              3500000                         // ƽ�����ٶ�(cnt/s^2)  DC
#define QUICKSTOP_DEC       1000000000                      // ��ͣ���ٶ�(cnt/s^2)  SD
#define POSITION_LIMIT_MAX  1000000000                      // ���λ�ü���         VH[3] HL[3]
#define POSITION_LIMIT_MIN  (u32)-1000000000                // ��Сλ�ü���         VL[3] LL[3]

/* CANopen COB identifiers */
#define COBID_NMT_SERVICE   0x000					
#define COBID_SYNC          0x080
#define COBID_EMERGENCY     0x080
#define COBID_TIME_STAMP    0x100
#define COBID_TPDO1         0x180
#define COBID_RPDO1         0x200
#define COBID_TPDO2         0x280
#define COBID_RPDO2         0x300
#define COBID_TPDO3         0x380
#define COBID_RPDO3         0x400
#define COBID_TPDO4         0x480
#define COBID_RPDO4         0x500
#define COBID_TSDO          0x580
#define COBID_RSDO          0x600
#define COBID_HEARTBEAT     0x700

/* NMT Command Specifier */
#define NMT_ENTER_OPERATIONAL      0x01
#define NMT_ENTER_STOPPED          0x02
#define NMT_ENTER_PRE_OPERATIONAL  0x80
#define NMT_RESET_NODE             0x81
#define NMT_RESET_COMMUNICATION    0x82

/* Binary Interpreter Command */
#define UM_IDLE             0x00
#define UM_TCM              0x01                      // Torque control mode,���ؿ���ģʽ
#define UM_PCM              0x05                      // Position control mode��λ�ÿ���ģʽ
#define UM_UNC              0x06                      // ����ȷ��ģʽ��������ȫ���������

#if JV_IN_PCM
   #define UM_SCM           0x05                      // Position control mode��
#else
   #define UM_SCM           0x02                      // Speed control mode
#endif

#define TYPE_INTEGER      0
#define TYPE_FLOAT        1

#define MO_OFF            0
#define MO_ON             1

#define POS_REL           0
#define POS_ABS           1



/*******************************************************************************
* �ṹ��
*******************************************************************************/
/* CANѭ������Ԫ�� */ 
typedef struct __CANDATA 
{
   u16 COBID;               // CANopen COB identifier + NodeID
   u8  DLC;                 // Data Length Code
   u8  DATA[8];             // Data
} CANDATA;

/* CANѭ�����нṹ�� */
typedef struct __CANQUEUE
{
   u16 Front;        
   u16 Rear;
   CANDATA CANBUF[CAN_BUF_NUM];
} CANQUEUE;

/* Elmo�ṹ��,��¼�ڵ�ID,״̬�Ϳ��Ʋ��� */
typedef struct __Elmo
{
   u8 NodeID;         // elmo����
   u8 CurOPMode;      // ��ǰ����ģʽ 
}Elmo;


/*******************************************************************************
* ��������
*******************************************************************************/
/* CAN����ѭ������QUEUE_CAN2 */ 
static CANQUEUE QUEUE_CAN2;
/* elmo[0]Ϊ�㲥,elmo[i]Ϊ��i��Elmo */ 
static Elmo elmo[ELMO_NUM + 1];
/* ����elmo */
static Elmo elmogroup;

/*******************************************************************************
* ��������
*******************************************************************************/
/* ELMO��ʼ������,������� */
extern u32 Elmo_Init( CAN_TypeDef* CANx, uint8_t PPr, uint8_t SPr);

/* ELMO���ƺ������������ */
extern u8 Elmo_PTM(u8 elmoID, float torque);
extern u8 Elmo_PVM(u8 elmoID, s32 speed);  
extern u8 Elmo_PPM(u8 elmoID, u32 speed, s32 position, u8 PPMmode);		//		POS_ABS  POS_REL 
extern u8 Elmo_Close(u8 elmoID);
extern u8 Elmo_Stop(u8 elmoID);
extern u8 Elmo_SetAcc(u8 elmoID, u32 acc, u32 dec);


/* CANOpen��ʵ�ֺ���,��������� */
static void NMTCmd(Elmo *elmo, u8 MNTCmd);
static void RSDO(Elmo *elmo, u16 Index, u8 SubIndex, u32 Data);
static void RPDO2_Cmd_data(Elmo *elmo, u8 *Cmd, u8 Index, u8 Type, u32 Data);
static void RPDO2_Cmd_string(Elmo *elmo, u8 *Cmd);

/* Ӳ����ʼ������,��������� */
static void CAN_init(CAN_TypeDef* CANx);                    
static void TIM7_init(uint8_t PPr, uint8_t SPr);
static int Self_test(void);
static void Variate_init(void);

/* ���ݷ��͡�ת������ʱ����,��������� */
static void Elmo_SendCmd(void);
static void Elmo_CANSend(CANDATA *pCANDATA);
static void Elmo_Delay100us(u8 N100us);
static void Elmo_software_delay_ms(unsigned int t);
static u32 f2h(float x);


#endif


