#ifndef _PID_H_
#define _PID_H_

#include "zf_common_headfile.h"

#define KP 0
#define KI 1
#define KD 2
#define KT 3

typedef struct PID // ����PID�����������
{
    float SumError;  // ����ۼ�
    int32 LastError; // �ϴ����
    int32 PrevError; // Ԥ�����
    int32 LastData;  // �ϴ�����
} PID;
extern PID speedpid;
extern PID lightpid;
extern PID turnpid;
extern PID difpid;

int32 PID_IncreaseSpeedCirle(PID *sprt, float *PID, int32 NowPiont, int32 SetPoint);
int32 PlacePID_Control(PID *sprt, float *PID, int32 NowPiont, float SetPoint);
int32 PID_Increase(PID *sptr, float *PID, int32 NowPoint, int32 SetPoint);
int32 PID_Realize(PID *sptr, float *PID, int32 NowPoint, int32 SetPoint);

int32 Pid_Angle(int32 angle_error, int32 kp2, int32 kp1, int32 kd);




typedef struct
{
    float kp;    // P
    float ki;    // I
    float kd;    // D
    float i_max;
    float p_max;
    float d_max;

    float low_pass;

    float out_p;
    float out_i;
    float out_d;

    float kgyro;

    float error;
    float pre_error;
    float pre_pre_error;

    float output;
    float pre_output;
} pid_param_t;

float quadradic_pid_solve_1(pid_param_t *pid, float error);
float increment_pid_solve(pid_param_t *pid, float error);
extern pid_param_t Motor_pid_l;
extern pid_param_t Motor_pid_r;
extern pid_param_t Light_pid;
extern pid_param_t Turn_pid;




#endif
