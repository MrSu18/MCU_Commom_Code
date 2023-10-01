#ifndef _SU_FILTER_LPF_H
#define	_SU_FILTER_LPF_H
/*低通滤波器*/
#include "su_common_typedef.h"

typedef struct SuFirstorderLPF
{
    float    now_data;//输入
    float    last_data;//存储上一次
    float    out_data;//输出
    float    a;// a~[0,1] out=in_data*a+(1-a)*last_data
}SuFirstorderLPF;

FunctionStatus First_Order_LPF_Init(SuFirstorderLPF *lpf,float a);//一阶低通滤波器初始化
void First_Order_LPF(SuFirstorderLPF *lpf,float in_data);//一阶低通滤波

#endif
