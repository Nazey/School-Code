#include <stdio.h>

int main(void){
    int num=0, distinct=0, temp=0;
    int arr[10]; int arr2[10];
    
    for(int i=0; i<10; i++){
        scanf("%d",&num);
        arr[i]=num%42;
        arr2[i]=-1;
    }
    for(int i=0; i<10; i++){ 
        temp=0;
        for(int k=0; k<10; k++){ 
            if(arr[i]!=arr2[k]){
                temp++;
            }
     
        }
        if(temp==10){
            arr2[i]=arr[i];
        }
    }
    for(int i=0; i<10; i++){
        if(arr2[i]!=-1){
            distinct++;
        }
    }
   
    printf("%d",distinct);
    
    return 0;
}