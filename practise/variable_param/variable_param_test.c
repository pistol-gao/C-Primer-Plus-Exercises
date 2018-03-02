//
// Created by gaoqingrui on 2018/3/2.
//
#include <stdio.h>
#include <zconf.h>

static int SqSum(int n1, ...)
{
    /*定义保存函数参数的结构*/
    va_list arg_ptr;
    int nSqSum = 0, n = n1;
    /* va_start(arg_ptr, argN)：使参数列表指针arg_ptr指向函数参数列表中的第一个可选参数， 说明：argN是位于第一个可选参数之前的固定参数，（或者说，最后一个固定参数；…之前的一个参数），
     函数参数列表中参数在内存中的顺序与函数声明时的顺序是一致的。如果有一va函数的声明是void va_test(char a, char b, char c, …)，则它的固定参数依次是a,b,c，最后一个固定参数argN为c，因此就是va_start(arg_ptr, c)。*/
    va_start(arg_ptr, n1);
    while (n > 0)
    {
        nSqSum += (n * n);
        /* va_arg(arg_ptr, type)：返回参数列表中指针arg_ptr所指的参数，返回类型为type，并使指针arg_ptr指向参数列表中下一个参数。*/
        n = va_arg(arg_ptr, int);
    }
    /*va_end(arg_ptr)：清空参数列表，并置参数指针arg_ptr无效。 说明：指针arg_ptr被置无效后，可以通过调用va_start()、va_copy()恢复arg_ptr。
    每次调用va_start() / va_copy()后，必须得有相应的va_end()与之匹配。参数指针可以在参数列表中随意地来回移动，但必须在va_start() … va_end()之内。*/
     /*将ap置为NULL*/
    va_end(arg_ptr);
    return nSqSum;
}
void main(){
    int nSqSum = SqSum(3, 2, 5);
    printf("%d", nSqSum);
}
