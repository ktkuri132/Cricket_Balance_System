#ifndef __INIT__H
#define __INIT__H

#include <sysport.h>

void test();

void LED_Init(SYS_Port *port);
void LED_ON(SYS_Port *port);
void LED_OFF(SYS_Port *port);
void LED_Flip(SYS_Port *port);
void USART1_Init(SYS_Port *port);
void USART2_Init(SYS_Port *port);
void USART3_Init(SYS_Port *port);
void PWM_Init(SYS_Port *port);
void TIM2_INT_Init(uint8_t ms);

void Sys_cmd_Init();
void led(void *const arg);

void DisPlay_SystemData(int argc,void *argv[]);
void __led(int argc,void * argv[]);
void __pid(int argc,void *argv[]);
void __refe(int argc,void *argv[]);
void __mode(int argc, void *argv[]);
void __Site(int argc, void *argv[]);
#endif