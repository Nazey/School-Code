#include <stdio.h>

int main(void){
    int group_size=0, unique=-1, dupe=0, count=0;
    scanf("%d",&group_size);
    int arr[group_size];
    
    for(int i=0; i<group_size; i++){
        scanf("%d", &arr[i]);
    }
    
    for(int i=0; i<group_size; i++){
        dupe=0;
        for(int k=0; k<group_size; k++){
            if(arr[i]==arr[k] && i!=k){
                dupe=1;
            } 
        }
        if(dupe==0 && arr[i]>arr[unique]){
            unique=i;
        }
    }
    if(unique==-1){
        printf("none");
    }
    else {
     
     printf("%d\n", unique+1);
    }
    return 0;
}