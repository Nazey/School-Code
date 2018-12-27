#include <stdio.h>
#include <stdlib.h>

typedef struct {
int a;
double b;
} TWONUMS;

int main(void){
    TWONUMS *t = (TWONUMS *) malloc(sizeof(TWONUMS));
    t->a=4;
    printf("t->a: %d", t->a);
    return 0;
}