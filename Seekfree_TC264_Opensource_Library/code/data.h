#ifndef DATA_H
#define DATA_H



#include"zf_common_headfile.h"


//#define ATM_distance  45//4¸öwhiteµã//50//45wansai//43
//#define ATM_distance  100

extern int32 ATM_distance;
extern float turn_dif;

#define mid_zero 94  //95.6

extern int32 distance_flag;
extern bool on;

extern float speed_pid_l[4];
extern float speed_pid_r[4];

extern  float dif_pid[4];

extern float turn_pid[4];
extern float Kp2;

extern float light_pid[4];
extern int16 Median_line;

extern int16 Median_line_x;
extern int16 Median_line_y;

extern int32 AllSetSpeed;
extern int32 bendSpeed;
extern float turn_weight;
extern float dif_weight;

extern int32 kp2;
extern int32 kp1;
extern int32 kd;

extern int32 uniform_duty;
extern int32 decelerate_speed;
extern int32 last_decelerate_speed;


extern float kgyro;

void data_init();

#endif
