#include <errno.h>
#include "sysport.h"
#include <stdint.h>
#include <Serial.h>
#include <shell.h>
#define USART
#define TIM



/**
    * @brief  系统接口初始化函数
    * @param  None
 */
SYS_Port*  SysPort_Init() {
    static SYS_Port sys_port = {
        .System_Init = SystemClock_Config,
        .SysTick_Init = SysTick_Init,
        .syscall_port = {
          .bsp_systick_delay_us = delay_us,
          .bsp_systick_delay_ms = delay_ms,
          .NVIC_Configuration = NVIC_Init,
        },
        .rcc_periph_port = {
            .bsp_rcc_periph_clock = NULL,
        },
        .gpio_port = {
            .bsp_gpio_init = H723_GPIO_Config,
            .bsp_gpio_af_set = H723_GPIO_AF_Config,
            .bsp_gpio_pin_set = H723_GPIO_Pin_Set,
           .bsp_gpio_pin_get = H723_GPIO_Pin_Get,
            .GetGPIOPeriphClock = NULL,
        },
        #ifdef I2C
        .i2c_port = {
            .Soft_IIC_Init = NULL,
            .Soft_IIC_Start = NULL,
           .Soft_IIC_Stop = NULL,
           .Soft_IIC_Wait_Ack = NULL,
           .Soft_IIC_Ack = NULL,
        }
        #endif
        #ifdef USART    
        .usart_port = {
            .bsp_usart_x_inti = H723_USART_Init,
        },
        #endif
        #ifdef TIM
        .tim_port = {
            .bsp_tim_x_inti = H723_TIM_Init,
            .bsp_tim_x_start = NULL,
        }
        #endif
    };
    return &sys_port;
}

/*  系统接口声明    */
extern SYS_Port *port;
/* 项目环境变量声明  */
extern EnvVar MyEnv[];


/// 任务切换函数
/// @param userEnv: 用户环境变量数组
void Task_Switch(EnvVar *userEnv) {
    // 假如环境变量过长可采取其他的查找算法:如二分查找等
    // 这里采用线性查找
    int i;
    for (i = 0; userEnv[i].name != NULL; i++) {
        if(userEnv[i].RunStae){
            // 执行命令
            port->syspfunc = userEnv[i].callback;  // 设置系统函数指针
            port->Parameters = userEnv[i].arg;  // 设置参数
            userEnv[i].RunStae = 0;  // 重置运行状态
            return;  // 跳出循环，避免重复执行
        }
    }
    i = 0;  // 重置循环变量
}

void PendSV_Handler(){
    Task_Switch(MyEnv); // 执行任务切换
}

/**
 *
 * 不使用标准库的重定向
 * @}
 */
#ifdef STDLIB
int _write(int file, char *ptr, int len) {
    (void)file;
    int i = 0;
    for (i = 0; i < len; i++) {
        while ((USART1->SR & USART_SR_TXE) == 0);
        USART1->DR = ptr[i];
    }
    return len;
}

int _read(int file, char *ptr, int len) {
    (void)file;
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        *ptr++ = USART1->DR;
    }
    return len;
}


int __attribute__((__weak__)) _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    return -1;
}

void __attribute__((__weak__)) _exit(int status) {
    _kill(status, -1);
    while (1) {
    } /* Make sure we hang here */
}

int __attribute__((__weak__)) _close(int file) {
    (void)file;
    return -1;
}

int __attribute__((__weak__)) _fstat(int file, struct stat *st) {
    (void)file;
    return 0;
}

int __attribute__((__weak__)) _isatty(int file) {
    (void)file;
    return 1;
}

int __attribute__((__weak__)) _lseek(int file, int ptr, int dir) {
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int __attribute__((__weak__)) _open(char *path, int flags, ...) {
    (void)path;
    (void)flags;
    /* Pretend like we always fail */
    return -1;
}

int __attribute__((__weak__)) _wait(int *status) {
    (void)status;
    return -1;
}

int __attribute__((__weak__)) _unlink(char *name) {
    (void)name;
    return -1;
}

int __attribute__((__weak__)) _times(struct tms *buf) {
    (void)buf;
    return -1;
}

int __attribute__((__weak__)) _stat(char *file, struct stat *st) {
    (void)file;
    return 0;
}

int __attribute__((__weak__)) _link(char *old, char *new) {
    (void)old;
    (void)new;
    return -1;
}

int __attribute__((__weak__)) _fork(void) { return -1; }

int __attribute__((__weak__)) _execve(char *name, char **argv, char **env) {
    (void)name;
    (void)argv;
    (void)env;
    return -1;
}

static uint8_t *__sbrk_heap_end = NULL;

void* __attribute__((__weak__)) _sbrk(int incr) {
    extern uint8_t _end;             /* Symbol defined in the linker script */
    extern uint8_t _estack;          /* Symbol defined in the linker script */
    extern uint32_t _Min_Stack_Size; /* Symbol defined in the linker script */
    const uint32_t stack_limit =
        (uint32_t)&_estack - (uint32_t)&_Min_Stack_Size;
    const uint8_t *max_heap = (uint8_t *)stack_limit;
    uint8_t *prev_heap_end;

    /* Initialize heap end at first call */
    if (NULL == __sbrk_heap_end) {
        __sbrk_heap_end = &_end;
    }

    /* Protect heap from growing into the reserved MSP stack */
    if (__sbrk_heap_end + incr > max_heap) {
        errno = ENOMEM;
        return (void *)-1;
    }

    prev_heap_end = __sbrk_heap_end;
    __sbrk_heap_end += incr;

    return (void *)prev_heap_end;
}

int __attribute__((__weak__)) _getpid(void) {
    (void)1;
    return 1;
}
#endif