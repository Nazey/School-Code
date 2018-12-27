#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int value;
    struct int_node* next;
} int_node;

typedef struct {
    int_node* top;
} stack_node;

stack_node head;

void push(int a);

int pull(void);

void print_stack(void);

int main(void){
    char inputs[50], output[50];
    int x = 0, y = 0, z = 0, test = 0, fix = 2;
    printf("postfix(1) or prefix(2)?: ");
    scanf("%d", &fix);
    printf("Enter your expression:\n");
    scanf("\n");
    gets(inputs);
    if(fix == 1 ){
        for(int i=0; i<strlen(inputs); i++){
        test = inputs[i];
            if(isspace(test) == 0 && inputs[i] != '+' && inputs[i] != '-' && inputs[i] != '*' && inputs[i] != '/'){ 
                test = inputs[i] - '0';
                printf("test: %d\n", test);
                push(test);
            } else if(inputs[i] == '+'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y + x;
                push(z);    

            } else if(inputs[i] == '-'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y - x;
                push(z);

            } else if(inputs[i] == '*'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y * x;
                push(z);

            } else if(inputs[i] == '/'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y / x;
                push(z);

            } 
        }
    } else {
        for(int i=strlen(inputs)-1; i>=0; i--){
            test = inputs[i];
            if(isspace(test) == 0 && inputs[i] != '+' && inputs[i] != '-' && inputs[i] != '*' && inputs[i] != '/'){ 
                test = inputs[i] - '0';
                printf("test: %d\n", test);
                push(test);
            } else if(inputs[i] == '+'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y + x;
                push(z);    

            } else if(inputs[i] == '-'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y - x;
                push(z);

            } else if(inputs[i] == '*'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y * x;
                push(z);

            } else if(inputs[i] == '/'){
                x = 0; y = 0; z = 0;
                x = pull();
                y = pull();
                z = y / x;
                push(z);

            } 
        }
    }
    
    print_stack();
    z = pull();
    printf("%s = %d\n", inputs, z);
    return 0;
}

void push(int a){
    int_node* newnode = (int_node*) malloc(sizeof(int_node));
    newnode->next = NULL;
    newnode->value = a;
    
    if(head.top == NULL){
        head.top = newnode;
    } else {
        int_node* tempnode = head.top;
        head.top = newnode;
        newnode->next = tempnode;
    }
    
}

int pull(void){
    int a = 0;
    a = head.top->value;
    head.top = head.top->next;
    return a;
    
    
}

void print_stack(void){
    int_node* temp = head.top;
    while(temp!=NULL){
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}