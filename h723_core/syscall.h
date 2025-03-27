#ifndef __SYSCALL_H
#define __SYSCALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32h7xx.h>

void SystemClock_Config();
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
void NVIC_Configuration(void);

#ifdef __cplusplus
}
#endif

#endif