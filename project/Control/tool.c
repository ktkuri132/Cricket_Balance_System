#include <control.h>    
#include <stdint.h>


void DS2318_Load(int32_t Output){
    if(Output<0){
        Output = -Output;
    }
    
}