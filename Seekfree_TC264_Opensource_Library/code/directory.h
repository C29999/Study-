#ifndef DIRECTORY_H
#define DIRECTORY_H

#include"zf_common_headfile.h"


typedef struct MENU
{
    char *name;
    void (*func)();
} M_SELECT;

// �������ƣ�����ָ�룬���ݸ��²�������������
typedef struct OPTION
{
    char *name;
    void *value;
    float Step;
    enum type_e{
        O_BOOL,
        O_UINT8,
        O_INT8,
        O_INT16,
        O_UINT16,
        O_FLOAT,
        O_TYPE_NUM
    } type;
} O_SELECT;

extern void (*current_func)();

void interface_main();
void display_main();

#endif
