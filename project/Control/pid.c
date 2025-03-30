#include "Project.h"
#include "pid.h"
#include <control.h>

/*
 * 这里为什么要提供一个通用，还建议开发者提供专用的PID算法，通用的只有单极PID
 * 但是专用算法的可以随意发挥，并机，串级，这里提供了两个PID算法的接口，可供开发者提供最多两级的算法支持
 * 如有更多需求，可在结构体内添加，初始化函数中加入接口
 */


void PID_TypeStructInit(PID *pid,int16_t kp,int16_t kd,int16_t ki,int16_t target)
{
    pid->max_output = 2000;
    pid->min_output = -1000;
    pid->max_integral = 2000;
    pid->integral = 120;
    pid->target = target;
    pid->Kp = kp;
    pid->Kd = kd;
    pid->Ki = ki;
}


/// @brief PID 对于直线的专用控制函数
void PID_forX(PID *pid)
{

    pid->current = OpenMVData_Y;

    pid->error = pid->current-pid->target;
    pid->integral += pid->error;
    // 积分限幅
    if (pid->integral > pid->max_integral)
    {
        pid->integral = pid->max_integral;
    }
    else if (pid->integral < -pid->max_integral)
    {
        pid->integral = -pid->max_integral;
    }

    pid->derivative = pid->error - pid->last_error;

    pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + pid->Kd * pid->derivative;
    // 输出限幅
    if (pid->output > pid->max_output)
    {
        pid->output = pid->max_output;
    }
    else if (pid->output < pid->min_output)
    {
        pid->output = pid->min_output;
    }
    pid->last_error = pid->error;
}


