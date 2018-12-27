/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: tic-tac-toe
 */
#include <stdio.h>
#include <stdlib.h>

void who_wins(int length, int *x_wins, int *o_wins, char arr[length][length]);

int main(void){
    char str[9];
    char temp[3][3];
    int difference_of_xo, x=0, o=0, x_wins=0, o_wins=0, num_=0;;
    
    printf("Enter the finished game: ");
   
    
    for(int i=0; i<3; i++){
        for(int k=0; k<3; k++){
            scanf("%c",&temp[i][k]);
            if(temp[i][k]=='o'){
                o++;
            } else if(temp[i][k]=='x'){
                x++;
            } else if(temp[i][k]=='_'){
                num_++;
            }
        }
        
    }
    
    
    difference_of_xo=abs(x-o);
    who_wins(3, &x_wins, &o_wins, temp);
    
    //checking to see impossible cases with more than one or or x
    if(difference_of_xo>1 && x>o){
        printf("start x\n");
        printf("impossible");
    } else if(difference_of_xo>1 && o>x){
        printf("start o\n");
        printf("impossible");
    } else if(difference_of_xo==0){ // else now test a bunch of cases where there are even amount of x's and o's
        if((x_wins==0 & o_wins==0) && num_>0){
            printf("start o|x\nunfinished"); 
        } else if(x_wins==1 & o_wins==0){
            printf("start o\nwin x"); 
        } else if(x_wins==0 & o_wins==1){
            printf("start x\nwin o"); 
        } else if((x_wins==1 && o_wins==1)){
            printf("start o|x\nimpossible");
        }
    } else if(difference_of_xo==1){ // else now test a bunch of cases where there is one more x or o
        if(x_wins==1 && o_wins==0){
            printf("start x\nwin x");
        } else if(x_wins==0 && o_wins==1){
            printf("start o\nwin o");
        } else if(x_wins==2 && o_wins==0){
            printf("start x\nwin x");
        } else if(x_wins==0 && o_wins==2){
            printf("start o\nwin o");
        } else if(x_wins==1 && o_wins==1){
            if(x>o){
                printf("start x\nimpossible");
            } else if(o>x){
                printf("start o\nimpossible");
            } 
        } else if(x_wins==0 && o_wins==0){
            if(x>o && num_>0){
                printf("start x\nunfinished");
            } else if(o>x && num_>0){
                printf("start o\nunfinished");
            } else if(x>o && num_==0){
                printf("start x\ndraw");
            } else if(o>x && num_==0){
                printf("start o\ndraw");
            }
        } 
    } 
    // and if the difference is greater than 1, that is covered already by the first 2 if's
}

void who_wins(int length, int *x_wins, int *o_wins, char arr[length][length]){
     
     //checking to see how many times x wins
     if(arr[0][0]=='x'){
        if(arr[0][1]=='x'){
           if(arr[0][2]=='x'){
               *x_wins+=1;
           } 
     } 
        if(arr[1][0]=='x'){
            if(arr[2][0]=='x'){
                *x_wins+=1;
            }
     } 
        if(arr[1][1]=='x'){
            if(arr[2][2]=='x'){
                *x_wins+=1;
            }
        }
     }  
     if(arr[0][2]=='x'){
         if(arr[1][2]=='x'){
             if(arr[2][2]=='x'){
                 *x_wins+=1;
             }
         }
    } 
     if(arr[2][0]=='x'){
        if(arr[1][1]=='x'){
            if(arr[0][2]=='x'){
                *x_wins+=1;
            } 
        }             
        if(arr[2][1]=='x'){
            if(arr[2][2]=='x'){
                *x_wins+=1;
            }
        }
            
                 
    }  
     if(arr[0][1]=='x'){
        if(arr[1][1]=='x'){
            if(arr[2][1]=='x'){
                *x_wins+=1;
            }
        }
     }
     if(arr[1][0]=='x'){
        if(arr[1][1]=='x'){
           if(arr[1][2]=='x'){
               *x_wins+=1; 
           }
        }
     }
     
     //checking to see how many times x wins
      if(arr[0][0]=='o'){
        if(arr[0][1]=='o'){
           if(arr[0][2]=='o'){
               *o_wins+=1;
           } 
      } 
        if(arr[1][0]=='o'){
            if(arr[2][0]=='o'){
                *o_wins+=1;
            }
        } 
        if(arr[1][1]=='o'){
            if(arr[2][2]=='o'){
                *o_wins+=1;
            }
        }
     }  
     if(arr[0][2]=='o'){
         if(arr[1][2]=='o'){
             if(arr[2][2]=='o'){
                 *o_wins+=1;
             }
         }
     } 
     if(arr[2][0]=='o'){
        if(arr[1][1]=='o'){
            if(arr[0][2]=='o'){
                *o_wins+=1;
            } 
        }             
        if(arr[2][1]=='o'){
            if(arr[2][2]=='o'){
                *o_wins+=1;
            }
        }
            
                 
     }  
     if(arr[0][1]=='o'){
        if(arr[1][1]=='o'){
            if(arr[2][1]=='o'){
                *o_wins+=1;
            }
        }
     }
     if(arr[1][0]=='o'){
        if(arr[1][1]=='o'){
           if(arr[1][2]=='o'){
               *o_wins+=1; 
           }
        }
     }
     
}