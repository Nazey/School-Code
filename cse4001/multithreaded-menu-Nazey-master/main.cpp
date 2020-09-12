//
//
// Compilation:
//
//       g++ main.cpp -lpthread -o serial -lm
//
//
//
/* Includes */

#include <cmath>
#include <iostream>     // std::cin, std::cout


/* global vars */
#define N 1000000      // length of measurement array 


// Matrix of measurements 
double Measurements[N];



// Populate the measurement matrix with some numbers 
void generateMeasurements(void)
{

    double period      = N/4;       // Signal period 
    double maxminTemperature = 200; // Range of values 

    for(long int i = 0; i < N; i++ ){               

        // Standard deviation of noise distribution 
        double std = 10.0; 

        // Generate random number in [0,1]
        double noise = std * ((double) rand() / (RAND_MAX));  

        // Calculate noiseless measurement from a cosine curve in [-1,1]
        double temperatureClean =  maxminTemperature * cos( 2.0 * M_PI * (1.0/period) * (double)i);

        // Generate final (noisy) measurement 
        double temperature = temperatureClean + noise;

        //printf("Temperature: %f\n", temperature );
        //fflush(stdout);

        // Store measurement into global array 
        Measurements[ i ] = temperature;

    }
}





void *calculateAverage (void *)
{
  
    // TODO 
    double avgValue = 0;
    for(long int i = 0; i < N; i++ )                  
        avgValue = avgValue + Measurements[ i ] / N;

    printf("Average value: %f\n", avgValue );
    fflush(stdout);

    pthread_exit(0); /* exit thread */
}

void *DisplayMaximum (void *){
    double maxValue = -1;
    for (long int i = 0; i < N; i++){
        if(Measurements[i] > maxValue)
            maxValue = Measurements[i];
    }
    printf("Maximum Value: %f\n", maxValue);

}
void *DisplayMinimum (void *){
    double minValue = Measurements[0];
    for (long int i = 0; i < N; i++){
        if(Measurements[i] < minValue)
            minValue = Measurements[i];
    }
    printf("Minimun Value: %f\n", minValue);

}


int main()
{


    // Generate measurements. All values stored in the global array Measurements. 
    generateMeasurements();   



    pthread_t worker1;
    pthread_t worker2;
    pthread_t worker3;


    // Menu selection 
    int input;
    do{
         /*Displays the menu to user*/
        printf("Main menu\n");
        printf("1. Calculate Average\n");
        printf("2. Display Maximum:\n");   
        printf("3. Display Minimum:\n");
        printf("0. Exit:\n");
        scanf("%d",&input);

        switch(input){
            case 0:
                printf("Exiting...\n");
                break;
            case 1:
                pthread_create (&worker1, NULL, calculateAverage,   (void *)NULL );
                break;
            case 2 :
                pthread_create(&worker2, NULL, DisplayMaximum, (void *)NULL );                 
                break;
            case 3:
                pthread_create(&worker3, NULL, DisplayMinimum, (void *)NULL );
                break;
            default:
                printf("invalid\n");
                break;
        }

    } while(input != 0);



    /* exit */
    exit(0);
    
} /* main() */

