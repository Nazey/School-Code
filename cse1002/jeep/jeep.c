/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu
 * Course: CSE 1002, Section 02, Spring 2018 
 * Project: jeep
 */
 
#include <stdio.h>

int main(void){
    int n=1, count=0;
    double cap=0, rate=0, distance=0, can_distance=0;
    double final[127];
    
    while(n!=0){
        n=1; cap=0; rate=0; can_distance=0; distance=0;
        scanf(" %d", &n);
        if(n==0){
            break;
        }
        scanf(" %lf %lf", &cap, &rate);       
        distance=((cap*100)/rate);     
        
        for(double i=1; i<n; i++){
            can_distance+=(1/((2*i)-1));      
        }        
        
        distance=can_distance*distance;
        distance+=((cap*100)/rate);
        final[count]=distance;
        
        count++;
    }
    
    for(int i=0; i<count; i++){
        printf("%d. Distance is %.2lf Kilometers", i+1, final[i]);
        printf("\n");
    }
    return 0;
}
