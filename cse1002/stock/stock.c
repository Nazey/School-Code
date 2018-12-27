/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: stock
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    char Date[50];
    double Open;
    double High;
    double Low;
    double Close;
    int Volume;
    double Adj_Close;
} STOCK;


int main(int argc, char *argv[]){
    FILE *fin = fopen(argv[1], "r");
    int count = 0;
    char line[300];
    double highest = INT_MIN;
    STOCK *biggest =  (STOCK*) malloc(sizeof(STOCK));
    
    fgets(line, sizeof(line), fin);
    while(fgets(line, sizeof(line), fin)!=NULL){
        count++;
    }
    
    fclose(fin);
    fin = fopen(argv[1], "r");
    fgets(line, sizeof(line), fin);
    
    STOCK *array = (STOCK*) malloc(count*sizeof(STOCK));
    
    for(int i=0; i<count; i++){
        fgets(line, sizeof(line), fin);
        char *s = strtok(line, ",");       
        strcpy(array[i].Date, s);
        s = strtok(NULL, ",");
        array[i].Open = atof(s);
        s = strtok(NULL, ",");
        array[i].High = atof(s);
        s = strtok(NULL, ",");
        array[i].Low = atof(s);
        s = strtok(NULL, ",");
        array[i].Close = atof(s);
        s = strtok(NULL, ",");
        array[i].Volume = atoi(s);
        s = strtok(NULL, ",");
        array[i].Adj_Close = atof(s);        
        if(array[i].High>highest){
           highest=array[i].High; 
           *biggest = array[i];
        }
    }
    
    printf("Date: %s\nOpen: %.2lf\nHigh: %.2lf\nLow: %.2lf\nClose: %.2lf\nVolume: %d\nAdj. Close: %.2lf\n",biggest->Date, biggest->Open, biggest->High, biggest->Low, biggest->Close, biggest->Volume, biggest->Adj_Close);
    
    fclose(fin);
    return 0;
}
