#include"image.h"
uint8 max = 0;
int16 ROW, COL;
int16 turn_error;
int16 ROW_last = 0, COL_last = 0;
int16 error_d;
int16 last_error_d;
int32 error_x;
int32 init_error_x;
int32 last_error_x;
float k=0;
int16 init_distance=14;
int16 distance_err = 0;
int16 Dis_err;
int16 last_distance_err;
void get_distance(int16 ROW, int16 COL)
{
//    if(ROW_last==ROW&&COL_last==COL)
//        return 0;
//    else
//    {
        distance_err = tricore_abs((COL - COL_last));
        COL_last = COL;
        ROW_last=ROW;
         error_d=init_distance-distance_err;
        error_x=(ROW_last+ROW)/2-94-init_error_x;
//        return init_distance-distance_err;
//    }

}

void get_distance_dragon(int16 ROW, int16 COL)
{
    distance_err = tricore_abs((ROW - ROW_last));
    COL_last = COL;
    ROW_last=ROW;
    error_d=init_distance-distance_err;
    k=(ROW_last-ROW)/(COL_last-COL);
}
int16 tricore_abs(int16 num)
{
    return num > 0 ? num : -num;
}
void draw_frame(int16 ROW, int16 COL, int16 half_step)
{
    // 向上下左右四个方向分别移动六个像素点，别问我为什么不是四个，四不吉利。

    // 左边线
    ips200_draw_line(ROW - half_step, COL - half_step, ROW - half_step, COL + half_step, RGB565_WHITE);

    // 右边线
    ips200_draw_line(ROW + half_step, COL - half_step, ROW + half_step, COL + half_step, RGB565_WHITE);

    // 上边线
    ips200_draw_line(ROW - half_step, COL - half_step, ROW + half_step, COL - half_step, RGB565_WHITE);

    // 下边线
    ips200_draw_line(ROW - half_step, COL + half_step, ROW + half_step, COL + half_step, RGB565_WHITE);
}
void image_process()
{
    // 找白点,遍历即可
    // 从下往上 从左往右
    // 搜碰到白点就跳出
    int n=0;
    for (COL = MAX_H; COL >= MIN_H; COL -= step)
    {
        for (ROW = MAX_W; ROW >= MIN_W; ROW -= step)
        {
            if (mt9v03x_image[COL][ROW] >= 240)
            {
                // ips200_show_int(0, 170, distance_err,3);
            //    ips200_show_float(0, 190, k, 2,2);
                get_distance(ROW, COL);
                draw_frame(ROW, COL, 6);
                COL-=3;
                n++;
                light_flag=1;
                break;
            }
        }
    }
    if(light_flag==0&n<2)
        stop_flag=1;

     ips200_draw_line(MAX_W, 0, MAX_W, MT9V03X_H, RGB565_GREEN);
     ips200_draw_line(MIN_W, 0, MIN_W, MT9V03X_H, RGB565_BLUE);
     ips200_draw_line(0, MIN_H, MT9V03X_W, MIN_H, RGB565_PINK);
     ips200_draw_line(0, MAX_H, MT9V03X_W, MAX_H, RGB565_GRAY);
}
int16 light_up[2][2];
int16 light_down[2][2];
int16 Light[2][2];
void image_process_170()
{
    // 找白点,遍历即可
    // 从下往上 从左往右
    // 搜碰到白点就跳出
    int n=0;
    for (COL = Min_h; COL <=Max_h; COL += step)//light_1_l_up
    {
        if(light_find[2]==1)
        {
            break;
        }
        for (ROW = Min_w; ROW <= Max_w; ROW += step)
        {
            if (mt9v03x_image[COL][ROW] >= thres)
            {
                // ips200_show_int(0, 170, distance_err,3);
            //    ips200_show_float(0, 190, k, 2,2);
                light_up[O][1]=ROW;
                light_up[O][2]=COL;
                light_find[2]=1;
//                 ips200_show_int(0,300,light_up[O][2],3);
                 ips200_show_int(40,300,ROW,3);ips200_show_int(80,300,light_find[2],1);//no_find
                stop_flag=0;
                 ips200_draw_point(ROW,COL,RGB565_RED);
                break;
            }
        }
    }
    ips200_show_int(0,300,light_up[O][2],3);
    for (COL = Max_h; COL >= Min_h; COL -= step)//light_2_r_down
    {
        if(light_find[1]==1)
        {
            break;
        }
        for (ROW = Max_w; ROW >= Min_w; ROW -= step)
        {
            if (mt9v03x_image[COL][ROW] >= thres)
            {
                // ips200_show_int(0, 170, distance_err,3);
            //    ips200_show_float(0, 190, k, 2,2);
                light_down[T][1]=ROW;
                light_down[T][2]=COL;
                light_find[1]=1;
//                 ips200_show_int(100,300,COL,3);
                ips200_show_int(140,300,ROW,3);ips200_show_int(180,300,light_find[1],1);
                 ips200_draw_point(ROW,COL,RGB565_RED);
                 stop_flag=0;
                break;
            }
        }

    }
    ips200_show_int(100,300,light_down[T][2],3);

    if(light_find[1]==1&&light_find[2]==1)
    {
        Median_line=(int16)(light_up[O][2]+light_down[T][2])/2;
        ips200_draw_line(0,Median_line,Max_w,Median_line,RGB565_BLUE);
    }

    else if((light_find[1]!=1&&light_find[2]!=1))
    {
        Median_line=30;
        ips200_draw_line(0,Median_line,Max_w,Median_line,RGB565_GREEN);
    }
    ips200_show_int(200,300,Median_line,3);


    for (COL = Median_line; COL >= Min_h; COL -= step)//light_1_r_down
    {
        if(light_find[3]==1)
        {
            break;
        }
        for (ROW = Max_w; ROW >= Min_w; ROW -= step)
        {
            if (mt9v03x_image[COL][ROW] >= thres)
            {
                // ips200_show_int(0, 170, distance_err,3);
            //    ips200_show_float(0, 190, k, 2,2);
                light_down[O][1]=ROW;
                light_down[O][2]=COL;
                light_find[3]=1;
//                ips200_show_int(0,240,COL,3);ips200_show_int(40,240,ROW,3);ips200_show_int(80,240,light_find[3],1);
                ips200_draw_point(ROW,COL,RGB565_RED);
                stop_flag=0;
                break;
            }
        }
    }

    for (COL = Median_line; COL <= Max_h; COL += step)//light_2_l_down
    {
        if(light_find[4]==1)
        {
            break;
        }
        for (ROW = Min_w; ROW <=Max_w; ROW += step)
        {
            if (mt9v03x_image[COL][ROW] >= thres)
            {
                // ips200_show_int(0, 170, distance_err,3);
            //    ips200_show_float(0, 190, k, 2,2);
                light_up[T][1]=ROW;
                light_up[T][2]=COL;
                light_find[4]=1;
//                ips200_show_int(0,260,COL,3);ips200_show_int(40,260,ROW,3);ips200_show_int(80,260,light_find[4],1);//no_find
                ips200_draw_point(ROW,COL,RGB565_RED);
                stop_flag=0;
                break;
            }
        }
    }
    //1
    if(light_find[1]==1&&light_find[4]==1&&light_find[2]==1&&light_find[3]==1)//2
    {

        Light[T][1] = (light_up[T][1]+light_down[T][1])/2;//h
        Light[T][2] = (light_up[T][2]+light_down[T][2])/2;//w

        Light[O][1] = (light_up[O][1]+light_down[O][1])/2;//h
        Light[O][2] = (light_up[O][2]+light_down[O][2])/2;//w


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;
        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);

        error_d=init_distance-distance_err;
        last_error_x=error_x;last_error_d=error_d;

        if((Light[O][2]-Light[T][2])!=0)
            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
        angle=slopeToAngle(slope);
        last_angle=angle;
    }
    //light_down
    else if(light_find[1]==1&&light_find[4]!=1&&light_find[2]==1&&light_find[3]==1)
    {
        Light[T][1] = light_down[T][1];
        Light[T][2] = light_down[T][2];

        Light[O][1] = (light_up[O][1]+light_down[O][1])/2;//h
        Light[O][2] = (light_up[O][2]+light_down[O][2])/2;//w


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);


//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));


        error_d=init_distance-distance_err;
        last_error_x=error_x;last_error_d=error_d;
        if((Light[O][2]-Light[T][2])!=0)
            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
        angle=slopeToAngle(slope);
        last_angle=angle;

    }
    //light_up
    else if(light_find[1]!=1&&light_find[4]==1&&light_find[2]==1&&light_find[3]==1)
    {
        Light[T][1] = light_up[T][1];
        Light[T][2] = light_up[T][2];

        Light[O][1] = (light_up[O][1]+light_down[O][1])/2;//h
        Light[O][2] = (light_up[O][2]+light_down[O][2])/2;//w


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;


        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);


//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));


        error_d=init_distance-distance_err;
        last_error_x=error_x;last_error_d=error_d;

        if((Light[O][2]-Light[T][2])!=0)
            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
        angle=slopeToAngle(slope);
        last_angle=angle;
    }


    //2    else if(light_find[3]==1&&light_find[2]!=1)
    else if(light_find[1]==1&&light_find[4]==1&&light_find[3]==1&&light_find[2]!=1)//2
    {

        Light[T][1] = (light_up[T][1]+light_down[T][1])/2;//h
        Light[T][2] = (light_up[T][2]+light_down[T][2])/2;//w

        Light[O][1] = light_down[O][1];
        Light[O][2] = light_down[O][2];


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);

//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));


        error_d=init_distance-distance_err;
        last_error_x=error_x;last_error_d=error_d;

//        slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
//        angle=slopeToAngle(slope);

    }
    //light_down
    else if(light_find[1]==1&&light_find[4]!=1&&light_find[3]==1&&light_find[2]!=1)
    {
        Light[T][1] = light_down[T][1];
        Light[T][2] = light_down[T][2];

        Light[O][1] = light_down[O][1];
        Light[O][2] = light_down[O][2];


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);


//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        error_d=init_distance-distance_err;
        last_error_x=error_x;  last_error_d=error_d;

//        if((Light[O][2]-Light[T][2])!=0)
//            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
//        angle=slopeToAngle(slope);
//        last_angle=angle;
    }
    //light_up
    else if(light_find[1]!=1&&light_find[4]==1&&light_find[3]==1&&light_find[2]!=1)
    {
        Light[T][1] = light_up[T][1];
        Light[T][2] = light_up[T][2];

        Light[O][1] = light_down[O][1];
        Light[O][2] = light_down[O][2];


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);


//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));
        error_d=init_distance-distance_err;
        last_error_x=error_x;last_error_d=error_d;

//        if((Light[O][2]-Light[T][2])!=0)
//            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
//        angle=slopeToAngle(slope);
//        last_angle=angle;
    }


    //3

    else if(light_find[1]==1&&light_find[4]==1&&light_find[3]!=1&&light_find[2]==1)//2
    {

        Light[T][1] = (light_up[T][1]+light_down[T][1])/2;//h
        Light[T][2] = (light_up[T][2]+light_down[T][2])/2;//w

        Light[O][1] = light_up[O][1];
        Light[O][2] = light_up[O][2];


        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);

//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));
        error_d=init_distance-distance_err;
        last_error_x=error_x;last_error_d=error_d;

//        if((Light[O][2]-Light[T][2])!=0)
//            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
//        angle=slopeToAngle(slope);
//        last_angle=angle;

    }
    //light_down
    else if(light_find[1]==1&&light_find[4]!=1&&light_find[3]!=1&&light_find[2]==1)
    {
        Light[T][1] = light_down[T][1];
        Light[T][2] = light_down[T][2];

        Light[O][1] = light_up[O][1];
        Light[O][2] = light_up[O][2];

        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);

//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        error_d=init_distance-distance_err;
        last_error_x=error_x;
        last_error_d=error_d;

//        if((Light[O][2]-Light[T][2])!=0)
//            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
//        angle=slopeToAngle(slope);
//        last_angle=angle;
    }
    //light_up
    else if(light_find[1]!=1&&light_find[4]==1&&light_find[3]!=1&&light_find[2]==1)
    {
        Light[T][1] = light_up[T][1];
        Light[T][2] = light_up[T][2];

        Light[O][1] = light_up[O][1];
        Light[O][2] = light_up[O][2];

        error_x=(Light[O][1]+Light[T][1])/2-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-Light[T][2]));

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],Light[T][1],Light[T][2]);

//        distance_err=tricore_abs((Light[O][2]-Light[T][2]));
        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

//        if((Light[O][2]-Light[T][2])!=0)
//            slope=Slope( Light[O][2]-Light[T][2] , Light[O][1]-Light[T][1] );
//        angle=slopeToAngle(slope);
//        last_angle=angle;
    }

#if 0

    else if(light_find[1]!=1&&light_find[4]!=1&&light_find[3]==1&&light_find[2]==1)
    {
        Light[O][1] = (light_up[O][1]+light_down[O][1])/2;
        Light[O][2] = (light_up[O][2]+light_down[O][2])/2;
        error_x=Light[O][1]-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-30))*2;

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],X,Y)*2;

//        distance_err=tricore_abs((Light[O][2]-30))*2;
        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

        if(( Light[O][2]-30 )!=0)
            slope=Slope( Light[O][2]-30 , Light[O][1]-94 );
        angle=slopeToAngle(slope);
        last_angle=angle;
    }

    else if(light_find[1]!=1&&light_find[4]!=1&&light_find[3]!=1&&light_find[2]==1)
    {
        Light[O][1] = light_up[O][1];
        Light[O][2] = light_up[O][2];
        error_x=Light[O][1]-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-30))*2;

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],X,Y)*2;

//        distance_err=tricore_abs((Light[O][2]-30))*2;

        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

        if(( Light[O][2]-30 )!=0)
            slope=Slope( Light[O][2]-30 , Light[O][1]-94 );
        angle=slopeToAngle(slope);
        last_angle=angle;
    }

    else if(light_find[1]!=1&&light_find[4]!=1&&light_find[3]==1&&light_find[2]!=1)
    {
        Light[O][1] = light_down[O][1];
        Light[O][2] = light_down[O][2];
        error_x=Light[O][1]-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[O][2]-30))*2;

        else if(distance_flag==1)
            distance_err=Distance(Light[O][1],Light[O][2],X,Y)*2;

//        distance_err=tricore_abs((Light[O][2]-30))*2;
        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

        if(( Light[O][2]-30 )!=0)
            slope=Slope( Light[O][2]-30 , Light[O][1]-94 );
        angle=slopeToAngle(slope);
        last_angle=angle;

    }

    else if(light_find[1]==1&&light_find[4]==1&&light_find[3]!=1&&light_find[2]!=1)
    {
        Light[T][1] = (light_down[T][1]+light_up[T][1])/2;
        Light[T][2] = (light_down[T][2]+light_up[T][2])/2;
        error_x=Light[T][1]-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[T][2]-30))*2;

        else if(distance_flag==1)
            distance_err=Distance(Light[T][1],Light[T][2],X,Y)*2;

//        distance_err=tricore_abs((Light[T][2]-30))*2;
        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

        if(( 30-Light[T][2] )!=0)
            slope=Slope( 30-Light[T][2] , 94-Light[T][1] );
        angle=slopeToAngle(slope);
        last_angle=angle;
    }

    else if(light_find[1]==1&&light_find[4]!=1&&light_find[3]!=1&&light_find[2]!=1)
    {
        Light[T][1] = light_up[T][1];
        Light[T][2] = light_up[T][2];
        error_x=Light[T][1]-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[T][2]-30))*2;

        else if(distance_flag==1)
            distance_err=Distance(Light[T][1],Light[T][2],X,Y)*2;

//        distance_err=tricore_abs((Light[T][2]-30))*2;
        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

        if(( 30-Light[T][2] )!=0)
            slope=Slope( 30-Light[T][2] , 94-Light[T][1] );
        angle=slopeToAngle(slope);
        last_angle=angle;
    }

    else if(light_find[1]==1&&light_find[4]==1&&light_find[3]!=1&&light_find[2]!=1)
    {
        Light[T][1] = light_down[T][1];
        Light[T][2] = light_down[T][2];
        error_x=Light[T][1]-94-init_error_x;

        if(distance_flag==0)
            distance_err=tricore_abs((Light[T][2]-30))*2;

        else if(distance_flag==1)
            distance_err=Distance(Light[T][1],Light[T][2],X,Y)*2;

//        distance_err=tricore_abs((Light[T][2]-30))*2;
        error_d=init_distance-distance_err;
        last_error_d=error_d;
        last_error_x=error_x;

        if(( 30-Light[T][2] )!=0)
            slope=Slope( 30-Light[T][2] , 94-Light[T][1] );
        angle=slopeToAngle(slope);
        last_angle=angle;

    }
#endif


//    else if(light_find[1]!=1&&light_find[4]!=1&&light_find[2]==1&&light_find[3]==1)
//    {
//
//    }
    //1
//    if(light_find[2]==1&&light_find[3]==1)//1
//
//    {
    //        Light[O][1] = (light_up[O][1]+light_down[O][1])/2;//h
    //        Light[O][2] = (light_up[O][2]+light_down[O][2])/2;//w
//    }

//    else if(light_find[3]==1&&light_find[2]!=1)
//    {
//        Light[O][1] = light_down[O][1];
//        Light[O][2] = light_down[O][2];
//    }

//    else if(light_find[3]!=1&&light_find[2]==1)
//    {
//        Light[O][1] = light_up[O][1];
//        Light[O][2] = light_up[O][2];
//    }
    else if(light_find[3]!=1&&light_find[2]!=1&&light_find[1]!=1&&light_find[4]!=1)
    {
//        distance_err=last_distance_err;
        error_x=last_error_x;
        error_d=last_error_d;
       stop_flag=1;

       angle=last_angle;
//        distance_err=init_distance;
    }

    last_distance_err=distance_err;

//    error_d=init_distance-distance_err;
//    last_error_x=error_x;
//    draw_frame(Light[O][1], Light[O][2], 3);
//    draw_frame(Light[T][1], Light[T][2], 3);
//    ips200_draw_point(Light[O][1],Light[O][2],RGB565_RED);
//    ips200_draw_point(Light[T][1],Light[T][2],RGB565_RED);
//     ips200_show_int(0,160,Light[O][1],3);ips200_show_int(40,160,Light[O][2],3);
//     ips200_show_int(0,180,Light[T][1],3);ips200_show_int(40,180,Light[T][2],3);
    light_find[1]=0;
    light_find[2]=0;
    light_find[3]=0;
    light_find[4]=0;
}

void get_thres_white()
{
    for (COL = Max_h; COL >= Min_h; COL -= step)
    {
        for (ROW = Max_w; ROW >= Min_w; ROW -= step)
        {
            if (max <= mt9v03x_image[COL][ROW])
                max = mt9v03x_image[COL][ROW];
            ips200_show_int(0, 170, max, 3);
        }
    }
}


int32 light[4][2],light_fun[4],n=0;
int16 image_process_two()
{
    for (COL = MIN_H; COL <=MAX_H; COL += step)
    {
        for (ROW = MIN_W; ROW <= MAX_W; ROW += step)
        {
            if (mt9v03x_image[COL][ROW] >= 60&&n%4==0)
            {
                light[1][1]=ROW;
                light[1][2]=COL;
                light_fun[1]=1;
                n++;
                break;
            }
            if (mt9v03x_image[COL][ROW] >= 60&&n%4==1)
            {
                light[2][1]=ROW;
                light[2][2]=COL;
                light_fun[2]=1;
                n++;
                COL=MAX_H;
                break;
            }
        }
    }
    for (COL = MAX_H; COL >= MIN_H; COL -= step)
    {
        for (ROW = MAX_W; ROW >= MIN_W; ROW -= step)
        {
            if (mt9v03x_image[COL][ROW] >= 60&&n%4==2)
            {
                light[3][1]=ROW;
                light[3][2]=COL;
                light_fun[3]=1;
                n++;
                break;
            }
            if (mt9v03x_image[COL][ROW] >= 60&&n%4==3)
            {
                light[4][1]=ROW;
                light[4][2]=COL;
                light_fun[4]=1;
                n++;
                COL=MIN_H;
                break;
            }
        }
    }
    if(n%4==0)
    {
        n=0;
        light_flag=2;
    }
}
//龙邱方案
void image_process_dragon()
{
    for (ROW = MAX_W; ROW >= MIN_W; ROW -= step)
    {
        for (COL = MAX_H; COL >= MIN_H; COL -= step)
        {
            if (mt9v03x_image[COL][ROW] >= 60)
            {
                // ips200_show_int(0, 170, distance_err,3);
            //    ips200_show_float(0, 190, k, 2,2);
                get_distance(ROW, COL);
                draw_frame(ROW, COL, 6);
                COL-=3;
                n++;
                light_flag=1;
                break;
            }
        }
    }
    if(light_flag==0&n<2)
        stop_flag=1;

     ips200_draw_line(MAX_W, 0, MAX_W, MT9V03X_H, RGB565_GREEN);
     ips200_draw_line(MIN_W, 0, MIN_W, MT9V03X_H, RGB565_BLUE);
     ips200_draw_line(0, MIN_H, MT9V03X_W, MIN_H, RGB565_PINK);
     ips200_draw_line(0, MAX_H, MT9V03X_W, MAX_H, RGB565_GRAY);
}


//上大风扇
//             +//1
//        3//+   +//4
//             +//2
//
int16 four[4][3];
int16 light_find_four[4][2];

//return true||false int||bool都可以
 int16 seek_only()
 {
     //上面那个点
     for(uint8 i=0;i<Max_h;i++)
     {
         for(uint8 j=0;j<Max_w;j++)
         {
             if(mt9v03x_image[i][j]==255)
             {
                 four[1][x]=j;
                 four[1][y]=i;
                 light_find_four[1][1]=1;
                 break;
             }
         }
         if(light_find_four[1][1]==1)
             break;
     }
     int x1=four[1][x],y1=four[1][y];
     ips200_draw_point(x1,y1,RGB565_RED);

     for(uint8 i=y1;i<Max_h;i++)
     {
         for(uint8 j=x1;j<Max_w;j++)
         {
             if(mt9v03x_image[i][j]==255&&(mt9v03x_image[i][j+1]!=255))
             {
                 four[1][x]=(j+x1)/2;
                 four[1][y]=(i+y1)/2;
                 light_find_four[1][2]=1;
                 break;
             }
         }
         if(light_find_four[1][2]==1)
             break;
     }

     //下面那个点
     for(uint8 i=Max_h;i>0;i--)
     {
         for(uint8 j=0;j<Max_w;j++)
         {
             if(mt9v03x_image[i][j]==255)
             {
                 four[2][x]=j;
                 four[2][y]=i;
                 light_find_four[2][1]=1;
                 break;
             }
         }
        if(light_find_four[2][1]==1)
            break;
     }
    int x2=four[2][x],y2=four[2][y];
     for(uint8 i=four[2][x];i>0;i--)
     {
         for(uint8 j=four[2][x];j<Max_w;j++)
         {
             if(mt9v03x_image[i][j]==255&&mt9v03x_image[i][j+1]!=255)
             {
                 four[2][x]=(j+x2)/2;
                 four[2][y]=(i+y2)/2;
                 light_find_four[2][2]=1;
                 break;
             }
         }
         if(light_find_four[2][2]==1)
         break;
     }


     Median_line_y=(four[2][y]+four[1][y])/2;
     Median_line_x=(four[2][x]+four[1][x])/2;


     ips200_draw_line(0,Median_line_y,188,Median_line_y,RGB565_RED);
     ips200_draw_line(Median_line_x,0,Median_line_x,60,RGB565_BLUE);
     if( !light_find_four[1][1] && !light_find_four[1][2] && !light_find_four[2][1] && !light_find_four[2][2] )
     {
        return false;
     }

    if( light_find_four[1][1] && light_find_four[1][2] && light_find_four[2][1] && light_find_four[2][2] )
     
    {
        for(uint8 i=Median_line_y;i>0;i--)
     {
         for(uint8 j=0;j<Median_line_x;j++)
         {
             if(mt9v03x_image[i][j]==255&&mt9v03x_image[i][j-1]!=255)
             {
                 four[3][x]=j;
                 four[3][y]=i;
                 light_find_four[3][1]=1;
                 break;
             }
         }
         if(light_find_four[3][1]==1)
         break;
     }
     int x3=four[3][x],y3=four[3][y];
     for(uint8 j=four[3][x];j<Median_line_x;j++)
     {
            if(mt9v03x_image[x3][j]==255&&mt9v03x_image[x3][j+1]!=255)
             {
                 four[3][x]=(j+y3)/2;
                 light_find_four[3][2]=1;
                 break;
             }
     }

     for(uint8 i=Median_line_y;i>0;i--)
     {
         for(uint8 j=Median_line_x;j<Max_w;j++)
         {
             if(mt9v03x_image[i][j]==255&&mt9v03x_image[i][j-1]!=255)
             {
                 four[4][x]=j;
                 four[4][y]=i;
                 light_find_four[4][1]=1;
                 break;
             }
         }
         if(light_find_four[4][1]==1)
         break;
     }
         int x4=four[4][x],y4=four[4][y];
     for(uint8 j=four[4][x];j<Median_line_x;j++)
     {
            if(mt9v03x_image[x4][j]==255&&mt9v03x_image[x4][j+1]!=255)
             {
                 four[4][x]=(j+y4)/2;
                 light_find_four[4][2]=1;
                 break;
             }
     }

    }
//     for(int i=1;i<=4;i++)
//     {
//        for(int j=1;j<=2;j++)
//
//        {
//            light_find_four[i][j]=0;
//        }
//     }
    ips200_show_int(50,260,four[1][2],3);
    ips200_show_int(50,280,four[1][3],3);

    ips200_show_int(90,260,four[2][2],3);
    ips200_show_int(90,280,four[2][3],3);

    ips200_show_int(130,260,four[3][2],3);
    ips200_show_int(130,280,four[3][3],3);

    ips200_show_int(170,260,four[4][2],3);
    ips200_show_int(170,280,four[4][3],3);
     memset(light_find_four, 0, sizeof(light_find_four));
     return true;
 }
