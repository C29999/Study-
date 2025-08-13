 #include"control.h"

enum speed speed_car = routine;

motor_param_t motor_l = MOTOR_CREATE(MODE_NORMAL);
motor_param_t motor_r = MOTOR_CREATE(MODE_NORMAL);

void speed_circle()
{
        #if 0
        //¹ùÊ¦ÐÖ
//    encoder_get();
    motor_l.duty = (int32)PID_Increase(&speedpid, speed_pid_l,(int32) motor_l.current_speed_raw,(int32) motor_l.target_speed+(int32)light_pwm);
    motor_r.duty = (int32)PID_Increase(&speedpid, speed_pid_r,(int32) motor_r.current_speed_raw,(int32) motor_r.target_speed+(int32)light_pwm);

        #endif

#if 0


    motor_l.duty = (int32)PID_Increase(&speedpid, speed_pid_l,(int32) motor_l.current_speed_raw,motor_l.target_speed-dif_pwm);
    motor_r.duty = (int32)PID_Increase(&speedpid, speed_pid_r,(int32) motor_r.current_speed_raw,motor_r.target_speed+dif_pwm);

//        motor_l.duty = (int32)PID_Increase(&speedpid, speed_pid_l,(int32) motor_l.current_speed_raw,motor_l.target_speed);
//        motor_r.duty = (int32)PID_Increase(&speedpid, speed_pid_r,(int32) motor_r.current_speed_raw,motor_r.target_speed);

    motor_pwmout(Motor_L, motor_l.duty);
    motor_pwmout(Motor_R, motor_r.duty);


#endif
#if 1

if(!stop_flag)
{
//    dif_pwm=PlacePID_Control (&difpid, dif_pid,(int32)x_point,(float)94);
//        dif_pwm=0;

//    motor_l.target_speed = bendSpeed+light_pwm;
//    motor_r.target_speed = bendSpeed+light_pwm;
//   motor_l.duty = (int32)PID_Increase(&speedpid, speed_pid_l,(int32) motor_l.current_speed_raw,motor_l.target_speed );
//   motor_r.duty = (int32)PID_Increase(&speedpid, speed_pid_r,(int32) motor_r.current_speed_raw,motor_r.target_speed );
    if(hasten_flag == 1)
    {
        motor_l.target_speed+=10;
        motor_r.target_speed += 10;
    }

    motor_l.increment_duty = (int32)increment_pid_solve(&Motor_pid_l, (float)(motor_l.target_speed - motor_l.current_speed));
    motor_r.increment_duty = (int32)increment_pid_solve(&Motor_pid_r, (float)(motor_r.target_speed - motor_r.current_speed));
***
    motor_l.duty+=motor_l.increment_duty;
    motor_r.duty+=motor_r.increment_duty;
}
else

{
//            motor_l.duty = (int32)PID_Increase(&speedpid, speed_pid_l,(int32) motor_l.current_speed_raw,0);
//            motor_r.duty = (int32)PID_Increase(&speedpid, speed_pid_r,(int32) motor_r.current_speed_raw,0);

    motor_l.increment_duty = (int32)increment_pid_solve(&Motor_pid_l, (float)(0 - motor_l.current_speed));
    motor_r.increment_duty = (int32)increment_pid_solve(&Motor_pid_r, (float)(0 - motor_r.current_speed));

    motor_l.duty+=motor_l.increment_duty;
    motor_r.duty+=motor_r.increment_duty;
}



    motor_pwmout(Motor_L, motor_l.duty);
    motor_pwmout(Motor_R, motor_r.duty);
    hasten_flag = 0;
#endif
}


void speed_control(void)
{
#if 0
    light_pwm=PlacePID_Control (&lightpid, light_pid,(int32)error_d,(float)0);
    if(stop_flag==0){
        motor_l.target_speed=bendSpeed+light_pwm;
        motor_r.target_speed=bendSpeed+light_pwm;
    }
    else
    {
        motor_l.target_speed=0+0;
        motor_r.target_speed=0+0;
    }

#endif
#if 1

//    int32 bendspeed;
//    if(on == true)
//    {
//        int16 Time_count;
//        float bili;
//        Time_count++;
//
//        if (Time_count == 100)
//        {
//            bili = bili + 0.25;
//            bendspeed = (int16)(bili * AllSetSpeed);
//            Time_count = 0;
//            if (bili == 1)
//            {
//                on = false;
//            }
//        }
//    }
//    Time_count++;
//    bendspeed=100;
//    if(Time_count == 100)
//
//    {
//
//    }

//    dif_pwm=(int32)PlacePID_Control(&difpid,dif_pid,(int32)y_point,ATM_distance);
//    dif_pwm=0;

//    bendSpeed = bendspeed;
//    dif_pwm = turn_dif*turn_pwm;
    if(stop_flag)//stop_jin_flag
    {
        motor_l.target_speed=0+0;
        motor_r.target_speed=0+0;
    }

    else if(!stop_flag)

    {
        motor_l.target_speed=bendSpeed+light_pwm - dif_pwm;
        motor_r.target_speed=bendSpeed+light_pwm + dif_pwm;
    }
    else if(!stop_flag&& (turn_pwm>50 || turn_pwm<-50 ))//stop_jin_flag
    {
        motor_l.target_speed=bendSpeed+light_pwm-dif_pwm + 25;
        motor_r.target_speed=bendSpeed+light_pwm+dif_pwm + 25;
        hasten_flag = 1;
    }
    else if(!stop_flag&& ( (turn_pwm<50&&turn_pwm>30) || ( turn_pwm<-30&& turn_pwm>-50) ))//stop_jin_flag
    {
        motor_l.target_speed=bendSpeed+light_pwm-dif_pwm + 15;//9
        motor_r.target_speed=bendSpeed+light_pwm+dif_pwm + 15;//9
        hasten_flag = 1;

    }
    else if(!stop_flag&& ( (turn_pwm<30&&turn_pwm>10) || ( turn_pwm<-10&& turn_pwm>-30) ))//stop_jin_flag
    {
        motor_l.target_speed=bendSpeed+light_pwm-dif_pwm + 0;
        motor_r.target_speed=bendSpeed+light_pwm+dif_pwm + 0;
        hasten_flag = 0;
    }


#endif
}


#define turn_diff 3.8
inline int16 differential_add_speed(int16 aim, float turn)
{
    return (int16)((float)aim * (turn * turn_diff / 14.5f)); // 0.47
}
void light_control()
{
//    if(x_point<20||x_point>168)
//        ATM_distance = 37;
//    else if( (x_point > 20 && x_point < 50 )|| ( x_point > 138 && x_point <= 168 ))
//        ATM_distance = 36;//49
//    else if( (x_point > 50 && x_point < 60 )|| ( x_point > 128 && x_point <= 138 ))
//        ATM_distance = 38;//49
//    else if(x_point<114&&x_point>74)
//        ATM_distance = 45;
//    else
//        ATM_distance = 42;
    //330
    //if(x_point<114&&x_point>74)
    //        ATM_distance = 47;
  //  else
  //      ATM_distance = 46;
//
//300
  if(x_point<114&&x_point>74)
            ATM_distance = 46;
    else
        ATM_distance = 44;

//    if(x_point<74)
//        ATM_distance = 45+(int32)(94-x_point)/4;
//    else if(x_point>114)
//        ATM_distance = 45-(int32)(x_point - 94)/8.5;
//    else if(x_point<114&&x_point>74)
//        ATM_distance = 45;
}
