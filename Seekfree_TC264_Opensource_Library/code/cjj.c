#include"cjj.h"

double avg;
int16 NUM;
int16 cjj_system = 0;
int16 b1,b2;

void region_c()
{
    for (COL = Min_h; COL <=Max_h; COL += step)//light_1_l_up
    {
        if(light_flag==1)
            break;
        for (ROW = Min_w; ROW <= Max_w; ROW += step)
        {
            if (mt9v03x_image[COL][ROW] == Thres)
            {
                light_flag=1;
                avg=Search(ROW,COL,2);
                ips200_show_int(170,180,mt9v03x_image[COL][ROW],4);
                ips200_show_int(170,200,mt9v03x_image[COL+1][ROW],4);
                ips200_show_int(170,220,mt9v03x_image[COL+2][ROW],4);

//                 ips200_show_int(0,220,COL,3);ips200_show_int(40,220,ROW,3);ips200_show_int(80,220,light_find[2],1);//no_find
                break;
            }
        }
    }
    light_flag=0;
}
int16 Search(int16 ROW,int16 COL,int a)
{
    NUM=0;
    if((COL-a)>=0&&(COL+a)<=MT9V03X_H&&(ROW-a)>=0&&(ROW+a)<=MT9V03X_W)
    {
        for(int16 i=ROW-a;i<=ROW+a;i+=step)
        {
            for(int16 j=COL-a;j<=COL+a;j+=step)
            {
                NUM+=mt9v03x_image[j][i];
            }
        }
        return NUM;
    }
    else
        return -1;
    // return NUM;
} 

double fang_dif;

float Search_fang(int16 ROW,int16 COL,int a)
{
    NUM=0;
    if((COL-a)>=0&&(COL+a)<=MT9V03X_H&&(ROW-a)>=0&&(ROW+a)<=MT9V03X_W)
    {
        for(int16 i=ROW-a;i<=ROW+a;i+=step)
        {
            for(int16 j=COL-a;j<=COL+a;j+=step)
            {
                NUM+=mt9v03x_image[j][i];
            }
        }
        NUM/=4*a*a;
        double standardDeviation;
        for(int16 i=ROW-a;i<=ROW+a;i+=step)
        {
            for(int16 j=COL-a;j<=COL+a;j+=step)
            {
                standardDeviation+= pow(mt9v03x_image[j][i] - NUM, 2) ;
            }
        }
//        return sqrt(standardDeviation / a*a);
        return standardDeviation/4/a/a;
    }
    else
        return -1;
    // return NUM;
}

int16 light_num=0;

int16 y1,y2;

void region_g()
{
    light_num=0;
    for (COL = Min_h; COL <=Max_h; COL += step)//light_1_l_up
    {
        if(light_flag==1)
            break;
        for (ROW = Min_w; ROW <= Max_w; ROW += step)
        {
            if (mt9v03x_image[COL][ROW] == Thres)
            {
                y1=COL;
                light_flag=1;
//                 ips200_show_int(0,220,COL,3);ips200_show_int(40,220,ROW,3);ips200_show_int(80,220,light_find[2],1);//no_find
                break;
            }
        }
    }
    light_flag=0;
    for (COL = Max_h; COL >= Min_h; COL -= step)//light_2_r_down
    {
        if(light_flag==1)
        {
            break;
        }
        for (ROW = Max_w; ROW >= Min_w; ROW -= step)
        {
            if (mt9v03x_image[COL][ROW] == Thres)
            {
                y2=COL;
                light_flag=1;
                break;
            }
        }

    }
    Median_line=(y2+y1)/2;

    for (COL = Median_line; COL >= y1; COL -= step)//light_1_r_down
    {
        for (ROW = Max_w; ROW >= Min_w; ROW -= step)
        {
            if (mt9v03x_image[COL][ROW] == Thres)
            {
                light_num++;
                ips200_draw_point(ROW,COL+70,RGB565_RED);
            }
        }
    }

    for (COL = Median_line; COL <= y2; COL += step)//light_2_l_down
    {
        for (ROW = Min_w; ROW <=Max_w; ROW += step)
        {
            if (mt9v03x_image[COL][ROW] == Thres)
            {
                light_num++;
                ips200_draw_point(ROW,COL+70,RGB565_RED);
            }
        }
    }
}
