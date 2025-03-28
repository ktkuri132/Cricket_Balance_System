#include <sysport.h>


void NVIC_Init(void){
    u32 temp,temp1;	  
	temp1=(~4)&0x07;
	temp1<<=8;
	temp=SCB->AIRCR;  
	temp&=0X0000F8FF; 
	temp|=0X05FA0000; 
	temp|=temp1;	   
	SCB->AIRCR=temp; 

    u32 temp_2;	  
	temp_2=0<<0;	  
	temp_2|=0&(0x0f>>4);
	temp_2&=0xf;								
	NVIC->ISER[TIM2_IRQn/32]|=1<<TIM2_IRQn%32;
	NVIC->IP[TIM2_IRQn]|=temp_2<<4;	
    temp_2 = 0;

    temp_2=1<<0;
    temp_2|=0&(0x0f>>4);
    temp_2&=0xf;
    NVIC->ISER[USART1_IRQn/32]|=1<<USART1_IRQn%32;
    NVIC->IP[USART1_IRQn]|=temp_2<<4;
    temp_2 = 0;
    
    temp_2=2<<0;
    temp_2|=0&(0x0f>>4);
    temp_2&=0xf;									//设置中断优先级分组为2：2位抢占优先级，2位响应优先级
    NVIC->ISER[USART2_IRQn/32]|=1<<USART2_IRQn%32;	//使能USART2中断通道
    NVIC->IP[USART2_IRQn]|=temp_2<<4;				//设置抢占优先级
    temp_2 = 0;
    
}