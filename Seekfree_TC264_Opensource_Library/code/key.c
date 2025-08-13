#include"key.h"


// Mode 读取模式 0:非连按 1:连按
bool KEY_PRESS_SHORT(key_index_enum KEY_N)
{
    if (key_get_state(KEY_N) == KEY_SHORT_PRESS)
    {
        key_clear_state(KEY_N);
        return TRUE;
    }
    return FALSE;
}
bool key_long_press(key_index_enum KEY_ENUM)
{
    if (key_get_state(KEY_ENUM) == KEY_LONG_PRESS)
    {
        // key_clear_state(KEY_ENUM);
        key_clear_all_state();
        return true;
    }
    return false;
}
void key_control_go()
{
    motor_l.set_speed = AllSetSpeed;
    motor_r.set_speed = AllSetSpeed;
}
