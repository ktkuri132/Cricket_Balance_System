#include <control.h>    
#include <stdint.h>

int32_t Get_Blobs_Speed(int32_t dir,uint32_t current) {
    static int32_t Blobs_Speed[2] = {0, 0};
    if(dir == X) {
        int32_t temp = current - Blobs_Speed[X];
        temp = temp*30000;
        Blobs_Speed[X] = current;
        return temp;
    } else if(dir == Y) {
        int32_t temp = current - Blobs_Speed[Y];
        temp = temp*30000;
        Blobs_Speed[Y] = current;
        return temp;
    }
}