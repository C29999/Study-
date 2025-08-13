/*
 * Image_process.c
 *
 *  Created on: 2025年1月13日
 *      Author: 吴
 */
#include"long_qiu.h"
#define LIMIT  0

uint8_t threshold_value =80;
uint8_t image_deal[MT9V03X_H][MT9V03X_W];

uint8_t point1[2][2], point2[2][2],  centre[2][2];
uint8_t point1_flag = 0;
// 0: 未发现第一个点的左上角
// 1： 发现第一个点的左上角
// 2： 发下第一个点的右下角
uint8_t point2_flag = 0;
// 0: 未发现第二个点的左下角
// 1： 发现第二个点的左下角
// 2： 发下第二个点的右上角
uint8_t protect_flag;
float  x_point,y_point;
uint8_t Deal_succeed_count = 0; //对正确处理图像计数 当正确处理图像超100次时退出该状态
void Image_process_calculate(float *x_error,float *y_reeor)
{
    Image_filter(threshold_value);
    uint8_t Y_L =0,X_L=0;
    float value1 = 0,value2 = 0;
    if( (point1_flag == 0 && point2_flag == 1) || (point1_flag == 0 && point2_flag == 0) || (point1_flag == 1 && point2_flag == 0))//寻找点1的左上角和左二的右下角
    { for(Y_L =0;Y_L< MT9V03X_H  ;Y_L++)
      { for(X_L = 0;X_L< MT9V03X_W  ;X_L++)
        {   if(point1_flag == 0)//寻找第一个点的左上角
            { value1 = Image_process_deal_point1(X_L,Y_L);
              if(value1 > LIMIT ){ point1[0][0] = X_L; point1[0][1] = Y_L; point1_flag  = 1;}
            }
            if(point2_flag == 0)//寻找第二个点的左下角
            { value2 = Image_process_deal_point2(X_L,Y_L);
             if(value2 > LIMIT ){ point2[0][0] = X_L;  point2[0][1] =  MT9V03X_H - Y_L - 1; point2_flag  = 1; }
            }
            if(point1_flag == 1 &&  point2_flag == 1) break;
        }
            if(point1_flag == 1 &&  point2_flag == 1) break;
      }
    }
    if( (point1_flag == 1 && point2_flag == 1) || (point1_flag == 1 && point2_flag == 2) || (point1_flag == 2 && point2_flag == 1))//寻找点1的右下角和左二的右上角
    {
       for(Y_L = ( point2[0][1] +  point1[0][1])/2 ; Y_L< MT9V03X_H   ; Y_L++)
       {
           for( X_L = MT9V03X_W-1; X_L>0 ;X_L-- )
           {
               if(point1_flag == 1)
               { value1 = Image_process_deal_point1_right(X_L,Y_L);
                 if(value1 > LIMIT ){ point1[1][0] = X_L; point1[1][1] = ( point2[0][1] +  point1[0][1]) - Y_L; point1_flag  = 2;}
               }
               if(point2_flag  == 1)
               { value2 = Image_process_deal_point2_right(X_L,Y_L);
                 if(value2 > LIMIT ){ point2[1][0] = X_L; point2[1][1] = Y_L; point2_flag  = 2; }
               }
               if(point1_flag == 2 &&  point2_flag == 2) break;
           }
               if(point1_flag == 2 &&  point2_flag == 2) break;
       }
    }

    if(point1_flag == 2 &&  point2_flag == 2)
    {
         Square_centre(point1,&centre[0][0],&centre[0][1]);
         Square_centre(point2,&centre[1][0],&centre[1][1]);
         *y_reeor =  centre[1][1] - centre[0][1];
         *x_error = (centre[0][0] + centre[1][0])/2.0;
         point1_flag = 0;
         point2_flag = 0;
         Deal_succeed_count ++;
         if(Deal_succeed_count > 100)
         {
             if(protect_flag == 1)//退出保护状态
             {
                 protect_flag = 0;
             }
             Deal_succeed_count = 0;
         }
    }else
    {
        protect_flag  = 1;
    }
    //图像识别保护 若经过上述两个过程后
    //point1_flag和 point2_flag 两个都不为2则证明图像丢失这时开启保护位

}

// function : 传入图像的两个对角坐标(x1,y1) (x2,y2)，计算中心点坐标(centre_x,centre_y)
// parameter: 两个对角坐标(x1,y1) (x2,y2) 中心点坐标(centre_x,centre_y)指针
// return   : NULL
void Square_centre(uint8_t point[2][2],uint8_t * center_x,uint8_t*centre_y)
{
    *center_x = (point[0][0]*1.0 + point[1][0]*1.0)/2;
    *centre_y = (point[0][1]*1.0 + point[1][1]*1.0)/2;
}


// function : 取绝对值
// parameter: value值
// return   : value的绝对值
float  absolute(float value)
{
    if(value <0)
    {
        value = -value;
    }
    return value;
}

// function : 从图像左上到右下寻找第一个亮点的左上角
// parameter:
// return   :
//    ----------------
//   | ->   **        |
//   |      **        |
//   |                |
//   |                |
//    ----------------
float  Image_process_deal_point1(uint8_t x_l,uint8_t y_l)
{
    float value = 0;
    if (x < MT9V03X_W - 1)//防止数组越界
    {
      value = ( image_deal[y][x+1]*1.0 - image_deal[y][x])/
              ( image_deal[y][x+1]*1.0 + image_deal[y][x]);
    }//计算相邻两个点的差比和
    value = absolute(value);//取绝对值保障都是正数
    return value;
}

// function : 从图像左下到右上寻找第二个亮点的左下角
// parameter:
// return   :
//    ---------------
//   |                |
//   |      **        |
//   |      **        |
//   | ->             |
//    ---------------
float  Image_process_deal_point2(uint8_t x_l,uint8_t y_l)
{
    float value = 0;
    y_l  = MT9V03X_H - y_l - 1;
    if (x < MT9V03X_W - 1)//防止数组越界
    {
      value = ( image_deal[y][x+1]*1.0 - image_deal[y][x])/
              ( image_deal[y][x+1]*1.0 + image_deal[y][x]);
    }//计算相邻两个点的差比和
    value = absolute(value);//取绝对值保障都是正数
    return value;
}


// function : 从图像左上到右下寻找第一个亮点的右下角
// parameter:
// return   :
//    ----------------
//   |      **        |
//   |      **      <-|
//   |                |
//   |                |
//    ----------------
float  Image_process_deal_point1_right(uint8_t x_l,uint8_t y_l)
{
    float value = 0;
    y_l  = ( point2[0][1] +  point1[0][1]) - y_l;
    if (x > 0)//防止数组越界
    {
      value = ( image_deal[y_l][x_l-1]*1.0 - image_deal[y_l][x_l])/
              ( image_deal[y_l][x_l-1]*1.0 + image_deal[y_l][x_l]);
    }//计算相邻两个点的差比和
    value = absolute(value);//取绝对值保障都是正数
    return value;
}

// function : 从图像左下到右上寻找第二个亮点的右上角
// parameter:
// return   :
//    ---------------
//   |               |
//   |               |
//   |      **     <-|
//   |      **       |
//    ---------------
float  Image_process_deal_point2_right(uint8_t x_l,uint8_t y_l)
{
    float value = 0;
    if (x_l > 0)//防止数组越界
    {
      value = ( image_deal[y_l][x_l-1]*1.0 - image_deal[y_l][x_l])/
              ( image_deal[y_l][x_l-1]*1.0 + image_deal[y_l][x_l]);
    }//计算相邻两个点的差比和
    value = absolute(value);//取绝对值保障都是正数
    return value;
}

// function : 将图像预处理，将外界小光斑滤掉（小于阈值的点的灰度值赋1）
// parameter:  threshold 阈值
// return   :
void Image_filter(uint8_t threshold)
{
      for (uint8_t i = 0; i < MT9V03X_H; i++)
      {
          for (uint8_t j = 0; j < MT9V03X_W; j++)
          {
              if (mt9v03x_image[j][i] >= threshold)
                  image_deal[j][i] = mt9v03x_image[j][i]  ;
              else
                  image_deal[j][i] = 1;
          }
      }
}

float cauclate_variance(float average,float num)
{
    float out = 0;
    out = (num - average)*(num - average);
    return out;
}


// function :  将图像预处理，计算图片中所有白色光斑的横坐标的均值和方差
// parameter:  threshold 阈值   Image_x_average 横坐标的均值    variance  横坐标的方差
// return   :
void LQ_Deal_Image(float *Image_x_average, float *variance,uint8_t threshold)
{
    uint16_t  point_x_record[800] = {0}; //存储所有白色光斑点的横向坐标
    uint16_t i = 0,j = 0,point_count = 0;
    float x_sum = 0,variance_sum = 0;
    for(i= 0 ;i < MT9V03X_H;i++)
    {
        for(j= 0 ;j < MT9V03X_W;j++)
        {
               if (mt9v03x_image[i][j] >= threshold )
               {
                   x_sum += j;
                   point_x_record[point_count] = j;
                   point_count ++;
                   if(point_count >= 800)
                   {
                       ips200_show_string(100,120,"ERROR");
                   }
               }
        }
    }

    if(point_count != 0 )        //图像中残存的有亮点
    {
        if( protect_flag  == 1) //保护状态机
        {
            Deal_succeed_count ++;
            if(Deal_succeed_count > 5)
            {
                Deal_succeed_count =0;
                protect_flag = 0;
            }
        }
        *Image_x_average= x_sum/point_count;
         for (uint8_t k = 0 ;k < point_count;k++)
         {
            variance_sum += cauclate_variance(*Image_x_average,point_x_record[k]);
         }
         *variance = variance_sum/ point_count;
         if(*variance < 4)
         {
              protect_flag  = 1; //开启保护
         }
         else
             protect_flag = 0;
    }else if(point_count == 0)    //图像光电丢失
    {
        *variance = 0;
        *Image_x_average = 0;
         protect_flag  = 1; //开启保护
    }
}


float found_juge()
{
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
                break;
            }
        }
    }
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
                light_down[T][1]=ROW;
                light_down[T][2]=COL;
                light_find[1]=1;
                break;
            }
        }
    }
    double t = get_k( light_down[T][1] , light_down[T][2] , light_down[O][1] , light_down[O][2]);
   return cos(atan(t));
}
inline float get_k(int x1,int y1,int x2,int y2)
{
    if(x1 == x2)
        return ANGLE_TO_RAD(90.);
    if(y1 == y2)
        return ANGLE_TO_RAD(0.);
    double ki = ( y2 - y1 )/( x2 - x1);
    return atan(ki);
}
