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
    int16 current_speed_raw; // ��������ʵ����
    int16 current_speed;     // �����������ͨ�˲���

    int16 set_speed;    // �����ٶȣ���ʱ����
    int16 target_speed; // Ŀ���ٶȣ����������ٶȼ����Ĵ�����

    int32 increment_duty; // ռ�ձ�����
    int32 duty;           // ռ�ձ��������ۼӣ�Ҳ������������������ռ�ձ�

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
    routine = 0, //����
    uniform,//����
    hasten,//����
    decelerate,       // ����
    stop,
};
extern enum speed speed_car ;



extern motor_param_t motor_l, motor_r;





void speed_control(void);
void speed_circle(void);

inline int16 differential_add_speed(int16 aim, float turn);
void light_control();

#endif
