//
// Created by gaoqingrui on 2018/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct PString {
    char *chars;
    int (*length)();
} PString;

int length(PString *self) {
    return strlen(self->chars);
}

PString *initializeString(int n) {
    PString *str = malloc(sizeof(PString));

    str->chars = malloc(sizeof(char) * n);
    str->length = length;
    str->chars[0] = '\0';

    return str;
}

int main() {
    PString *p = initializeString(30);
    strcpy(p->chars, "Hello");
    printf("\n%d", p->length(p));
    return 0;
}