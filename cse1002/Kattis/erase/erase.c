#include <stdio.h>
#include <string.h>

int main(void){
    int iterations=0;
    char num_1[1000], num_2[1000], temp[1000];
    scanf(" %d",&iterations);
    scanf(" %s",num_1);
    scanf(" %s",num_2);
    for(int k=0; k<iterations; k++){
        for(int i=0; i<strlen(num_1); i++){
            if(num_1[i]=='0'){
                num_1[i]='1';
            } else {
                num_1[i]='0';
            }
        }
    }
    if((strcmp(num_1,num_2)==0)){
        printf("Deletion succeeded");
    }  else {
        printf("Deletion failed");
    }
    return 0;
}