#ifndef CONTROL_H
#define CONTROL_H

#include"zf_common_headfile.h"

#define MOTOR_CREATE(_MODE_NORMAL) \
    {                              \
        .current_speed_raw = 0,    \
        .current_speed = 0,        \
        .set_speed = 0,            \
        .target_speed = 0,         \
        .increment_duty = 0,       \
        .duty = 0,                 \
        .motor_mode = MODE_NORMAL, \
    }

typedef struct
{
    int16 current_speed_raw; // 编码器真实输入
    int16 current_speed;     // 编码器输入低通滤波后

    int16 set_speed;    // 设置速度，临时常量
    int16 target_speed; // 目标速度，根据设置速度计算后的储存量

    int32 increment_duty; // 占空比增量
    int32 duty;           // 占空比增量的累加，也就是最终输出给电机的占空比

    enum
    {
        MODE_NORMAL,
        MODE_BANGBANG,
        MODE_SOFT,
        MODE_POSLOOP,
    } motor_mode;

} motor_param_t;


enum speed
{
    routine = 0, //常规
    uniform,//均衡
    hasten,//加速
    decelerate,       // 减速
    stop,
};
extern enum speed speed_car ;



extern motor_param_t motor_l, motor_r;





void speed_control(void);
void speed_circle(void);

inline int16 differential_add_speed(int16 aim, float turn);
void light_control();

#endif
