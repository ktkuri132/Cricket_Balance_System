#ifndef __SEHLL_H
#define __SEHLL_H
#include <sysport.h>

typedef struct {
    uint8_t c;
    uint8_t Res_len;   // 接收数据的下标
    uint8_t UART_NOTE;  // 本次数据节点
    uint8_t RunStae;  // 运行状态   --> 这里出现了一个bug,下面的Data数组访问越界,导致RunStae的值被覆盖了
    uint8_t Data[20];  // 数据长度酌情调整
} Bie_ShellTypeDef;     // Shell协议结构体

typedef struct {
    char *name;  // 命令名称
    uint8_t RunStae;  // 运行状态
    void *arg;  // 命令参数指针
    int argc;   // 参数个数
    void (*callback)(int argc,void *argv[]);  // 命令回调函数
} EnvVar;   // 环境变量结构体

void Shell_Deal(Bie_ShellTypeDef *ShellTypeStruct,EnvVar *env_vars);
void BIE_UART(USART_TypeDef *USARTx, Bie_ShellTypeDef *ShellTypeStruct,EnvVar *env);

typedef struct {
    Bfunc ls;  // ls命令回调函数
    Bfunc reset;  // reboot命令回调函数
    Bfunc poweroff;  // poweroff命令回调函数
    Bfunc help;  // help命令回调函数
    Bfunc clear;  // clear命令回调函数
}Cmd_PointerTypeDef;    // 系统默认配置命令指针结构体


#endif