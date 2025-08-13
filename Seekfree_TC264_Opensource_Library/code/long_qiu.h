
#ifndef CODE_IMAGE_PROCESS_H_
#define CODE_IMAGE_PROCESS_H_
#include "zf_common_headfile.h"
void Image_process_calculate(float *x_error,float *y_reeor);
void LQ_Deal_Image(float *Image_x_average, float *variance,uint8_t threshold);

void   Square_centre(uint8_t point[2][2],uint8_t * center_x,uint8_t *centre_y);
void   Image_filter(uint8_t threshold);
float  Image_process_deal_point1(uint8_t x_l,uint8_t y_l);
float  Image_process_deal_point2(uint8_t x_l,uint8_t y_l);
float  Image_process_deal_point2_right(uint8_t x_l,uint8_t y_l);
float  Image_process_deal_point1_right(uint8_t x_l,uint8_t y_l);

float found_juge();
inline float get_k(int x1,int y1,int x2,int y2);

extern uint8_t protect_flag;
extern float  x_point,y_point;
extern uint8_t Deal_succeed_count;

#endif /* CODE_IMAGE_PROCESS_H_ */
