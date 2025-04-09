#include <control.h>    
#include <stdint.h>

int32_t Get_Blobs_Speed(int32_t dir,uint32_t current) {
    static int32_t Blobs_Speed[2] = {0, 0};
    static int32_t tempx = 0, tempy = 0;
    if(dir == X) {
        tempx = current - Blobs_Speed[X];
        // if((tempx<3)||(tempx > -3)){
        //     tempx = 0;
        // }
        tempx = tempx*3;
        Blobs_Speed[X] = current;
        return tempx;
    } else if(dir == Y) {
        tempy = current - Blobs_Speed[Y];
        // if((tempy<3)||(tempy > -3)){
        //     tempy = 0;
        // }
        tempy = tempy*3;
        Blobs_Speed[Y] = current;
        return tempy;
    }
}