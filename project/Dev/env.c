#include <sysport.h>
#include "Serial.h"
#include <pid.h>

extern Bie_ShellTypeDef* USART1_Data;

extern SYS_Port *port;
extern Cmd_PointerTypeDef Cmd;
extern PID pid_x;



void __ls(void *const Parameters) {
    if(strcmp(Parameters,"pid") == 0) {
        printf("kp: %d kd: %d ki: %d\n", pid_x.Kp, pid_x.Kd, pid_x.Ki);
    } 
}


void Sys_cmd_Init()
{
    Cmd.ls = __ls;
    Cmd.reboot = NULL;
    Cmd.poweroff = NULL;
    Cmd.kp = NULL;
    Cmd.clear = NULL;
}


void DisPlay_SystemData(void *const Parameters) {

    printf(CLEAR_SCREEN);
    // 绘制 "E"
    Wirte_String(0, 2, 1, "######");
    Wirte_String(1, 2, 1, "##    ");
    Wirte_String(2, 2, 1, "##### ");
    Wirte_String(3, 2, 1, "##    ");
    Wirte_String(4, 2, 1, "######");

    // 绘制 "V"
    Wirte_String(0, 10, 1, "##   ##");
    Wirte_String(1, 10, 1, "##   ##");
    Wirte_String(2, 10, 1, " ## ## ");
    Wirte_String(3, 10, 1, "  ###  ");
    Wirte_String(4, 10, 1, "   #   ");

    // 绘制 "A"
    Wirte_String(0, 18, 1, "  ###  ");
    Wirte_String(1, 18, 1, " ## ## ");
    Wirte_String(2, 18, 1, "##   ##");
    Wirte_String(3, 18, 1, "#######");
    Wirte_String(4, 18, 1, "##   ##");
    Wirte_String(7, 1, 3," ----------STM32H723ZGT6------System Data---------------------------");
    Wirte_String(8, 1, 1,"|------------------------------------------------------------------|");
    Wirte_String(9, 1, 1,"|                                                                  |");
    Wirte_String(10, 1, 1,"|                                                                  |");
    Wirte_String(11, 1, 1,"|                                                                  |");
    Wirte_String(12, 1, 1,"|                                                                  |");
    Wirte_String(13, 1, 1,"|                                                                  |");
    Wirte_String(14, 1, 1,"|                                                                  |");
    Wirte_String(15, 1, 1,"|------------------------------------------------------------------|");

    Wirte_String(9, 2, 2, "Time:    Conut:      Sec:    Min:"); // 显示数字
    Wirte_String(10, 2, 2, "OpenMV:     PidOut:"); // 显示数字
    refresh_Partscreen(0, 1, 1); // 刷新屏幕
    while(!USART1_Data->RunStae){
        static uint32_t i = 0;
        Wirte_String(9, 17, 2, "%d", i); // 显示秒
        Wirte_String(9, 27, 2, "%d", srt.SysRunTimeSec); // 显示秒
        Wirte_String(9, 35, 2, "%d", srt.SysRunTimeMin); // 显示分钟
        // Wirte_String(10, 9, 2, "%d", OpenMVData_Y); // 显示数字
        // Wirte_String(10, 21, 2, "%d", Motor_x); // 显示数字
        refresh_Partscreen(0, 1, 1); // 刷新屏幕
        i++;
    }
    USART1_Data->RunStae = 0; // 退出显示
    printf(CLEAR_SCREEN);
}


void set_pid_arg(void *const Parameters) {
    int32_t *arg_value = (int32_t *)Parameters;  // 获取参数值
    // 设置PID参数的函数实现
    // 这里可以根据需要进行参数设置
    printf("Setting PID parameters: %d\n", *arg_value);
}


/**
 * @brief  LED翻转函数
 * @note   该函数将LED的状态进行翻转
 * @param  None
 * @retval None
 */
 void LED_Flip(SYS_Port *port) {
    while (!USART1_Data->RunStae) {
        GPIOG->ODR ^= (1 << 7);              // 翻转
        syscall.bsp_systick_delay_ms(1000);  // 延时100ms
    }
    USART1_Data->RunStae = 0; // 退出翻转
    printf(CLEAR_SCREEN);
}


void led(void *const arg) {
    // 处理LED命令
    if (strcmp(arg, "on") == 0) {
        LED_ON(port);  // 打开LED
    } else if (strcmp(arg, "off") == 0) {
        LED_OFF(port);  // 关闭LED
    } else if (strcmp(arg, "flip") == 0) {
        LED_Flip(port);  // 翻转LED状态
    } else {
        printf("Invalid argument for led command\n");
    }
}

