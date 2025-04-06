#include <stdint.h>
#include <sysport.h>
#include <Serial.h>
#include "stm32h7xx_it.h"
extern SYS_Port *port;

typedef struct Thd{
    struct Thd *prev;  // 上一个线程
    uint8_t *name;  // 线程名称
    void (*func)(void* const Parameters);  // 函数指针
    uint8_t RunStae;  // 运行状态
    void *arg;  // 函数参数
    uint8_t node;  // 节点编号
    struct Thd *next;  // 下一个线程
} Thread;

Thread *Thread_Head = NULL;  // 线程链表头指针

static void sleep(uint32_t ms) {


}

static void app_main(){
    while(1){

    }
}

static void app_thread_1(){
    while(1){
        
    }
}

static void app_thread_2(){
    while(1){
        
    }
}

static Thread *app_thread_regist(void (*func)(void*),void *arg){
    

}




void test() {
    printf(CURSOR_SHOW);
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN;  // 使能 GPIOG 时钟
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN;  // 使能 GPIOF 时钟
    RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;  // 使能 SPI5 时钟
    GPIO_Init_Parameters spi_gpio_init;
    spi_gpio_init.GPIOx = GPIOG;
    spi_gpio_init.GPIO_Pin_Source[Pin6] = ENABLE;  
    spi_gpio_init.GPIO_Mode_x = GPIO_MODE_OUT;
    gpio.bsp_gpio_init(&spi_gpio_init);
    spi_gpio_init.GPIOx = GPIOF;
    spi_gpio_init.GPIO_Pin_Source[Pin6] = ENABLE;
    spi_gpio_init.GPIO_Pin_Source[Pin7] = ENABLE;
    spi_gpio_init.GPIO_Pin_Source[Pin8] = ENABLE;
    spi_gpio_init.GPIO_Pin_Source[Pin9] = ENABLE;
    spi_gpio_init.GPIO_Mode_x = GPIO_MODE_AF;
    spi_gpio_init.GPIO_AF_x = 5;
    spi_gpio_init.GPIO_OType_xx = GPIO_OTYPE_PP;
    spi_gpio_init.GPIO_Speed_x = GPIO_SPEED_HIGH;
    spi_gpio_init.GPIO_PuPd_x = GPIO_PUPD_NONE;
    gpio.bsp_gpio_af_set(&spi_gpio_init);
    gpio.bsp_gpio_init(&spi_gpio_init);


    
    // gpio.bsp_gpio_init();
    // SPI1->CR1 |= 


    while (1) {
        
    }
}






