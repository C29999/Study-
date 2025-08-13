#include"Servos.h"


void servos_test()
{
    if(KEY_PRESS_SHORT(KEY_1)==KEY_SHORT_PRESS)
    {
        turn_pwm++;
    }
    else if(KEY_PRESS_SHORT(KEY_2)==KEY_SHORT_PRESS)
    {
        turn_pwm--;
    }
    if(KEY_PRESS_SHORT(KEY_3)==KEY_SHORT_PRESS)
    {
        turn_pwm+=10;
    }
    else if(KEY_PRESS_SHORT(KEY_4)==KEY_SHORT_PRESS)
    {
        turn_pwm-=10;
    }
    pwm_set_duty(Turn_servos, Median_pwm+turn_pwm);
    ips200_show_int(100,0,turn_pwm+Median_pwm,4);
}
