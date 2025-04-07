#ifndef __CONTROL__H
#define __CONTROL__H


#include <bsp/Serial.h>
extern Stde_DataTypeDef *USART2_Data;

#define OpenMVData_X StdeUSART_Deal(USART2_Data,1)
#define OpenMVData_Y StdeUSART_Deal(USART2_Data,2)

typedef enum {
    X,
    Y
} Axis;


#define Motor_x TIM3->CCR4
#define Motor_y TIM3->CCR3

void Control_Init();
void Control();

int32_t Get_Blobs_Speed(int32_t dir,uint32_t current);

#endif