
#include <stdint.h>
#include <sysport.h>
#include <Init.h>
#include "bsp/h723/h723.h"
#include "bsp/Serial.h"
#include "stm32h7xx_it.h"
#include <control.h>
SYS_Port *port;

Stde_DataTypeDef *USART2_Data;

extern GraphicsChar_Unit Graphics_Memory[20][120];

void Draw_EVA() {
    // 绘制 "E"
    Wirte_String(2, 2, 1, "######");
    Wirte_String(3, 2, 1, "##    ");
    Wirte_String(4, 2, 1, "##### ");
    Wirte_String(5, 2, 1, "##    ");
    Wirte_String(6, 2, 1, "######");

    // 绘制 "V"
    Wirte_String(2, 10, 1, "##   ##");
    Wirte_String(3, 10, 1, "##   ##");
    Wirte_String(4, 10, 1, " ## ## ");
    Wirte_String(5, 10, 1, "  ###  ");
    Wirte_String(6, 10, 1, "   #   ");

    // 绘制 "A"
    Wirte_String(2, 18, 1, "  ###  ");
    Wirte_String(3, 18, 1, " ## ## ");
    Wirte_String(4, 18, 1, "##   ##");
    Wirte_String(5, 18, 1, "#######");
    Wirte_String(6, 18, 1, "##   ##");
}


int main() {
    port = SysPort_Init();
	port->System_Init();
    syscall.NVIC_Configuration();
    port->SysTick_Init(); 
    Stde_DataTypeDef_Init(USART2_Data);

    
    LED_Init(port);
    USART2_Init(port);
    USART1_Init(port);
    
    PWM_Init(port);
    TIM2_INT_Init(5);	//10KhzÊ±ÖÓ
    Control_Init();
    printf(CLEAR_SCREEN);
    Draw_EVA();
    Wirte_String(7, 1, 3," ----------STM32H723ZGT6------System Data---------------------------");
    Wirte_String(8, 1, 1,"|------------------------------------------------------------------|");
    Wirte_String(9, 1, 1,"|                                                                  |");
    Wirte_String(10, 1, 1,"|                                                                  |");
    Wirte_String(11, 1, 1,"|                                                                  |");
    Wirte_String(12, 1, 1,"|                                                                  |");
    Wirte_String(13, 1, 1,"|                                                                  |");
    Wirte_String(14, 1, 1,"|                                                                  |");
    Wirte_String(15, 1, 1,"|------------------------------------------------------------------|");
    refresh_Partscreen(0, 1, 1); // 刷新屏幕
    while (1) {
        
        Wirte_String(9, 2, 2, "OpenMV:%d", OpenMVData_Y); // 显示数字
        Wirte_String(10, 2, 2, "SysRunTime:%d", port->SysRunTime); // 显示数字
        refresh_Partscreen(0, 1, 1); // 刷新屏幕
    }
}


void SysTick_Handler(){
    port->SysRunTime++;
}

void TIM2_IRQHandler(void)
{ 		  
	if(TIM2->SR & TIM_SR_UIF)
	{
        Control();
	}				   
	TIM2->SR&=~TIM_SR_UIF;	    
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

