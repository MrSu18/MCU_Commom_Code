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
* @return: 函数执行是否成功
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Init (SuFIFO *fifo, SuFIFODataType type, void *buffer_addr, uint32_t size)
{
    FunctionStatus return_value = kSuccess;
    if(NULL == buffer_addr)
    {
        return_value = kERROR;
        fifo->state = kFIFOBufferNull;
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
        fifo->state             = kFIFOBufferEmpty;
    }
    return return_value;
}

/***********************************************
* @brief : 数据入队
* @param : SuFIFO *fifo: 队列变量
*          uint32_t dat: 需要存储的数据
* @return: 函数执行是否成功
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Write_Element (SuFIFO *fifo, uint32_t dat)
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
    SuFIFOState return_value = kSuccess;
    // 判断一下该返回的状态
    if(1 < fifo->size)//剩余长度不能等于1，要空开一个给循环队列循环
    {
        //如果队列还没满队头就不用跟着变
        fifo->size -= 1; // 缓冲区剩余长度减小
        fifo->length+=1; // 队列长度增大
        if (fifo->length>0) fifo->state = kFIFOBufferNoFull;//队列长度大于0并且没满就队列未满状态
        else                fifo->state = kFIFOBufferEmpty;//队列长度为0则空队列状态
    }
    else
    {
        //如果队列是满队，队头也要跟着增，才能是循环队列
        FIFO_Front_Offset(fifo, 1);
        fifo->state = kFIFOBufferFull;
    }
    return return_value;
}

/***********************************************
* @brief : 数据出队
* @param : SuFIFO *fifo: 队列变量
*          uint32_t dat: 需要存储的数据
* @return: 函数执行是否成功
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Out_Element(SuFIFO *fifo, void *dat)
{
    SuFIFOState return_value = kSuccess;
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
        fifo->state=kFIFOBufferNoFull;
    }
    else
    {
        return_value=kERROR;
        fifo->state=kFIFOBufferEmpty;
    }

    return return_value;
}

/***********************************************
* @brief : 查询队列里面第几个元素
* @param : SuFIFO *fifo: 队列变量
*          uint32_t dat: 需要存储的数据
*          uint32_t num: 查询第几个数据
* @return: 函数执行是否成功
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Search_Element(SuFIFO *fifo, void *dat, uint32_t num)
{
    SuFIFOState return_value = kSuccess;
    if (fifo->state==kFIFOBufferNull || fifo->state==kFIFOBufferEmpty || fifo->length<num)
    {
        return_value = kERROR;
    }
    else
    {
        switch(fifo->type)
        {
            case kFIFOData8bit:
                *((uint8_t *)dat) = ((uint8_t *)fifo->buffer)[(fifo->front+num)%fifo->max];
                break;
            case kFIFOData16bit:
                *((uint16_t *)dat) = ((uint16_t *)fifo->buffer)[(fifo->front+num)%fifo->max];
                break;
            case kFIFOData32bit:
                *((uint32_t *)dat) = ((uint32_t *)fifo->buffer)[(fifo->front+num)%fifo->max];
                break;
        }
    }
    return return_value;
}

/***********************************************
* @brief : 队列清空
* @param : SuFIFO *fifo: 队列变量
* @return: 函数执行是否成功
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Clear(SuFIFO *fifo)
{
    SuFIFOState return_value = kSuccess;
    memset(fifo->buffer,0,fifo->max*fifo->type);
    fifo->front             = 0;
    fifo->rear              = 0;
    fifo->size              = fifo->max;
    fifo->length            = 0;
    fifo->state             = kFIFOBufferEmpty;
    return return_value;
}
