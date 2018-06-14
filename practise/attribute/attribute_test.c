//
// Created by gaoqingrui on 2018/6/14.
//
/**
 GNU C 的一大特色就是__attribute__ 机制。__attribute__ 可以设置函数属性（Function Attribute ）、变量属性（Variable Attribute ）和类型属性（Type Attribute ）。

__attribute__ 书写特征是：__attribute__ 前后都有两个下划线，并切后面会紧跟一对原括弧，括弧里面是相应的__attribute__ 参数。

__attribute__ 语法格式为：__attribute__ ((attribute-list))

其位置约束为：放于声明的尾部“ ；” 之前。


    aligned (alignment)
    该属性设定一个指定大小的对齐格式（以字节 为单位）

    packed
    使用该属性对struct 或者union 类型进行定义，设定其类型的每一个变量的内存约束。当用在enum 类型 定义时，暗示了应该使用最小完整的类型（it indicates that the smallest integral type should be used）。

 */
#include <stdio.h>
struct S {
    short b[3];
} __attribute__ ((aligned (8)));
struct S1 {
    short b[3];
};
struct unpacked_struct
{
    char c;
    int i;
};
struct packed_struct
{
    char c;
    int i;
}__attribute__ ((__packed__));
int main(int argc, char *argv[])
{
    struct S s;
    s.b[0] = 1;
    s.b[1] = 2;
    s.b[2] = 3;
    printf("sizeof short:%d\n", sizeof(short)); //2
    printf("sizeof s:%d\n",sizeof(s)); // 8
    printf("%d,%d,%d\n",s.b[0],s.b[1],s.b[2]);
    struct S1 s1;
    printf("sizeof s1:%d\n",sizeof(s1)); // 6


    printf("sizeof unpacked_struct: %d\n",sizeof(struct unpacked_struct)); //  8
    printf("sizeof packed_struct: %d\n",sizeof(struct packed_struct)); //  5
}
