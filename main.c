
#include <stdint.h>
#include <sysport.h>
#include <Init.h>
#include "bsp/h723/h723.h"
#include "bsp/Serial.h"
#include <control.h>
SYS_Port *port;

Stde_DataTypeDef *USART2_Data;






int main() {
    port = SysPort_Init();
	port->System_Init();

    Stde_DataTypeDef_Init(USART2_Data);

    NVIC_Init();
    LED_Init(port);
    USART2_Init(port);
    USART1_Init(port);
    
    PWM_Init(port);
    // TIM3->CCR3=2000;
    TIM3->CCR4=3500;
    TIM2_INT_Init(5);	//10KhzÊ±ÖÓ
    Control_Init();
    // printf("X: , Y: \n");
    // printf("Motor_x:");
    // printf(CURSOR_HOME);
    // printf(CURSOR_UP(9));
    // printf("hhh");
    while (1) {
        
        
        // 
        // printf(CLEAR_LINE);
        printf("y:%d,Motor_x:%d \n", OpenMVData_Y-120, Motor_x);
        // printf("%d\n", Motor_x);
        
    }
}


void TIM2_IRQHandler(void)
{ 		  
	if(TIM2->SR & TIM_SR_UIF)//Òç³öÖÐ¶Ï
	{
        Control();
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
        STDE_UART(USART2,USART2_Data);
    }
    USART2->ISR|=USART_ICR_ORECF;
}

