#include <Init.h>
#include <control.h>
#include <pid.h>
#include <stdint.h>

PID pid_x;



void Control_Init() {
    static uint8_t i = 0;
    if (!i) {
        PID_TypeStructInit(&pid_x, 300, 0, 0, 120);
        pid_x.PID_Update = PID_forX;
        i                = 1;
    } 
}

void Control() {
    pid_x.PID_Update(&pid_x);
    
    Motor_x = pid_x.output + 2000;
}