#ifndef _IMAGE_H
#define _IMAGE_H

#include "stm32f4xx.h"
#include "math.h"
#include "pid.h"
#include "ili9320_api.h"
#include "led_show.h"
#include "Kalman.h"
#include "led.h"
#include "usart.h"

#define IMAGE_COLUMN 320
#define IMAGE_ROW    200

#define R 41
#define C 80


extern int left[R];//记录左边缘的数组
extern int right[R];//记录右边缘列的数组
extern int edge[R];//记录边缘像素跳变值
extern int center[R+1];
extern int number;//从最后一行采集到倒数第三行
extern int left_angle_flag, right_angle_flag,ll,rr;
extern int whitelost_left;
extern float control_message;
extern int edge_row0;
extern int white_count;
extern double row_sub,white_count_ratio;
extern double race,race1;
extern int center_row;
extern int nu,eff_row,nu_last;
extern int zd_flag2,start_row;
extern int control_line,pixel_value;
extern int sp_flag,hd_flag,xp_flag,zj_start,img_stop_flag,img_cross_flag,hand_restart; 
extern int hd_stage_flag;
//extern int FrameCount,framecount;
extern int Detect;
extern int row_white_count22;
extern int start_row_hd,stop_row_hd,standard_row;
extern int stop_time;
extern int sum_left, sum_right;
extern int zj_keep_flag;
extern int restart_flag;
extern int center_base;
extern int cross_flag;
extern int stage_flag,beep_count;
extern int ZjClearDistance,ZjDetectDistance,Hd1ToHd5Distance,Hd1ToXpDistance,XpScDistance;
extern s16 speed_now;
extern s16 speed_left,speed_hd1,speed_hd5,speed_now_hd5,speed_xp,speed_stop1,speed_stop2,speed_stop3,speed_stop4,speed_last2,speed_sc,speed_last;
extern float race_hd1,race_hd2,race_hd3,race_hd4,race_hd5,Xp3RaceTop,Xp3RaceCross;
extern int early_late_flag,late_cut_down;
extern int zj_speed,speed_time,zj_sc_count,beep_send_flag,beep_count_send,beep_time_send,zj_time;
extern int center_average;
extern u8 XpHuorStartFlag;
extern int xp_threshold_value,xp_value_su;

// 直角
extern int ZjBigAngleRow,ZjScSpeed ;
// 河道
extern float HdAngle;
extern int HdScSpeed;
// 下坡
extern float xpp1,xpp2,xpp3;
extern int XpScSpeed;
extern u8 ScreenChangeFlag;
enum image_type
{
    IMAGE_TYPE_Y,
    IMAGE_TYPE_Cb,
    IMAGE_TYPE_Cr,
};

void Transfer2Gray(uint16_t *image,uint8_t  *gray_image);
void Transfer2Gray_UV(uint16_t *image,uint8_t  *gray_image);
void image_threshold_sp(u8 *Data);
void image_threshold_hd(u8 *Data);
void image_threshold_hd_improve(u8 *Data);
void image_threshold_xp(u8 *Data);
void midline_draw(u8 *img);
void midline_draw_hd(u8 *img);
float error_ca(void);
void race_identity(void);
void Screen(void);
int restart_judge(u8 *Data);
s16 max(s16 *a);
 

#endif
