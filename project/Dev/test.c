#include <sysport.h>
#include <Serial.h>
extern SYS_Port *port;
void test() {


    Wirte_String(0, 0, 1," Hello:");
    Wirte_String(0, 7, 1,"为什么不能显示中文？");

    Wirte_String(0,18, 1,"nihao");
    Wirte_String(0, 24, 1,"Now time is :");

    Wirte_String(1, 0, 2," This is a USART Test:");
    Wirte_String(1, 24, 2, "Time_2 is :" );

    Wirte_String(2, 0, 4," good:");
    Wirte_String(2, 24, 4, "Eva" );
    refresh_Partscreen(0, 0, 1); // 刷新屏幕
    // printf("Hello World!");
    // fflush(stdout);
    // printf(CURSOR_RESTORE);
    // fflush(stdout);
    // // printf(CURSOR_DOWN(1));
    // printf("This is a USART Test!");
    // fflush(stdout);
    while (1) {
        static int i = 0;
        static int j = 0;
        
        Wirte_String(0, 38, 1, "%d", i); // 显示数字
        Wirte_String(1, 36, 2, "%d", j); // 显示数字
        refresh_Partscreen(0, 0, 1); // 刷新屏幕
        i++;
        j+=2;
        // syscall.bsp_systick_delay_ms(5000);
    }
}