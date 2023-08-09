#include <stdio.h>
#include "sushizhou_common/su_common_fifo.h"

int main()
{
    SuFIFO fifo;
    uint8_t fifo_buffer[5]={0};
    //fifo初始化
    fifo.state=FIFO_Init(&fifo,kFIFOData8bit,fifo_buffer,5);
    //入队
    for (int i = 0; i < 7; ++i)
    {
        fifo.state=FIFO_Write_Element(&fifo,i);
    }
    uint8_t data=0;
    for (int i = 0; i < 10; ++i)
    {
        fifo.state=FIFO_Read_Element(&fifo, &data);
    }

    return 0;
}
