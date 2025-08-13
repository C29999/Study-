#include"directory.h"


void display_main()
{
    ips200_show_string(72, 0, "[Main]");
    M_SELECT select_opt[] =
        {
            {"Run", display_run},
            {"Image", display_image},
////             {"Wifi Debug", wifi_debug_init},
////            {"Edit Speed", display_edit_speed},
//
////            {"Edit Turn", display_edit_turn},
////            {"Edit Motor", display_edit_motor},
//            // {"Edit Motor Bangbang", display_edit_motor_bangbang},
//            // {"Edit Motor Soft", display_edit_motor_soft},
//
//            // {"Edit Garage", display_edit_garage_data},
//            // {"Edit Roadblock", display_edit_roadblock_data},
//            // {"Edit Ramp", display_edit_ramp_data},
////            {"Edit Cross", display_edit_cross_data},
//            //  {"Edit Circle", display_edit_circle_data},
//
////            {"Edit Image Data", display_edit_image_data},
//
//            // {"Edit Camera Config", camera_set_config},
        };
    const uint8 select_opt_num = sizeof(select_opt) / sizeof(M_SELECT);

    static uint8 main_options = 0;

     //换页
     if (KEY_PRESS_SHORT(KEY_1))
     {
         uint8 last_option = main_options;
         if (main_options-- == 0)
             main_options = select_opt_num - 1;

         ips200_show_string(0, 12 * (last_option + 1), "  ");
     }
    if (KEY_PRESS_SHORT(KEY_4))
    {
        uint8 last_option = main_options;
        if (++main_options >= select_opt_num)
            main_options = 0;

        ips200_show_string(0, 12 * (last_option + 1), "  ");
    }

    // 显示级联主菜单与选项指针
    for (uint8 i = 0; i < select_opt_num; i++)
    {
        if (main_options == i)
            ips200_show_string(0, 12 * (i + 1), "->");
        ips200_show_string(24, 12 * (i + 1), select_opt[i].name);
    }

    if (KEY_PRESS_SHORT(KEY_2))
    {
        ips200_clear();
//        sprintf(chr, "[%s]", select_opt[main_options].name);
//        ips200_show_string(72, 0, chr);
        current_func = select_opt[main_options].func;
    }
}

void (*current_func)() = display_main;
void interface_main()
{
    // key_control_old();
    // display_main_old();

    current_func();
}
