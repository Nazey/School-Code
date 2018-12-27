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

void selection_sort(void);

void addv(int a);

void print(void);


int main(void){
    int random;
    clock_t start_t, end_t;
    double total_t;
    srand(time(NULL));
    for(int i=11000; i>=0; i--){
        random = rand();
        addv(random);
    }
    start_t = clock();
    selection_sort();
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("cpu time: %lf\n", total_t);
    
    return 0;
}

void selection_sort(void){
    struct link_list* temp = headnode;
    struct link_list* tm = headnode;
    struct link_list* temp2;    
    struct link_list* min;
    struct link_list* swap;
    
    while(tm->next != NULL){
        temp = tm;
        temp2 = temp->next;   
        min = temp;
        
        while(temp2 != NULL){
            if(min->value >= temp2->value){
                min = temp2;
            }
            temp2 = temp2->next;
        }
        if (temp == headnode) {
            headnode = min;
        }
        if (min == tailnode) {
            tailnode = temp;
        }
        if(temp->next == min){
            
            if(min->next != NULL){                
                min->next->prev = temp;
            }
            
            temp->next = min->next;
            min->next = temp;
            min->prev = temp->prev;
            if(min->prev != NULL){
                min->prev->next = min;
            }
            temp->prev = min;
            
        } else {
            temp->next->prev = min;//printf("1\n");
            min->prev->next = temp;//printf("2\n");
            
            if(min->next != NULL){
                
                min->next->prev = temp;
            }
            if(temp->prev != NULL){
                
                temp->prev->next = min;
            }
            swap = temp->prev;
            temp->prev = min->prev;
            min->prev = swap;
            swap = temp->next;
            temp->next = min->next;
            min->next = swap;

        }
        tm = min->next;
    }
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
     