#ifndef __INIT__H
#define __INIT__H

#include <sysport.h>

void LED_Init(SYS_Port *port);
void LED_ON(SYS_Port *port);
void LED_OFF(SYS_Port *port);
void USART1_Init(SYS_Port *port);
void PWM_Init(SYS_Port *port);

#endif