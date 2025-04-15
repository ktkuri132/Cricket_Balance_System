#include <control.h>    
#include <stdint.h>
#include "pid.h"


int32_t Get_Blobs_Speed(int32_t dir,uint32_t current) {
    static int32_t Blobs_Speed[2] = {0, 0};
    static int32_t tempx = 0, tempy = 0;
    if(dir == X) {
        tempx = current - Blobs_Speed[X];
        tempx = tempx*3;
        Blobs_Speed[X] = current;
        return tempx;
    } else if(dir == Y) {
        tempy = current - Blobs_Speed[Y];
        tempy = tempy*3;
        Blobs_Speed[Y] = current;
        return tempy;
    }
}

extern int32_t PWM_Refe[6];
extern int32_t Space_Sit[9][2];
extern PID pid_x;
extern PID pid_y;

void split_digits(const char *str, int *digits) {
    for (int i = 0; i < strlen(str); i++) {
        digits[i] = str[i] - '0'; // 将字符转换为整数
    }
}

/**
 * @brief 对应所有的点位情况
 * 
 * @param x 点位控制1
 * @param y 点位控制2
 */
void Goto_space(int x, int y) {
    if ((x == 1) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 2300;
        PWM_Refe[YMid_PWM] = 3650;
    } else if ((x == 2) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 2300;
        PWM_Refe[YMid_PWM] = 2700;
    } else if ((x == 3) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 2300;
        PWM_Refe[YMid_PWM] = 1800;
    } else if ((x == 4) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 3200;
        PWM_Refe[YMid_PWM] = 3580;
    } else if ((x == 5) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 3200;
        PWM_Refe[YMid_PWM] = 2700;
    } else if ((x == 6) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 3250;
        PWM_Refe[YMid_PWM] = 1800;
    } else if ((x == 7) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 4000;
        PWM_Refe[YMid_PWM] = 3600;
    } else if ((x == 8) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 4000;
        PWM_Refe[YMid_PWM] = 2700;
    } else if ((x == 9) && (y == 0)) {
        PWM_Refe[XMid_PWM] = 4100;
        PWM_Refe[YMid_PWM] = 1800;
    } else if (((x == 1) && (y == 2)) || ((x == 2) && (y == 1))) {
        PWM_Refe[XMid_PWM] = 2500;
        PWM_Refe[YMid_PWM] = 3270;
    } else if (((x == 1) && (y == 4)) || ((x == 4) && (y == 1))) {
        PWM_Refe[XMid_PWM] = 2750;
        PWM_Refe[YMid_PWM] = 3500;
    } else if (((x == 1) && (y == 5)) || ((x == 5) && (y == 1))) {
        PWM_Refe[XMid_PWM] = 2900;
        PWM_Refe[YMid_PWM] = 3300;
    } else if (((x == 2) && (y == 3)) || ((x == 3) && (y == 2))) {
        PWM_Refe[YMid_PWM] = 2400;
    } else if (((x == 2) && (y == 4)) || ((x == 4) && (y == 2))) {
        PWM_Refe[XMid_PWM] = 2900;
        PWM_Refe[YMid_PWM] = 3300;
    } else if (((x == 2) && (y == 5)) || ((x == 5) && (y == 2))) {
        PWM_Refe[XMid_PWM] = 2750;
        PWM_Refe[YMid_PWM] = 2850;
    } else if (((x == 2) && (y == 6)) || ((x == 6) && (y == 2))) {
        PWM_Refe[XMid_PWM] = 2900;
        PWM_Refe[YMid_PWM] = 2400;
    } else if (((x == 3) && (y == 5)) || ((x == 5) && (y == 3))) {
        PWM_Refe[XMid_PWM] = 2900;
        PWM_Refe[YMid_PWM] = 2400;
    } else if (((x == 3) && (y == 6)) || ((x == 6) && (y == 3))) {
        // 处理3和6相邻的逻辑
    } else if (((x == 4) && (y == 5)) || ((x == 5) && (y == 4))) {
        PWM_Refe[XMid_PWM] = 3200;
        PWM_Refe[YMid_PWM] = 3270;
    } else if (((x == 4) && (y == 7)) || ((x == 7) && (y == 4))) {
        // 处理2和5相邻的逻辑
    } else if (((x == 4) && (y == 8)) || ((x == 8) && (y == 4))) {
        PWM_Refe[XMid_PWM] = 3600;
        PWM_Refe[YMid_PWM] = 3400;
    } else if (((x == 5) && (y == 6)) || ((x == 6) && (y == 5))) {
        PWM_Refe[XMid_PWM] = 3200;
        PWM_Refe[YMid_PWM] = 2400;
    } else if (((x == 5) && (y == 7)) || ((x == 7) && (y == 5))) {
        PWM_Refe[XMid_PWM] = 3600;
        PWM_Refe[YMid_PWM] = 3300;
    } else if (((x == 5) && (y == 8)) || ((x == 8) && (y == 5))) {
        PWM_Refe[XMid_PWM] = 3600;
        PWM_Refe[YMid_PWM] = 2850;
    } else if (((x == 5) && (y == 9)) || ((x == 9) && (y == 5))) {
        PWM_Refe[XMid_PWM] = 3600;
        PWM_Refe[YMid_PWM] = 2400;
    } else if (((x == 6) && (y == 8)) || ((x == 8) && (y == 6))) {
        PWM_Refe[XMid_PWM] = 3600;
        PWM_Refe[YMid_PWM] = 2400;
    } else if (((x == 6) && (y == 9)) || ((x == 9) && (y == 6))) {
        PWM_Refe[XMid_PWM] = 3600;
        PWM_Refe[YMid_PWM] = 1900;
    } else if (((x == 7) && (y == 8)) || ((x == 8) && (y == 7))) {
        // 处理7和8相邻的逻辑
    } else if (((x == 8) && (y == 9)) || ((x == 9) && (y == 8))) {
        PWM_Refe[XMid_PWM] = 4000;
        PWM_Refe[YMid_PWM] = 2400;
    } else {
        // 处理其他情况
    }
}

void Site_set(int x) {
    switch (x) {
        case 1:
            pid_x.target = Space_Sit[S1][X];
            pid_y.target = Space_Sit[S1][Y];
            break;
        case 2:
            pid_x.target = Space_Sit[S2][X];
            pid_y.target = Space_Sit[S2][Y];
            break;
        case 3:
            pid_x.target = Space_Sit[S3][X];
            pid_y.target = Space_Sit[S3][Y];
            break;
        case 4:
            pid_x.target = Space_Sit[S4][X];
            pid_y.target = Space_Sit[S4][Y];
            break;
        case 5:
            pid_x.target = Space_Sit[S5][X];
            pid_y.target = Space_Sit[S5][Y];
            break;
        case 6:
            pid_x.target = Space_Sit[S6][X];
            pid_y.target = Space_Sit[S6][Y];
            break;
        case 7:
            pid_x.target = Space_Sit[S7][X];
            pid_y.target = Space_Sit[S7][Y];
            break;
        case 8:
            pid_x.target = Space_Sit[S8][X];
            pid_y.target = Space_Sit[S8][Y];
            break; 
        case 9:
            pid_x.target = Space_Sit[S9][X];
            pid_y.target = Space_Sit[S9][Y];
            break;
        default:    
            break;
    }
}

