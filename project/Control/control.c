#include <Init.h>
#include <control.h>
#include <pid.h>
#include <stdint.h>

PID pid_x;
PID pid_y;

PID pid_xs;
PID pid_ys;

int32_t PWM_Refe[6] = {
    4500, 1300, 3300, 4300, 1000, 2850
};

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
    PID_TypeStructInit(&pid_x, 7, 300, 0, 155, 
        PWM_Refe[XMAX_PWM] - PWM_Refe[XMid_PWM], PWM_Refe[XMid_PWM] - PWM_Refe[XMIN_PWM]);
    PID_TypeStructInit(&pid_y, 9, 300, 0, 118, 
        PWM_Refe[YMAX_PWM] - PWM_Refe[YMid_PWM], PWM_Refe[YMid_PWM] - PWM_Refe[YMIN_PWM]);
    /* 速度环  */
    PID_TypeStructInit(&pid_xs, 3000, -2000, 0, 0, 
        PWM_Refe[XMAX_PWM] - PWM_Refe[XMid_PWM], PWM_Refe[XMid_PWM] - PWM_Refe[XMIN_PWM]);
    PID_TypeStructInit(&pid_ys, -3000, 0, 0, 0,
        PWM_Refe[YMAX_PWM] - PWM_Refe[YMid_PWM], PWM_Refe[YMid_PWM] - PWM_Refe[YMIN_PWM]);
    /* 注册最终pid计算输出函数(最终输出在位置环pid计算里)  */
    pid_x.PID_Update = PID_forX;
    pid_y.PID_Update = PID_forY;
}

void Control() {
    pid_x.PID_Update(&pid_x,&pid_xs);
    pid_y.PID_Update(&pid_y,&pid_ys);
    Motor_x = pid_x.output + PWM_Refe[XMid_PWM];
    Motor_y = pid_y.output + PWM_Refe[YMid_PWM];
}