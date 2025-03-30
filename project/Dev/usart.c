#include <sysport.h>
#include "h723/h723.h"


void USART1_Init(SYS_Port *port){
    

    // GPIO_Init_Parameters gpio_init;
    // gpio_init.GPIOx = GPIOA;
    // gpio_init.GPIO_Pin_x = PIN9|PIN10;
    // gpio_init.GPIO_Mode_x = 2; // alternate function mode
    // gpio_init.GPIO_PuPd_x = 0; // no pull-up or pull-down resistor enabled
    // gpio_init.GPIO_Speed_x = 3; // high speed
    // gpio_init.GPIO_AF_x = 7; // AF7
    // gpio_init.GPIO_Pin_Source_x = 9;
    // gpio.bsp_gpio_af_set(&gpio_init);
    // gpio_init.GPIO_Pin_Source_x = 10;
    // gpio.bsp_gpio_af_set(&gpio_init);
    // gpio.bsp_gpio_init(&gpio_init);
    // GPIO_Set(GPIOA, PIN9|PIN10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_FAST, GPIO_PUPD_PU);
    // GPIO_AF_Set(GPIOA,9,7);	//PA9,AF7
	// GPIO_AF_Set(GPIOA,10,7);//PA10,AF7 
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
    
    // GPIO_Init_Parameters gpio_init;
    // gpio_init.GPIOx = GPIOA;
    // gpio_init.GPIO_Pin_x = PIN2|PIN3;
    // gpio_init.GPIO_Mode_x = 2; // alternate function mode
    // gpio_init.GPIO_PuPd_x = 0; // no pull-up or pull-down resistor enabled
    // gpio_init.GPIO_Speed_x = 3; // high speed
    // gpio_init.GPIO_AF_x = 7; // AF7
    // gpio_init.GPIO_Pin_Source_x = 2; // set pin to PA2
    // gpio.bsp_gpio_af_set(&gpio_init);
    // gpio_init.GPIO_Pin_Source_x = 3; // set pin to PA3
    // gpio.bsp_gpio_af_set(&gpio_init);
    // gpio.bsp_gpio_init(&gpio_init);
    // GPIO_Set(GPIOD, PIN5|PIN6, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_FAST, GPIO_PUPD_PU);
    // GPIO_AF_Set(GPIOD,5,7);	//PA2,AF7
    // GPIO_AF_Set(GPIOD,6,7);//PA3,AF7
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
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