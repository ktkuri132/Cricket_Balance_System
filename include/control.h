#ifndef __CONTROL__H
#define __CONTROL__H


#include <bsp/Serial.h>
extern Stde_DataTypeDef *USART2_Data;

#define OpenMVData_X USART_Deal(USART2_Data,1)
#define OpenMVData_Y USART_Deal(USART2_Data,2)
#define Motor_x TIM3->CCR3
#define Motor_y TIM3->CCR4

void Control_Init();
void Control();

#endif