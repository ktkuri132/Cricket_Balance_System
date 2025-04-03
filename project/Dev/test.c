#include <stdint.h>
#include <sysport.h>
#include <Serial.h>
#include "stm32h7xx_it.h"
extern SYS_Port *port;





void test() {
    printf(CURSOR_SHOW);
    while (1) {
        if(port->syspfunc != NULL) {
            port->syspfunc(port->Parameters);  // 执行系统函数
            port->syspfunc = NULL;
        }
    }
}




