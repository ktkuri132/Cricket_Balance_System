#include <Init.h>
#include <control.h>
#include <pid.h>
#include <stdint.h>

PID pid_x;


/**
    * @brief PID控制器初始化函数
    * @param pid 指向PID结构体的指针
    * @param Kp 比例系数
    * @param Ki 积分系数
    * @param Kd 微分系数
    * @param max_output 最大输出值
*/
void Control_Init() {
    
    PID_TypeStructInit(&pid_x, 300, 0, 0, 120);
    pid_x.PID_Update = PID_forX;
       
}

void Control() {
    pid_x.PID_Update(&pid_x);
    
    Motor_x = pid_x.output + 2000;
}