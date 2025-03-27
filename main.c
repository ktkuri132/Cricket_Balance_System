
#include <stdint.h>
#include <sysport.h>
#include <Init.h>
#include "bsp/h723/h723.h"

SYS_Port *port;

typedef  uint32_t u32;
typedef  uint16_t u16;
typedef  uint8_t u8;
typedef volatile uint32_t  vu32;


int main() {
    port = SysPort_Init();
	port->System_Init();
    RCC->AHB4ENR |= 1<<1;
    RCC->APB1LENR |= 1<<1;

    GPIO_Init_Parameters gpioc_tim3_init;
    gpioc_tim3_init.GPIOx = GPIOB;
    gpioc_tim3_init.GPIO_Pin_x = 1;
    gpioc_tim3_init.GPIO_Mode_x = 2;
    gpioc_tim3_init.GPIO_AF_x = 2;
    gpioc_tim3_init.GPIO_PuPd_x = 1;
    gpioc_tim3_init.GPIO_Speed_x = 2;
    gpio.bsp_gpio_af_set(&gpioc_tim3_init);
    gpio.bsp_gpio_init(&gpioc_tim3_init);
    
    TIM3->ARR=9000-1;			
	TIM3->PSC=30-1;			 
	TIM3->CCMR2|=TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2;  		 
	TIM3->CCMR2|=TIM_CCMR2_OC4FE; 		   
	TIM3->CCER|=TIM_CCER_CC4E;   	
	TIM3->CR1|=TIM_CR1_ARPE|TIM_CR1_CEN;   	
    
    TIM3->CCR4=4500;  
    LED_Init(port);
    USART1_Init(port);
    while (1) {
        uint32_t sysclk = HAL_RCC_GetSysClockFreq();
        uint32_t hclk = HAL_RCC_GetHCLKFreq();
        uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();
        uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
        printf("System Clock Frequency: %lu Hz\n", sysclk);
        printf("HCLK Frequency: %lu Hz\n", hclk);
        printf("PCLK1 Frequency: %lu Hz\n", pclk1);
        printf("PCLK2 Frequency: %lu Hz\n", pclk2);
        LED_ON(port);
        syscall.bsp_systick_delay_ms(1000);
        LED_OFF(port);
        syscall.bsp_systick_delay_ms(1000);
    }
}
