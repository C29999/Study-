#include"data.h"

int32 uniform_duty;
int32 ATM_distance = 45;
float turn_dif = 0.24;

bool on=false;

float 
 kgyro,
 speed_pid_l[4] = {3.2, 2.7, 0, 4000},
 speed_pid_r[4] = {3.2, 2.7, 0, 4000},

 dif_pid[4] = {1.3 ,  0.2 , 0.15, 20 },//175

// dif_pid[4] = {1.8 ,  0.2 , 0.15, 0 },//175



// turn_pid[4] = { 1.2 , 1.65 , 1.7 , 94},//1.5 , 2.3 , 1.8//-230

// turn_pid[4] = { 2.25 , 2.0 , 1.6 , 94},//1.5 , 2.3 , 1.8//-230

 turn_pid[4] = { 1.8 , 3.0 , 1.7 , 94},//1.8，2.8，1.6

Kp2=0.0,


// turn_pid[4] = { 1.0 , 0.0 , 1.0 , 94},//3.85, 1.3, 0.5, 50
// turn_pid[4] = {4.0, 0.0, 0.6, 80},//3.85, 1.3, 0.5, 50

light_pid[4]={0.4 , 2.1 , 3.2 ,0};
//light_pid[4]={2.8, 1.5, 0.5, 50};

int32 distance_flag=0;

int32 AllSetSpeed;
int32 bendSpeed;
int32 decelerate_speed;
int32 last_decelerate_speed;

int16 Median_line;
int16 Median_line_x;
int16 Median_line_y;
float turn_weight;
float dif_weight;

int32 kp2,kp1,kd;

void data_init()
{
//    distance_flag=0;//distance(Y_error)
    distance_flag=1;//两点间的距离
    light_find[1]=0;
    light_find[2]=0;
    light_find[3]=0;
    light_find[4]=0;
    protect_flag = 1;
    stop_jin_flag=0;
    AllSetSpeed=280;

//    turn_dif = 0.75;//0.24
//    turn_dif = 0.7;//0.24
    turn_dif = 0.76;//0.24
//    turn_dif = 1.2;

//    bendSpeed=230;
//    bendSpeed=145;//145-//成功

//    bendSpeed=190;//-230

    bendSpeed=255;
 //   bendSpeed = 300;
//    bendSpeed = 330;

//    turn_weight=2.8;
    turn_weight=3.0;
//    turn_weight=2.5;
    dif_weight=3.7;
//    dif_weight=0;

//    kgyro=0.40;
//    kgyro=0.05;//0.25//0.2//0.1出界少很多//抑制越大，在微小转角上容易被处理为直线//175
    kgyro=0.05;

    gyro_euler.kp=0.24;
    gyro_euler.ki=0.006;

//    kp2 = 0.0;
//    kp1 = 5.0;
//    kd = 20.0;


    stop_flag=0;
    // init_distance=12;//250
    init_distance= 14 ;//240[7,12]
//    init_error_x=26;//250
    error_x=0;
    error_d=0;
    init_error_x=0;//240

//    light_pwm=0;
    turn_pwm=0;
    light_flag=0;
    pwm_set_duty(Turn_servos,Median_pwm);
    memset(light_find_four, 0, sizeof(light_find_four));
    
}
pid_param_t Motor_pid_l = PID_CREATE(20.0, 3.0, 0.0, 0, 7000, 5000, 0, 0.);
pid_param_t Motor_pid_r = PID_CREATE(20.0, 3.0, 0.0, 0, 7000, 5000, 0, 0.);
pid_param_t Light_pid = PID_CREATE(8.0, 1.5, 2.0, 0, 70, 20, 0, 0.00);

//pid_param_t Turn_pid = PID_CREATE(3.6, 2.2, 2.5, 0, 100, 60, 0, 0.05);//2.8, 2.9, 2.1//330

pid_param_t Turn_pid = PID_CREATE(2.8, 2.4, 1.6, 0, 100, 50, 0, 0.05);//2.8, 2.9, 2.1//260

//pid_param_t Turn_pid = PID_CREATE(3.0, 1.9, 1.8, 0, 100, 50, 0, 0.05);//3.6, 2.0, 2.4//300
