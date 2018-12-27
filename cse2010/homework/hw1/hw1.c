/*

  Author: Brian Massino	
  Email: bmassino2017@my.fit.edu	
  Course: CSE2010
  Section: 4
  Description: hw1.c

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Defining the structs for the customers on hold queue and the available representatives queue, 
//as well as the chat session linked list.

struct person {
    char name;
	int rTime;
	int duration;
	struct person *next;
};

//peronQueue will hold the customers on hold.
struct personQueue{
    struct person *head;
    struct person *tail;
};

struct representative {
     char name[6];
     struct representative *next;
};

//representativeQueue will hold the available reps ready for assignment.
struct representativeQueue{
    struct representative *head;
    struct representative *tail;
};

//chatSession will be a linked list holding all of the current chat sessions.
struct chatSession{
	int timeRemaining;
	int assignmentTime;
	struct person *customer;
	struct representative *rep;
	struct chatSession *next;
	
};
 
//various functions for input

//assigns customer to a representative if there is an available representative, else the function will determine if the customer wants to be put on hold.
void ChatRequest(struct representativeQueue *rQPtr, struct personQueue *pQPtr, int requestTime, char customer, int chatDuration, char waitOrLater[6]);

//removes a customer from the hold queue, if they have decided they do not want to wait any longer.
void QuitOnHold(struct personQueue *qPtr, char customer);

//prints the names of the avaiable reps at the time of request.
void PrintAvailableRepList(struct representativeQueue *qPtr);

//prints the max wait time up to the specific time requested.
void PrintMaxWaitTime(void);

//function to add each representative to the AvailableReps queue, input being the name as a string, as well as the queue.
void EnqueueRep(struct representativeQueue *qPtr, char n[6]);

//function to remove a representative from the queue.
struct representative* DequeueRep(struct representativeQueue *qPtr);  

//function to add a customer to the on-hold queue.
void EnqueueHoldCustomer(struct personQueue *qPtr, struct person *newHoldCustomer);

//function to remove a customer to the on-hold queue.
struct person* DequeueHoldCustomer(struct personQueue *qPtr);  

//function to simulate a minute passing, by subtracting 1 from the remainingTime variable in each chat session. 
void MinutePassed(void);

//creates a new chat session based on assignment time, the representative available and the person from the customers on hold queue.
void NewChatSession(struct representative* r, struct person *c, int AT);

//Checks to see if remainingTime is 0, if true, function removes the chatsession and prints ChatEnded
char* CheckChatEnded(void);


//Global variables for time and max wait time to make access easier for each function.
int TIME = -9999;
int MaxWaitTime = 0;


//list for the individual chat sessions.
struct chatSession *AllSessions = NULL;

int main(int argc, char *argv[])
{	
	/*
    description of declared variables
    */
	
	//Queue for available representatives.
	struct representativeQueue AvailableReps;
	AvailableReps.head = NULL;
	AvailableReps.tail = NULL;
	
	//Queue for customers on hold.
	struct personQueue CustomersOnHold;
	CustomersOnHold.head = NULL;
	CustomersOnHold.tail = NULL;
	
	//input will be the string that contains each line in the txt file
	char input[50];
	char inputCopy[50];
	char RepFinishChat[6];
	
	
	//adding in all the representatives to the queue.
    EnqueueRep(&AvailableReps,"Alice");
    EnqueueRep(&AvailableReps,"Bob");
    EnqueueRep(&AvailableReps,"Carol");
    EnqueueRep(&AvailableReps,"David");
    EnqueueRep(&AvailableReps,"Emily");

	
	

	//opening file from command line args
	FILE *fin = fopen(argv[1], "r");

	while(!feof(fin)){
		fgets(input, sizeof(input), fin); 
		strcpy(inputCopy,input);
		
        char *s = strtok(input, " ");
		
		//in each strcmp, I compare the input with each of the 4 possible input functions.
        if(strcmp(s, "ChatRequest") == 0){
			
			int requestTime;
			char customer;
			int chatDuration;
			char waitOrLater[6];
			

			s = strtok(NULL, " ");
			requestTime = atoi(s);
			s = strtok(NULL, " ");
			customer = *s;
			s = strtok(NULL, " ");
			chatDuration = atoi(s);
			s = strtok(NULL, " ");
			strcpy(waitOrLater, s);
			
			//for each instance, I check before each line of input to see if a chat has ended, so that when a new chat request comes in, the time isn't in conflict with the most up to date time.
			if(TIME == -9999){ //has time been initialized? if not, set time = to current request time from input.
				TIME = requestTime;				
			} else {
				//finalTime will be the amount of times the for loop will go around, to simulate a minute passing for each part
				int finalTime = requestTime-TIME;
				struct representative *assignedRep = (struct representative*) malloc(sizeof(struct representative));
				struct person *newCustomer = (struct person*) malloc(sizeof(struct person));
			    
				for(int i=0; i<(finalTime); i++){
					MinutePassed(); //simulate a minute passing for each chat session
					strcpy(RepFinishChat, CheckChatEnded());
					//if chat session ends up returning a representative name, will take the representative, check to see if someone is on hold, then if someone is on hold, add them to a new chat session.
					if(strncmp(RepFinishChat, "Alice", 5) == 0 || strncmp(RepFinishChat, "Bob", 3) == 0 || strncmp(RepFinishChat, "Carol", 5) == 0 || strncmp(RepFinishChat, "David", 5) == 0 || strncmp(RepFinishChat, "Emily", 5) == 0 ){							
						if(CustomersOnHold.head != NULL){							
							EnqueueRep(&AvailableReps, RepFinishChat);
							
							assignedRep = DequeueRep(&AvailableReps);
							newCustomer = DequeueHoldCustomer(&CustomersOnHold);
							
							printf("RepAssignment %c %s %d\n", newCustomer->name, assignedRep->name, TIME);								
							if(MaxWaitTime < requestTime - newCustomer->rTime){
								MaxWaitTime = requestTime - newCustomer->rTime; //because requestTime is the most up to date time, subtract the two and compare it with current maxwaittime to see if it should be the new maxwaittime or not.	
							}							
							NewChatSession(assignedRep, newCustomer, TIME);
						} else EnqueueRep(&AvailableReps, RepFinishChat); //else there is no one waiting, so, add them to the available reps list.
					}
					
					strcpy(RepFinishChat, "");
				}

				TIME = requestTime; //newest time is request time
			}
			printf("%s", inputCopy); 
			ChatRequest(&AvailableReps, &CustomersOnHold, requestTime, customer, chatDuration, waitOrLater); //call a chat request function to see if they should be put on hold or not.
			
		} else if(strcmp(s, "QuitOnHold") == 0){
			
			int requestTime;
			char customer;
				
			s = strtok(NULL, " ");
			requestTime = atoi(s);
			s = strtok(NULL, " ");
			customer = *s;
				//finalTime will be the amount of times the for loop will go around, to simulate a minute passing for each part
				int finalTime = requestTime-TIME;
				struct representative *assignedRep = (struct representative*) malloc(sizeof(struct representative));
				struct person *newCustomer = (struct person*) malloc(sizeof(struct person));
				
				for(int i=0; i<(finalTime); i++){
					MinutePassed(); //simulate a minute passing for each chat session
					strcpy(RepFinishChat, CheckChatEnded());
					//if chat session ends up returning a representative name, will take the representative, check to see if someone is on hold, then if someone is on hold, add them to a new chat session.
					if(strncmp(RepFinishChat, "Alice", 5) == 0 || strncmp(RepFinishChat, "Bob", 3) == 0 || strncmp(RepFinishChat, "Carol", 5) == 0 || strncmp(RepFinishChat, "David", 5) == 0 || strncmp(RepFinishChat, "Emily", 5) == 0 ){								
						if(CustomersOnHold.head != NULL){							
							EnqueueRep(&AvailableReps, RepFinishChat);
							assignedRep = DequeueRep(&AvailableReps);
							newCustomer = DequeueHoldCustomer(&CustomersOnHold);
							printf("RepAssignment %c %s %d\n", newCustomer->name, assignedRep->name, TIME);
							if(MaxWaitTime < requestTime - newCustomer->rTime){
								MaxWaitTime = requestTime - newCustomer->rTime; //because requestTime is the most up to date time, subtract the two and compare it with current maxwaittime to see if it should be the new maxwaittime or not.	
							}
							NewChatSession(assignedRep, newCustomer, TIME);
						} else EnqueueRep(&AvailableReps, RepFinishChat); //else there is no one waiting, so, add them to the available reps list.
					}
				}
				TIME = requestTime;  //newest time is request time
			
			
			printf("%s", inputCopy);
			QuitOnHold(&CustomersOnHold, customer);
			
			
		} else if(strcmp(s, "PrintAvailableRepList") == 0){
			int requestTime;
			
			s = strtok(NULL, " ");
			requestTime = atoi(s);
			
			if(TIME == -9999){
				TIME = requestTime;
				
			} else {
				int finalTime = requestTime-TIME;
				struct representative *assignedRep = (struct representative*) malloc(sizeof(struct representative));
				struct person *newCustomer = (struct person*) malloc(sizeof(struct person));
				
				for(int i=0; i<(finalTime); i++){
					MinutePassed(); //simulate a minute passing for each chat session
					strcpy(RepFinishChat, CheckChatEnded());
					//if chat session ends up returning a representative name, will take the representative, check to see if someone is on hold, then if someone is on hold, add them to a new chat session.
					if(strncmp(RepFinishChat, "Alice", 5) == 0 || strncmp(RepFinishChat, "Bob", 3) == 0 || strncmp(RepFinishChat, "Carol", 5) == 0 || strncmp(RepFinishChat, "David", 5) == 0 || strncmp(RepFinishChat, "Emily", 5) == 0 ){								
						if(CustomersOnHold.head != NULL){							
							EnqueueRep(&AvailableReps, RepFinishChat);
							assignedRep = DequeueRep(&AvailableReps);
							newCustomer = DequeueHoldCustomer(&CustomersOnHold);
							printf("RepAssignment %c %s %d\n", newCustomer->name, assignedRep->name, TIME);
							if(MaxWaitTime < requestTime - newCustomer->rTime){
								MaxWaitTime = requestTime - newCustomer->rTime; //because requestTime is the most up to date time, subtract the two and compare it with current maxwaittime to see if it should be the new maxwaittime or not.	
							}
							NewChatSession(assignedRep, newCustomer, TIME);
						} else EnqueueRep(&AvailableReps, RepFinishChat); //else there is no one waiting, so, add them to the available reps list.
					}
				}
				TIME = requestTime;  //newest time is request time
			}
			PrintAvailableRepList(&AvailableReps);
		} else if(strcmp(s, "PrintMaxWaitTime") == 0){
			int requestTime;
			
			s = strtok(NULL, " ");
			requestTime = atoi(s);
			
			//check to see if time has been initialize yet, if not, initialize it.
			if(TIME == -9999){
				TIME = requestTime;
				
			} else {
				int finalTime = requestTime-TIME;
				struct representative *assignedRep = (struct representative*) malloc(sizeof(struct representative));
				struct person *newCustomer = (struct person*) malloc(sizeof(struct person));
				
				for(int i=0; i<(finalTime); i++){
					MinutePassed(); //simulate a minute passing for each chat session
					strcpy(RepFinishChat, CheckChatEnded());
					//if chat session ends up returning a representative name, will take the representative, check to see if someone is on hold, then if someone is on hold, add them to a new chat session.
					if(strncmp(RepFinishChat, "Alice", 5) == 0 || strncmp(RepFinishChat, "Bob", 3) == 0 || strncmp(RepFinishChat, "Carol", 5) == 0 || strncmp(RepFinishChat, "David", 5) == 0 || strncmp(RepFinishChat, "Emily", 5) == 0 ){								
						if(CustomersOnHold.head != NULL){							
							EnqueueRep(&AvailableReps, RepFinishChat);
							assignedRep = DequeueRep(&AvailableReps);
							newCustomer = DequeueHoldCustomer(&CustomersOnHold);
							printf("RepAssignment %c %s %d\n", newCustomer->name, assignedRep->name, TIME);
							if(MaxWaitTime < requestTime - newCustomer->rTime){
								MaxWaitTime = requestTime - newCustomer->rTime; //because requestTime is the most up to date time, subtract the two and compare it with current maxwaittime to see if it should be the new maxwaittime or not.	
							}
							NewChatSession(assignedRep, newCustomer, TIME);
						} else EnqueueRep(&AvailableReps, RepFinishChat); //else there is no one waiting, so, add them to the available reps list.
					}
				}
				TIME = requestTime;  //newest time is request time
			}
			PrintMaxWaitTime();
		}

	}
    //check to see if there are any more sessions left, if there are, simulate minutes passing until they are ended.
	if(AllSessions != NULL){
		while(AllSessions != NULL){
			MinutePassed();
			strcpy(RepFinishChat, CheckChatEnded());			
		}
	}
	

}

void ChatRequest(struct representativeQueue *rQPtr, struct personQueue *pQPtr, int requestTime, char customer, int chatDuration, char waitOrLater[6]){
	//setting up new rep and customer structs
	struct representative *assignedRep = (struct representative*) malloc(sizeof(struct representative));
	struct person *newCustomer = (struct person*) malloc(sizeof(struct person));
	
	newCustomer->name = customer;
	newCustomer->rTime = requestTime;
	newCustomer->duration = chatDuration;
	newCustomer->next = NULL;
	
	
	
	if(rQPtr->head != NULL){ //first check to see if any available reps
		assignedRep = DequeueRep(rQPtr);
		printf("RepAssignment %c %s %d\n", customer, assignedRep->name, TIME);
		NewChatSession(assignedRep, newCustomer, TIME);
	} else if(rQPtr->head == NULL){ //else there are no available reps for assignment, so put them on hold if they want to wait, or do not add them if they aren't going to wait
		if(strncmp(waitOrLater, "wait", 4) == 0){			
			printf("PutOnHold %c %d\n", customer, TIME);
			EnqueueHoldCustomer(pQPtr, newCustomer);	
		} else if (strncmp(waitOrLater, "later", 5) == 0){
			printf("TryLater %c %d\n", customer, TIME);
			free(newCustomer);
		}
	}
	
}

//essentially, creates temp struct based on head of personQueue, goes through and finds the correct customer to remove and removes them from the list accordingly.
void QuitOnHold(struct personQueue *qPtr, char customer){
	struct person *temp = qPtr->head;
	struct person *tempPrev = qPtr->head; 
	if(temp != NULL){
		if(temp->name == customer){
			qPtr->head = qPtr->head->next;
			free(temp);
		} else {
			while(temp != NULL){
				if(temp->next == NULL && temp->name == customer){					
					tempPrev->next = NULL;
					free(temp);
					
					break;
				} else if(temp->name == customer){
					tempPrev->next = temp->next;
					free(temp);
					break;
				}
				tempPrev = temp;
				temp = temp->next;			
			}
		}		
	}	
}

//navigates through the list of available reps and prints out each name in the list.
void PrintAvailableRepList(struct representativeQueue *qPtr){
		printf("AvailableRepList %d", TIME);
	    struct representative *temp = (struct representative*) malloc(sizeof(struct representative));
		temp = qPtr->head;
		while(temp!=NULL){
			printf(" %s", temp->name);
			temp = temp->next;
		}
		printf("\n");
	
}

//prints max wait time
void PrintMaxWaitTime(void){
	printf("MaxWaitTime %d %d\n", TIME, MaxWaitTime);
}

//enqueues a representative, based on the queue struct. always tail->next.
void EnqueueRep(struct representativeQueue *qPtr, char n[6]){
	struct representative *newRep = (struct representative*) malloc(sizeof(struct representative));
    
    strcpy(newRep->name, n);
    newRep->next = NULL;
   
    if(qPtr->head == NULL)  {
        qPtr->tail = newRep;
        qPtr->head = newRep;

    } else {
		qPtr->tail->next = newRep;
        qPtr->tail = newRep;
    }
	  
    return;
}

//dequeues rep based on queue struct, first in first out.
struct representative* DequeueRep(struct representativeQueue *qPtr){ 
	
	
	if(qPtr->head == NULL) {
		return NULL;
	}

	struct representative *temp;
	
	temp = qPtr->head;
	qPtr->head = temp->next;
	
	if(qPtr->head == NULL) {
		qPtr->tail = NULL;
	}

	
	return temp;
}

//enqueues a hold customer based on queue struct, always tail->next.
void EnqueueHoldCustomer(struct personQueue *qPtr, struct person *newHoldCustomer){
   
    if(qPtr->head == NULL)  {
        qPtr->tail = newHoldCustomer;
        qPtr->head = newHoldCustomer;

    } else {
		qPtr->tail->next = newHoldCustomer;
        qPtr->tail = newHoldCustomer;
    }
	  
    

}

//dequeues hold customer based on queue struct, first in first out.
struct person* DequeueHoldCustomer(struct personQueue *qPtr){
	if(qPtr->head == NULL) {
		return NULL;
	}

	struct person *temp;
	
	temp = qPtr->head;
	qPtr->head = temp->next;
	
	if(qPtr->head == NULL) {
		qPtr->tail = NULL;
	}
	
	return temp;
}

//simulates a minute passing in each chat session by subtracting 1 from time remaining.
void MinutePassed(void){
	struct chatSession *temp = AllSessions;
	
	if(temp != NULL){
			while(temp != NULL){
				if(temp->timeRemaining > 0){
					temp->timeRemaining = temp->timeRemaining-1;	
					//TIME = TIME+1;
				} 
				//printf("temp->timeremaining=%d %c %s\n",temp->timeRemaining, temp->customer->name, temp->rep->name);
				temp = temp->next;			
			}					
	}
}

//creates a new chat session based on assignment time, the representative available and the person from the customers on hold queue.
void NewChatSession(struct representative* r, struct person *c, int AT){
	struct chatSession *temp = (struct chatSession*) malloc(sizeof(struct chatSession));
	struct chatSession *traverse = AllSessions;
	temp->rep = r;
	temp->customer = c;
	temp->next = NULL;
	temp->timeRemaining = c->duration;
	temp->assignmentTime = AT;	
	
	if(AllSessions == NULL){
		AllSessions = temp;			
	} else {
		while(traverse->next != NULL){
			traverse = traverse->next;
		}
		traverse->next = temp;
	}
}

//goes through the list of chat sessions, checks to see if time remaining is 0 and accordingly removes the chat session from the linked list of chat sessions.
char* CheckChatEnded(void){
	static char n[6]="";
	struct chatSession *temp = AllSessions;
	struct chatSession *tempPrev = NULL;
	
	if(temp != NULL){
		if(temp->next == NULL && tempPrev == NULL && temp->timeRemaining == 0){
			printf("ChatEnded %c %s %d\n", temp->customer->name, temp->rep->name, (temp->assignmentTime + temp->customer->duration));
			strcpy(n, temp->rep->name);
			TIME = (temp->assignmentTime + temp->customer->duration);
			AllSessions = NULL;
			
			
		} else {
			while(temp != NULL){
				if(temp->timeRemaining == 0 && temp->next != NULL && tempPrev != NULL){
					printf("ChatEnded %c %s %d\n", temp->customer->name, temp->rep->name, (temp->assignmentTime + temp->customer->duration));
					strcpy(n, temp->rep->name);
					TIME = (temp->assignmentTime + temp->customer->duration);
					tempPrev->next = temp->next;
					free(temp);
					
				} else if(temp->timeRemaining == 0 && temp->next == NULL && tempPrev != NULL){
					printf("ChatEnded %c %s %d\n", temp->customer->name, temp->rep->name, (temp->assignmentTime + temp->customer->duration));
					strcpy(n, temp->rep->name);
					TIME = (temp->assignmentTime + temp->customer->duration);
					tempPrev->next = NULL;
					free(temp);
				} else if(temp->timeRemaining == 0 && tempPrev == NULL){
					printf("ChatEnded %c %s %d\n", temp->customer->name, temp->rep->name, (temp->assignmentTime + temp->customer->duration));
					strcpy(n, temp->rep->name);
					TIME = (temp->assignmentTime + temp->customer->duration);
					AllSessions = temp->next;
					free(temp);
				}
				tempPrev = temp;
				temp = temp->next;
				
			}

		}
		
	}
	
	return n;
	
}



















