#include "h723.h"
#include <stdint.h>

void H723_TIM_Init(void* const Parameters) {
    TIM_Parameters* TIM_Parameter = (TIM_Parameters*)Parameters;
    RCC->AHB4ENR |= 1<<1;
    RCC->APB1LENR |= 1<<1;

    TIM_Parameter->TIMx->ARR = TIM_Parameter->ARR;  
    TIM_Parameter->TIMx->PSC = TIM_Parameter->PSC;
	if(TIM_Parameter->Channel == 1) {
        TIM_Parameter->TIMx->CCMR2|=TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2;  		 
	    TIM_Parameter->TIMx->CCMR2|=TIM_CCMR2_OC4FE;
	}

	TIM_Parameter->TIMx->CCER|=TIM_CCER_CC4E;   	
	TIM_Parameter->TIMx->CR1|=TIM_CR1_ARPE|TIM_CR1_CEN;   	
}