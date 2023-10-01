#ifndef _SU_FILTER_LPF_H
#define	_SU_FILTER_LPF_H
/*��ͨ�˲���*/
#include "su_common_typedef.h"

typedef struct SuFirstorderLPF
{
    float    now_data;//����
    float    last_data;//�洢��һ��
    float    out_data;//���
    float    a;// a~[0,1] out=in_data*a+(1-a)*last_data
}SuFirstorderLPF;

FunctionStatus First_Order_LPF_Init(SuFirstorderLPF *lpf,float a);//һ�׵�ͨ�˲�����ʼ��
void First_Order_LPF(SuFirstorderLPF *lpf,float in_data);//һ�׵�ͨ�˲�

#endif
