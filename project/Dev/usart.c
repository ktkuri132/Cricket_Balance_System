#include <sysport.h>


void USART1_Init(SYS_Port *port){
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART_Parameters usart_init;
    usart_init.USARTx   = USART1;
    usart_init.baudrate = 115200;
    usart_init.GPIOx    = GPIOA;
    usart_init.GPIO_Mode_x = 2;
    usart_init.GPIO_PuPd_x = 0;
    usart_init.GPIO_Speed_x = 3;
    usart_init.GPIO_Pin_Source[AF_0] = 9;
    usart_init.GPIO_Pin_Source[AF_1] = 10;
    usart_init.GPIO_AF = 7;

    usart.bsp_usart_x_inti(&usart_init);
}

void USART2_Init(SYS_Port *port){
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    RCC->APB1LENR |= RCC_APB1LENR_USART2EN;
    USART_Parameters usart_init;
    usart_init.USARTx   = USART2;
    usart_init.baudrate = 115200;
    usart_init.GPIOx    = GPIOA;
    usart_init.GPIO_Mode_x = 2;
    usart_init.GPIO_PuPd_x = 0;
    usart_init.GPIO_Speed_x = 3;
    usart_init.GPIO_Pin_Source[AF_0] = 2;
    usart_init.GPIO_Pin_Source[AF_1] = 3;
    usart_init.GPIO_AF = 7;
    usart.bsp_usart_x_inti(&usart_init);
}