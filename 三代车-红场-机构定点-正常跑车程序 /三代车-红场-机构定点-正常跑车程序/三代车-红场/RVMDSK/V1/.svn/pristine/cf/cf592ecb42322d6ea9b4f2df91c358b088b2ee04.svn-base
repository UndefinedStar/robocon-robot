#include "state_change.h"
void StateChange(void)
{
		if(sp_flag==1&&Detect>=1)
		{
			right_angle_flag = 0;
			if(left_angle_flag==1&&(double)white_count_ratio<0.1&&(double)white_count_ratio>0.03&&standard_row>15&&nu>20)
			{ 
				sp_flag=0;
				hd_flag=1;
				zj_sc_flag=0;
				Detect=0;
				left_angle_flag = 0;
			}
		}
		/* 河道标志位，分为5个阶段 */
		if(hd_flag==1)
		{
			if((sum_right>30||(double)race<-0.6)&&hd_stage_flag==0)
			{
				hd_stage_flag = 1; 
			}
			else if(((double)race>0.2)&&hd_stage_flag==1)
			{
				hd_stage_flag = 2;
			}
			else if((sum_right>20||(double)race<-0.3)&&hd_stage_flag==2)
			{
				hd_stage_flag = 3; 
			}
			else if(((double)race>0.12)&&hd_stage_flag==3)
			{
				hd_stage_flag = 4;
			}
			else if(((double)race<-0.5)&&hd_stage_flag==4)//&&Fdistance>8.15
			{
				hd_stage_flag = 5;
			}
		}	
		/* 下坡标志位，分为四个阶段 */
		if(xp_flag==1)
		{
			if((double)race<-0.6&&img_stop_flag==0&&nu>20&&nu<28)
			{
				img_stop_flag=1;
				stop_time = 0;
				stop_time1 = 0;
			}
			else if(nu<36&&(double)race>0.4&&img_stop_flag==1&&nu>30)
				img_stop_flag=2;
			else if((double)race<-0.38&&img_stop_flag==2&&nu>30)
				img_stop_flag=3;
		}
}
