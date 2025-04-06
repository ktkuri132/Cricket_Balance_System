#ifndef __NVIC_
#define __NVIC_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "sysport.h"


#define Port_Header "h723/h723.h"
#define Syscall_Header <syscall.h>

/* 添加芯片头文件  */
#ifndef Port_Header
#error \
    "Port_Header is not defined,please define Port_Header,like this:#define Port_Header h723/h723.h"
#endif

/* 添加芯片对应提供的系统调用头文件 */
#ifndef Syscall_Header
#error \
    "Syscall_Header is not defined,please define Syscall_Header,like this:#define Syscall_Header <syscall.h>"
#endif

#include Port_Header
#include Syscall_Header
#define sys_port port

/**
 * @brief  系统接口结构体
 * @note   该结构体用于存储系统接口的相关参数和函数指针,如果没有定义sys_port,则会报错
 * @param  sys_port: 系统接口结构体
 */
#ifndef sys_port
#error \
    "sys_port is not defined,plesae define sys_port,like this: SYS_Port *sys_port in you main.c file,and like this :#define sys_port port"
#endif

/* 定义系统指针  */
#define srt sys_port->SRT              /* 系统时钟指针  */
#define syscall sys_port->syscall_port /* 系统调用指针  */
#define gpio sys_port->gpio_port       /* gpio指针  */
#define rcc sys_port->rcc_periph_port  /* 外设时钟指针  */
#define i2c sys_port->i2c_port         /* I2C指针  */
#define usart sys_port->usart_port     /* USART指针  */
#define tim sys_port->tim_port         /* TIM指针  */

typedef void (*func)(void *const Parameters);

/**
 * @brief GPIO接口结构体
 * @note  该结构体用于存储GPIO接口的相关参数和函数指针
 * @param  bsp_gpio_init: GPIO初始化函数指针
 * @param  bsp_gpio_af_set: GPIO复用函数指针
 * @param  bsp_gpio_pin_set: GPIO引脚设置函数指针
 * @param  bsp_gpio_pin_get: GPIO引脚读取函数指针
 * @param  GetGPIOPeriphClock: 获取GPIO外设时钟函数指针
 */
typedef struct {
    // GPIO_Init_Parameters *gpio_init_parameters;
    // GPIO_Pin_Parameters *gpio_pin_parameters;
    func bsp_gpio_init;
    func bsp_gpio_af_set;
    void (*bsp_gpio_pin_set)(void *const Parameters, uint8_t status);
    func bsp_gpio_pin_get;
    uint32_t (*GetGPIOPeriphClock)(void *const Parameters);
} GPIO_Port;

/**
 * @brief I2C接口结构体
 * @note  该结构体用于存储I2C接口的相关参数和函数指针
 * @param  Soft_IIC_Init: I2C初始化函数指针
 * @param  Soft_IIC_Start: I2C开始函数指针
 * @param  Soft_IIC_Stop: I2C停止函数指针
 * @param  Soft_IIC_Send_Byte: I2C发送字节函数指针
 * @param  Soft_IIC_Receive_Byte: I2C接收字节函数指针
 * @param  Soft_IIC_Wait_Ack: I2C等待应答函数指针
 * @param  Soft_IIC_Ack: I2C应答函数指针
 * @param  Soft_IIC_NAck: I2C不应答函数指针
 */
typedef struct {
    func Soft_IIC_Init;
    func Soft_IIC_Start;
    func Soft_IIC_Stop;
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
    // SPI_Parameters *spi_parameters;
    func bsp_spi_x_inti;
    func bsp_spi_x_send;
    func bsp_spi_x_receive;
} SPI_Port;

/**
 * @brief USART接口结构体
 * @note  该结构体用于存储USART接口的相关参数和函数指针
 * @param  bsp_usart_x_inti: USART初始化函数指针
 * @param  bsp_usart_x_send: USART发送函数指针
 */
typedef struct {
    // USART_Parameters *usart_parameters;
    func bsp_usart_x_inti;
    func bsp_usart_x_send;
} USART_Port;

/**
 * @brief TIM接口结构体
 * @note  该结构体用于存储TIM接口的相关参数和函数指针
 * @param  bsp_tim_x_inti: TIM初始化函数指针
 * @param  bsp_tim_x_start: TIM启动函数指针
 * @param  其他的额函数暂未用到
 */
typedef struct {
    // TIM_Parameters *tim_parameters;
    func bsp_tim_x_inti;
    func bsp_tim_x_start;
} TIM_Port;

/**
 * @brief SYSCALL(系统调用)接口结构体
 * @note  该结构体用于存储SYSCALL接口的相关参数和函数指针
 * @param  bsp_systick_delay_us: SysTick延时函数指针
 * @param  bsp_systick_delay_ms: SysTick延时函数指针
 * @param  NVIC_Configuration: NVIC配置函数指针
 */
typedef struct {
    void (*bsp_systick_delay_us)(uint32_t us);
    void (*bsp_systick_delay_ms)(uint32_t ms);
    void (*NVIC_Configuration)(void);
} SYSCALL_Port;

/**
 * @brief RCC(时钟)接口结构体
 * @note  该结构体用于存储RCC接口的相关参数和函数指针
 * @param  bsp_rcc_periph_clock: RCC外设时钟函数指针
 */
typedef struct {
    func bsp_rcc_periph_clock;
} RCC_PeriphClock_Port;

/**
 * @brief SystemRunTime(系统运行时间)结构体
 * @note  该结构体用于存储系统运行时间的相关参数
 * @param  SysRunTime: 系统运行时间(不间断计时器)
 * @param  SysRunTimeSec: 系统运行秒数
 * @param  SysRunTimeMin: 系统运行分钟
 * @param  SysRunTimeBeat: 系统运行节拍
 */
typedef struct {
    uint64_t SysRunTime;      // 系统运行时间(不间断计时器)
    uint32_t SysRunTimeSec;   // 系统运行秒数
    uint32_t SysRunTimeMin;   // 系统运行分钟
    uint32_t SysRunTimeBeat;  // 系统运行节拍
} SystemRunTime_t;


/**
    * @brief SYS_Port(系统接口)结构体
    * @note  该结构体用于存储系统接口的相关参数和函数指针
    * @param  SysRunTime: 系统运行时间
    * @param  syscall_port: SYSCALL接口结构体
    * @param  rcc_periph_port: RCC接口结构体
    * @param  gpio_port: GPIO接口结构体
    * @param  i2c_port: I2C接口结构体
    * @param  usart_port: USART接口结构体
    * @param  tim_port: TIM接口结构体
    * @param  System_Init: 系统初始化函数指针
    * @param  SysTick_Init: SysTick初始化函数指针
    * @param  syspfunc: 系统函数指针
    * @param  Parameters: 系统函数指针参数
 */
typedef struct {
    SystemRunTime_t SRT;
    SYSCALL_Port syscall_port;
    RCC_PeriphClock_Port rcc_periph_port;
    GPIO_Port gpio_port;
    I2C_Port i2c_port;
    USART_Port usart_port;
    TIM_Port tim_port;
    void (*System_Init)(void);
    void (*SysTick_Init)(void);
    func syspfunc;
    void *Parameters;
} SYS_Port;

SYS_Port *SysPort_Init();





#endif