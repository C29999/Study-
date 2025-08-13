#include "pid.h"
PID speedpid;
PID turnpid;
PID lightpid;
PID difpid;

int32 Increase;
int32 Speed_Increase;
int32 PID_Increase(PID *sptr, float *PID, int32 NowPoint, int32 SetPoint)
{
    // 当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    int32 iError = 0; // 当前误差

    iError = SetPoint - NowPoint; // 计算当前误差

    float out_i = PID[KI] * iError;
//    if (fabsf(sptr->LastError) > 1000. && fabsf(out_i) > 1000.)
//        out_i = 0.;

    Increase += PID[KP] * (iError - sptr->LastError) +
                out_i +
                PID[KD] * (iError - 2.0f * sptr->LastError + sptr->PrevError);

    sptr->PrevError = sptr->LastError; // 更新前次误差
    sptr->LastError = iError;          // 更新上次误差
    sptr->LastData = NowPoint;         // 更新上次数据
    if (PID[KT] < Increase && PID[KT] != 0)
        Increase = (int32)(PID[KT]);
    else if (-PID[KT] > Increase && PID[KT] != 0)
        Increase = (int32)(-PID[KT]);

    return Increase; // 返回增量
}
// ********************位置式动态PID控制************************************
/*
函数：int32 PlacePID_Control(PID *sprt, float *PID, int32 NowPiont, int32 SetPoint)
功能：位置式动态PID控制
参数：
PID *sprt：      结构体指针
float *PID：     PID数组  （通过数组定义PID值）
int32 NowPiont： 当前值  （可使用结构体定义变量）
int32 SetPoint： 设定目标值   转向控制中设定值为0。

说明：  该函数参考其他程序。动态控制一般用于转向控制
返回值： int32 Realize
eg：Radius = PlacePID_Control(&Turn_PID, Turn[Fres], Difference, 0);// 动态PID控制转向
*/
// 位置式动态PID控制
int32 PlacePID_Control(PID *sprt, float *PID, int32 NowPiont, float SetPoint)
{
    // 定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    float iError,                 // 当前误差
        Actual;                   // 最后得出的实际输出值
    float Kp;                     // 动态P
    iError = (float)(SetPoint - NowPiont); // 计算当前误差
    sprt->SumError += iError * 0.01;
    if (sprt->SumError >= PID[KT])
    {
        sprt->SumError = PID[KT];
    }
    else if (sprt->SumError <= -PID[KT])
    {
        sprt->SumError = -PID[KT];
    }
    Kp = (iError * iError / 12500.f) * PID[KP] + PID[KI];
    // Kp = 1.0 * (iError * iError) / PID[KP] + PID[KI]; // P值与差值成二次函数关系，此处P和I不是PID参数，而是动态PID参数，要注意！！！

    Actual = Kp * iError + PID[KD] * ((0.8 * iError + 0.2 * sprt->LastError) - sprt->LastError); // 只用PD
    sprt->LastError = iError;                                                                    // 更新上次误差

    // Actual += sprt->SumError*0.1;
//     Actual = limit(Actual, 50); //限幅


    return (int32)Actual;
}

float quadradic_pid_solve(PID *sprt, float *PID, int32 NowPiont, float SetPoint)
{
    // pid->out_p = pid->kp * error * error / 12500.f + pid->ki;
    // pid->out_d = error * pid->low_pass + (pid->pre_error - pid->pre_pre_error) * (1 - pid->low_pass);
    // // pid->out_i = 0;

    // pid->pre_pre_error = pid->pre_error;
    // pid->pre_error = error;

    // return MINMAX(error * pid->out_p, -pid->p_max, pid->p_max) + MINMAX(pid->kd * pid->out_d, -pid->d_max, pid->d_max) ;//- imu963ra_gyro_transition(imu963ra_gyro_z) * 0.0333; //* 0.0333;
float iError = (float)(SetPoint - NowPiont);

    float Actual=PID[KP]*iError+PID[KI]* abs(iError)*iError+PID[KD]*(iError-sprt->LastError);//-imu963ra_data.gyro_z*GDK

    sprt->LastError = iError;
//    pid->out_p = pid->kp * error;
//    pid->out_i=pid->ki* abs(error)*error;
//    pid->out_d = pid->kd * (error -pid->pre_error )-(pid->kgyro*imu963ra_data.gyro_z);


//    return MINMAX(pid->out_p+pid->out_i+pid->out_d, -pid->p_max, pid->p_max);//+ MINMAX(pid->kd * pid->out_d, -pid->d_max, pid->d_max);
    return Actual;
}

float quadradic_pid_solve_1(pid_param_t *pid, float error)
{
    pid->out_p = pid->kp * error * error / 12500.f + pid->ki;
    pid->out_d = error * pid->low_pass + (pid->pre_error - pid->pre_pre_error) * (1 - pid->low_pass);
    // pid->out_i = 0;

    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;

    return MINMAX(error * pid->out_p, -pid->p_max, pid->p_max) + MINMAX(pid->kd * pid->out_d, -pid->d_max, pid->d_max) - imu.z * pid->kgyro;
}

int32 PID_Realize(PID *sptr, float *PID, int32 NowPoint, int32 SetPoint)
{
    // 当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    int32 iError;  // 当前误差
    float Realize; // 最后得出的实际增量

    iError = SetPoint - NowPoint;       // 计算当前误差      设定减当前
    sptr->SumError += PID[KI] * iError; // 误差积分
    // sptr->SumError = limit(sptr->SumError, PID[KT]); // 积分限幅

    Realize = PID[KP] * iError +
              sptr->SumError +
              PID[KD] * (iError - sptr->LastError); // P  I   D  相加s
    sptr->PrevError = sptr->LastError;              // 更新前次误差
    sptr->LastError = iError;                       // 更新上次误差
    sptr->LastData = NowPoint;                      // 更新上次数据    没用 */

    return Realize; // 返回实际值
}
int32 PID_IncreaseSpeedCirle(PID *sptr, float *PID, int32 NowPoint, int32 SetPoint)
{
    // 当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    int32 iError = 0; // 当前误差

    iError = SetPoint - NowPoint; // 计算当前误差

    Speed_Increase += PID[KP] * (iError - sptr->LastError) +
                      PID[KI] * iError +
                      PID[KD] * (iError - 2.0f * sptr->LastError + sptr->PrevError);

    sptr->PrevError = sptr->LastError; // 更新前次误差
    sptr->LastError = iError;          // 更新上次误差
    sptr->LastData = NowPoint;         // 更新上次数据
    if (PID[KT] < Speed_Increase && PID[KT] != 0)
        Speed_Increase = (int32)(PID[KT]);
    else if (-PID[KT] > Speed_Increase && PID[KT] != 0)
        Speed_Increase = (int32)(-PID[KT]);

    return Speed_Increase; // 返回增量
}

float increment_pid_solve(pid_param_t *pid, float error)
{
    pid->out_d = MINMAX(pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error), -pid->d_max, pid->d_max);
    pid->out_p = MINMAX(pid->kp * (error - pid->pre_error), -pid->p_max, pid->p_max);
    pid->out_i = MINMAX(pid->ki * error, -pid->i_max, pid->i_max);

    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;

    pid->output = pid->out_p + pid->out_i + pid->out_d;

    if (pid->pre_output > 10000)
        if (pid->output > 0)
            pid->output = 0.;
    if (pid->pre_output < -10000)
        if (pid->output < 0)
            pid->output = 0.;

    pid->pre_output = pid->output;

    return pid->output;
}
//转向
int32 Pid_Angle(int32 angle_error, int32 kp2, int32 kp1, int32 kd)
{
    static int32 last_error=0;
    int32 angle_pwm_out=0,kp2_temp=0,kp1_temp=0,kd_temp=0;
    int32 kd_num_temp=0;

    kp2_temp = angle_error*Abs(angle_error)*kp2/100;//PPD控制
    kp1_temp = angle_error*kp1;
    kd_num_temp = angle_error-last_error;
    kd_temp = kd_num_temp * kd;
    last_error = angle_error;

    angle_pwm_out=kp2_temp+kp1_temp+kd_temp;//位置式整合

    return angle_pwm_out;
}
