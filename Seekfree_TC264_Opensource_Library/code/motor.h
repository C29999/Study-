#ifndef MOTOR_H
#define MOTOR_H

#include"zf_common_headfile.h"


#define MOTOR_A   ATOM0_CH7_P02_7//+
#define MOTOR_B   ATOM0_CH6_P02_6//-

#define MOTOR_C  ATOM0_CH5_P02_5//+
#define MOTOR_D  ATOM0_CH4_P02_4//-


#define Motor_L 0
#define Motor_R 1

////µç»úËÀÇø
#define L_Dead_Zone 0
#define R_Dead_Zone 0

#define MOTOR_DUTY_MAX 10000


void motor_test(void);
void motor_init(void);


extern int32 light_pwm;
extern int32 turn_pwm;
extern int32 dif_pwm;

#endif
