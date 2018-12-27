#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){
    double avg=0;
    
        
        int num_points=0, points_in_circle=0;
        double approx_pi=0;
        printf("Enter number of points: ");
        scanf(" %d",&num_points);
    for(int k=0; k<30; k++){
        approx_pi=0;
        points_in_circle=0;
        
       for(int i=0; i<num_points; i++){
            double x = (double)rand()/RAND_MAX;
            double y = (double)rand()/RAND_MAX;
            x=pow(x,2);
            y=pow(y,2);
            if(x+y<1){
                points_in_circle++;
            }
        }
        approx_pi=((double)points_in_circle/(double)num_points)*4;
        printf("Inside points: %d\n", points_in_circle);
        printf("Approximate value of PI: %lf\n", approx_pi);
        printf("Error is: %lf\n",(approx_pi-3.1415));
        avg+=approx_pi;
       
    }
    
    printf("Average is %lf\n", avg/30);
    return 0;
}