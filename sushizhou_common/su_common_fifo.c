#include "su_common_fifo.h"
#include "string.h"

/***********************************************
* @brief : ��ͷ�ƶ�(һ����˵��Ԫ�س���)
* @param : SuFIFO *fifo: ��Ҫ��ʼ���Ķ��б���
*          int offset: ��ǰ���������ƶ��ľ���
* @return: void
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
static void FIFO_Front_Offset (SuFIFO *fifo, int offset)
{
    fifo->front=(fifo->front+offset)%fifo->max;
}

/***********************************************
* @brief : ��β�ƶ�(һ����˵��Ԫ�����)
* @param : SuFIFO *fifo: ��Ҫ��ʼ���Ķ��б���
*          int offset: ��ǰ���������ƶ��ľ���
* @return: void
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
static void FIFO_Rear_Offset (SuFIFO *fifo, int offset)
{
    fifo->rear=(fifo->rear+offset)%fifo->max;
}

/***********************************************
* @brief : ���л�������ʼ��
* @param : SuFIFO *fifo: ��Ҫ��ʼ���Ķ��б���
*          SuFIFODataType type: �洢����������
*          void *buffer_addr�������ĸ���ַ
*          uint32_t size: ��С
* @return: ��ʼ����״̬
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
* @brief : �������
* @param : SuFIFO *fifo: ���б���
*          uint32_t dat: ��Ҫ�洢������
* @return: ��ӵ�״̬
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
SuFIFOState FIFO_Write_Element (SuFIFO *fifo, uint32_t dat)
{
    SuFIFOState return_value = kFIFOSuccess;
    if(1 <= fifo->size)                                                     // ʣ��ռ��㹻װ�±�������
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
        fifo_rear_offset(fifo, 1);                                          // ͷָ��ƫ��
        fifo->size -= 1;                                                    // ������ʣ�೤�ȼ�С
        fifo->length+=1;                                                    // ���г�������
    }
    else
    {
        return_value = kFIFOBufferFull;
    }
    return return_value;
}

/***********************************************
* @brief : ���ݳ���
* @param : SuFIFO *fifo: ���б���
*          uint32_t dat: ��Ҫ�洢������
* @return: ��ӵ�״̬
* @date  : 2023.8.8
* @author: sushizhou
************************************************/
SuFIFOState FIFO_Read_Element(SuFIFO *fifo, void *dat)
{
    SuFIFOState return_value = kFIFOSuccess;
}
