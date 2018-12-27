#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){
    int random = 0; int len = 99999; int start, end;
    int array[len];
    start = 0; 
    end = len;
    clock_t start_t, end_t;
    double total_t;
    
    srand(time(NULL));
    
    start_t = clock();
    for(int i=0; i<len; i++){
        random = rand()%10;
        array[i] = random;
    }
    end_t = clock();
    
    
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Cpu time for adding %d elements: %lf\n", len, total_t);
    
    start_t = end_t - start_t;
    end_t = end_t - start_t;
    
    start_t = clock();
    for(int i=0; i<len; i++){
      array[i] = -1;
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Cpu time for deleting %d elements: %lf\n", len, total_t);
    
    start_t = end_t - start_t;
    end_t = end_t - start_t;
    
    start_t = clock();
    while (start < end){        
        int temp = array[start]; 
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    } 
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Cpu time for reversing %d elements: %lf\n", len, total_t);
}