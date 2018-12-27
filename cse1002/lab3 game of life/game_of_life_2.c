/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: game_of_life_2
 */
 
#include <stdio.h>
#include <stdlib.h>

//every time update_board is run, the cells are evaluated and set to their proper states 
void update_board(int length, int arr1[length][length]);

//prints result to output.csv file
void print_to_file(int length, int arr1[length][length]);

//prints board state to console
void print_board(int length, int arr1[length][length]);

int main(int argc, char *argv[]){
    
    //taking in command line arguments, setting up the file
    int num_times_run = atoi(argv[2]);
	FILE *fin = fopen(argv[1], "r");
    int length = 1;
   
    //gets the length by the amount of characters in the first line of the file
    //divides it by 2 to get the dimensions of the matrix
    while(getc(fin)!='\n'){
         length++;
    }
    length/=2;
   
    //closing and opening the file again to start from the beginning of the file
    //since this is how to make the program work with the nature of getc()
    fclose(fin);
    fin = fopen(argv[1], "r");
   
    int arr[length][length];
    char temp;
    
    //storing values inside newly created array
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
    //updates board for however many times specified by user/command line arguments
    //also prints out each iteration of the board

    for(int i=0; i<=num_times_run; i++){
        if(i==0){
           system("clear");           
           printf("Input\n");
           print_board(length, arr); 
           system("clear");           
        } else {
            printf("Iteration %d\n", i);
            update_board(length, arr);
            print_board(length, arr);          
            system("clear");
        }
        
    }
    fclose(fin);
    print_to_file(length, arr);
}

void update_board(int length, int arr1[length][length]){
    
    //temporary array, stores new board state
    int arr2[length][length];
    int num_neighbors=0;
    
    //setting temp array to all 0s
    for(int p=0; p<length; p++){
        for(int q=0; q<length; q++){
            arr2[p][q]=0;
        }
    }
    
    //checks to see if the spot is valid, then if it equals 1, adds 1 to num_neighbors
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){          
            if((k+1)<length && arr1[i][k+1]==1){
                num_neighbors++;                
            }
            if((k-1)>=0 && arr1[i][k-1]==1){
                num_neighbors++;                   
            }
            if((i+1)<length && arr1[i+1][k]==1){
                num_neighbors++;
            }
            if((i-1)>=0 && arr1[i-1][k]==1){
                num_neighbors++;
            }
            if((k+1)<length && (i+1)<length && arr1[i+1][k+1]==1){
                num_neighbors++;
            }
            if((k+1)<length && (i-1)>=0 && arr1[i-1][k+1]==1){
                num_neighbors++;
            }
            if((k-1)>=0 && (i+1)<length && arr1[i+1][k-1]==1){
                num_neighbors++;                  
            }
            if((k-1)>=0 && (i-1)>=0 && arr1[i-1][k-1]==1){
                num_neighbors++;                    
            }
               
            //checking and assigning new dead or alive states
            if(arr1[i][k]==1 && num_neighbors<2){
                arr2[i][k]=0;
            } else if(arr1[i][k]==1 && num_neighbors>3){
                arr2[i][k]=0;
            } else if(arr1[i][k]==1 && (num_neighbors==3 || num_neighbors==2)){
                arr2[i][k]=1;
            } else if(arr1[i][k]==0 && num_neighbors==3){
                arr2[i][k]=1;
            }            
            num_neighbors=0;
        }
    }
    
    //setting the original array to the temporary one
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
            arr1[i][k]=arr2[i][k]; 
        }        
    }

}
void print_board(int length, int arr1[length][length]){
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
            if(arr1[i][k]==1){
                printf("|o");
            } else {
                printf("| ");
            }            
        }
        printf("|\n");
    }
}
void print_to_file(int length, int arr1[length][length]){
    FILE *fout = fopen("output.csv", "w");
    
    for(int i=0; i<length; i++){
        for(int k=0; k<length; k++){
            if(arr1[i][k]==1 && k==length-1){
                fprintf(fout, "1");                                                 
            } else if(arr1[i][k]==1 && k<length-1){
                fprintf(fout, "1;");                                                 
            } else if(k==length-1){
                fprintf(fout, "0");
            } else {
                fprintf(fout, "0;");
            }    
        }
        fprintf(fout, "\n");
    }
    
}