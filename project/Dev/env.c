#include <pid.h>
#include <stdint.h>
#include <string.h>
#include <sysport.h>
#include <shell.h>
#include "Serial.h"


extern Bie_ShellTypeDef *USART1_Data;

extern SYS_Port *port;
extern Cmd_PointerTypeDef Cmd;
extern PID pid_x;
extern PID pid_y;
extern PID pid_xs;
extern PID pid_ys;

void __ls(int argc, void *argv[]) {
    if (strcmp(argv[1], "pid") == 0) {
        printf("xkp: %d xkd: %d xki: %d\n", pid_x.Kp, pid_x.Kd, pid_x.Ki);
        printf("ykp: %d ykd: %d yki: %d\n", pid_y.Kp, pid_y.Kd, pid_y.Ki);
        printf("xskp: %d xskd: %d xski: %d\n", pid_xs.Kp, pid_xs.Kd, pid_xs.Ki);
        printf("yskp: %d yskd: %d yski: %d\n", pid_ys.Kp, pid_ys.Kd, pid_ys.Ki);
    }
}

void __clear(int argc, void *argv[]) {
    printf(CLEAR_SCREEN);
    printf(CURSOR_HOME);
}

void __reset(int argc, void *argv[]) {
    NVIC_SystemReset();  // 重启系统
}

void __pid(int argc,void *argv[]){
    if (argv == NULL) {
        printf("Invalid argument for pid command\n");
        return;
    }
    if(argc < 1) {
        printf("Invalid argument for pid command\n");
        return;
    } else if(argc >3){
        printf("Too mach argument to pid command\n");
        return;
    }
    char *endptr;
    int32_t arg_value = strtol(argv[3], &endptr, 10);  // 将字符串转换为整数

    if(!strcmp(argv[1],"x")){
        if(strcmp(argv[2], "kp") == 0) {
            pid_x.Kp = arg_value;  // 设置PID参数
        } else if(strcmp(argv[1], "kd") == 0) {
            pid_x.Kd = arg_value;
        } else if(strcmp(argv[1], "ki") == 0) {
            pid_x.Ki = arg_value;
        } else {
            printf("Invalid argument for pid command\n");
        }
    } else if(!strcmp(argv[1], "y")){
        if(strcmp(argv[2], "kp") == 0) {
            pid_y.Kp = arg_value;  // 设置PID参数
        } else if(strcmp(argv[1], "kd") == 0) {
            pid_y.Kd = arg_value;
        } else if(strcmp(argv[1], "ki") == 0) {
            pid_y.Ki = arg_value;
        } else {
            printf("Invalid argument for pid command\n");
        }
    } else if(!strcmp(argv[1], "xs")){
        if(strcmp(argv[2], "kp") == 0) {
            pid_xs.Kp = arg_value;  // 设置PID参数
        } else if(strcmp(argv[1], "kd") == 0) {
            pid_xs.Kd = arg_value;
        } else if(strcmp(argv[1], "ki") == 0) {
            pid_xs.Ki = arg_value;
        } else {
            printf("Invalid argument for pid command\n");
        }
    } else if(!strcmp(argv[1], "ys")){
        if(strcmp(argv[2], "kp") == 0) {
            pid_ys.Kp = arg_value;  // 设置PID参数
        } else if(strcmp(argv[1], "kd") == 0) {
            pid_ys.Kd = arg_value;
        } else if(strcmp(argv[1], "ki") == 0) {
            pid_ys.Ki = arg_value;
        } else {
            printf("Invalid argument for pid command\n");
        }
    }
    
    printf("Setting PID parameters: %d\n", arg_value);
}



void Sys_cmd_Init() {
    Cmd.ls       = __ls;
    Cmd.reset    = __reset;
    Cmd.poweroff = NULL;
    Cmd.clear    = __clear;
}

void DisPlay_SystemData(int argc,void *argv[]) {
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
    Wirte_String(7, 1, 3, " ----------STM32H723ZGT6------System Data---------------------------");
    Wirte_String(8, 1, 1, "|------------------------------------------------------------------|");
    Wirte_String(9, 1, 1, "|                                                                  |");
    Wirte_String(10, 1, 1, "|                                                                  |");
    Wirte_String(11, 1, 1, "|                                                                  |");
    Wirte_String(12, 1, 1, "|                                                                  |");
    Wirte_String(13, 1, 1, "|                                                                  |");
    Wirte_String(14, 1, 1, "|                                                                  |");
    Wirte_String(15, 1, 1, "|------------------------------------------------------------------|");

    Wirte_String(9, 2, 2, "Time:    Conut:      Sec:    Min:");  // 显示数字
    Wirte_String(10, 2, 2, "OpenMV_y:     PidOut:");             // 显示数字
    refresh_Partscreen(0, 1, 1);                                 // 刷新屏幕
    while (!USART1_Data->RunStae) {
        Wirte_String(9, 27, 2, "%d", srt.SysRunTimeSec);  // 显示秒
        Wirte_String(9, 35, 2, "%d", srt.SysRunTimeMin);  // 显示分钟
        Wirte_String(10, 11, 2, "%d", OpenMVData_Y);      // 显示数字
        Wirte_String(10, 23, 2, "%d", Motor_x);           // 显示数字
        refresh_Partscreen(0, 1, 1);                      // 刷新屏幕
    }
    USART1_Data->RunStae = 0;  // 退出显示
    printf(CLEAR_SCREEN);
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
    USART1_Data->RunStae = 0;  // 退出翻转
    printf(CLEAR_SCREEN);
}

void __led(int argc,void * argv[]) {
    // 处理LED命令
    if (strcmp(argv[1], "on") == 0) {
        LED_ON(port);  // 打开LED
    } else if (strcmp(argv[1], "off") == 0) {
        LED_OFF(port);  // 关闭LED
    } else if (strcmp(argv[1], "flip") == 0) {
        LED_Flip(port);  // 翻转LED状态
    } else {
        printf("Invalid argument for led command\n");
    }
}
