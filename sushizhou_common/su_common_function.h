#ifndef _SU_COMMON_FUNCTION_H
#define	_SU_COMMON_FUNCTION_H

/***********************************************
* @brief : 给x设置上下限幅
* @param : x:需要限幅的变量
*          low:下限
*          int: 上限
* @return: 无
* @date  : 2023.8.6
* @author: sushizhou
************************************************/
int Limit_Int(int x, int low, int up)
{
    return x > up ? up : x < low ? low : x;
}
float Limit_Float(float x, float low, float up)
{
    return x > up ? up : x < low ? low : x;
}

/***********************************************
* @brief : 获得a,b最小值
* @param : a,b
* @return: 无
* @date  : 2023.8.6
* @author: sushizhou
************************************************/
int Min_Int(int a,int b)
{
    return a<b?a:b;
}
float Min_Float(float a,float b)
{
    return a<b?a:b;
}

/***********************************************
* @brief : 获得a,b最大值
* @param : a,b
* @return: 无
* @date  : 2023.8.6
* @author: sushizhou
************************************************/
int Max_Int(int a,int b)
{
    return a>b?a:b;
}
float Max_Float(float a,float b)
{
    return a>b?a:b;
}

#endif
