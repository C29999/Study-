#ifndef MATH_CAR_H
#define MATH_CAR_H

#include"zf_common_headfile.h"

double slopeToAngle(double slope) ;
double Slope(int16 COL,int16 ROW);
int16 Distance(uint8 x1,uint8 y1,uint8 x2,uint8 y2);

int32 Abs(int32 value);

extern double slope;
extern double angle;
extern double last_angle;

#endif
