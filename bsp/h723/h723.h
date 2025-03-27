#ifndef __H723_H
#define __H723_H

#include <sysport.h>
#include <stm32h7xx.h>

#include <stdint.h>
#include <stddef.h>
#include "stm32h723xx.h"

typedef enum{
    AF_0,AF_1,AF_2,AF_3,AF_4,AF_5,AF_6,AF_7,
    AF_8,AF_9,AF_10,AF_11,AF_12,AF_13,AF_14,AF_15
 
}GPIO_Pin;

typedef enum{
    Channel_1,Channel_2,Channel_3,Channel_4
}Channel;

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_Pin_x;
    uint32_t GPIO_Mode_x;
    uint32_t GPIO_PuPd_x;
    uint32_t GPIO_Speed_x;
    uint32_t GPIO_OType_xx;
    uint32_t GPIO_AF_x;
}GPIO_Init_Parameters;

typedef struct{
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_Pin_x;
    uint8_t value;
}GPIO_Pin_Parameters ;



typedef struct{
    USART_TypeDef *USARTx;
    uint32_t baudrate;
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_Mode_x;
    uint32_t GPIO_PuPd_x;
    uint32_t GPIO_Speed_x;
    uint16_t GPIO_Pin_Source[16];
    uint32_t TX_Pin;
    uint32_t RX_Pin;
    uint32_t GPIO_AF;
    uint8_t DR;
}USART_Parameters;


typedef struct{
    TIM_TypeDef* TIMx;
    uint32_t ARR;
    uint32_t PSC;
    uint32_t ClockDivision;
    uint32_t CounterMode;
    uint32_t Channel;
    uint32_t OCMode;
    uint32_t OutputState;
    uint32_t Pulse;
    uint32_t OCPolarity;

    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin_Source[16];
    uint32_t Output_Pin;
    uint32_t GPIO_AF;
}TIM_Parameters;


typedef struct{
    RCC_TypeDef *RCCx;
    uint32_t RCC_BusPeriph;
    FunctionalState NewState;
}RCC_PeriphClock_Parameters;


void H723_PeriphClockCmd(void* const Parameters);
void H723_GPIO_Config(void* const Parameters);
void H723_GPIO_Pin_Set(void* const Parameters,uint8_t status);
void H723_GPIO_AF_Config(void* const Parameters);
void H723_USART_Init(void* const Parameters);
void H723_TIM_Init(void* const Parameters);


#endif