#include <Init.h>
#include <control.h>
#include <pid.h>
#include <stdint.h>
#include "Serial.h"

PID pid_x;
PID pid_y;

PID pid_xs;
PID pid_ys;

/**
 * @brief PID控制器初始化函数
 * @param pid 指向PID结构体的指针
 * @param Kp 比例系数
 * @param Ki 积分系数
 * @param Kd 微分系数
 * @param max_output 最大输出值
 */
void Control_Init() {
    /* 位置环 */
    PID_TypeStructInit(&pid_x, 20, 0, 0, 155, 
        XMAX_PWM - XMid_PWM, XMid_PWM - XMIN_PWM);
    PID_TypeStructInit(&pid_y, 30, 0, 0, 118, 
        YMAX_PWM - YMid_PWM, YMid_PWM - YMIN_PWM);
    /* 速度环  */
    PID_TypeStructInit(&pid_xs, 0, 0, 0, 0, 
        XMAX_PWM - XMid_PWM, XMid_PWM - XMIN_PWM);
    PID_TypeStructInit(&pid_ys, 0, 0, 0, 0,
        YMAX_PWM - YMid_PWM, YMid_PWM - YMIN_PWM);
    /* 注册最终pid计算输出函数(最终输出在位置环pid计算里)  */
    pid_x.PID_Update = PID_forX;
    pid_y.PID_Update = PID_forY;
}

void Control() {
    int32_t tmp = Get_Blobs_Speed(X, OpenMVData_X);
    Wirte_String(11, 2, 0, "sx:%d",tmp);
    // Get_Blobs_Speed(Y, OpenMVData_Y);
    pid_x.PID_Update(&pid_x,&pid_xs);
    pid_y.PID_Update(&pid_y,&pid_ys);
    Motor_x = pid_x.output + XMid_PWM;
    // Motor_y = pid_y.output + YMid_PWM;
}