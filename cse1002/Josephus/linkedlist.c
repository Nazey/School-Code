#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct link_list{
    int value;
    struct link_list *next;
};

struct link_list* headnode = NULL;
struct link_list* tailnode = NULL;

void addv(int a);

int josephus(void);

int main(void){
    clock_t start_t, end_t;
    double total_t;
    int k = 0;
    for(int i=0; i<1300000; i++){
        addv(i);
    }
    tailnode->next = headnode;
    start_t = clock();
    k = josephus();
    printf("person %d lives\n",k);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("total time %lf\n", total_t);
    return 0;
}

void addv(int a){
    struct link_list *newnode;
    newnode = (struct link_list*) malloc(sizeof(struct link_list));
    
    newnode->value = a;
    newnode->next = NULL;
    
    if(headnode==NULL){
        headnode = newnode;
        tailnode = headnode;
    } else {
        tailnode->next = newnode;
        tailnode = newnode;
    }
    
}

int josephus(void){
    struct link_list* tempnode = headnode;
    
    while(1){
        if(tempnode->next == tempnode){
            return tempnode->value;
        }
        tempnode->next = tempnode->next->next;
        tempnode = tempnode->next;
    }
    return 5;
}
