#include"math_car.h"

double slope;
double angle;
double last_angle;

double slopeToAngle(double slope)
{
    // ʹ�� atan ���㻡�ȣ�Ȼ��ת��Ϊ�Ƕ�
    double angle = atan(slope);
    double angle_pi = RAD_TO_ANGLE(angle);
    return angle_pi;
}
double Slope(int16 COL,int16 ROW)
{
    return (double)ROW/COL;
}

int16 Distance(uint8 x1,uint8 y1,uint8 x2,uint8 y2)
{
    return sqrt((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2));
}

int32 Abs(int32 value){
    return ((value < 0) ? (-value) : value);
}


