/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: percolation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//initializes grid to all blocked sites
void initialize_grid(int size, char temp_grid[size][size]);

//checks to see if grid percolates
int percolates(int size, char temp_grid[size][size]);

//chooses a random, non repeating point to set to an empty site
void choose_point(int size, char temp_grid[size][size]);

//prints grid
void print_grid(int size, char temp_grid[size][size]);

//calculates percolation threshold
double percolation_threshold(int size, char temp_grid[size][size]);

int main(int argc, char *argv[]){
    int size_of_grid=0, num_experiments=0;
    double threshold=0;
    sscanf(argv[1], "%d", &size_of_grid);
    sscanf(argv[2], "%d", &num_experiments);
    char grid[size_of_grid][size_of_grid];
    srand(time(NULL)); 
    
    
    for(int m=0; m<num_experiments; m++){
        initialize_grid(size_of_grid, grid);
        int p=0;
        while(p==0){
            choose_point(size_of_grid, grid);
            p=percolates(size_of_grid, grid);
        }
        threshold+=percolation_threshold(size_of_grid, grid);    
    }
    
    
    printf("The threshold is: %.1lf\n", threshold/num_experiments);
    printf("The last final grid is: \n");
    print_grid(size_of_grid, grid);
      
    return 0;
}

void initialize_grid(int size, char temp_grid[size][size]){
      for(int i=0; i<size; i++){
            for(int k=0; k<size; k++){
                temp_grid[i][k]='-';
            }
            
        }
}
//White cells: 1 empty space
//Black cells: - 
//Percolated element: + 
int percolates(int size, char temp_grid[size][size]){
    int percolates=0;   
    for(int k=0; k<size; k++){
        if(temp_grid[0][k]==' '){
            temp_grid[0][k]='+';
        }
    }    
     for(int i=1; i<size; i++){
        for(int k=0; k<size; k++){
            if(temp_grid[i][k]==' '){
                if(temp_grid[i-1][k]=='+'){
                    temp_grid[i][k]='+';
                }
                if(k>0 && temp_grid[i][k-1]=='+'){
                    temp_grid[i][k]='+';
                }
                if(k<size && temp_grid[i][k+1]=='+'){
                    temp_grid[i][k]='+';
                }
                
            }
        }    
    }
    for(int k=0; k<size; k++){
        if(temp_grid[size-1][k]=='+'){
            percolates=1;
        }
    }
    if(percolates==1){
        return 1;
    } else return 0;
    
}

void choose_point(int size, char temp_grid[size][size]){
    int x=0, y=0, different=0;
    while(different==0){
            x = rand()%size;
            y = rand()%size;
            if(temp_grid[x][y]==' '){
                different=0;
            } else{
                different=1;
                temp_grid[x][y]=' ';
            } 
        }

}

void print_grid(int size, char temp_grid[size][size]){
    for(int i=0; i<size; i++){
        for(int k=0; k<size; k++){
          if(temp_grid[i][k]=='+'){
                printf("|+");
            } else if(temp_grid[i][k]=='-'){
                printf("|-");
            } else if(temp_grid[i][k]==' '){
                printf("| ");
            }            
        }
        printf("|\n");
    }
}
double percolation_threshold(int size, char temp_grid[size][size]){
    double unblocked_sites=0, total_sites=size*size, threshold=0;
    for(int i=0; i<size; i++){
        for(int k=0; k<size; k++){
            if(temp_grid[i][k]=='+' || temp_grid[i][k]==' '){
                unblocked_sites++;
            }
        }
    }
    threshold=unblocked_sites/total_sites;
    return threshold;
}