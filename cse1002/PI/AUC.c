#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    
    int num_points=0, points_in_circle=0;
    double p=0, total=0;
    printf("Enter number of points: ");
    scanf(" %d",&num_points);
    srand(time(NULL));
    for(int i=0; i<num_points; i++){
            double x = ((double)rand()/RAND_MAX)*2;
            double y = ((double)rand()/RAND_MAX)*2;
            double y2 = 0;
            printf("x: %lf y: %lf\n", x, y);
            x=pow(x,2);
            y2=sqrt((4-x));
            if(y<y2){
                points_in_circle++;
            }
        }
    
    p=((double)points_in_circle/(double)num_points);
    printf("points in square: %d ratio: %lf\n",points_in_circle, p);    
    total=p*4; 
    printf("total: %lf", total);
    
    return 0;
}