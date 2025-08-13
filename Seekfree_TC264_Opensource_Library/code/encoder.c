#include"encoder.h"



void encoder_init(void)
{
    encoder_dir_init(TIM5_ENCODER, TIM5_ENCODER_CH1_P10_3, TIM5_ENCODER_CH2_P10_1);
    encoder_dir_init(TIM2_ENCODER,TIM2_ENCODER_CH1_P33_7 ,TIM2_ENCODER_CH2_P33_6 );
}

float speed_alpha = 0.6;
void encoder_get(void)
{
    // 采集左右轮的速度
    motor_l.current_speed_raw = -encoder_get_count(TIM5_ENCODER);
    motor_r.current_speed_raw = +encoder_get_count(TIM2_ENCODER);


    encoder_clear_count(TIM5_ENCODER);
    encoder_clear_count(TIM2_ENCODER);

    motor_l.current_speed = motor_l.current_speed * speed_alpha + motor_l.current_speed_raw * (1 - speed_alpha);

    motor_r.current_speed = motor_r.current_speed * speed_alpha + motor_r.current_speed_raw * (1 - speed_alpha);
}
