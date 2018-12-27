#include <stdio.h>

void QuickSort(int array[10], int low, int high);

void Swap(int* low, int* high);

void PrintArray(int arr[]);

int main(void){
    int a[10];
    printf("Enter values for the array ");
    for(int i=0; i<10; i++){
        scanf("%d",&a[i]);
    }
    PrintArray(a);
    QuickSort(a, 0, 9);
    PrintArray(a);
    return 0;
}

void QuickSort(int array[10], int low, int high){
    int l=low, h=high, pivot=low;
    while(l<h){
       while(array[l]<=array[pivot] && l < high){
           l++;
       }
       while(array[h]>array[pivot]){
           h--;
       } 
       if(l<h){
        Swap(&array[l], &array[h]);
       }
    
    Swap(&array[pivot], &array[h]);
    QuickSort(array, low, h-1);
    QuickSort(array, h+1, high);
    }
}

void Swap(int* low, int* high){
    int a=*low;
    *low=*high;
    *high=a;
}
void PrintArray(int arr[]){
    for(int i=0; i<10; i++){
       printf("%d ",arr[i]);
    }
    printf("\n");
}