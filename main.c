#include <stdio.h>
#include "sushizhou_common/su_common_fifo.h"

int main()
{
    SuFIFO fifo;
    uint8_t fifo_buffer[5]={0};
    //fifo初始化
    FIFO_Init(&fifo,kFIFOData8bit,fifo_buffer,5);
    //入队
    for (int i = 0; i < 7; ++i)
    {
        FIFO_Write_Element(&fifo,i);
    }
    uint8_t data=0;
    FIFO_Search_Element(&fifo,&data,5);
    FIFO_Clear(&fifo);
    return 0;
}
