/*********************************************************************************************************************
 * TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
 * Copyright (c) 2022 SEEKFREE 逐飞科技
 *
 * 本文件是 TC264 开源库的一部分
 *
 * TC264 开源库 是免费软件
 * 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
 * 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
 *
 * 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
 * 甚至没有隐含的适销性或适合特定用途的保证
 * 更多细节请参见 GPL
 *
 * 您应该在收到本开源库的同时收到一份 GPL 的副本
 * 如果没有，请参阅<https://www.gnu.org/licenses/>
 *
 * 额外注明：
 * 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
 * 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
 * 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
 * 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
 *
 * 文件名称          cpu0_main
 * 公司名称          成都逐飞科技有限公司
 * 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
 * 开发环境          ADS v1.9.4
 * 适用平台          TC264D
 * 店铺链接          https://seekfree.taobao.com/
 *
 * 修改记录
 * 日期              作者                备注
 * 2022-09-15       pudding            first version
 ********************************************************************************************************************/
#include "zf_common_headfile.h"
#include"isr.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************
float time1 = 0,time2 = 0;
int16 time3=0;


#define A 0.25
float real_y = 0;
uint8_t Image_threshold = 190;
int core0_main(void)
{
    clock_init(); // 获取时钟频率<务必保留>
    debug_init(); // 初始化默认调试串口
                  // 此处编写用户代码 例如外设初始化代码等
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

//    if(wireless_uart_init())                                                    // 判断是否通过初始化
//    {
//        while(1)                                                                // 初始化失败就在这进入死循环
//        {
//             ips200_show_string(0, 0, "wireless init failed");
//        }
//    }

    pwm_init(Turn_servos, 50, 0);
//    gpio_init(P33_9, GPO, 1, GPO_PUSH_PULL);
//    gpio_init(P21_4, GPO, 1, GPO_PUSH_PULL);

    data_init();
    speed_control();

    // 此处编写用户代码 例如外设初始化代码等
    pit_ms_init(CCU60_CH0, 1);
    cpu_wait_event_ready(); // 等待所有核心初始化完毕
     last_y = 0;
     last_x = 0;

     float t,t2;

    while (TRUE)
    {
        // 此处编写需要循环执行的代码
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



        // 此处编写需要循环执行的代码
    }
}

#pragma section all restore
// **************************** 代码区域 ****************************
