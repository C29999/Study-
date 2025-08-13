#include"menu.h"



uint8 pages = 0;

void display_run()
{
    key_control_old();
    display_main_old();

    if (key_long_press(KEY_4))
    {
        ips200_clear();
        current_func = display_main;
        return;
    }
}
void key_control_old()
{
    if (KEY_PRESS_SHORT(KEY_1))
    {
        ips200_clear();


        if (pages == 1)
            pages = 0;
        else
            pages = 1;
    }

    // if (key_short_press(KEY_3))
    // {
    //     int16 bpm = 240;
    //     int16 notes = 67;
    //     int16 wholenote = 60000 * 4 / bpm;
    //     for (int16 thisNote = 0; thisNote < notes; thisNote = thisNote++)
    //     {
    //         int16 noteDuration = wholenote * melody[thisNote].divider;

    //         buzz_keep_ms(noteDuration * 0.9, melody[thisNote].freq);
    //         buzz_keep_ms(noteDuration * 0.1, 0);
    //     }
    // }

    // if (key_short_press(KEY_5))
    // {
    //     key_control_bless();
    // }

    // 发车
    if (KEY_PRESS_SHORT(KEY_2))
    {
        key_control_go();
    }
}
void display_main_old()
{

    image_process_170();
    b1=Search(Light[O][1],Light[O][2],2); 
    b2=Search(Light[T][1],Light[T][2],2);



    // 显示部分
    switch (pages)
    {
    case 0:

        ips200_show_string(0,70,"l_d:");ips200_show_int(40,70,motor_l.duty,4);ips200_show_string(90,70,"l_cs");ips200_show_int(130,70,motor_l.current_speed_raw,4);ips200_show_string(180,70,"c");ips200_show_int(190,70,motor_l.current_speed,4);
        ips200_show_string(0,90,"r_d:");ips200_show_int(40,90,motor_r.duty,4);ips200_show_string(90,90,"r_cs");ips200_show_int(130,90,motor_r.current_speed_raw,4);ips200_show_string(180,90,"c");ips200_show_int(190,90,motor_r.current_speed,4);
        ips200_show_string(0,110,"e_x:");ips200_show_int(40,110,error_x,2);ips200_show_string(70,110,"e_d:");ips200_show_int(110,110,error_d,2);
        ips200_show_string(0,130,"l_p:");(40,130,light_pwm,4);ips200_show_string(100,130,"t_p:");ips200_show_int(140,130,turn_pwm,2);ips200_show_string(170,130,"l/S_f");ips200_show_int(220,220,light_flag,1);ips200_show_int(40,230,stop_flag,1);  
        ips200_show_string(70,200,"a1:");ips200_show_int(110,200,b1,6);
        break;
    case 1:

        break;
    case 2:

        break;
    default:
        break;
    }
}
// ------------ 换页逻辑 -------------

void display_image()
{
    // display_main_old();
    const uint8 image_index_num = 6;
    static uint8 image_index = 0;

    // if (key_short_press(KEY_1))
    // {
    //     ips200_clear();
    //     if (image_index-- == 0)
    //         image_index = image_index_num - 1;
    // }

    if (KEY_PRESS_SHORT(KEY_2))
    {
        ips200_clear();
        if (++image_index >= image_index_num)
            image_index = 0;
    }

    if (key_long_press(KEY_4))
    {
        ips200_clear();
        current_func = display_main;
        return;
    }

//    if (!image_calc_finished)
//    {
//        ips200_show_string((MT9V03X_W) / 2, 200, "No IMAGE");
//        return;
//    }
//    image_calc_finished = 0;

    ips200_show_int(0, 312, image_index, 2);
    switch (image_index)
    {
    case 0:
        ips200_clear();
        ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);


        break;
    case 1:
        ips200_clear();
        ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, thres);

        break;


    default:
        break;
    }
}
