/*********************************************************************************************************************
 * TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
 * Copyright (c) 2022 SEEKFREE ��ɿƼ�
 *
 * ���ļ��� TC264 ��Դ���һ����
 *
 * TC264 ��Դ�� ��������
 * �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
 * �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
 *
 * ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
 * ����û�������������Ի��ʺ��ض���;�ı�֤
 * ����ϸ����μ� GPL
 *
 * ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
 * ���û�У������<https://www.gnu.org/licenses/>
 *
 * ����ע����
 * ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
 * �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
 * ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
 * ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
 *
 * �ļ�����          cpu0_main
 * ��˾����          �ɶ���ɿƼ����޹�˾
 * �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
 * ��������          ADS v1.9.4
 * ����ƽ̨          TC264D
 * ��������          https://seekfree.taobao.com/
 *
 * �޸ļ�¼
 * ����              ����                ��ע
 * 2022-09-15       pudding            first version
 ********************************************************************************************************************/
#include "zf_common_headfile.h"
#include"isr.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

// **************************** �������� ****************************
float time1 = 0,time2 = 0;
int16 time3=0;


#define A 0.25
float real_y = 0;
uint8_t Image_threshold = 190;
int core0_main(void)
{
    clock_init(); // ��ȡʱ��Ƶ��<��ر���>
    debug_init(); // ��ʼ��Ĭ�ϵ��Դ���
                  // �˴���д�û����� ���������ʼ�������
    key_init(1);
    ips200_init(IPS200_TYPE_SPI);
    mt9v03x_init();
    motor_init();
    encoder_init();
    imu_init();
    gyro_offset_init();
//    if (imu660ra_init())
//    {
//        ips200_show_string(0, 0, "gyro init failed");
//        system_delay_ms(500);
//        ips200_clear();
//    }

//    if(wireless_uart_init())                                                    // �ж��Ƿ�ͨ����ʼ��
//    {
//        while(1)                                                                // ��ʼ��ʧ�ܾ����������ѭ��
//        {
//             ips200_show_string(0, 0, "wireless init failed");
//        }
//    }

    pwm_init(Turn_servos, 50, 0);
//    gpio_init(P33_9, GPO, 1, GPO_PUSH_PULL);
//    gpio_init(P21_4, GPO, 1, GPO_PUSH_PULL);

    data_init();
    speed_control();

    // �˴���д�û����� ���������ʼ�������
    pit_ms_init(CCU60_CH0, 1);
    cpu_wait_event_ready(); // �ȴ����к��ĳ�ʼ�����
     last_y = 0;
     last_x = 0;

     float t,t2;

    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
//        if (!mt9v03x_finish_flag)
//            continue;

//        motor_test();
//        pwm_set_duty(MOTOR_A, 0);
//        pwm_set_duty(MOTOR_B, 2000);

//        pwm_set_duty(MOTOR_C, 2000);
//        pwm_set_duty(MOTOR_D, 0);
//               motor_pwmout(Motor_L,2000);
//               motor_pwmout(Motor_R,2000);

//        get_thres_white();
//        image_process();
#if 0
        servos_test();
        ips200_show_int(40,140,motor_r.current_speed_raw,4);ips200_show_int(80,140,motor_r.current_speed,4);
#endif

#if 0
        image_process_170();

        turn_pwm=(int32)PlacePID_Control(&turnpid, turn_pid,(int32)error_x*turn_weight, (float)0)-(int32)imu.z* kgyro;
//        turn_pwm=-turn_pwm;
        turn_pwm=(turn_pwm>60)?60:turn_pwm;
        turn_pwm=(turn_pwm<-60)?-60:turn_pwm;
        pwm_set_duty(Turn_servos,turn_pwm+Median_pwm);//turn_pwm
        // region_g();
        // region_c();
//        stop_cars();
       ips200_show_gray_image(0, 70, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,thres );//
       ips200_draw_line(94,70,94,130,RGB565_RED);
        ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
        ips200_draw_line(94,0,94,60,RGB565_RED);
//
//
        ips200_show_int(0,140,motor_l.duty,4);
        ips200_show_int(0,160,motor_r.duty,4);

        ips200_show_int(40,140,motor_l.current_speed_raw,4);ips200_show_int(80,140,motor_l.current_speed,4);ips200_show_string(120,140,"n:");ips200_show_int(170,140,light_num,3);
        ips200_show_int(40,160,motor_r.current_speed_raw,4);ips200_show_int(80,160,motor_r.current_speed,4);
        ips200_show_int(0,180,error_x,2);ips200_show_int(40,180,error_d,2);ips200_show_int(80,180,dif_pwm,2);
        ips200_show_int(0,200,light_pwm,4);ips200_show_int(40,200,turn_pwm,2);  ips200_show_string(70,200,"a1:");ips200_show_int(110,200,b1,6);
        ips200_show_int(0,220,light_flag,1);ips200_show_int(40,220,stop_flag,1);ips200_show_string(70,220,"a2:");ips200_show_int(110,220,b2,6);
        ips200_show_int(0,240,distance_err,2);ips200_show_float(80,240,fang_dif,5,5);
        ips200_show_int(0,260,light_find[1],1);  ips200_show_int(20,260,light_find[2],1); ips200_show_int(40,260,light_find[2],1); ips200_show_int(60,260,light_find[4],1);
        ips200_show_int(0,280,stop_ms,3);ips200_show_int(60,280,motor_r.target_speed,4);

//        ips200_show_float(0,300,slope,2,2);ips200_show_float(80,300,angle,2,1);ips200_show_float(160,300,(double)distance_err/angle,2,2);
#endif

#if 1
        if(mt9v03x_finish_flag)
        {
           LQ_Deal_Image(&x_point,&y_point,200);
           real_y = y_point;
           if(protect_flag ==0)
           {
               y_point = y_point*A + last_y*(1 - A);
               last_y=y_point;
               last_x=x_point;
                t = found_juge();
//                t2 = 1/( t * t );
//                y_point/=t;
                y_point = (y_point>35)?y_point:35;
           }
           else
           {
               y_point=0;
               x_point=0;
           }
           //jj_recommend
           mt9v03x_finish_flag  =0 ;
//           cjj_system++;
        }




//        if(timer>=1000)
//        {
//            ips200_show_int(0,180,cjj_system,4);
//            cjj_system =0;
//            timer=0;
//        }
        ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 200);
        ips200_draw_line(94,0,94,60,RGB565_RED);
        ips200_draw_line(0,30,188,30,RGB565_BLUE);
        ips200_show_float(0,70,y_point,3,2);ips200_show_int(70,70,turn_pwm,3);
        ips200_show_float(0,100,x_point,3,2);ips200_show_int(70,100,motor_l.target_speed,3);
        float t=RAD_TO_ANGLE(imu.z);
        ips200_show_string(0,120,"atan:");ips200_show_float(50,120,t,3,3);

        ips200_show_string(0,140,"gy_:");ips200_show_float(50,140,imu.z*kgyro,3,3);
        ips200_show_string(0,160,"gy_a:");ips200_show_float(50,160,t*kgyro,3,3);
        
        ips200_show_int(0,200,protect_flag,2);

        ips200_show_string(0,220,"gyro:");ips200_show_float(60,220,imu.z,3,3); ips200_show_string(100,220,"num:");ips200_show_int(140,220,Deal_succeed_count,3);
//       ips200_show_int(0,240,time3/1000,5);
        ips200_show_int(0,240,motor_l.current_speed_raw,3);ips200_show_int(110,240,motor_r.target_speed,3);
        ips200_show_int(50,240,motor_r.current_speed_raw,3);ips200_show_int(160,240,motor_r.target_speed,3);
        ips200_show_int(0,260,motor_r.duty,4); ips200_show_string(50,260,"light_pwm");ips200_show_int(120,260,dif_pwm,2);ips200_show_float(180,260,t,2,2);
        ips200_show_int(0,280,motor_l.duty,4);ips200_show_int(50,280,light_pwm,4);ips200_show_float(120,280,t  , 2,2);
//        time3=0;
#endif



        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#pragma section all restore
// **************************** �������� ****************************
