#include <stdio.h>

int main(void){
    int n=0, s=0, t=0, temp=0, total=0, count=0;
    int arr[10];
    do {
        scanf("%d",&n);
        temp=0;total=0;
        for(int i=0; i<n; i++){
            scanf("%d%d",&s,&t);
            if(i==0){
                total+=(s*t);
                temp=t;
            } else {
                total+=s*(t-temp);
                temp=t;
            }
        }
        arr[count]=total;
        count++;
        
    }while(n!=-1);
    
    for(int i=0; i<count-1; i++){
        printf("%d miles\n",arr[i]);
    }
    
    return 0;
}