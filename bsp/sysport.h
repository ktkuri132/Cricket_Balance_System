#ifndef __NVIC_
#define __NVIC_

#include <stdint.h>
#include <stdio.h>
#include <stm32h723xx.h>
#include <stm32h7xx.h>

#include <syscall.h>
#include <stddef.h>
#include "h723/h723.h"
#define sys_port port

#ifndef sys_port
#error "sys_port is not defined,plesae define sys_port,like this: SYS_Port *sys_port in you main.c file,and like this :#define sys_port port"
#endif

#define syscall sys_port->syscall_port
#define gpio sys_port->gpio_port
#define rcc sys_port->rcc_periph_port
#define i2c sys_port->i2c_port
#define usart sys_port->usart_port
#define tim sys_port->tim_port

typedef void (*BaseFPPort)(void *const Parameters) ;

typedef struct {
    // GPIO_Init_Parameters *gpio_init_parameters;
    // GPIO_Pin_Parameters *gpio_pin_parameters;
    void (*bsp_gpio_init)(void *const Parameters);
    void (*bsp_gpio_af_set)(void *const Parameters);
    void (*bsp_gpio_pin_set)(void *const Parameters,uint8_t status);
    uint8_t (*bsp_gpio_pin_get)(void *const Parameters);
    uint32_t (*GetGPIOPeriphClock)(void *const Parameters);
} GPIO_Port;

typedef struct {
    void (*Soft_IIC_Init)(void *const Parameters);
    void (*Soft_IIC_Start)(void *const Parameters);
    void (*Soft_IIC_Stop)(void *const Parameters);
    void (*Soft_IIC_Send_Byte)(uint8_t txd);
    uint8_t (*Soft_IIC_Receive_Byte)(unsigned char ack);
    uint8_t (*Soft_IIC_Wait_Ack)(void);
    void (*Soft_IIC_Ack)(void);
    void (*Soft_IIC_NAck)(void);
    uint8_t (*Soft_IIC_Write_Len)(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
    uint8_t (*Soft_IIC_Read_Len)(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
    uint8_t (*Soft_IIC_Write_Byte)(uint8_t addr, uint8_t reg, uint8_t data);
    uint8_t (*Soft_IIC_Read_Byte)(uint8_t addr, uint8_t reg);
} I2C_Port;

typedef struct {
    // USART_Parameters *usart_parameters;
    void (*bsp_usart_x_inti)(void *const Parameters);
    void (*bsp_usart_x_send)(void *const Parameters);
} USART_Port;

typedef struct {
    // TIM_Parameters *tim_parameters;
    void (*bsp_tim_x_inti)(void *const Parameters);
    void (*bsp_tim_x_start)(void *const Parameters);
    void (*bsp_tim_x_stop)(void *const Parameters);
    void (*bsp_tim_x_set_period)(void *const Parameters);
    void (*bsp_tim_x_set_prescaler)(void *const Parameters);
    void (*bsp_tim_x_set_clock_division)(void *const Parameters);
    void (*bsp_tim_x_set_counter_mode)(void *const Parameters);
    void (*bsp_tim_x_set_channel)(void *const Parameters);
    void (*bsp_tim_x_set_oc_mode)(void *const Parameters);
    void (*bsp_tim_x_set_output_state)(void *const Parameters);
    void (*bsp_tim_x_set_pulse)(void *const Parameters);
    void (*bsp_tim_x_set_oc_polarity)(void *const Parameters);
    void (*bsp_tim_x_set_oc_preload)(void *const Parameters);
    void (*bsp_tim_x_set_cmd)(void *const Parameters);
    void (*bsp_tim_x_get_counter)(void *const Parameters);
    void (*bsp_tim_x_set_counter)(void *const Parameters);
    void (*bsp_tim_x_set_autoreload_preload)(void *const Parameters);
    void (*bsp_tim_x_set_compare)(void *const Parameters);
    void (*bsp_tim_x_set_compare_preload)(void *const Parameters);
    void (*bsp_tim_x_set_one_pulse_mode)(void *const Parameters);
    void (*bsp_tim_x_set_master_output_trigger)(void *const Parameters);
    void (*bsp_tim_x_set_slave_mode)(void *const Parameters);
    void (*bsp_tim_x_set_input_trigger)(void *const Parameters);
    void (*bsp_tim_x_set_external_clock)(void *const Parameters);
    void (*bsp_tim_x_set_internal_clock)(void *const Parameters);
    void (*bsp_tim_x_set_it)(void *const Parameters);
    void (*bsp_tim_x_get_it_status)(void *const Parameters);
    void (*bsp_tim_x_clear_it)(void *const Parameters);
    void (*bsp_tim_x_get_flag_status)(void *const Parameters);
    void (*bsp_tim_x_clear_flag)(void *const Parameters);
    void (*bsp_tim_x_get_it_source)(void *const Parameters);
    void (*bsp_tim_x_get_flag_index)(void *const Parameters);
    void (*bsp_tim_x_get_capture)(void *const Parameters);
} TIM_Port;


typedef struct {
    void (*bsp_systick_delay_us)(uint32_t us);
    void (*bsp_systick_delay_ms)(uint32_t ms);
    void (*NVIC_Configuration)(void);
} SYSCALL_Port;


typedef struct{
    void (*bsp_rcc_periph_clock)(void *const Parameters);
}RCC_PeriphClock_Port;

typedef struct {
    SYSCALL_Port syscall_port;
    RCC_PeriphClock_Port rcc_periph_port;
    GPIO_Port gpio_port;
    I2C_Port i2c_port;
    USART_Port usart_port;
    TIM_Port tim_port;
    void (*System_Init)(void);

} SYS_Port;

SYS_Port *SysPort_Init();



// #define delay_us(x) bsp_systick_delay_us(x)

#endif