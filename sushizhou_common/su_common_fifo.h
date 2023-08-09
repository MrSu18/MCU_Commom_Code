#ifndef _SU_COMMON_FIFO_H
#define	_SU_COMMON_FIFO_H

/*FIFO的缓存形式为:循环队列-*/

#include "su_common_typedef.h"

typedef enum SuFIFOState
{
    kFIFOBufferNull=0,//内存不存在
    kFIFOBufferNoFull,//队列满(未空)
    kFIFOBufferFull,//队满
    kFIFOBufferEmpty,//队空
}SuFIFOState;

typedef enum SuFIFODataType
{
    kFIFOData8bit=0,
    kFIFOData16bit,
    kFIFOData32bit,
}SuFIFODataType;

typedef struct SuFIFO
{
    SuFIFODataType  type;         // 数据类型
    void            *buffer;      // 缓存指针
    int             front;        // 缓存头指针 总是指向空的缓存
    int             rear;         // 缓存尾指针 总是指向非空缓存（缓存全空除外）
    uint32_t        size;         // 缓存剩余大小
    uint32_t        length;       // 缓存长度
    uint32_t        max;          // 缓存总大小
    SuFIFOState     state;        //队列状态
}SuFIFO;

FunctionStatus FIFO_Init (SuFIFO *fifo, SuFIFODataType type, void *buffer_addr, uint32_t size);
FunctionStatus FIFO_Write_Element (SuFIFO *fifo, uint32_t dat);//入队
FunctionStatus FIFO_Out_Element(SuFIFO *fifo, void *dat);//出队
FunctionStatus FIFO_Search_Element(SuFIFO *fifo, void *dat, uint32_t num);//查询队列里面第几个元素

#endif
