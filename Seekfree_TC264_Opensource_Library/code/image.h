#ifndef IMAGE_H
#define IMAGE_H

#include"zf_common_headfile.h"

#define max_error max - 10
#define step 1
#define X_error 74
#define MAX_H MT9V03X_H - 10
#define MIN_H MT9V03X_H - 110
#define MAX_W MT9V03X_W / 2 + X_error
#define MIN_W MT9V03X_W / 2 - X_error


#define O 1
#define T 2

#define x 2
#define y 3

#define Max_h MT9V03X_H
#define Min_h 0
#define Max_w MT9V03X_W
#define Min_w 0

#define thres 250

#define X 94
#define Y 30



int16 tricore_abs(int16 num);
void get_distance(int16 ROW, int16 COL);
void get_thres_white();
void draw_frame(int16 ROW, int16 COL, int16 half_step);

void image_process_170();

int16 seek_only();//four_light


extern int16 ROW;
extern int16 COL;

extern int16 error_d;
extern int16 last_error_d;
extern int16 distance_err;
extern int16 Dis_err;
extern int16 last_distance_err;
extern int16 init_distance;
extern int32 error_x;
extern int32 init_error_x;
extern int32 last_error_x;

extern int16 Light[2][2];

extern int16 four[4][3]; 

extern int16 light_down[2][2];
extern int16 light_up[2][2];

extern int16 light_find_four[4][2];
#endif
