#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Cumulative, so 15 minutes 5 people, 30 minutes 16 people (5+5+6), so on..

// A typedef for a single node of the queue
struct name_node {
     char name[50];
     struct name_node *next;
};

// The main typedef that defines the queue 
struct name_queue{
     struct name_node *q_head;
     struct name_node *q_tail;
     int q_size;
};

void enqueue(struct name_queue *qPtr, char the_name[50]);

void dequeue(struct name_queue *qPtr);

int main(void){
    FILE *fin = fopen("party.csv", "r");
    char inputs[50];
    char people[350][50];
    struct name_queue party;
    double time = 0, zuck = 0;
    int num_left = 350, i = 0, fifty_were_present = 0;
    party.q_head = NULL;
    party.q_tail = NULL;
    
    while(fgets(inputs, sizeof(inputs), fin)){
        strcpy(people[i], inputs);
        i++;
	}
    
    i = 0;
    
    while(num_left>0){
        if(i<350){
            if(i == 256){
                zuck = time;
            }                 
            enqueue(&party, people[i]);
            time+=1.5;
            i++;
        } 
                    
        if(party.q_size>=50 || fifty_were_present == 1){
           
            if(party.q_size == 50)
                fifty_were_present = 1;
        
            if(fmod(time, 15.0) == 0){
                for(int i = 0; i < 5; i++){
                    dequeue(&party);
                    num_left--;
                }
            } 
            
            if(fmod(time, 30.0) == 0){
                for(int i = 0; i < 6; i++){
                    dequeue(&party);
                    num_left--;
                }
            }
              
            if(fmod(time, 60.0) == 0){
                for(int i = 0; i < 4 ; i++){
                    dequeue(&party);
                    num_left--;
                }
            }
                
            if(fmod(time, 120.0) == 0){
                for(int i = 0; i< 20; i++){
                    dequeue(&party);
                    num_left--;
                }
            }
            
            
        } 
    }
        
     
    
    printf("The party lasted %lf minutes and Mark came in at %lf minutes", time, zuck);
    fclose(fin);
    return 0;
}

void enqueue(struct name_queue *qPtr, char the_name[50])  {
     struct name_node *newNode = (struct name_node*) malloc(sizeof(struct name_node));
     
     strcpy(newNode->name, the_name);
     newNode->next = NULL;
     
     if(qPtr->q_size == 0)  {
          qPtr->q_tail = newNode;
          qPtr->q_head = newNode;
      } else {
          qPtr->q_tail->next = newNode;
          qPtr->q_tail = newNode;
      }
      (qPtr->q_size)++;
      return;
}

void dequeue(struct name_queue *qPtr)   {
     struct name_node *tempPtr;
     char namep[50];

     tempPtr = qPtr->q_head;
     strcpy(namep, tempPtr->name);
     qPtr->q_head = tempPtr->next;
     (qPtr->q_size)--;

     if(qPtr->q_size == 0)
          qPtr->q_tail = NULL;

     free(tempPtr);
     //printf("Removed %s\n", namep);
}