#include <errno.h>
#include "sysport.h"
#include <stdint.h>

#define USART
#define TIM

SYS_Port*  SysPort_Init() {
    static SYS_Port sys_port = {
        .System_Init = SystemClock_Config,
        .syscall_port = {
          .bsp_systick_delay_us = delay_us,
          .bsp_systick_delay_ms = delay_ms,
          .NVIC_Configuration = NULL,
        },
        .rcc_periph_port = {
            .bsp_rcc_periph_clock = NULL,
        },
        .gpio_port = {
            .bsp_gpio_init = H723_GPIO_Config,
            .bsp_gpio_af_set = H723_GPIO_AF_Config,
            .bsp_gpio_pin_set = H723_GPIO_Pin_Set,
           .bsp_gpio_pin_get = NULL,
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
            .bsp_tim_x_stop = NULL,
            .bsp_tim_x_set_period = NULL,
            .bsp_tim_x_set_prescaler = NULL,
            .bsp_tim_x_set_clock_division = NULL,
            .bsp_tim_x_set_counter_mode = NULL,
            .bsp_tim_x_set_channel = NULL,
        }
        #endif
    };
    return &sys_port;
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