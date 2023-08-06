#ifndef _SU_COMMON_FUNCTION_H
#define	_SU_COMMON_FUNCTION_H

/***********************************************
* @brief : ��x���������޷�
* @param : x:��Ҫ�޷��ı���
*          low:����
*          int: ����
* @return: ��
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
* @brief : ���a,b��Сֵ
* @param : a,b
* @return: ��
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
* @brief : ���a,b���ֵ
* @param : a,b
* @return: ��
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
