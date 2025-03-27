#include "f407.h"

#ifdef STM32F407xx

#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>





void F407_PeriphClockCmd(void* const Parameters){
    if(Parameters == NULL){
        return;
    }
    RCC_PeriphClock_Parameters *RCC_Parameter = (RCC_PeriphClock_Parameters*)Parameters;
    if(RCC_Parameter->NewState == ENABLE){
        RCC_AHB1PeriphClockCmd(RCC_Parameter->RCC_BusPeriph, ENABLE);
    }else{
        RCC_AHB1PeriphClockCmd(RCC_Parameter->RCC_BusPeriph, DISABLE);
    }
}

#endif