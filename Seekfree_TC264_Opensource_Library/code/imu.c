#include"imu.h"


#define delta_T 0.005f // 5ms����һ��

float I_ex, I_ey, I_ez; // ������


imu_param_t imu;
quater_param_t Q_info;
euler_param_t eulerAngle; 
gyro gyro_euler;


bool gyro_offset_init_flag = false;

float fast_sqrt(float t)
{
    float halfx = 0.5f * t;
    float t2 = t;
    long i = *(long *)&t;
    i = 0x5f3759df - (i >> 1);
    t2 = *(float *)&i;
    t2 = t2 * (1.5f - (halfx * t2 * t2));
    return t2;
}

/////////��������Ʈ��ʼ��
void gyro_offset_init()
{
        if (gyro_offset_init_flag )
        return;
    static int16 i = 0;

    if (i == 0)
    {
        imu.Zdata = 0;
    }

    // imu660ra_get_acc();
    imu660ra_get_gyro();

    // gyro_offset.Xdata += (float)imu_gyro_x;
    // gyro_offset.Ydata += (float)imu_gyro_y;
    imu.Zdata += (float)imu660ra_gyro_z;

    imu.Xdata /= 100;
    imu.Ydata /= 100;
    imu.Zdata /= 100;

    gyro_offset_init_flag = true;
}


void imu_init()
{
    imu660ra_init();
}
#define alpha 0.3f
void gyro_get_values()
{
    // һ�׵�ͨ�˲�����λg/s
//    imu.acc_x = (((float)imu660ra_acc_x) * alpha) * 8 / 4096 + imu.acc_x * (1 - alpha);
//    imu.acc_y = (((float)imu660ra_acc_y) * alpha) * 8 / 4096 + imu.acc_y * (1 - alpha);
//    imu.acc_z = (((float)imu660ra_acc_z) * alpha) * 8 / 4096 + imu.acc_z * (1 - alpha);
//
//    // �����ǽǶ�ת����
//    imu.gyro_x = ANGLE_TO_RAD(imu963ra_gyro_transition((float)imu660ra_gyro_x - imu.Xdata));
//    imu.gyro_y = ANGLE_TO_RAD(imu963ra_gyro_transition((float)imu660ra_gyro_y - imu.Ydata));
//    imu.gyro_z = ANGLE_TO_RAD(imu963ra_gyro_transition((float)imu660ra_gyro_z - imu.Zdata));


    imu.z=imu660ra_gyro_transition((float)imu660ra_gyro_z - imu.z);
}

// �����˲�
void gyro_update_AHRS(float gx, float gy, float gz, float ax, float ay, float az)
{
    float halfT = 0.5 * delta_T;
    float vx, vy, vz; // ��ǰ�Ļ�������ϵ�ϵ�������λ����
    float ex, ey, ez; // ��Ԫ������ֵ����ٶȼƲ���ֵ�����
    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;
    float delta_2 = 0;

    // �Լ��ٶ����ݽ��й�һ�� �õ���λ���ٶ�
    float norm = fast_sqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    // ���ݵ�ǰ��Ԫ������ֵ̬����������������������ںͼ��ټ�ʵ�ʲ��������ĸ������������жԱȣ��Ӷ�ʵ�ֶ�������̬������
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    // vz = (q0*q0-0.5f+q3 * q3) * 2;

    // �������������������ʵ�ʲ�����������������������֮�����
    ex = ay * vz - az * vy;
    ey = az * vx - ax * vz;
    ez = ax * vy - ay * vx;

    // �ò���������PI����������ƫ��
    // ͨ������ gyro_euler.kp��gyro_euler.ki ����������
    // ���Կ��Ƽ��ٶȼ����������ǻ�����̬���ٶȡ�
    I_ex += halfT * ex; // integral error scaled by Ki
    I_ey += halfT * ey;
    I_ez += halfT * ez;

    gx = gx + gyro_euler.kp * ex + gyro_euler.ki * I_ex;
    gy = gy + gyro_euler.kp * ey + gyro_euler.ki * I_ey;
    gz = gz + gyro_euler.kp * ez + gyro_euler.ki * I_ez;

    /*����������ɣ���������Ԫ��΢�ַ���*/

    // ��Ԫ��΢�ַ��̣�����halfTΪ�������ڵ�1/2��gx gy gzΪ�����ǽ��ٶȣ����¶�����֪��������ʹ����һ��������������Ԫ��΢�ַ���
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    // ������Ԫ����    ��Ԫ��΢�ַ���  ��Ԫ�������㷨�����ױϿ���
    // delta_2 = (2 * halfT * gx) * (2 * halfT * gx) + (2 * halfT * gy) * (2 * halfT * gy) + (2 * halfT * gz) * (2 * halfT * gz);
    // q0 = (1 - delta_2 / 8) * q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    // q1 = (1 - delta_2 / 8) * q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    // q2 = (1 - delta_2 / 8) * q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    // q3 = (1 - delta_2 / 8) * q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    // normalise quaternion
    norm = fast_sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    Q_info.q0 = q0 * norm;
    Q_info.q1 = q1 * norm;
    Q_info.q2 = q2 * norm;
    Q_info.q3 = q3 * norm;
}


/*����Ԫ��ת����ŷ����*/
void gyro_get_euler_angles()
{
    if (!gyro_offset_init_flag)
        return;

    // �ɼ�����������
    imu660ra_get_gyro();
    imu660ra_get_acc();
    // imu963ra_get_mag();

    gyro_get_values();
    gyro_update_AHRS(imu.gyro_x, imu.gyro_y, imu.gyro_z, imu.acc_x, imu.acc_y, imu.acc_z);
    // gyro_update_AHRS_mag(imu963ra_data.gyro_x, imu963ra_data.gyro_y, imu963ra_data.gyro_z, imu963ra_data.acc_x, imu963ra_data.acc_y, imu963ra_data.acc_z, imu963ra_data.mag_x, imu963ra_data.mag_y, imu963ra_data.mag_z);
    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;

    // ��Ԫ������ŷ����
    eulerAngle.pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 180 / PI;                                // pitch
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / PI; // roll
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / PI;  // yaw
}
