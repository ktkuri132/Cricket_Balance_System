#ifndef __CONTROL__H
#define __CONTROL__H


#include <bsp/Serial.h>
extern Stde_DataTypeDef USART2_Data;

#define OpenMVData_X StdeUSART_Deal(&USART2_Data,1)
#define OpenMVData_Y StdeUSART_Deal(&USART2_Data,2)

typedef enum {
    X,
    Y
} Axis;

typedef enum{
    XMAX_PWM ,
    XMIN_PWM ,
    XMid_PWM ,
    YMAX_PWM ,
    YMIN_PWM ,
    YMid_PWM 
} PWM_Range;

typedef enum {
    S1,S2,S3,
    S4,S5,S6,
    S7,S8,S9
} Space_Site;

#define Motor_x TIM3->CCR4
#define Motor_y TIM3->CCR3

void Control_Init();
void Control();

int32_t Get_Blobs_Speed(int32_t dir,uint32_t current);
void Goto_space(int x,int y);
void Site_set(int x);

#endif