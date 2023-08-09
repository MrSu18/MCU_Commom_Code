#ifndef _SU_COMMON_FIFO_H
#define	_SU_COMMON_FIFO_H

#include "su_common_typedef.h"

typedef enum SuFIFOState
{
    kFIFOSuccess=0,
    kFIFOBufferNull,//�ڴ治����
    kFIFOBufferFull,//����
    kFIFOBufferEmpty,//�ӿ�
}SuFIFOState;

typedef enum SuFIFODataType
{
    kFIFOData8bit=0,
    kFIFOData16bit,
    kFIFOData32bit,
}SuFIFODataType;

typedef struct SuFIFO
{
    SuFIFODataType  type;         // ��������
    void            *buffer;      // ����ָ��
    int             front;        // ����ͷָ�� ����ָ��յĻ���
    int             rear;         // ����βָ�� ����ָ��ǿջ��棨����ȫ�ճ��⣩
    uint32_t        size;         // ����ʣ���С
    uint32_t        length;       // ���泤��
    uint32_t        max;          // �����ܴ�С
}SuFIFO;

SuFIFOState FIFO_Init (SuFIFO *fifo, SuFIFODataType type, void *buffer_addr, uint32_t size);
SuFIFOState FIFO_Write_Element (SuFIFO *fifo, uint32_t dat);
SuFIFOState FIFO_Read_Element(SuFIFO *fifo, void *dat);

#endif
