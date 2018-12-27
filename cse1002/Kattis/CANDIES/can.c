#include <stdio.h>
#include <string.h>

int main(void){
    int count=0;
    
    scanf("%d", &count);
   // printf("\n");
    char arr1[count][6];
    int n=0; long long sum=0; long long test=0; 
    
    for(int i=0; i<count; i++){
        n=0; sum=0; test=0;
       
       scanf("%d", &n);
       for(int k=0; k<n; k++){
           scanf("%lld", &test);
           sum+=test;
       }
       if(sum>n && sum%n==0){
           strcpy(arr1[i], "YES");
       } else {
           strcpy(arr1[i], "NO");
       }
     //  printf("\n");
    }
    
    for(int l=0; l<count; l++){
        printf("%s\n", arr1[l]);
    }

    
    return 0;
}