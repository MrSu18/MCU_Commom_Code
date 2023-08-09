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
* @return: ����ִ���Ƿ�ɹ�
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
* @brief : �������
* @param : SuFIFO *fifo: ���б���
*          uint32_t dat: ��Ҫ�洢������
* @return: ����ִ���Ƿ�ɹ�
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Write_Element (SuFIFO *fifo, uint32_t dat)
{
    //ѭ��������Ӳ���
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
    FIFO_Rear_Offset(fifo, 1);// ������ζ��еĶ�β����Ҫ���ӵģ����յ�����Ϣ���ܱ�����
    SuFIFOState return_value = kSuccess;
    // �ж�һ�¸÷��ص�״̬
    if(1 < fifo->size)//ʣ�೤�Ȳ��ܵ���1��Ҫ�տ�һ����ѭ������ѭ��
    {
        //������л�û����ͷ�Ͳ��ø��ű�
        fifo->size -= 1; // ������ʣ�೤�ȼ�С
        fifo->length+=1; // ���г�������
        if (fifo->length>0) fifo->state = kFIFOBufferNoFull;//���г��ȴ���0����û���Ͷ���δ��״̬
        else                fifo->state = kFIFOBufferEmpty;//���г���Ϊ0��ն���״̬
    }
    else
    {
        //������������ӣ���ͷҲҪ��������������ѭ������
        FIFO_Front_Offset(fifo, 1);
        fifo->state = kFIFOBufferFull;
    }
    return return_value;
}

/***********************************************
* @brief : ���ݳ���
* @param : SuFIFO *fifo: ���б���
*          uint32_t dat: ��Ҫ�洢������
* @return: ����ִ���Ƿ�ɹ�
* @date  : 2023.8.10
* @author: sushizhou
************************************************/
FunctionStatus FIFO_Out_Element(SuFIFO *fifo, void *dat)
{
    SuFIFOState return_value = kSuccess;
    //����Ҫ������෴������״̬���ӣ���Ϊ��ѭ���������������һֱ��ģ����ǳ��ӣ�������˾Ͳ��ܳ���
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
        fifo->size+=1;//���û�������
        fifo->length-=1;//���г��ȼ�С
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
* @brief : ��ѯ��������ڼ���Ԫ��
* @param : SuFIFO *fifo: ���б���
*          uint32_t dat: ��Ҫ�洢������
*          uint32_t num: ��ѯ�ڼ�������
* @return: ����ִ���Ƿ�ɹ�
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
* @brief : �������
* @param : SuFIFO *fifo: ���б���
* @return: ����ִ���Ƿ�ɹ�
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
