#include <stdio.h>

void MergeSort(int array[10], int p, int r);

void Merge(int array[10], int p, int q, int r);

int main(void){
    printf("Enter the array of numbers ");
    int arr[10];
    int max=0;
    
    while(1){
        scanf("%d", &arr[max]);
        if(arr[max] == -1){
            max--;
            break;
            
        }
        max++;
    }
    for(int p=0; p<=max; p++)
        printf("%d ",arr[p]);
    
    printf("\n");
    
    MergeSort(arr, 0, max);
    
    for(int p=0; p<=max; p++)
        printf("%d ",arr[p]);
    return 0;
}

void MergeSort(int array[10], int p, int r){
    int q=0;
    if(p<r){
        q=(p+r)/2;
        MergeSort(array, p, q);
        MergeSort(array, q+1, r);
        Merge(array, p, q, r);
    }

}

void Merge(int array[10], int p, int q, int r){
    int array2[10];
    int k=p;
    int i=k;
    int j = q+1;

    while(i<=q && j<=r){
        if(array[i] <= array[j]){
            array2[k++] = array[i++];
        } else {
            array2[k++] = array[j++];
        }
    }
    while(i<=q){       
        array2[k++] = array[i++];

    }
    while(j<=r){
        array2[k++] = array[j++];    
    }
    for(i=p; i<=r; i++){
        array[i] = array2[i];
    }
}
