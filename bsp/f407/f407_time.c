
#include "f407.h"
#ifdef STM32F407xx  // 选择对应的芯片

#include <stdint.h>
#include <stm32f4xx.h>



void F407_TIM_Init(void* const Parameters) {
    TIM_Parameters* TIM_Parameter = (TIM_Parameters*)Parameters;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(TIM_Parameter->RCC_Bus1Periph, ENABLE);
    RCC_AHB1PeriphClockCmd(TIM_Parameter->RCC_Bus2Periph, ENABLE);

    GPIO_InitStructure.GPIO_Pin = TIM_Parameter->GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(TIM_Parameter->GPIOx, &GPIO_InitStructure);

    GPIO_PinAFConfig(TIM_Parameter->GPIOx, TIM_Parameter->GPIO_Pin_Source_1, TIM_Parameter->GPIO_AF);
    GPIO_PinAFConfig(TIM_Parameter->GPIOx, TIM_Parameter->GPIO_Pin_Source_2, TIM_Parameter->GPIO_AF);

    TIM_TimeBaseStructure.TIM_Period = TIM_Parameter->TIM_Period - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = TIM_Parameter->TIM_Prescaler - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_Parameter->TIM_ClockDivision;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_Parameter->TIM_CounterMode;
    TIM_TimeBaseInit(TIM_Parameter->TIMx, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_Parameter->TIM_OCMode;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = TIM_Parameter->TIM_Pulse;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM_Parameter->TIMx, &TIM_OCInitStructure);
    TIM_OC2Init(TIM_Parameter->TIMx, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM_Parameter->TIMx, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM_Parameter->TIMx, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM_Parameter->TIMx, ENABLE);

    TIM_CtrlPWMOutputs(TIM_Parameter->TIMx, ENABLE);

    TIM_Cmd(TIM_Parameter->TIMx, ENABLE);
}

#endif