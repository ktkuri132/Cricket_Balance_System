#include <pid.h>
#include <shell.h>
#include <stdint.h>
#include <string.h>
#include <sysport.h>

#include "Serial.h"

extern Bie_ShellTypeDef *USART1_Data;
extern SYS_Port *port;
extern Cmd_PointerTypeDef Cmd;
extern PID pid_x;
extern PID pid_y;
extern PID pid_xs;
extern PID pid_ys;
extern char *syscmd[20];
extern int32_t PWM_Refe[6];

void __ls(int argc, void *argv[]) {
    if (!strcmp(argv[0], "pid")) {
        printf("xkp: %d xkd: %d xki: %.2f\n", pid_x.Kp, pid_x.Kd, pid_x.Ki);
        printf("ykp: %d ykd: %d yki: %.2f\n", pid_y.Kp, pid_y.Kd, pid_y.Ki);
        printf("xskp: %d xskd: %d xski: %.2f\n", pid_xs.Kp, pid_xs.Kd, pid_xs.Ki);
        printf("yskp: %d yskd: %d yski: %.2f\n", pid_ys.Kp, pid_ys.Kd, pid_ys.Ki);
    } else if (!strcmp(argv[0], "refe")) {
        printf("xmax: %d xmin: %d xmid: %d\n", PWM_Refe[XMAX_PWM], PWM_Refe[XMIN_PWM],
               PWM_Refe[XMid_PWM]);
        printf("ymax: %d ymin: %d ymid: %d\n", PWM_Refe[YMAX_PWM], PWM_Refe[YMIN_PWM],
               PWM_Refe[YMid_PWM]);
    } else if (!strcmp(argv[0], "cmd")) {
        for (int i = 0; syscmd[i] != NULL; i++) {
            printf("- %s\n", syscmd[i]);
        }
    }
}

void __clear(int argc, void *argv[]) {
    printf(CLEAR_SCREEN);
    printf(CURSOR_HOME);
}

void __reset(int argc, void *argv[]) {
    NVIC_SystemReset();  // 重启系统
}

/*
XMid_PWM 变小时,球会偏向x轴外侧,变大时,球会偏向x轴内侧
YMid_PWM 变小时,球会偏向y轴右侧,变大时,球会偏向y轴左侧
*/
/**
 * @brief 处理 refe 命令
 * @note 该命令用于设置PWM参考值
 */
void __refe(int argc, void *argv[]) {
    if (!strcmp(argv[0], "x")) {
        if (argc < 2) {
            printf(FG_RED "Too few arameters for refe x command\n" RESET_ALL);
            return;
        } else if (argc > 3) {
            printf(FG_RED "Too many argument to refe x command\n" RESET_ALL);
            return;
        }
        int32_t arg_value  = strtol(argv[1], NULL, 10);  // 将字符串转换为整数
        PWM_Refe[XMid_PWM] = arg_value;                  // 设置PWM参考值
    } else if (!strcmp(argv[0], "y")) {
        if (argc < 2) {
            printf(FG_RED "Too few arameters for refe y command\n" RESET_ALL);
            return;
        } else if (argc > 3) {
            printf(FG_RED "Too many argument to refe y command\n" RESET_ALL);
            return;
        }
        int32_t arg_value  = strtol(argv[1], NULL, 10);  // 将字符串转换为整数
        PWM_Refe[YMid_PWM] = arg_value;                  // 设置PWM参考值
    } else {
        printf(FG_RED "Invalid argument for refe command\n" RESET_ALL);
    }
}

/**
 * @brief 处理 pid 命令
 * @note 该命令用于设置PID参数
 */
void __pid(int argc, void *argv[]) {
    if (argv == NULL) {
        printf(FG_RED "Invalid argument for pid command:NULL\n" RESET_ALL);
        return;
    }
    if (argc < 1) {
        printf(FG_RED "Too few arameters for pid command\n" RESET_ALL);
        return;
    } else if (argc > 4) {
        printf(FG_RED "Too many argument to pid command\n" RESET_ALL);
        return;
    }
    char *endptr;
    int32_t arg_value = strtol(argv[2], &endptr, 10);  // 将字符串转换为整数
    float arg_value_f = strtof(argv[2], &endptr);  // 将字符串转换为浮点数
    if (!strcmp(argv[0], "x")) {
        if (strcmp(argv[1], "kp") == 0) {
            pid_x.Kp = arg_value;  // 设置PID参数
        } else if (strcmp(argv[1], "kd") == 0) {
            pid_x.Kd = arg_value;
        } else if (strcmp(argv[1], "ki") == 0) {
            pid_x.Ki = arg_value_f;
        } else {
            printf(FG_RED "Invalid argument for pid x command\n" RESET_ALL);
        }
    } else if (!strcmp(argv[0], "y")) {
        if (strcmp(argv[1], "kp") == 0) {
            pid_y.Kp = arg_value;  // 设置PID参数
        } else if (strcmp(argv[1], "kd") == 0) {
            pid_y.Kd = arg_value;
        } else if (strcmp(argv[1], "ki") == 0) {
            pid_y.Ki = arg_value_f;
        } else {
            printf(FG_RED "Invalid argument for pid y command\n" RESET_ALL);
        }
    } else if (!strcmp(argv[0], "xs")) {
        if (strcmp(argv[1], "kp") == 0) {
            pid_xs.Kp = arg_value;  // 设置PID参数
        } else if (strcmp(argv[1], "kd") == 0) {
            pid_xs.Kd = arg_value;
        } else if (strcmp(argv[1], "ki") == 0) {
            pid_xs.Ki = arg_value_f;
        } else {
            printf(FG_RED "Invalid argument for pid xs command\n" RESET_ALL);
        }
    } else if (!strcmp(argv[0], "ys")) {
        if (strcmp(argv[1], "kp") == 0) {
            pid_ys.Kp = arg_value;  // 设置PID参数
        } else if (strcmp(argv[1], "kd") == 0) {
            pid_ys.Kd = arg_value;
        } else if (strcmp(argv[1], "ki") == 0) {
            pid_ys.Ki = arg_value_f;
        } else {
            printf(FG_RED "Invalid argument for pid ys command\n" RESET_ALL);
        }
    } else if(!strcmp(argv[0],"xy")){
        if (strcmp(argv[1], "kp") == 0) {
            pid_x.Kp = arg_value;  // 设置PID参数
            pid_y.Kp = arg_value;
        } else if (strcmp(argv[1], "kd") == 0) {
            pid_x.Kd = arg_value;
            pid_y.Kd = arg_value;
        } else if (strcmp(argv[1], "ki") == 0) {
            pid_x.Ki = arg_value_f;
            pid_y.Ki = arg_value_f;
        } else if(strcmp(argv[1], "del") == 0){
            pid_x.Kp = 0;
            pid_y.Kp = 0;
            pid_x.Kd = 0;
            pid_y.Kd = 0;
            pid_x.Ki = 0;
            pid_y.Ki = 0;
        } else {
            printf(FG_RED "Invalid argument for pid xy command\n" RESET_ALL);
        }
    } else if(!strcmp(argv[0],"xys")){
        if (strcmp(argv[1], "kp") == 0) {
            pid_xs.Kp = arg_value;  // 设置PID参数
            pid_ys.Kp = arg_value;
        } else if (strcmp(argv[1], "kd") == 0) {
            pid_xs.Kd = arg_value;
            pid_ys.Kd = arg_value;
        } else if (strcmp(argv[1], "ki") == 0) {
            pid_xs.Ki = arg_value_f;
            pid_ys.Ki = arg_value_f;
        } else if(!strcmp(argv[1], "del")){
            pid_xs.Kp = 0;
            pid_ys.Kp = 0;
            pid_xs.Kd = 0;
            pid_ys.Kd = 0;
            pid_xs.Ki = 0;
            pid_ys.Ki = 0;
        }else {
            printf(FG_RED "Invalid argument for pid xys command\n" RESET_ALL);
        }
    }
    printf(FG_GREEN "Setting %s %s parameters: %.2f\n" RESET_ALL, argv[0], argv[1], arg_value_f);
}

void __test(int argc, void *argv[]) {
    printf("cmd:%s argc:%d argv1:%s argv2:%s argv3:%s\n", "test", argc, argv[0], argv[1], argv[2]);
}

void Sys_cmd_Init() {
    Cmd.ls       = __ls;
    Cmd.reset    = __reset;
    Cmd.poweroff = NULL;
    Cmd.clear    = __clear;
    Cmd.test     = __test;
}

void DisPlay_SystemData(int argc, void *argv[]) {
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
    Wirte_String(10, 2, 2, "OpenMV_y:     PidOut:        speed_x:     speed_y:     ");             // 显示数字
    refresh_Partscreen(0, 1, 1);                                 // 刷新屏幕
    while (!USART1_Data->RunStae) {
        Wirte_String(9, 27, 2, "%d   ", srt.SysRunTimeSec);  // 显示秒
        Wirte_String(9, 35, 2, "%d   ", srt.SysRunTimeMin);  // 显示分钟
        Wirte_String(10, 11, 2, "%d  ", OpenMVData_X);      // 显示数字
        Wirte_String(10, 23, 2, "%d   ", Motor_x);           // 显示数字
        Wirte_String(10, 39, 2, "%d   ", pid_xs.current);
        Wirte_String(10, 52, 2, "%d   ", pid_ys.current);  // 显示数字
        loading_bar(12, 2, 3, 1, 282, OpenMVData_X);
        refresh_Partscreen(0, 0, 1);  // 刷新屏幕
    }
    USART1_Data->RunStae = 0;  // 退出显示
    sfp.syspfunc         = NULL;
    printf(CLEAR_SCREEN);
    return;
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

void __led(int argc, void *argv[]) {
    // 处理LED命令
    if (strcmp(argv[0], "on") == 0) {
        LED_ON(port);  // 打开LED
    } else if (strcmp(argv[0], "off") == 0) {
        LED_OFF(port);  // 关闭LED
    } else if (strcmp(argv[0], "flip") == 0) {
        LED_Flip(port);  // 翻转LED状态
    } else {
        printf("Invalid argument for led command\n");
    }
}
