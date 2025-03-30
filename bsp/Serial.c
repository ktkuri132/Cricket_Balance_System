#include "Serial.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "sysport.h"

// 通用串口发送函数
void usart_send_string(SYS_Port *port, uint8_t *data)
{
    
}




#ifdef Basic_Serial

#endif

#ifdef ATOM_Serial       // 正点原子串口协议,用于兼容性交互


#endif

#ifdef STDE_Serial       // st,d,..e 串口协议,用于常规通信



// 初始化函数，模拟类的构造函数
void Stde_DataTypeDef_Init(Stde_DataTypeDef *data)
{
    data->CMD_Callback = NULL;
    data->DR_Eevet_Callback = NULL;
    data->UART_DATA_TYPE_Callback = NULL;
    data->c = 0;
    data->UART_Strat = 0;
    data->UART_End = 0;
    data->Res_Data_type = 0;
    data->UART_DATA_TYPE = 0;
    data->Res_note = 0;
    data->Res_len = 0;
    data->UART_NOTE = 0;
    data->UART_LEN = 0;
    memset(data->UART_NOTE_LEN, 0, sizeof(data->UART_NOTE_LEN));
    memset(data->USART_array, 0, sizeof(data->USART_array));
    memset(data->Data, 0, sizeof(data->Data));
}

#define DR USART2->RDR

/// @brief STDE串口协议处理函数
uint8_t STDE_UART(USART_TypeDef* USARTx, Stde_DataTypeDef* DataTypeStruct)
{
    DataTypeStruct->c = USARTx->RDR;   //获取第一个字符
    if(DataTypeStruct->c=='s')          //如果是开始字符
    {
        DataTypeStruct->UART_Strat = 1;     //开始接收
        DataTypeStruct->UART_End = 0;       //关闭结束标志
        DataTypeStruct->Res_Data_type = 1;    //开始检测数据格式
        DataTypeStruct->Res_len = 0;        //下标清零
        DataTypeStruct->Res_note = 0;       //数据节点清零
        return 0;
    }
    else if(DataTypeStruct->c=='e')     //如果是结束字符
    {
        DataTypeStruct->UART_NOTE_LEN[DataTypeStruct->Res_note] = DataTypeStruct->Res_len;  //保存最后一次数据节点的长度

        DataTypeStruct->UART_Strat = 0;     //重新开始
        DataTypeStruct->UART_End = 1;       //打开结束标志
        DataTypeStruct->UART_LEN = DataTypeStruct->Res_len;   //保存本次数据长度
        DataTypeStruct->UART_NOTE = DataTypeStruct->Res_note+1;  //保存本次数据节点

        DataTypeStruct->Res_note = 0;       //数据节点清零
        DataTypeStruct->Res_len=0;          //下标清零
        memcpy(DataTypeStruct->Data,DataTypeStruct->USART_array,sizeof(DataTypeStruct->USART_array));   //将数据拷贝到Data数组
        memset(DataTypeStruct->USART_array,0,sizeof(DataTypeStruct->USART_array));   //清空USART_array数组

        // 数据帧结束，产生回调事件

        return 0;
    }
    else if(DataTypeStruct->c==',')
    {
        DataTypeStruct->UART_NOTE_LEN[DataTypeStruct->Res_note] = DataTypeStruct->Res_len;  //保存本次数据节点的长度
        DataTypeStruct->Res_note++;     //数据节点加1
        DataTypeStruct->Res_len = 0;    //下标清零
    }
    else
    {
        if(DataTypeStruct->Res_Data_type)     //先检测数据格式
        {
            switch (DataTypeStruct->c)
            {
                
                // 检测数据格式
                case '1':DataTypeStruct->UART_DATA_TYPE=1;break;
                case '5':DataTypeStruct->UART_DATA_TYPE=5;break;
                case '6':DataTypeStruct->UART_DATA_TYPE=6;break;
                case '3':DataTypeStruct->UART_DATA_TYPE=3;break;
                case '4':DataTypeStruct->UART_DATA_TYPE=4;break;
                case '2':DataTypeStruct->UART_DATA_TYPE=2;break;
                // 检测：命令数据格式
                
                case 'p':DataTypeStruct->UART_DATA_TYPE='p';
                break;

                default:break;
                    
            }
            (DataTypeStruct->UART_DATA_TYPE_Callback != NULL) ? DataTypeStruct->UART_DATA_TYPE_Callback(DataTypeStruct) : 0;
            DataTypeStruct->Res_Data_type=0;   //关闭数据格式检测
        }

        if(DataTypeStruct->UART_Strat)      // 开始接收后，数组的第一个位置存储的是数据格式，读数据要从第二个位置开始
        {
            DataTypeStruct->USART_array[DataTypeStruct->Res_note][DataTypeStruct->Res_len] = DataTypeStruct->c;  //存储数据
            DataTypeStruct->Res_len++;     //下标加1
        }
    }
}

/// @brief 处理串口数据针对于数字
/// @param point_note 待处理的指定节点 
uint16_t StdeUSART_Deal(Stde_DataTypeDef* DataTypeStruct,uint8_t point_note)
{
    //检查是否越界
    if(point_note > DataTypeStruct->UART_NOTE)
    {
        return 0;
    }

    uint16_t sum = 0;
    uint8_t len = DataTypeStruct->UART_NOTE_LEN[point_note];
    
    for (uint8_t i = 0; i < len; i++)
    {
        uint8_t temp_target = DataTypeStruct->Data[point_note][i];
        // 判断临时目标数据的ascll码值
        if(!(temp_target >= '0' && temp_target <= '9'))     //如果不是数字字符
        {
            return temp_target;         //直接返回
        }
        
        sum = sum * 10 + (temp_target - '0');
    }

    return sum;
}

#endif

#ifdef BIE_Serial        // 专用于模拟PC交互shell脚本协议

Bie_ShellTypeDef * ShellTypeStruct;

// 命令模式回调函数
void CMD_Callback()
{
    //处理命令
}

// 数据接收完成回调函数
void DR_Eevet_Callback()
{
    if(Shell_Deal(0,ShellTypeStruct)==NULL)
    {
        printf("\nroot@stm32:");
    }
    else 
    {
        printf("\n%s\nroot@stm32:",Shell_Deal(0,ShellTypeStruct));
    }
    
    fflush(stdout);
}

// 串口1中断处理函数：检测数据格式，接收数据
void BIE_UART(USART_TypeDef * USARTx,Bie_ShellTypeDef* ShellTypeStruct)
{
    //判断是否是接收中断
    if (USARTx->ISR & USART_ISR_RXNE_RXFNE)
    {
        ShellTypeStruct->c = USARTx->RDR;   //获取第一个字符

        if(ShellTypeStruct->c==0x0D)     //如果是回车
        {
            ShellTypeStruct->UART_NOTE_LEN[ShellTypeStruct->Res_note] = ShellTypeStruct->Res_len;  //保存最后一次数据节点的长度

            ShellTypeStruct->UART_End = 1;       //打开结束标志
            ShellTypeStruct->UART_LEN = ShellTypeStruct->Res_len;   //保存本次数据长度
            ShellTypeStruct->UART_NOTE = ShellTypeStruct->Res_note+1;  //保存本次数据节点

            ShellTypeStruct->Res_note = 0;       //数据节点清零
            ShellTypeStruct->Res_len=0;          //下标清零
            memcpy(ShellTypeStruct->Data,ShellTypeStruct->USART_array,sizeof(ShellTypeStruct->USART_array));   //将数据拷贝到Data数组
            memset(ShellTypeStruct->USART_array,0,sizeof(ShellTypeStruct->USART_array));   //清空USART_array数组
            ShellTypeStruct->Total_LEN=0;
            // 产生一个接收完成的事件(可选)
            DR_Eevet_Callback();

            return;
        }
        else if(ShellTypeStruct->c==0x20)        // 检测到空格
        {
            ShellTypeStruct->USART_array[ShellTypeStruct->Res_note][ShellTypeStruct->Res_len] = ShellTypeStruct->c;  //存储数据

            ShellTypeStruct->UART_NOTE_LEN[ShellTypeStruct->Res_note] = ShellTypeStruct->Res_len;  //保存本次数据节点的长度
            ShellTypeStruct->Res_note++;     //数据节点加1
            ShellTypeStruct->Res_len = 0;    //下标清零
            ShellTypeStruct->Total_LEN++;
            // 输入回显
            USARTx->RDR = ShellTypeStruct->c;
        }
        else if(ShellTypeStruct->c==0x7F)  // 检测到backspace
        {
            if(ShellTypeStruct->Res_len!=0)      // 新的节点已经有字符了
            {
               ShellTypeStruct->USART_array[ShellTypeStruct->Res_note][ShellTypeStruct->Res_len-1] = 0;    // 上一次存储的字符换成0
               ShellTypeStruct->Res_len--;       // 下次存储字符的位置回退
            }
            else        // 这个新的节点还没有字符 回退键会将这个空格连带新产生的节点都删除
            {
                ShellTypeStruct->Res_note--;     // 节点的位置回退
                ShellTypeStruct->Res_len = ShellTypeStruct->UART_NOTE_LEN[ShellTypeStruct->Res_note]; // 上一个节点的最后一个位置取出来
            }

            if(ShellTypeStruct->Total_LEN>0)
            {
                // 回显删除字符
                USARTx->RDR = 0x08;  // 发送Backspace
                while (!(USARTx->ISR & USART_ISR_TXE_TXFNF));  // 等待发送完成
                USARTx->RDR = ' ';   // 发送空格覆盖
                while (!(USARTx->ISR & USART_ISR_TXE_TXFNF));  // 等待发送完成
                USARTx->RDR = 0x08;  // 再发送Backspace
                while (!(USARTx->ISR & USART_ISR_TXE_TXFNF));  // 等待发送完成
            }
            ShellTypeStruct->Total_LEN--;
            if(ShellTypeStruct->Total_LEN<0)
            {
                ShellTypeStruct->Total_LEN=0;
            }
        }
        else
        {
            ShellTypeStruct->Total_LEN++;
            ShellTypeStruct->USART_array[ShellTypeStruct->Res_note][ShellTypeStruct->Res_len] = ShellTypeStruct->c;  //存储数据
            ShellTypeStruct->Res_len++;     //下标加1
            // 输入回显
            USARTx->RDR = ShellTypeStruct->c;
        }
    }
}

// 待添加的命令
char* cmd[20] = 
{
    "hello","reboot","poweroff"
};


/// @brief 处理串口发送的指令
/// @param point_note 待处理的节点
/// @return 字符串指针
uint8_t Shell_Deal(uint8_t point_note,Bie_ShellTypeDef* ShellTypeStruct)
{
    //检查是否越界
    if(point_note > ShellTypeStruct->UART_NOTE)
    {
        return 0;
    }

    uint8_t i;
    for(i=0;strcmp(ShellTypeStruct->Data[point_note],cmd[i]);i++)
    {
        if(i==19)
        {
            return "command not found!";
        }
    }

    return i;
}



GraphicsChar_Unit Graphics_Memory[20][120]; // 显存区，存储字符和坐标信息

/// @brief 写入显存区中的字符和坐标信息
void Wirte_Char(uint8_t x, uint8_t y, char c, uint8_t color)
{
    // 在显存区中存储字符和坐标信息
    Graphics_Memory[x][y].c = c;
    Graphics_Memory[x][y].sit_x = x;
    Graphics_Memory[x][y].sit_y = y;
    Graphics_Memory[x][y].color = color;
    Graphics_Memory[x][y].fresh = 1; // 设置刷新标志位
    Graphics_Memory[x][y].color_fresh = 1; // 设置颜色刷新标志位
    Graphics_Memory[x][y].sit_fresh = 1; // 设置坐标刷新标志位
    // 这里可以添加代码将字符显示到屏幕上，例如调用LCD或OLED的显示函数
}

/// @brief 读取显存区中的字符和坐标信息
void Read_Char(uint8_t x, uint8_t y, char *c, uint8_t *color)
{
    // 从显存区中读取字符和坐标信息
    *c = Graphics_Memory[x][y].c;
    *color = Graphics_Memory[x][y].color;
}

/// @brief 清除显存区中的字符和坐标信息
void Clear_Char(uint8_t x, uint8_t y)
{
    // 清除显存区中的字符和坐标信息
    Graphics_Memory[x][y].c = 0;
    Graphics_Memory[x][y].sit_x = 0;
    Graphics_Memory[x][y].sit_y = 0;
    Graphics_Memory[x][y].color = 0;
    Graphics_Memory[x][y].fresh = 0; // 清除刷新标志位
    Graphics_Memory[x][y].color_fresh = 0; // 清除颜色刷新标志位
    Graphics_Memory[x][y].sit_fresh = 0; // 清除坐标刷新标志位
    // 这里可以添加代码将字符从屏幕上清除，例如调用LCD或OLED的清除函数
}

void Clear_Screen()
{
    // 清除显存区中的所有字符和坐标信息
    for (uint8_t i = 0; i < 50; i++)
    {
        for (uint8_t j = 0; j < 50; j++)
        {
            Clear_Char(i, j);
        }
    }
}

void __Wirte_String(uint8_t x, uint8_t y,  uint8_t color,char *str)
{
    // 在显存区中存储字符串和坐标信息
    for (uint8_t i = 0; str[i] != '\0'; i++)
    {
        Wirte_Char(x, y + i, str[i], color);
    }
} 

void Wirte_String(uint8_t x, uint8_t y,  uint8_t color,char *str,...)
{
    char String[100];						//定义字符数组
	va_list arg;							//定义可变参数列表数据类型的变量arg
	va_start(arg, str);					//从format开始，接收参数列表到arg变量
	vsprintf(String, str, arg);			//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);							//结束变量arg
    __Wirte_String(x, y, color, String); // 调用Wirte_String函数将字符串写入显存区
}

void Read_String(uint8_t x, uint8_t y, char *str, uint8_t color)
{
    // 从显存区中读取字符串和坐标信息
    for (uint8_t i = 0; i < 50; i++)
    {
        Read_Char(x, y + i, &str[i], &color);
    }
}

void refresh_Allscreen()
{
    // 刷新屏幕，将显存区中的字符和坐标信息显示到屏幕上
    for (uint8_t i = 0; i < 50; i++)
    {
        for (uint8_t j = 0; j < 50; j++)
        {
            if (Graphics_Memory[i][j].c != 0)
            {
                // 显示字符
                printf("%c", Graphics_Memory[i][j].c);
            }
        }
    }
}

/// @brief 部分刷新,将刷新标志位的字符显示到屏幕上
/// @param x 刷新显存的起始坐标x
/// @param y 刷新显存的起始坐标y
/// @param Mode 1: 覆盖显示 0: 不覆盖,追尾显示
void refresh_Partscreen(uint8_t x, uint8_t y,uint8_t Mode)
{
    int i, j;
    for (i = x; i < 20; i++)
    {
        for (j = y; j < 100; j++)
        {
            if (Graphics_Memory[i][j].fresh == 1) // 如果需要刷新
            {
                // 显示字符
                if(Mode == 1)
                {
                    // 覆盖显示
                    printf("\033[%d;%dH", Graphics_Memory[i][j].sit_x+1, Graphics_Memory[i][j].sit_y); // 设置光标位置
                }
                else if (Mode == 0)
                {
                    // 追尾显示
                    printf("\033[%d;%dH", i, j); // 设置光标位置
                }
                if(Graphics_Memory[i][j].color_fresh == 1) // 如果需要刷新颜色
                {
                    // 设置颜色
                    switch (Graphics_Memory[i][j].color)
                    {
                        case 0: printf("\033[0m"); break; // 默认颜色
                        case 1: printf("\033[31m"); break; // 红色
                        case 2: printf("\033[32m"); break; // 绿色
                        case 3: printf("\033[33m"); break; // 黄色
                        case 4: printf("\033[34m"); break; // 蓝色
                        case 5: printf("\033[35m"); break; // 紫色
                        case 6: printf("\033[36m"); break; // 青色
                        default: printf("\033[0m"); break; // 默认颜色
                    }
                }
                printf("%c",Graphics_Memory[i][j].c); // 显示字符
                Graphics_Memory[i][j].fresh = 0; // 清除刷新标志位 
            } 
        }
        printf(CURSOR_RESTORE); // 设置光标位置到下一行
    }
    printf(CURSOR_HOME);
    printf(CURSOR_HIDE); // 显示光标
    fflush(stdout);
}

/***********************应用层***************************** */

void loading_bar(){
    
}



#endif