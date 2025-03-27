#ifndef __F407_H
#define __F407_H

#ifdef STM32F407xx

#include <stdint.h>
#include <stm32f4xx.h>
#include <stddef.h>

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_Pin_x;
    uint32_t GPIO_Mode_x;
    uint32_t GPIO_PuPd_x;
    uint32_t GPIO_Speed_x;
    uint32_t GPIO_OType_xx;
} GPIO_Init_Parameters;

typedef struct{
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_Pin_x;
    uint8_t value;
}GPIO_Pin_Parameters ;

typedef struct{
    USART_TypeDef *USARTx;
    uint32_t baudrate;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin_Source;
    uint32_t TX_Pin;
    uint32_t RX_Pin;
    uint32_t GPIO_AF;
    uint8_t DR
}USART_Parameters ;


typedef struct{
    TIM_TypeDef* TIMx;
    uint32_t TIM_Period;
    uint32_t TIM_Prescaler;
    uint32_t TIM_ClockDivision;
    uint32_t TIM_CounterMode;
    uint32_t TIM_Channel;
    uint32_t TIM_OCMode;
    uint32_t TIM_OutputState;
    uint32_t TIM_Pulse;
    uint32_t TIM_OCPolarity;

    uint32_t RCC_Bus1Periph;
    uint32_t RCC_Bus2Periph;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin_Source_1;
    uint16_t GPIO_Pin_Source_2;
    uint32_t GPIO_Pin_x;
    uint32_t GPIO_AF;
}TIM_Parameters;


typedef struct{
    uint32_t RCC_BusPeriph;
    FunctionalState NewState;
}RCC_PeriphClock_Parameters;


void F407_PeriphClockCmd(void* const Parameters);
void F407_GPIO_Config(void* const Parameters);
void F407_GPIO_Pin_Set(void* const Parameters,uint8_t status);

void F407_USART_Init(void* const Parameters);
void F407_TIM_Init(void* const Parameters);

#endif

#endif