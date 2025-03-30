#include <stdint.h>
#include <sysport.h>
#include "stm32h7xx.h"
#include <stdlib.h>

void PWM_Init(SYS_Port *port){
    TIM_Parameters tim3_init;
    
    tim3_init.TIMx = TIM3;
    tim3_init.GPIOx = GPIOB;
    tim3_init.GPIO_Pin_Source[PIN0] = ENABLE;
    tim3_init.GPIO_Pin_Source[PIN1] = ENABLE;
    tim3_init.GPIO_AF = 2;
    tim3_init.RCC_TIMBusPeriph = RCC_APB1LENR_TIM3EN;
    tim3_init.RCC_GPIOBusPeriph = RCC_AHB4ENR_GPIOBEN;
    tim3_init.ARR = 6000-1;
    tim3_init.PSC = 135-1;
    tim3_init.Channel[Channel_4] = ENABLE;
    tim3_init.Channel[Channel_3] = ENABLE;
    tim3_init.OCMode = 1;
    tim.bsp_tim_x_inti(&tim3_init);

}

void TIM2_INT_Init(uint8_t ms){
    RCC->APB1LENR|=RCC_APB1LENR_TIM2EN;				 
	while((RCC->APB1LENR&(1<<1))==0);	
 	TIM2->ARR=100 * ms - 1;  				
	TIM2->PSC=2700-1;  				
	TIM2->DIER|=TIM_DIER_UIE;  					  
	TIM2->CR1|=TIM_CR1_CEN;				
}

