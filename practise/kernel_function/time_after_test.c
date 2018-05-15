//
// Created by gaoqingrui on 2018/5/15.
//
#include <stdio.h>
#include <limits.h>
#define typecheck(type,x) \
({        type __dummy; \
        typeof(x) __dummy2; \
        (void)(&__dummy == &__dummy2); \
        1; \
})
// 此函数防止jaffies溢出导致溢出后，导致溢出后的值小于溢出前的值。
//技巧 parse unsigned long to signed long，溢出前未负数,溢出后未正数，但不要太大
#define time_after(a,b) \
(typecheck(unsigned long,a) && \
typecheck(unsigned long,b) && \
((long)(b) -(long)(a) < 0))

int main(int argc,char * args[]){
        unsigned long a = ULONG_MAX,b=1;
        printf("a=%u,b=%u,time_after(a,a+b) = %d",a,b,time_after(a,a+b)); // 适用
        a = ULONG_MAX;
        b = ULONG_MAX/2+1;
        printf("a=%u,b=%u, time_after(a,a+b)=%d\n",a, b, time_after(a,a+b));  //不适用

}
