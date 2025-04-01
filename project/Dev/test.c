#include <sysport.h>
#include <Serial.h>
extern SYS_Port *port;

Bie_ShellTypeDef* USART1_Data;



void set_pid_arg(void *const Parameters) {
    int32_t *arg_value = (int32_t *)Parameters;  // 获取参数值
    // 设置PID参数的函数实现
    // 这里可以根据需要进行参数设置
    printf("Setting PID parameters: %d\n", *arg_value);
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
        // if(!sleep_ms(1000, srt.SysRunTime)) {
        //     continue;
        // }
        i++;

    }
    USART1_Data->RunStae = 0; // 退出显示
    printf(CLEAR_SCREEN);
}

void __te(void *const Parameters) {
    // 处理测试命令
    printf("Test command received.\n");
    while(!USART1_Data->RunStae){
        

    }
    USART1_Data->RunStae = 0; // 退出显示
    printf("Exiting...\n");
}

EnvVar testEnv[] = {
    {
        .name = "show",
        .callback = DisPlay_SystemData,
    },
    {
        .name ="kp", 
        .callback =set_pid_arg
    },
    {
        .name ="test",
        .callback =__te
    },
    {
        .name =NULL,
        .callback =NULL
    }
};

void test() {


    printf(CURSOR_SHOW);
    while (1) {
        int i;
        for (i = 0; i < 4; i++) {
            if(testEnv[i].RunStae){
                // 执行命令
                testEnv[i].callback(testEnv[i].arg);  // 调用命令函数.传递参数
                testEnv[i].RunStae = 0;  // 重置运行状态
                break;  // 跳出循环，避免重复执行
            }
        }
        i = 0;  // 重置循环变量
    }
}

void USART1_IRQHandler(void)
{
    if(USART1->ISR & USART_ISR_RXNE_RXFNE){
        BIE_UART(USART1,USART1_Data,testEnv);
    }
    USART1->ICR |= USART_ICR_ORECF;
}
