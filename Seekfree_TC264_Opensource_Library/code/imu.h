#ifndef IMU_H
#define IMU_H

#include"zf_common_headfile.h"

typedef struct
{
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
    float mag_x;
    float mag_y;
    float mag_z;
    float Xdata;
    float Ydata;
    float Zdata;

    float z;
} imu_param_t;

typedef struct
{
    float q0;
    float q1;
    float q2;
    float q3;
} quater_param_t;
extern quater_param_t Q_info;

extern imu_param_t imu;


typedef struct
{
        float ki;
        float kp;
        float kd;
}gyro;
extern gyro gyro_euler;

typedef struct
{
    float pitch; // ??????
    float roll;  // ??????
    float yaw;   // ¡¤?????
} euler_param_t;

extern euler_param_t eulerAngle;          // Å·À­½Ç


float fast_sqrt(float t);

void gyro_offset_init();

void imu_init();

void gyro_get_values();

void gyro_update_AHRS(float gx, float gy, float gz, float ax, float ay, float az);

 void gyro_get_euler_angles();

extern bool gyro_offset_init_flag;

#endif
