#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printarray(int a[10]){
    for(int i=0; i<10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void){
    int position, swap;
    int random, total = 11000;
    int array[total];
    clock_t start_t, end_t;
    double total_t;
    srand(time(NULL));
    for(int i=0; i<total; i++){
        random = rand();
        array[i] = random;
    }
    start_t = clock();

    for (int c = 0 ; c < total ; c++ ){
        position = c;
        for (int d = c + 1 ; d < total ; d++ ){
            if ( array[position] > array[d] )
                position = d;
        }
        if (position != c ){
            swap = array[c];
            array[c] = array[position];
            array[position] = swap;
        } 
   }
   end_t = clock();
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("cpu time: %lf\n", total_t);
   printarray(array);
   return 0;
}
