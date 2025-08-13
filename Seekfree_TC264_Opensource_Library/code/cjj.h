#ifndef CJJ_H
#define CJJ_H

#include"zf_common_headfile.h"

#define Thres 255

void region_g();
void region_c();
int16 Search(int16 ROW,int16 COL,int a);

float Search_fang(int16 ROW,int16 COL,int a);


extern double fang_dif;

extern int16 light_num;
extern double avg;
extern int16 NUM;
extern int16 b1;
extern int16 b2;


extern int16 cjj_system;


#endif
