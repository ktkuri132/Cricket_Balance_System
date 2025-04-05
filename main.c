
#include <stdint.h>
#include <sysport.h>
#include <Init.h>
#include "bsp/h723/h723.h"
#include "bsp/Serial.h"
#include "stm32h7xx_it.h"
#include <control.h>
SYS_Port *port;

Stde_DataTypeDef *USART2_Data;
Bie_ShellTypeDef* USART1_Data;
extern GraphicsChar_Unit Graphics_Memory[20][120];


EnvVar  MyEnv[] = {
    {
        .name = "led",
        .callback = led,
    },
    {
        .name = "show",
        .callback = DisPlay_SystemData,
    },
    {
        .name = "kp", 
        .callback = __kp,
    },
    {
        .name = "kd",
        .callback = __kd,
    },
    {
        .name = "ki",
        .callback = __ki,
    },
    {
        .name = NULL,
        .callback = NULL
    }
};

int main() {

    port = SysPort_Init();
	port->System_Init();
    syscall.NVIC_Configuration();
    port->SysTick_Init(); 
    Sys_cmd_Init();
    Stde_DataTypeDef_Init(USART2_Data);
    LED_Init(port);
    USART1_Init(port);
    USART2_Init(port);
    PWM_Init(port);
    Motor_x = 5000;
    Motor_y = 5000;
    // Motor_x = 2200;
    // Motor_y = 1900;
    Control_Init();
    TIM2_INT_Init(5);	//10KhzÊ±ÖÓ
    printf(CURSOR_SHOW);
    while (1) {
        if(port->syspfunc != NULL) {
            port->syspfunc(port->Parameters);  // 执行系统函数
            port->syspfunc = NULL;
            printf(CURSOR_SHOW);
        }
    }
}



void SysTick_Handler(){
    static uint64_t TempRunTime = 0;
    TempRunTime++;
    if(TempRunTime >= 10) { 
        TempRunTime = 0;
        srt.SysRunTimeBeat++;   // 10ms为一个系统节拍
    }
    if(srt.SysRunTimeBeat >= 100) { 
        srt.SysRunTimeBeat = 0;
        srt.SysRunTimeSec++;
    }
    if(srt.SysRunTimeSec == 60){
        srt.SysRunTimeSec = 0;
        srt.SysRunTimeMin++;
    }
    srt.SysRunTime++;
}


void TIM2_IRQHandler(void)
{ 		  
	if(TIM2->SR & TIM_SR_UIF)
	{
        // Control();
	}				   
	TIM2->SR&=~TIM_SR_UIF;	    
}

void USART1_IRQHandler(void)
{
    if(USART1->ISR & USART_ISR_RXNE_RXFNE){
        BIE_UART(USART1,USART1_Data,MyEnv);
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

