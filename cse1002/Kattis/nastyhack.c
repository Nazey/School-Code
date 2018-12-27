#include <stdio.h>

int main(void){
    int n=0, r=0, e=0, c=0;
    
    scanf("%d",&n);
    
    for(int i=0; i<n; i++){
        r=0;e=0;c=0;
        scanf("%d%d%d",&r,&e,&c);   
        if((e-c)>r){
            printf("advertise\n");
        } else if((e-c)<r){
            printf("do not advertise\n");
        } else{
            printf("does not matter\n");
        }
        
    }
    
    
    return 0;
}