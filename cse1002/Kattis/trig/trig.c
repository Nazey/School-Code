#include <stdio.h>

int main(void){
    long double c=3;
    signed long int length=0;
    int iteration=0, d_num, counter=1;
    while(scanf("%d", &iteration)>0){
        c=3;
        d_num=0;
        length=0;
    
        for(int i=0; i<iteration; i++){
            c=c/2;
            c=c*3;
        }
        
        printf("c:%d\n",c);
        length=c;
        
        while(length!=0){
            printf("length:%d\n", length);
            length=length/10;
            d_num++;
        }
        printf("Case %d: %d\n",counter, d_num);
        counter++;
    }
    return 0;
}
