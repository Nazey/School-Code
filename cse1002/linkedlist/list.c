#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct int_list {
    int value ;
    struct int_list * next;
};

struct int_list * head = NULL;

void print_list();
void addv(int num);
void addi(int num, int index);
void delv(int num);
void deli(int index);
void revs();

int main(void) {
    printf("Please insert the beloved instructions:\n");
    char input[100];

    while(1) {
    		fgets(input, 100, stdin);
    		if(input[0] == 'e') {
     		break;
     	}
     	
     	if(input[0] == 'p') {
			print_list();
		} else if(input[0] == 'r') {
			revs();
		} else if(input[0] == 'a' && input[3] == 'v') {
			char *s = strtok(input, " ");
			s = strtok(NULL, " ");
			addv(atoi(s));
		} else if(input[0] == 'a' && input[3] == 'i') {
			char *s = strtok(input, " ");
			s = strtok(NULL, " ");
			int a = atoi(s);
			s = strtok(NULL, " ");
			int b = atoi(s);
			addi(a, b);
		} else if(input[0] == 'd' && input[3] == 'v') {
			char *s = strtok(input, " ");
			s = strtok(NULL, " ");
			delv(atoi(s));
		} else if(input[0] == 'd' && input[3] == 'i') {
			char *s = strtok(input, " ");
			s = strtok(NULL, " ");
			deli(atoi(s));
		}
     }
    
    
    return 0;
}

//Print List
void print_list() {
    struct int_list *node = head;
    while(node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
	printf("\n");
}

//Add to end of list
void addv(int num) {
    if(head == NULL) {
        head = (struct int_list *) malloc(sizeof(struct int_list));
    		head->value = num;
    		head->next = NULL;
		return;
    }
	
	struct int_list *current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    struct int_list *newNode = (struct int_list *) malloc(sizeof(struct int_list));
    newNode->value = num;
    newNode->next = NULL;
    current->next = newNode;
}

//Add to specific index in list
void addi(int num, int index) {
	if(index == 0) {
		struct int_list *newNode = (struct int_list *) malloc(sizeof(struct int_list));
    		newNode->value = num;
    		newNode->next = head;
		head = newNode;
	} else {
		struct int_list *current = head;
    		while(current->next != NULL && index-- > 1) {
        		current = current->next;
    		}
		if(index > 0) {
			addv(num);
		} else {
			struct int_list *newNode = (struct int_list *) malloc(sizeof(struct int_list));
    			newNode->value = num;
    			newNode->next = current->next;
			current->next = newNode;
		}
	}
}

//Delete number in list
void delv(int num) {
	struct int_list *current = head;
	struct int_list * prev;
	
	if(current->value == num) {
		head = current->next;
		return;
	}
	
    while(current->next != NULL && current->value != num) {
		prev = current;
		current = current->next;
	}
	if(current == NULL) {
		printf("Not found!");
		return;
	}
	prev->next = current->next;
}

//Delete index from list
void deli(int index) {
    struct int_list *current = head;
	struct int_list *prev;
	
	if(index == 0) {
		head = current->next;
		return;
	}
	
	while(current->next != NULL && index-- > 0) {
		prev = current;
		current = current->next;
	}
	
	if(index > 0) {
		printf("Index out of order!");
		return;
	}
	
	prev->next = current->next;
}

//Reverses list
void revs() {
    struct int_list *current = head;
	struct int_list *prev = NULL;
	struct int_list *next = NULL;
	while(current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}