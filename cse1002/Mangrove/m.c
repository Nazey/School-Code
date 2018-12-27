#include<stdio.h>
#include<stdlib.h>

struct node {
	int Ti;
	int Di;
	struct node * next;
} node;

int findMax();
void addNode(int, int);
void delete(int index);

struct node *head = NULL;

int main(void){
	int num, t, d;
	scanf("%d", &num);
	for(int x = 0; x < num; x++){
		scanf("%d %d", &t, &d);
		addNode(t, d);
	}
	
	int total = 0;
	while(head->next != NULL) {
		int index = findMax(); //get highest
		
		struct node * _node = head;
		int total2 = 0;
	
		for(int x = 0; x < index; x++){
			_node = _node->next;
		}
		int multi = 2 * _node->Ti;
		delete(index);
		_node = head;					
	
		while(_node->next != NULL){	
			total2 += _node->Di;
			_node = _node->next;
		}
		total2 += _node->Di;
		total2 *= multi;	
		total += total2;
	}
	
	printf("\n%d", total);
	return 0;
}

//Find the biggest asshole manetee
int findMax() {
	int manatee = 0, count = 0;
	struct node *_node = head;
	double max = (double)_node->Ti/_node->Di;\
	
	while(_node->next != NULL){
		if((double)_node->Ti/_node->Di < max){
			max = (double)_node->Ti/_node->Di;
			manatee = count;
		}
		_node = _node->next;
		count++;
	}
	
	if((double)_node->Ti/_node->Di < max){
		max = (double)_node->Ti/_node->Di;
		manatee = count;
	}
	return manatee;
}

//Add node
void addNode(int _Ti, int _Di) {
	struct node * _node = (struct node *) malloc(sizeof(struct node));
	_node->Ti = _Ti;
	_node->Di = _Di;
	_node->next = NULL;
	
	if(head == NULL) {
		head = _node;
	} else {
		struct node * current = head;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = _node;
	}
	
	return;
}

//Remove node
void delete(int index) {	
	struct node * current = head;
	struct node * prev;
	
	if(index == 0) {
		head = current->next;
		return;
	}
	
	while(current->next != NULL && index-- > 0) {
		prev = current;
		current = current->next;
	}
	
	prev->next = current->next;
	return;
}