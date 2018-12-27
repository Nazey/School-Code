#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct link_list{
    int value;
    struct link_list *next;
	struct link_list *prev;
};

struct link_list* headnode = NULL;

void addv(int a);

void addi(int a, int ind);

void delv(int a);

void deli(int index);

void print(void);

void revs(void);

int main(void){
    char input[15];
    int num, ind;
    char input2[15];
    printf("Enter in a command: ");
    gets(input);
    while(strcmp(input, "end")!=0){
        num=0;
        strcpy(input2, "");        
        sscanf(input, "%s %d %d", input2, &num, &ind);
        
        if(strcmp(input2, "addv")==0){
            addv(num);
        } else if(strcmp(input2, "addi")==0){
            addi(num, ind);			
        } else if(strcmp(input2, "delv")==0){
            delv(num);			
        } else if(strcmp(input2, "deli")==0){
            deli(num);		
        } else if(strcmp(input2, "print")==0){
            print();
        } else if(strcmp(input2, "revs")==0){
            revs();
        }  
        print();
        printf("Enter in a command: ");
        gets(input);
    }
    
    return 0;
}

void addv(int a){
    struct link_list *currentnode, *newnode, *prevnode;
    newnode = (struct link_list*) malloc(sizeof(struct link_list));
    
    newnode->value = a;
    newnode->next = NULL;
    
    if(headnode==NULL){
        headnode = newnode;
		headnode->prev = NULL;
    } else {
        currentnode = headnode; 
        while(currentnode->next!=NULL){
			if(currentnode==headnode){
            prevnode = currentnode;
			currentnode = currentnode->next;
			} else {
				currentnode->prev = prevnode;
				currentnode = currentnode->next;
			}
			
		}
        currentnode->next = newnode;
        newnode->prev = currentnode;
        
    }
    
}

void addi(int a, int ind){
    struct link_list *tempnode, *newnode;
    newnode = (struct link_list*) malloc(sizeof(struct link_list));
    int counter=0;
    
    newnode->value = a;
    newnode->next = NULL;
    
    if(headnode == NULL && index == 0){
        headnode = newnode;
        headnode->prev = NULL;
    } else if(headnode == NULL && ind>0){
        headnode = newnode;
        headnode->prev = NULL;
    } else {
        tempnode = headnode;
        while(tempnode->next!=NULL && counter<ind){            
            tempnode = tempnode->next;
            counter++;
        }
        if(tempnode->next==NULL && counter<ind){
            addv(a);
        } else {
        newnode->next = tempnode->prev->next;
        tempnode->prev->next = newnode;
        newnode->prev = tempnode->prev;
        tempnode->prev = newnode;        
        }
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
			printf("Not Found\n");
            }
		} else {
			tempnode->prev->next = tempnode->next;
            tempnode->next->prev = tempnode->prev;
		}
    }
}

void deli(int index){
    struct link_list *tempnode;
    tempnode = headnode;

	if(index == 0){
        headnode = headnode->next;
        headnode->prev = NULL;
    } else {         
        while(tempnode->next!=NULL && index-->0){  		
			tempnode = tempnode->next;			
        }
		if(index >= 0){
			if(index > 0){
                printf("Index out of order\n");
            } else{
                tempnode->prev->next = NULL;
            }             
		} else{
			tempnode->prev->next = tempnode->next;
            tempnode->next->prev = tempnode->prev;
		}
		
    }

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
     