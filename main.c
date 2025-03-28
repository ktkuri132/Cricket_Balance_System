
#include <stdint.h>
#include <sysport.h>
#include <Init.h>
#include "bsp/h723/h723.h"

SYS_Port *port;



int main() {
    port = SysPort_Init();
	port->System_Init();

    
    NVIC_Init();
    LED_Init(port);
    USART1_Init(port);
    USART2_Init(port);
    PWM_Init(port);
    TIM3->CCR3=1000;
    TIM3->CCR4=1000;
    // TIM2_INT_Init(5);	//10KhzÊ±ÖÓ
    while (1) {
        // uint32_t sysclk = HAL_RCC_GetSysClockFreq();
        // uint32_t hclk = HAL_RCC_GetHCLKFreq();
        // // printf("System Clock Frequency: %lu Hz\n", sysclk);
        // // printf("HCLK Frequency: %lu Hz\n", hclk);
        // LED_ON(port);
        // syscall.bsp_systick_delay_ms(1000);
        // LED_OFF(port);
        // syscall.bsp_systick_delay_ms(1000);
        static uint32_t PWM = 1000;
        for(PWM=1000;PWM<=5000;PWM+=10){
        	TIM3->CCR3=PWM;
            TIM3->CCR4=PWM;
            printf("PWM: %d\n", TIM3->CCR3);
        	syscall.bsp_systick_delay_ms(5);
        }
        for(PWM=5000;PWM>=1000;PWM-=10){
        	TIM3->CCR3=PWM;
            TIM3->CCR4=PWM;
            printf("PWM: %d\n", TIM3->CCR3);
        	syscall.bsp_systick_delay_ms(5);
        }
    }
}


void TIM2_IRQHandler(void)
{ 		  
	if(TIM2->SR & TIM_SR_UIF)//Òç³öÖÐ¶Ï
	{
        
	}				   
	TIM2->SR&=~TIM_SR_UIF;//Çå³ýÖÐ¶Ï±êÖ¾Î» 	    
}


void USART1_IRQHandler(void)
{
    if(USART1->ISR & USART_ISR_RXNE_RXFNE){
        
    }
    USART1->ICR |= USART_ICR_ORECF;
}

void USART2_IRQHandler(void)
{
	if(USART2->ISR & USART_ISR_RXNE_RXFNE){
        
    }
    USART2->ICR |= USART_ICR_ORECF;
}