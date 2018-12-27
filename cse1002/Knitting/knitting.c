/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: knitting.c
 */
 
 #include <stdio.h>
 
 int main(void){
    int n, m, k, temp=0;
    
    
    while(n!=0 && m!=0 && k!=0){
        printf("Enter n m and k \n");
        scanf(" %d %d %d", &n, &m, &k);
        printf("Enter the pattern of %d integers\n",k);
        temp=0;
        int arr1[k];
        int final_arr[m];
        
        for(int i=0; i<k; i++){
            scanf("%d", &arr1[i]);
        }
        
        for(int i=0; i<m; i++){
            if(i==0){
               final_arr[i]=n;
            } else {
                final_arr[i]=final_arr[i-1]+arr1[temp];
                temp++;
            }
            if(temp==k){
                temp=0;
            }
            
            
        }
        temp = 0;
        for(int i=0; i<m; i++){
            temp+=final_arr[i];
        }
        
        printf("%d\n",temp);
    
    }
    
 }
 