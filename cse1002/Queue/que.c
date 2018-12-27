#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Node 
typedef struct char_node {
	char name[1000];
	struct char_node *next;
} char_node;

//Queue main
typedef struct {
	char_node * head;
	char_node * tail;
} char_queue;

void enQueue(char_queue *ptr, char newName[1000]);
void deQueue(char_queue *ptr);

int main(void){
	FILE *input;
	input = fopen("party.csv", "r");
	char name[1000];
	
	double total_time = 0;
	int total_ppl = 0;
	double zuccPos = 0.0; //Zuck 
	int flag = 1; //Marks the start of when to kick ppl from the party
	
	//queue
	char_queue myQueue;
	myQueue.head = NULL;
	myQueue.tail = NULL;
	
	while(1) {
		if(total_ppl < 100) {
			total_ppl++;
			fgets(name, 1000, input);
			enQueue(&myQueue, name);
		}
		
		if(total_ppl > 50) {
			flag = 0;
		}
		
		//people leaving
		int ppl_kicked = 0;
		if(flag == 0) {
			if(((int)total_time % 15) == 0) {
				for(int x = 0; x < 5; x++) {
					deQueue(&myQueue);
					total_ppl--;
				}
				ppl_kicked += 5;
			}
			
			if(((int)total_time % 30) == 0) {
				for(int x = 0; x < 6; x++) {
					deQueue(&myQueue);
					total_ppl--;
				}
				ppl_kicked += 6;
			}
			
			if(((int)total_time % 60) == 0) {
				for(int x = 0; x < 4; x++) {
					deQueue(&myQueue);
					total_ppl--;
				}
				ppl_kicked += 4;
			}
			
			if(((int)total_time % 120) == 0) {
				for(int x = 0; x < 20; x++) {
					deQueue(&myQueue);
					total_ppl--;
				}
				ppl_kicked += 20;
			}
			
		}
	
					
		if(name[0] == 'M' && name[1] == 'a' && name[2] == 'r' && name[3] == 'k') {
			
			zuccPos = total_time;
		}	
		
		if(total_ppl <= 0) {
			break;
		}
		total_time += 1.5;
	}
	
	printf("\nThe total amount of time the party took was: %.1lf\nThe Zuckerburg enters the party at: %.1lf", total_time, zuccPos);
	
	fclose(input);
	return 0;
}

//Add a person to the queue
void enQueue(char_queue *ptr, char newName[1000]) {
	char_node *node = (char_node *) malloc(sizeof(char_node));
	strcpy(node->name, newName);
	node->next = NULL;
	
	if(ptr->head == NULL) {
		ptr->tail = node;
		ptr->head = node;
	} else {
		ptr->tail->next = node;
		ptr->tail = node;
	}
	
	return;
}

//Remove a person from the queue
void deQueue(char_queue *ptr) {
	if(ptr->head == NULL) {
		return;
	}

	char_node * temp;
	
	temp = ptr->head;
	ptr->head = temp->next;
	
	if(ptr->head == NULL) {
		ptr->tail = NULL;
	}
	
	free(temp);
}