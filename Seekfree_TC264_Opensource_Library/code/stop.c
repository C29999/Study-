#include"stop.h"
int32 light_flag=0;
int32 hasten_flag = 0;
int32 stop_flag=0;
int32 light_find[4];//1：第二个灯右下角；2：第一个灯右上角；3：第一个灯右下角；4：第二个灯右下角
int16 decelerate_flag;
float last_y;
float last_x;
int16 stop_jin_flag = 0;
void stop_cars()
{
         motor_l.target_speed=0;
         motor_r.target_speed=0;
//         dif_pwm=0;
         turn_pwm=0;


        // motor_l.duty=0;
        // motor_r.duty=0;
}
