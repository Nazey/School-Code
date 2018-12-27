/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: game-of-life-1
 */
 
#include <stdio.h>
#include <stdlib.h>

//must be command line arguments, address of file, number of iterations, print numb

void update_board(int length, int arr1[length][length]);

void print_board(int length, int arr1[length][length]);

void print_to_file(int length, int arr1[length][length]);

int main(int argc, char *argv[]){
    int num_times_run = atoi(argv[2]);
    printf("%d\n", num_times_run);
	FILE *fin = fopen(argv[1], "r");
    int length = 1;
   
    
    while(getc(fin)!='\n'){
         length++;
    }
    length/=2;
   
    fclose(fin);
    fin = fopen(argv[1], "r");
   
    int arr[length][length];
    char temp;
    
    for(int i=0; i<length; i++){
        int x = 0;
        for(int k=0; k<length*2; k++){ 
            temp = getc(fin);   
            if(temp=='0' || temp=='1'){
                arr[i][x] = temp-'0';
                x++;
            } 
        }
    }
    
    print_board(length, arr);
    for(int i=0; i<num_times_run; i++){
        update_board(length, arr);
    }
    printf("\n");
    print_board(length, arr);
    fclose(fin);
    print_to_file(length, arr);
}

void update_board(int length, int arr1[length][length]){
    int arr2[length][length];
    int num_neighbors=0;
    int pp=1;
    for(int p=0; p<length; p++){
        for(int q=0; q<length; q++){
            arr2[p][q]=0;
        }
    }
    
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
            printf("Iteration %d: \n",pp);
            if((k+1)<6 && arr1[i][k+1]==1){
                num_neighbors++;  
                printf("NUM 1 = %d\n",arr1[i][k+1]);                    
            }
            if((k-1)>=0 && arr1[i][k-1]==1){
                num_neighbors++;
                printf("NUM 2 = %d\n",arr1[i][k-1]);                    
            }
            if((i+1)<6 && arr1[i+1][k]==1){
                num_neighbors++;
                printf("NUM 3 = %d\n",arr1[i+1][k]);                    
            }
            if((i-1)>=0 && arr1[i-1][k]==1){
                num_neighbors++;
                printf("NUM 4 = %d\n",arr1[i-1][k]);                    
            }
            if((k+1)<6 && (i+1)<6 && arr1[i+1][k+1]==1){
                num_neighbors++;
                printf("NUM 5 = %d\n",arr1[i+1][k+1]);                    
            }
            if((k+1)<6 && (i-1)>=0 && arr1[i-1][k+1]==1){
                num_neighbors++;
                printf("NUM 6 = %d\n",arr1[i-1][k+1]);                    
            }
            if((k-1)>=0 && (i+1)<6 && arr1[i+1][k-1]==1){
                num_neighbors++;
                printf("NUM 7 = %d\n",arr1[i+1][k-1]);                    
            }
            if((k-1)>=0 && (i-1)>=0 && arr1[i-1][k-1]==1){
                num_neighbors++;
                printf("NUM 8 = %d\n",arr1[i-1][k-1]);                    
            }
                       
            if(arr1[i][k]==1 && num_neighbors<2){
                arr2[i][k]=0;
                printf("NEIGHBORS < 2 AND ALIVE\n");
            } else if(arr1[i][k]==1 && num_neighbors>3){
                arr2[i][k]=0;
                printf("NEIGHBORS > 3 AND ALIVE\n");
            } else if(arr1[i][k]==1 && (num_neighbors==3 || num_neighbors==2)){
                arr2[i][k]=1;
                printf("NEIGHBORS = 2 or 3\n");
            } else if(arr1[i][k]==0 && num_neighbors==3){
                arr2[i][k]=1;
                printf("NEIGHBORS = 3 AND DEAD\n");
            }
            
        printf("Num_neighbors = %d\n",num_neighbors);
        printf("arr1[i][k] = %d arr2[i][k] = %d \n",arr1[i][k], arr2[i][k]);    
        printf("\n");
        num_neighbors=0;
        pp++;
        }
    
    }
  for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
         arr1[i][k]=arr2[i][k]; 
        }        
    }

}

void print_board(int length, int arr1[length][length]){
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
           printf("%d ",arr1[i][k]);
        }
        printf("\n");
    }
    
}
void print_to_file(int length, int arr1[length][length]){
    FILE *fout = fopen("output.csv", "w");
   
   fprintf(fout, "The final position:\n");
    
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
            if(arr1[i][k]==1){
                fprintf(fout, "%d %d\n", i+1,k+1);                                                 
            }          
        }
    }
    
}