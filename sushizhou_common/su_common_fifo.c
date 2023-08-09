#include "su_common_fifo.h"
#include "string.h"

/***********************************************
* @brief : 队头移动(一般来说是元素出队)
* @param : SuFIFO *fifo: 需要初始化的队列变量
*          int offset: 往前或者往后移动的距离
* @return: void
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
static void FIFO_Front_Offset (SuFIFO *fifo, int offset)
{
    fifo->front=(fifo->front+offset)%fifo->max;
}

/***********************************************
* @brief : 队尾移动(一般来说是元素入队)
* @param : SuFIFO *fifo: 需要初始化的队列变量
*          int offset: 往前或者往后移动的距离
* @return: void
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
static void FIFO_Rear_Offset (SuFIFO *fifo, int offset)
{
    fifo->rear=(fifo->rear+offset)%fifo->max;
}

/***********************************************
* @brief : 队列缓冲区初始化
* @param : SuFIFO *fifo: 需要初始化的队列变量
*          SuFIFODataType type: 存储的数据类型
*          void *buffer_addr：存在哪个地址
*          uint32_t size: 大小
* @return: 初始化的状态
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
SuFIFOState FIFO_Init (SuFIFO *fifo, SuFIFODataType type, void *buffer_addr, uint32_t size)
{
    SuFIFOState return_value = kFIFOSuccess;
    if(NULL == buffer_addr)
    {
        return_value = kFIFOBufferNull;
    }
    else
    {
        fifo->buffer            = buffer_addr;
        fifo->type              = type;
        fifo->front             = 0;
        fifo->rear              = 0;
        fifo->size              = size;
        fifo->length            = 0;
        fifo->max               = size;
    }
    return return_value;
}

/***********************************************
* @brief : 数据入队
* @param : SuFIFO *fifo: 队列变量
*          uint32_t dat: 需要存储的数据
* @return: 入队的状态
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
SuFIFOState FIFO_Write_Element (SuFIFO *fifo, uint32_t dat)
{
    SuFIFOState return_value = kFIFOSuccess;
    if(1 <= fifo->size)                                                     // 剩余空间足够装下本次数据
    {
        switch(fifo->type)
        {
            case kFIFOData8bit:
                ((uint8_t *)fifo->buffer)[fifo->rear] = dat & 0xFF;
                break;
            case kFIFOData16bit:
                ((uint16_t *)fifo->buffer)[fifo->rear] = dat & 0xFFFF;
                break;
            case kFIFOData32bit:
                ((uint32_t *)fifo->buffer)[fifo->rear] = dat;
                break;
        }
        fifo_rear_offset(fifo, 1);                                          // 头指针偏移
        fifo->size -= 1;                                                    // 缓冲区剩余长度减小
        fifo->length+=1;                                                    // 队列长度增大
    }
    else
    {
        return_value = kFIFOBufferFull;
    }
    return return_value;
}

/***********************************************
* @brief : 数据出队
* @param : SuFIFO *fifo: 队列变量
*          uint32_t dat: 需要存储的数据
* @return: 入队的状态
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
SuFIFOState FIFO_Read_Element(SuFIFO *fifo, void *dat)
{
    SuFIFOState return_value = kFIFOSuccess;
}
