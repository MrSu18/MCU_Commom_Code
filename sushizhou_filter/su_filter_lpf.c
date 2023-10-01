#include "su_filter_lpf.h"

/***********************************************
* @brief : һ�׵�ͨ�˲�����ʼ��
* @param : SuFirstorderLPF *lpf: һ�׵�ͨ�˲����ṹ��
*          float a:   �˲�ϵ��a~[0,1]
* @return: FunctionStatus a�Ƿ�Խ��
* @date  : 2023.10.1
* @author: sushizhou
************************************************/
FunctionStatus First_Order_LPF_Init(SuFirstorderLPF *lpf,float a)
{
    if (a<0 || a>1)
    {
        return kERROR;
    }
    lpf->now_data=0;
    lpf->last_data=0;
    lpf->out_data=0;
    lpf->a=a;
    return kSuccess;
}

/***********************************************
* @brief : һ�׵�ͨ�˲���
* @param : SuFirstorderLPF *lpf: һ�׵�ͨ�˲����ṹ��
*          float in_data:   ��Ҫ�˲�������
* @return: ��
* @date  : 2023.10.1
* @author: sushizhou
************************************************/
void First_Order_LPF(SuFirstorderLPF *lpf,float in_data)
{
    lpf->now_data=in_data;
    lpf->out_data=lpf->a*lpf->now_data+(1-lpf->a)*lpf->last_data;
    lpf->last_data=lpf->now_data;
}
