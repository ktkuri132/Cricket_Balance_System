
#include "f407.h"
#ifdef STM32F407xx


#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>



/// @brief GPIO配置函数（默认速度100，默认推挽输出，调用前请自行使能时钟）
/// @param GPIOx 不必多说
/// @param GPIO_Pin_x 不必多说
/// @param GPIO_Mode_x GPIO模式
/// @param GPIO_PuPd_x 上拉、下拉、浮空
void F407_GPIO_Config(void* const Parameters)
{
    GPIO_Init_Parameters *GPIO_Parameter = (GPIO_Init_Parameters*)Parameters;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Parameter->GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Parameter->GPIO_Mode_x;
    GPIO_InitStructure.GPIO_PuPd = GPIO_Parameter->GPIO_PuPd_x;
    GPIO_InitStructure.GPIO_Speed = GPIO_Parameter->GPIO_Speed_x;
    GPIO_InitStructure.GPIO_OType = GPIO_Parameter->GPIO_OType_xx;
    GPIO_Init(GPIO_Parameter->GPIOx, &GPIO_InitStructure);
}

void F407_GPIO_AF_Config(void* const Parameters){
    
}


void F407_GPIO_Pin_Set(void* const Parameters,uint8_t status){
    GPIO_Pin_Parameters *GPIO_Parameter = (GPIO_Pin_Parameters*)Parameters;
    GPIO_WriteBit(GPIO_Parameter->GPIOx,GPIO_Parameter->GPIO_Pin_x,status);
}

void F407_GPIO_Pin_Get(void* const Parameters){
    
}

uint32_t F407_GetGPIOPeriphClock(void* const Parameters){
    return 0;
}


#endif