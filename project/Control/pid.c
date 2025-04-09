#include "Project.h"
#include "pid.h"
#include <control.h>
#include <stdint.h>

/*
 * 这里为什么要提供一个通用，还建议开发者提供专用的PID算法，通用的只有单极PID
 * 但是专用算法的可以随意发挥，并机，串级，这里提供了两个PID算法的接口，可供开发者提供最多两级的算法支持
 * 如有更多需求，可在结构体内添加，初始化函数中加入接口
 */



void PID_TypeStructInit(PID *pid,int32_t kp,int32_t kd,float ki,
    int32_t target,int32_t max_output,int32_t min_output,int32_t max_integral)
{
    pid->max_output = max_output;
    pid->min_output = min_output;
    pid->max_integral = max_integral;
    // pid->integral = 120;
    pid->target = target;
    pid->Kp = kp;
    pid->Kd = kd;
    pid->Ki = ki;
}

void PID_for_speed(PID *pid,int32_t speed)
{
    pid->current = speed;

    pid->error = 0-pid->current;
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
    else if (pid->output < -pid->min_output)
    {
        pid->output = -pid->min_output;
    }
    pid->last_error = pid->error;
}

/// @brief PID 对于直线的专用控制函数
void PID_forX(PID *pid,PID *pid2)
{
    static int32_t old_output = 0;
    pid->current = OpenMVData_X;

    pid->error = pid->target-pid->current;
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
/******************加入对微分量的低通滤波************************************* */
    int32_t derivative = pid->Kd * pid->derivative;
    static int32_t old_derivative = 0;
    // 这里是为了防止抖动，使用了一个低通滤波器,防止伤害脆弱的舵机
    derivative = old_derivative*0.9 + derivative*0.1;

    pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + derivative;

    old_derivative = derivative;
/************************************************************ */
    // pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + pid->Kd * pid->derivative;
    // 输出限幅
    if (pid->output > pid->max_output)
    {
        pid->output = pid->max_output;
    }
    else if (pid->output < -pid->min_output)
    {
        pid->output = -pid->min_output;
    }
/****************加入对整体输出的低通滤波********************* */
    // // 这里是为了防止输出抖动，使用了一个低通滤波器,防止伤害脆弱的舵机
    // pid->output = old_output*0.8 + pid->output*0.2;

    // old_output = pid->output;
/******************************************* */
    PID_for_speed(pid2,Get_Blobs_Speed(X,pid->current));
    pid->output += pid2->output;

    pid->last_error = pid->error;
}

/// @brief PID 对于直线的专用控制函数
void PID_forY(PID *pid,PID *pid2)
{

    static int32_t old_output = 0;

    pid->current = OpenMVData_Y;

    pid->error = pid->target-pid->current;
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
/******************加入对微分量的低通滤波************************************* */
    int32_t derivative = pid->Kd * pid->derivative;
    static int32_t old_derivative = 0;
    // 这里是为了防止抖动，使用了一个低通滤波器,防止伤害脆弱的舵机
    derivative = old_derivative*0.9 + derivative*0.1;

    pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + derivative;

    old_derivative = derivative;
/************************************************************ */
    // pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + pid->Kd * pid->derivative;
    // 输出限幅
    if (pid->output > pid->max_output)
    {
        pid->output = pid->max_output;
    }
    else if (pid->output < -pid->min_output)
    {
        pid->output = -pid->min_output;
    }

/****************加入对整体输出的低通滤波********************* */
    // // 这里是为了防止输出抖动，使用了一个低通滤波器,防止伤害脆弱的舵机
    // pid->output = old_output*0.8 + pid->output*0.2;

    // old_output = pid->output;
/******************************************* */
    PID_for_speed(pid2,Get_Blobs_Speed(Y,pid->current));
    pid->output += pid2->output;

    pid->last_error = pid->error;
}


