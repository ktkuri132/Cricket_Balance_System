#include <sysport.h>


// void PWM_Init(SYS_Port *port){
//     TIM_Parameters tim_aram;
//     tim_aram.RCC_Bus1Periph = RCC_APB2Periph_TIM8;
//     tim_aram.RCC_Bus2Periph = RCC_AHB1Periph_GPIOC;
//     tim_aram.TIMx = TIM8;
//     tim_aram.TIM_Period = 60;
//     tim_aram.TIM_Prescaler = 8400;
//     tim_aram.TIM_ClockDivision = TIM_CKD_DIV1;
//     tim_aram.TIM_CounterMode = TIM_CounterMode_Up;
//     tim_aram.TIM_Channel = TIM_Channel_1;
//     tim_aram.TIM_OCMode = TIM_OCMode_PWM1;
//     tim_aram.TIM_OutputState = TIM_OutputState_Enable;
//     tim_aram.TIM_Pulse = 20;
//     tim_aram.TIM_OCPolarity = TIM_OCPolarity_High;

//     tim_aram.GPIOx = GPIOC;
//     tim_aram.GPIO_Pin_x = GPIO_Pin_6|GPIO_Pin_7;
//     tim_aram.GPIO_AF = GPIO_AF_TIM8;
//     tim_aram.GPIO_Pin_Source_1 = GPIO_PinSource6;
//     tim_aram.GPIO_Pin_Source_2 = GPIO_PinSource7;

//     tim.bsp_tim_x_inti(&tim_aram);

// }


void DS3218_Output(SYS_Port *port,uint8_t status){
    
}
