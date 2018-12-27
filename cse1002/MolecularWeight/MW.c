#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char Name[30];
    int Number;
    char Symbol[5];
    double Weight;
} ELEMENT;

int main(void){
    FILE *fin = fopen("elements.csv", "r");
    ELEMENT array[104];
    char stringo[300];
    char str[50];
    fgets(stringo, sizeof(stringo), fin);
    for(int i=0; i<103; i++){        
        fgets(stringo, sizeof(stringo), fin); 
        char *s = strtok(stringo, ",");
        strcpy(array[i].Name, s);
        s = strtok(NULL, ",");
        array[i].Number = atoi(s);
        s = strtok(NULL, ",");
        strcpy(array[i].Symbol, s);
        s = strtok(NULL, ",");
        array[i].Weight = atof(s);
        
    }
    
    printf("Enter a formula(s)\n");
    while(atoi(str)!=-1){
        double num=0, temp=0;
        char temp1[50];
        strcpy(str, " ");
        strcpy(temp1, " ");
        gets(str);
        strncpy(temp1, str, (strlen(str)-2));
        char *a = strtok(str, " ");
        while(a!=NULL && strcmp(a, ".")!=0){
            
            for(int i=0; i<103; i++){
                if(strcmp(a,array[i].Symbol)==0){
                    num+=array[i].Weight;
                    temp=array[i].Weight;
                }
            }

            if(a[0]>47 && a[0]<58){                
                num=num-temp;
                num+=atof(a)*temp;
            }
            a = strtok(NULL, " ");
        }
        if(num==0 && atoi(str)!=-1){
            printf("Unknown Molecular Equation!\n");
        } else if(atoi(str)!=-1){
            printf("Molecular Weight of %s: %.2lf\n", temp1, num);
        }
        
      
        
    }
    
    return 0;
}