#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct link_list{
    int value;
    struct link_list *next;
	struct link_list *prev;
};

struct link_list* headnode = NULL;
struct link_list* tailnode = NULL;

void addv(int a);

void delv(int a);

void print(void);

void revs(void);

int main(void){
    int random;
    clock_t start_t, end_t;
    double total_t;
    int len = 1000000;
    srand(time(NULL));

    start_t = clock();
    random = rand();
    for(int i=0; i<len; i++){
        addv(i);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    
    printf("cpu time for adding %d nodes: %lf\n", len, total_t);
    
    start_t = end_t - start_t;
    end_t = end_t - start_t;
    
    start_t = clock();
    for(int i=0; i<len; i++){
        delv(i);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    
    printf("cpu time for deleting %d nodes: %lf\n", len, total_t);
    
    start_t = end_t - start_t;
    end_t = end_t - start_t;
    
    start_t = clock();
    revs();
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    
    printf("cpu time for reversing %d nodes: %lf\n", len, total_t);
    
    return 0;
}


void addv(int a){
    struct link_list *currentnode, *newnode, *prevnode;
    newnode = (struct link_list*) malloc(sizeof(struct link_list));
    
    newnode->value = a;
    newnode->next = NULL;
    
    
    if(headnode == NULL){
        headnode = newnode;
        tailnode = newnode;
        newnode->prev = NULL;
        return;
    }
    tailnode->next = newnode;
    newnode->prev = tailnode;
    tailnode = newnode;
    
}



void print(void){
    struct link_list *tempnode;
    if(headnode!=NULL){
        tempnode=headnode;
        while(tempnode!=NULL){
            printf("%d ", tempnode->value);
            tempnode = tempnode->next;
        }
        printf("\n");
    }
    if(headnode!=NULL){
        tempnode=tailnode;
        while(tempnode!=NULL){
            printf("%d ", tempnode->value);
            tempnode = tempnode->prev;
        }
        printf("\n");
    }
}

void delv(int a){
    struct link_list *tempnode;
    tempnode = headnode;
	
    if(tempnode->value == a){
        headnode = tempnode->next;
        headnode->next->prev = headnode;
    } else {         
        while(tempnode->next!=NULL && tempnode->value!=a){  
			tempnode = tempnode->next;			
        }
		if(tempnode->next == NULL){
            if(tempnode->value == a){
                tempnode->prev->next = NULL;
            } else {
			//printf("Not Found ");
            }
		} else {
			tempnode->prev->next = tempnode->next;
            tempnode->next->prev = tempnode->prev;
		}
    }
}

void revs(void){
    struct link_list *tempnode = headnode, *prevnode = NULL, *nextnode = NULL;
	while(tempnode != NULL) {
        nextnode = tempnode->next; 
        tempnode->next = prevnode;
        tempnode->prev = nextnode;
        prevnode = tempnode;
        tempnode = nextnode;
	}
    headnode = prevnode;
    headnode->prev = NULL;
        
    tempnode = headnode;
        
}
     