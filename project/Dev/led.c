#include <sysport.h>

#include "stm32h7xx.h"
#include "syscall.h"


void LED_Init(SYS_Port *port) {
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN;
    // GPIO_Init_Parameters gpiog_init;
    // gpiog_init.GPIOx         = GPIOG;
    // gpiog_init.GPIO_Pin_x    = 7;
    // gpiog_init.GPIO_Mode_x   = 1;
    // gpiog_init.GPIO_OType_xx = 0;
    // gpiog_init.GPIO_PuPd_x   = 0;
    // gpiog_init.GPIO_Speed_x  = 0;
    // gpio.bsp_gpio_pin_set(&gpiog_init, 1);
    // gpio.bsp_gpio_init(&gpiog_init);
    GPIO_Init_Parameters gpiog_init;
    gpiog_init.GPIOx         = GPIOG;
    gpiog_init.GPIO_Pin_Source[Pin7] = ENABLE;
    gpiog_init.GPIO_Mode_x   = 1;
    gpiog_init.GPIO_OType_xx = 0;
    gpiog_init.GPIO_PuPd_x   = 0;
    gpiog_init.GPIO_Speed_x  = 0;
    gpio.bsp_gpio_pin_set(&gpiog_init, 1);
    gpio.bsp_gpio_init(&gpiog_init);

}

void LED_ON(SYS_Port *port) {
    GPIO_Pin_Parameters gpiog_pin_7;
    gpiog_pin_7.GPIOx      = GPIOG;
    gpiog_pin_7.GPIO_Pin_x = 7;
    gpio.bsp_gpio_pin_set(&gpiog_pin_7, 0);
}

void LED_OFF(SYS_Port *port) {
    GPIO_Pin_Parameters gpiog_pin_7;
    gpiog_pin_7.GPIOx      = GPIOG;
    gpiog_pin_7.GPIO_Pin_x = 7;
    gpiog_pin_7.value      = 0;
    gpio.bsp_gpio_pin_set(&gpiog_pin_7, 1);
}


