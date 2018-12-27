#include <stdio.h>
#include <limits.h>

int main(void){
    
    int max=INT_MIN, min=INT_MAX, range=0, num=0, temp=0; 
    int arr2[10][3];
    for(int o=0; o<10; o++){
        
        max=INT_MIN; min=INT_MAX; range=0; num=0; 
        scanf(" %d", &num);
        int arr[num];
    
        for(int i=0; i<num; i++){
            scanf(" %d", &arr[i]);
            if(arr[i]>max){
                max=arr[i];
            }
            if(arr[i]<min){
                min=arr[i];
            }
        }
    
        range = max-min;
        arr2[temp][0]=min;
        arr2[temp][1]=max;
        arr2[temp][2]=range;
        //printf("\nCase %d: %d %d %d", temp+1, min, max, range);
        temp++;
    }
    for(int h=0; h<temp; h++){
        printf("Case %d: %d %d %d\n", h+1, arr2[h][0], arr2[h][1], arr2[h][2]);
        
    }
    return 0;
}