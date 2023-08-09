#ifndef _SU_COMMON_FIFO_H
#define	_SU_COMMON_FIFO_H

/*FIFO�Ļ�����ʽΪ:ѭ������-*/

#include "su_common_typedef.h"

typedef enum SuFIFOState
{
    kFIFOBufferNull=0,//�ڴ治����
    kFIFOBufferNoFull,//������(δ��)
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
    SuFIFOState     state;        //����״̬
}SuFIFO;

FunctionStatus FIFO_Init (SuFIFO *fifo, SuFIFODataType type, void *buffer_addr, uint32_t size);
FunctionStatus FIFO_Write_Element (SuFIFO *fifo, uint32_t dat);//���
FunctionStatus FIFO_Out_Element(SuFIFO *fifo, void *dat);//����
FunctionStatus FIFO_Search_Element(SuFIFO *fifo, void *dat, uint32_t num);//��ѯ��������ڼ���Ԫ��

#endif
