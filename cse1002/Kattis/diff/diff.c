#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    long int x=0, y=0, AV=0;
    while(scanf("%li %li", &x, &y)>0){
        AV=fabs(x-y);
        printf("%li\n",AV);
        
        x=0; y=0; AV=0;

    }

    
    return 0;
}

