#ifndef __PID__H
#define __PID__H


#include <Project.h>
#include "pid.h"

#define MAX_PWM 4000
#define MIN_PWM 1000

typedef struct PID_TypeDef
{
    /* function  */
    void (*PID_Update)(struct PID_TypeDef *pid);
    // void (*PID_Update2)(struct PID_TypeDef *pid);
    // void (*PID_Update3)(struct PID_TypeDef *pid);
    /* data */
    int32_t error;
    int32_t last_error;
    int32_t integral;
    int32_t derivative;

    int32_t target;
    int32_t current;
    // 积分限幅
    int32_t max_integral;
    int32_t output;
    // 输出限幅
    int32_t max_output;
    int32_t min_output;
    int32_t Kp;
    int32_t Ki;
    int32_t Kd;
    
}PID;


void PID_TypeStructInit(PID *pid,int16_t kp,int16_t kd,int16_t ki,int16_t target);
void PID_forX(PID *pid);


#endif