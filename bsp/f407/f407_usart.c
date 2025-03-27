#include "f407.h"

#ifdef STM32F407xx

#include <stdint.h>
#include <stm32f4xx.h>




void F407_USART_Init(void* const Parameters) {
    USART_Parameters* USART_Parameter = (USART_Parameters*)Parameters;
    // GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  // 使能USART1时钟

    // 串口1对应引脚复用映射
    GPIO_PinAFConfig(USART_Parameter->GPIOx, GPIO_PinSource9, USART_Parameter->GPIO_AF);   // GPIOA9复用为USART1
    GPIO_PinAFConfig(USART_Parameter->GPIOx, GPIO_PinSource10, USART_Parameter->GPIO_AF);  // GPIOA10复用为USART1

    // USART1端口配置
    GPIO_InitStructure.GPIO_Pin   = USART_Parameter->TX_Pin | USART_Parameter->RX_Pin;  // GPIOA9与GPIOA10
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;              // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          // 速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;             // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;              // 上拉
    GPIO_Init(USART_Parameter->GPIOx, &GPIO_InitStructure);                     // 初始化PA9，PA10

    // USART1 初始化设置
    USART_InitStructure.USART_BaudRate   = USART_Parameter->baudrate;                // 波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;     // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;      // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;                              // 无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 收发模式
    USART_Init(USART_Parameter->USARTx, &USART_InitStructure);                        // 初始化串口1

    USART_Cmd(USART_Parameter->USARTx, ENABLE);  // 使能串口1

    USART_ITConfig(USART_Parameter->USARTx, USART_IT_RXNE, ENABLE);  // 开启相关中断
}

#endif