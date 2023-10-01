#include "su_filter_lpf.h"

/***********************************************
* @brief : 一阶低通滤波器初始化
* @param : SuFirstorderLPF *lpf: 一阶低通滤波器结构体
*          float a:   滤波系数a~[0,1]
* @return: FunctionStatus a是否越界
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
* @brief : 一阶低通滤波器
* @param : SuFirstorderLPF *lpf: 一阶低通滤波器结构体
*          float in_data:   需要滤波的数据
* @return: 空
* @date  : 2023.10.1
* @author: sushizhou
************************************************/
void First_Order_LPF(SuFirstorderLPF *lpf,float in_data)
{
    lpf->now_data=in_data;
    lpf->out_data=lpf->a*lpf->now_data+(1-lpf->a)*lpf->last_data;
    lpf->last_data=lpf->now_data;
}
