#include"motor.h"

int32 light_pwm,turn_pwm,dif_pwm;
// 电机初始化
void motor_init(void)
{
    pwm_init(MOTOR_A, 17000, 0); // 左轮PWM控制引脚
    pwm_init(MOTOR_B, 17000, 0); // 左轮PWM控制引脚

    pwm_init(MOTOR_C, 17000, 0); // 右轮PWM控制引脚
    pwm_init(MOTOR_D, 17000, 0); // 右轮PWM控制引脚
}

void motor_test()
{
    int n=0,pwm=0;
    if (KEY_PRESS_SHORT(KEY_1) == KEY_SHORT_PRESS)
    {
        n++;
    }
    else if (KEY_PRESS_SHORT(KEY_2) == KEY_SHORT_PRESS)
    {
        n--;
    }
    else if (KEY_PRESS_SHORT(KEY_3) == KEY_SHORT_PRESS)
    {
        pwm+=100;
    }
    else if (KEY_PRESS_SHORT(KEY_4) == KEY_SHORT_PRESS)
    {
        pwm-=100;
    }

    if(n==1&pwm>=0)
    {
        ips200_show_string(0,0,"L+:");
        pwm_set_duty(MOTOR_A, pwm);
        pwm_set_duty(MOTOR_B, 0);
    }
    else if(n==1&pwm<0)
    {
        ips200_show_string(0,0,"L-:");
        pwm_set_duty(MOTOR_A, 0);
        pwm_set_duty(MOTOR_B, -pwm);
    }

    if(n==2&pwm>=0)
    {
        ips200_show_string(0,0,"R+:");
        pwm_set_duty(MOTOR_C, pwm);
        pwm_set_duty(MOTOR_D, 0);
    }
    else if(n==2&pwm<0)
    {
        ips200_show_string(0,0,"R-:");
        pwm_set_duty(MOTOR_C, 0);
        pwm_set_duty(MOTOR_D, -pwm);
    }
    ips200_show_int(0,40,n,1);
    ips200_show_string(100,0,"pwm:");
    ips200_show_int(100,60,pwm,4);
}
void motor_pwmout(int16 motor, int32 pwmin)
{
    if (pwmin > 0)
    {
        if (motor == Motor_R)
        {
            pwmin += R_Dead_Zone;
            if (pwmin > MOTOR_DUTY_MAX) // 限幅
            {
                pwmin = MOTOR_DUTY_MAX;
            }

            pwm_set_duty(MOTOR_A, pwmin); // MOTOR_B
            pwm_set_duty(MOTOR_B, 0);     // MOTOR_A
        }

        if (motor == Motor_L)
        {
            pwmin += L_Dead_Zone;
            if (pwmin > MOTOR_DUTY_MAX)
            {
                pwmin = MOTOR_DUTY_MAX;
            }

            pwm_set_duty(MOTOR_C, pwmin); // MOTOR_D
            pwm_set_duty(MOTOR_D, 0);     // MOTOR_C
        }
    }
    else if (pwmin < 0)
    {
        if (motor == Motor_R)
        {
            pwmin -= R_Dead_Zone;
            if (pwmin < -MOTOR_DUTY_MAX)
            {
                pwmin = -MOTOR_DUTY_MAX;
            }

            pwm_set_duty(MOTOR_A, 0);      // MOTOR_B
            pwm_set_duty(MOTOR_B, -pwmin); // MOTOR_A
        }

        if (motor == Motor_L)
        {
            pwmin -= L_Dead_Zone;
            if (pwmin < -MOTOR_DUTY_MAX)
            {
                pwmin = -MOTOR_DUTY_MAX;
            }

            pwm_set_duty(MOTOR_C, 0);      // MOTOR_D
            pwm_set_duty(MOTOR_D, -pwmin); // MOTOR_C
        }
    }
    else
    {
        if (motor == Motor_R)
        {
            pwm_set_duty(MOTOR_A, 0); // MOTOR_B
            pwm_set_duty(MOTOR_B, 0); // MOTOR_A
        }
        if (motor == Motor_L)
        {
            pwm_set_duty(MOTOR_C, 0); // MOTOR_D
            pwm_set_duty(MOTOR_D, 0); // MOTOR_C
        }
    }
}
