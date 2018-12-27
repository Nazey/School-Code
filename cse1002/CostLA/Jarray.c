#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printarray(int size, int a[size]){
    for(int i=0; i<size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}
int josephus(int size, int a[size]);

int main(void){
   clock_t start_t, end_t;
   double total_t;
   
   int array[130000];
   for(int i=0; i<130000; i++){
       array[i] = 1;
   }
   start_t = clock();
   printf("%d\n",josephus(130000, array));
   end_t = clock();
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("cpu time: %lf\n", total_t);
   
   
   return 0;
}

int josephus(int size, int array[size]){
    int val = -1, i = 0;
    while(1){
        while(array[i] == 0){
            i++;
            if(i == size){
                i = 0;
            }
        }
        val = i;
        i++;
        if(i == size){
            i = 0;
        }
        while(array[i] == 0){
            i++;
            if(i == size){
                i = 0;
            }
        }
        if(val == i){
            return val;
        }
        array[i] = 0;
        
        
    }
    return i;
}

