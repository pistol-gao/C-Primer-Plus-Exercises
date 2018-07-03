//
// Created by pistol gao on 2018/7/4.
//
#include <stdio.h>
#include <stdlib.h>

void main(int argc,char* argv[])
{
    int length;
    printf("input array length");
    scanf("%d",&length);
    int * array;
    array = (int*)calloc(length, sizeof(int));
    for (int i = 0; i < length; i++) {
        printf("input %d's value:", i);
        scanf("%d",array + i);
    }
    for (int j = 0; j < length; ++j) {
        printf("%d\n", array[j]);
    }
    free(array);
}