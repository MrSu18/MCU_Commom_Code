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
* @return: 队列状态
* @date  : 2023.8.9
* @author: sushizhou
************************************************/
SuFIFOState FIFO_Write_Element (SuFIFO *fifo, uint32_t dat)
{
    //循环队列入队操作
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
    FIFO_Rear_Offset(fifo, 1);// 无论如何队列的队尾都需要进队的，接收到的信息不能被放弃
    SuFIFOState return_value = kFIFOSuccess;
    // 判断一下该返回的状态
    if(1 < fifo->size)//剩余长度不能等于1，要空开一个给循环队列循环
    {
        //如果队列还没满队头就不用跟着变
        fifo->size -= 1; // 缓冲区剩余长度减小
        fifo->length+=1; // 队列长度增大
        if (fifo->length>0) return_value = kFIFOBufferNoFull;//队列长度大于0并且没满就队列未满状态
        else                return_value = kFIFOBufferEmpty;//队列长度为0则空队列状态
    }
    else
    {
        //如果队列是满队，队头也要跟着增，才能是循环队列
        FIFO_Front_Offset(fifo, 1);
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
    //出队要跟入队相反，根据状态出队，因为是循环队列所以入队是一直入的，但是出队，你出完了就不能出了
    if (fifo->length>0)
    {
        switch(fifo->type)
        {
            case kFIFOData8bit:
                *((uint8_t *)dat) = ((uint8_t *)fifo->buffer)[fifo->front];
                break;
            case kFIFOData16bit:
                *((uint16_t *)dat) = ((uint16_t *)fifo->buffer)[fifo->front];
                break;
            case kFIFOData32bit:
                *((uint32_t *)dat) = ((uint32_t *)fifo->buffer)[fifo->front];
                break;
        }
        FIFO_Front_Offset(fifo, 1);
        fifo->size+=1;//可用缓存增加
        fifo->length-=1;//队列长度减小
        return_value=kFIFOBufferNoFull;
    }
    else return_value=kFIFOBufferEmpty;

    return return_value;
}
