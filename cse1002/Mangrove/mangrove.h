struct node {
	int hour;
	int destruction;
	struct node* next;
};

void addnode(int h, int d);

void delnode(int h, int d);

void print(void);

int move_mangrove(void);

struct node* find_largest(void);

int sum_nodes(void);

struct node* head;

struct node* tail;

void mangrove(){
	int num_man = 0, hr = 0, ds = 0, destruction = 0;
	printf("Enter Number of Manatees:");
	scanf("%d", &num_man);
	for(int i=0; i<num_man; i++){
		scanf("%d %d", &hr, &ds);
		addnode(hr, ds);
	}
    destruction = move_mangrove();
    printf("Total destruction: %d mangroves\n", destruction);
	
}


void addnode(int h, int d){
	struct node* new = (struct node*) malloc(sizeof(struct node));
	new->next = NULL;
	new->hour = h;
	new->destruction = d;
	
	if(head == NULL){
		head = new;
		tail = new;
	} else {
		tail->next = new;
		tail = tail->next;
	}
}

void delnode(int h, int d){
    struct node* temp;
    temp = head;
	
    if(temp->hour == h && temp->destruction == d){
        head = temp->next;
    } else {         
        while(temp->next!=NULL && (temp->next->hour!=h && temp->next->destruction!=d)){  
			temp = temp->next;			
        }
		if(temp->next == NULL){
			printf("Not Found\n");
		} else if(temp->next == tail){
			temp->next = temp->next->next;
			tail = temp->next;
		} else {
			temp->next = temp->next->next;
		}
    }

}

int move_mangrove(void){
    int total_destruction = 0, sum = 0;
    struct node* remove = (struct node*) malloc(sizeof(struct node));
    
    while(head!=NULL){
        remove = find_largest();
        delnode(remove->hour, remove->destruction);
        sum = sum_nodes();
        total_destruction += sum*((remove->hour)*2);
    }
    
    return total_destruction;
}

struct node* find_largest(void){
    struct node* temp = head;
    struct node* largest = head;
    
    while(temp!=NULL){
        if((double)(temp->hour)/(temp->destruction) < (double)(largest->hour)/(largest->destruction)){
            largest = temp;         
        }        
        temp = temp->next;
    }
    
    return largest;
}

int sum_nodes(void){
    struct node* temp = head;
    int sum = 0;
    while(temp!=NULL){
        sum += temp->destruction;
        temp = temp->next;
    }
    return sum;
}

void print(void){
    struct node* temp;
    if(head!=NULL){
        temp=head;
        while(temp!=NULL){
            printf("hour: %d destruction: %d\n", temp->hour, temp->destruction);
            temp = temp->next;
        }
        printf("\n");
    }
}
