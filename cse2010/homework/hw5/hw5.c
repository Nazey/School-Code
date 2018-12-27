/*

  Author: Brian Masino	
  Email: bmassino2017@my.fit.edu	
  Course: cse2010	
  Section: 4
  Description: hw5.c

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define POSINFINITY 9999
#define NEGINFINITY 0000

typedef struct SkipNode{	//skipnode struct
	int Date;				//date
	char EventName[100];	//name of event
	struct SkipNode *Up;	//pointers to up, down, left, and right of each node
	struct SkipNode *Down;
	struct SkipNode *Left;
	struct SkipNode *Right;
}SkipNode;

typedef struct SkipList{	//holds the skiplist, starting with initial -infinity value as the top
	SkipNode *Top;
	int Height;
}SkipList;

typedef struct ListOfSkipNodes{		//holds a linked list of skipnodes, so that we can edit and change according to the operation
	SkipNode *Node;
	struct ListOfSkipNodes *Next;
}ListOfSkipNodes;

typedef struct RedPath{				//holds the list of nodes where we need to either insert or remove, and also holds the name of an event (if it exists)
	ListOfSkipNodes *ListOfNodes;
	char EventName[100];
}RedPath;

extern int getRandHeight();
void insertSkipNodeToListOfSkipNodes(ListOfSkipNodes **NodeList,	 //inserts a skipnode into the given list of skipnodes
 SkipNode *NodeToInsert);										 
void initializeSkipList(SkipList *SL);								 //creates skiplist with a -infinity and a +infinity (empty)
void addEmptyRowSkipList(SkipList *SL);								 //takes in skiplist, adds a new empty row above it
RedPath* getWithPath(SkipList *SL, int Key);				  		 //returns the red path, as well as the value (if it exists)
char* get(SkipList *SL, int Key);									 //if key exists, return value associated with key; otherwise, return NULL
char* put(SkipList *SL, int Key, char NewName[100]);   				 //if key doesn’t exist, add entry and return NULL; otherwise, replace value and return the old value
char* removeDate(SkipList *SL, int Key);							 //if key exists, remove entry and return its value; otherwise, return NULL
SkipNode* ceilingEntry(SkipList *SL, int Key); 						 //return the entry with the smallest key greater than or equal to key; return null if no such entry exists
SkipNode* floorEntry(SkipList *SL, int Key);						 //return the entry with the largest key less than or equal to key; return null if no such entry exists
SkipNode* subMap(SkipList *SL, int Key1, int Key2);					 //return all entries with key such that key1 ≤ key ≤ key2
void printSkipList(SkipList *SL);									 //prints the skiplist according to height
void displayAllEvents(SkipList *SL);								 //displays all events in the skiplist (if any)

int main(int argc, char* argv[]){
	
	SkipList *MySkipList = (SkipList*) malloc(sizeof(SkipList));	//initial creation of empty skiplist
	MySkipList->Height = 0;
	initializeSkipList(MySkipList);
	
	FILE *fin = fopen(argv[1], "r");								//getting input from the file
	char buffer[300];
	
	while(!feof(fin)){
		strcpy(buffer, "");										//set the string to nothing
		fgets(buffer, sizeof(buffer), fin); 	
	 	if(buffer[strlen(buffer)-1] == '\n'){					//removes the trailing \n character from each line, 
				buffer[strlen(buffer)-1] = '\0';				//unless the line is the last line in the file, in which case it does not have a \n
		} 
		if(strcmp(buffer, "") == 0 ){
			break;
		}
		char *parse = strtok(buffer, " ");

		if(strcmp(parse, "DisplayEvent") == 0){					//if we want to display events
			int D;
			
			parse = strtok(NULL, " ");
			D = atoi(parse);
			
			RedPath *MyPath = getWithPath(MySkipList, D);
			
			char EN[100];
			strcpy(EN, MyPath->EventName);
			printf("DisplayEvent %.4d ", D);
			if(strcmp(EN, "") == 0){							//if the event was not found, print none
				printf("none\n");
			} else {
				printf("%s\n", EN);								//else print the event
			}
		} else if(strcmp(parse, "AddEvent") == 0){				//if we want to add events
			int D;
			char EN[100];
			char *Successful;
			
			parse = strtok(NULL, " ");				
			D = atoi(parse);
			parse = strtok(NULL, " ");
			strcpy(EN, parse);
			Successful = put(MySkipList, D, EN);
			
			printf("AddEvent %.4d %s ", D, EN);		
			if(Successful == NULL){							//if the event did not exist in the list, add it and print success
				printf("success\n");
			}
			else {
				printf("replacingExistingEvent\n");				//else it must have replaced something else
			}  
			
		} else if(strcmp(parse, "DeleteEvent") == 0){			//if we want to delete an event
			int D;
			char *Successful;
			
			parse = strtok(NULL, " ");
			D = atoi(parse);
			Successful = removeDate(MySkipList, D);
			
			printf("DeleteEvent %.4d ", D);
			 if(Successful == NULL){							//if NULL was returned, means it could not find the node
				printf("noDateError\n");
			} else {
				printf("success\n");							//else it deleted it
			}  
		} else if(strcmp(parse, "DisplayEventsBetweenDates") == 0){	//if we want to display events between a certain timeframe
			int D1;
			int D2;
			SkipNode *Beginning;
			
			parse = strtok(NULL, " ");
			D1 = atoi(parse);
			parse = strtok(NULL, " ");
			D2 = atoi(parse);
			Beginning = subMap(MySkipList, D1, D2);			

			printf("DisplayEventsBetweenDates %.4d %.4d", D1, D2);
			
			if(Beginning == NULL){								//check to see if the two timeframes are even valid
				printf("none\n");
			} else {
				
				while(Beginning != NULL && Beginning->Date <= D2){		//while there are still events to print that are within the timeframe, print them
					printf(" %.4d:%s", Beginning->Date, Beginning->EventName);
					Beginning = Beginning->Right;
				}
				printf("\n");
			}
			
		} else if(strcmp(parse, "DisplayEventsFromStartDate") == 0){	//if we want to display events from a starting period
			int D;

			SkipNode *Beginning;
			
			parse = strtok(NULL, " ");
			D = atoi(parse);
			Beginning = ceilingEntry(MySkipList, D);			

			printf("DisplayEventsFromStartDate %.4d", D);
			
			
			if(Beginning == NULL || Beginning->Date == 9999){	//check to make sure the start isn't at the end of the list (+infinity)
				printf("none\n");
			} else {
				
				while(Beginning != NULL && Beginning->Date != 9999){		//while there are still nodes, print them
					printf(" %.4d:%s", Beginning->Date, Beginning->EventName);
					Beginning = Beginning->Right;
				}
				printf("\n");
			}
		} else if(strcmp(parse, "DisplayEventsToEndDate") == 0){			//if we want to display all events up to a certain date
			int D;

			SkipNode *End, *Beginning;
			
			parse = strtok(NULL, " ");
			D = atoi(parse);
			Beginning = ceilingEntry(MySkipList, 1);	
			End = ceilingEntry(MySkipList, D);			
			printf("DisplayEventsToEndDate %.4d", D);
			
			if(End == NULL || End->Date == 0){								//first check if end date begins at the -infinity, then there are no dates past the one inputted
				printf("none\n");	
			} else {
				
				while(Beginning != NULL && Beginning->Date <= End->Date){		//while there are dates before or equal to the end date, print them
					printf(" %.4d:%s", Beginning->Date, Beginning->EventName);
					Beginning = Beginning->Right;
				}
				printf("\n");
			}
		} else if(strcmp(parse, "DisplayAllEvents") == 0){			//if we want to display all events, display them all (if any)
			
			printf("DisplayAllEvents ");
			displayAllEvents(MySkipList);
			
		} else if(strcmp(parse, "PrintSkipList") == 0){				//if we want to see the skiplist, print the skiplist
			printf("PrintSkipList\n");
			printSkipList(MySkipList);
		}
	} 
}

void insertSkipNodeToListOfSkipNodes(ListOfSkipNodes **NodeList, SkipNode *NodeToInsert){	//basic insert into a singly linked list of nodes 
	ListOfSkipNodes *TraverseListOfNodes = *NodeList;										//(used in storing the red path)
	ListOfSkipNodes *Insert = (ListOfSkipNodes*) malloc(sizeof(ListOfSkipNodes));	
	Insert->Node = NodeToInsert;
	Insert->Next = NULL;
	
	if(*NodeList == NULL){				//checking to see if list is empty, adding to next empty slot
		*NodeList = Insert;
	} else {
		while(TraverseListOfNodes->Next != NULL){
			TraverseListOfNodes = TraverseListOfNodes->Next;
		}
		TraverseListOfNodes->Next = Insert;
	}
	
}

void initializeSkipList(SkipList *SL){
	SkipNode* FirstNode = (SkipNode*) malloc(sizeof(SkipNode));		//creating first -infinity node
	FirstNode->Date = NEGINFINITY;
	strcpy(FirstNode->EventName, "NONE_BEGINNING");
	FirstNode->Up = NULL;
	FirstNode->Down = NULL;
	FirstNode->Left = NULL;
	
	SkipNode* SecondNode = (SkipNode*) malloc(sizeof(SkipNode));	//creating second +infinity node
	SecondNode->Date = POSINFINITY;
	strcpy(SecondNode->EventName, "NONE_END");
	SecondNode->Up = NULL;
	SecondNode->Down = NULL;
	SecondNode->Right = NULL;
	
	FirstNode->Right = SecondNode;
	SecondNode->Left = FirstNode;
	SL->Top = FirstNode;											//updating the top
	
	

}

void addEmptyRowSkipList(SkipList *SL){
	SkipNode* FirstNode = (SkipNode*) malloc(sizeof(SkipNode));		//creating first -infinity node
	FirstNode->Date = NEGINFINITY;
	strcpy(FirstNode->EventName, "NONE_BEGINNING");
	FirstNode->Up = NULL;
	FirstNode->Down = SL->Top;
	FirstNode->Left = NULL;
	
	SkipNode* SecondNode = (SkipNode*) malloc(sizeof(SkipNode));	//creating second +infinity node
	SkipNode* TempNode = SL->Top;
	SecondNode->Date = POSINFINITY;
	strcpy(SecondNode->EventName, "NONE_END");
	SecondNode->Up = NULL;
	SecondNode->Right = NULL;
	
	while(TempNode->Right != NULL){									//get the far most right node (aka +infinity)
		TempNode = TempNode->Right;
	}
	
	SecondNode->Down = TempNode;									//link each -infinity and +infinity
	TempNode->Up = SecondNode;

	
	FirstNode->Right = SecondNode;
	SecondNode->Left = FirstNode;
	
	SL->Top->Up = FirstNode;										//update the new top of list, along with height
	SL->Top = FirstNode;
	SL->Height++;
}

RedPath* getWithPath(SkipList *SL, int Key){ 		//returns the red path, along with the name of the event (if it exists)
	RedPath *MyPath = (RedPath*) malloc(sizeof(RedPath));	
	SkipNode *Traverse = SL->Top;
	MyPath->ListOfNodes = NULL;
	strcpy(MyPath->EventName, "");
	
 	while(Traverse != NULL){						//while there is still a bottom level

		 if(Traverse->Date == Key){					//if the current node is equal to the node we want, go down until we hit the bottom of the list, adding to the "Red Path"
			 strcpy(MyPath->EventName, Traverse->EventName);
			while(Traverse != NULL){
				insertSkipNodeToListOfSkipNodes(&(MyPath->ListOfNodes), Traverse);	//spot where we need to insert the new date after			
				Traverse = Traverse->Down;				
			} 
			return MyPath;
		}  else if(Key >= Traverse->Right->Date){ 	//if K >= NextKey, scan forward
			Traverse = Traverse->Right;
			
		} else if(Key < Traverse->Right->Date){		//if K < NextKey, drop down
			
			insertSkipNodeToListOfSkipNodes(&(MyPath->ListOfNodes), Traverse); 	//spot where we need to insert the new date after
			
			if(Traverse->Down == NULL){				//need to drop down, but we are at the bottom of the list, so return the path (element not found)
				return MyPath;
			} else {
				Traverse = Traverse->Down;
			}

		} 
	}  			
	
}

void printSkipList(SkipList *SL){
	int ListNum = SL->Height;
	SkipNode *Temp = SL->Top;
	SkipNode *Traverse;
	int AnythingPrinted = 0;
	
	while(Temp != NULL){			//while there are still nodes in the list
		AnythingPrinted = 0;
		Traverse = Temp;
		printf("S(%d)", ListNum); 
		while(Traverse != NULL){	//traverse each node in each "ListNum" list
			if(Traverse->Date != 0 && Traverse->Date != 9999){
				printf(" %.4d:%s", Traverse->Date, Traverse->EventName);			
				AnythingPrinted = 1;
			}
			Traverse = Traverse->Right; 
		}
		if(AnythingPrinted == 0){
			printf(" empty");
		}
		ListNum--;
		Temp = Temp->Down;			//go down one level, repeat until no more lists
		printf("\n");
	}
}

char* get(SkipList *SL, int Key){
	RedPath *MyPath = getWithPath(SL, Key);			//find and store the red path
	
	if(strcmp(MyPath->EventName, "") != 0){			//if an event was found, return the name
		return MyPath->EventName;
	} else return NULL;								//else it isn't in the skiplist
			
}

char* put(SkipList *SL, int Key, char NewName[100]){
	RedPath *MyPath = getWithPath(SL, Key);					//find and store the red path

	 if(strcmp(MyPath->EventName, "") != 0){				//value exists already, return old value 
		char *OldName = (char*) malloc(sizeof(char)*100);
		ListOfSkipNodes *TraverseRP = MyPath->ListOfNodes;
		while(TraverseRP != NULL){
			if(TraverseRP->Node->Date == Key){				//if we find the date, update it with the new event
				strcpy(OldName, TraverseRP->Node->EventName);
				strcpy(TraverseRP->Node->EventName, NewName);		
			}
			TraverseRP = TraverseRP->Next;
		}
		return OldName;
	} else {												//value doesn't exist, add the new values, return null
		int NewHeight = getRandHeight();
		int h = SL->Height;	

		
	
		ListOfSkipNodes *TraverseRP = MyPath->ListOfNodes;	//start at the beginning of the red path
		SkipNode* TempNode = NULL;
		SkipNode* PrevNode = NULL;

		while(TraverseRP != NULL){							
			SkipNode* NewNode = (SkipNode*) malloc(sizeof(SkipNode));	//allocate a new node for each 
			NewNode->Date = Key;
			strcpy(NewNode->EventName, NewName);
			NewNode->Up = NULL;
			NewNode->Down = NULL;
			NewNode->Left = NULL;
			NewNode->Right = NULL;
			if(NewHeight >= h){											//if the new height is > = the current height, add the node in
				NewNode->Right = TraverseRP->Node->Right;
				NewNode->Left = TraverseRP->Node;
				TraverseRP->Node->Right->Left = NewNode;
				TraverseRP->Node->Right = NewNode;
			
				if(PrevNode != NULL && NewHeight > h){					//if not at the top of the list, add the above and or below nodes
					NewNode->Up = PrevNode;
					PrevNode->Down = NewNode;
				} 
			}
			h--;					
			
			PrevNode = NewNode;					//setting PrevNode to current redpath node
			TraverseRP = TraverseRP->Next;		//moving forward in the list
			
		}
		if(SL->Top->Right->Date != 9999){		//if the top of the list is not empty, add a row
			addEmptyRowSkipList(SL);			
		}
		return NULL;
		
	} 
}

char* removeDate(SkipList *SL, int Key){
	RedPath *MyPath = getWithPath(SL, Key);		//find and store the red path

	if(strcmp(MyPath->EventName, "") == 0){		//if the event wasn't found, return null (can't remove something that doesn't exist)
		return NULL;
	} else {									//key exists, go through the list and update the pointers accordingly
		char *RemovedName = (char*) malloc(sizeof(char)*100);
		ListOfSkipNodes *TraverseRP = MyPath->ListOfNodes;
		SkipNode *FoundNode = NULL;
		while(TraverseRP != NULL){
			if(TraverseRP->Node->Date == Key){
				FoundNode = TraverseRP->Node;
				strcpy(RemovedName, FoundNode->EventName);
				break;
			}			
			TraverseRP = TraverseRP->Next;
		}
		SkipNode *TempNode = NULL;
		while(FoundNode != NULL){				//go through delete each node
			
			TempNode = FoundNode->Left;			//set nodes left = to nodes right, vice versa, theb free the nodes
			TempNode->Right = FoundNode->Right;
			FoundNode->Right->Left = TempNode;
			FoundNode = FoundNode->Down;
			
			if(TempNode->Date == 0 && TempNode->Right->Date == 9999){	//if list is empty, remove the top, update the top and decrease the height
				SL->Top = TempNode;
				free(TempNode->Up);
				TempNode->Up = NULL;
				TempNode->Right->Up = NULL;
				SL->Height--;
			}
			
		}
		
		free(FoundNode);						//since the nodes are all connected, free up the last foundnode, will get rid of everything else
		return RemovedName;
		
		
	}
}

SkipNode* ceilingEntry(SkipList *SL, int Key){
	RedPath *MyPath = getWithPath(SL, Key);		//find and store the red path
	
	ListOfSkipNodes *TraverseRP = MyPath->ListOfNodes;
	
	while(TraverseRP->Next != NULL){
		TraverseRP = TraverseRP->Next;
	}

	if(TraverseRP->Node->Date >= Key){			//if current node is >= the key, return that node
		return TraverseRP->Node;
	} else if(TraverseRP->Node->Right->Date != 9999 && TraverseRP->Node->Right->Date >= Key){	//else the right should be the ceiling of the key we are looking for
		return TraverseRP->Node->Right;
	} else return NULL;							//else it doesn't exist, return null
		

}

SkipNode* floorEntry(SkipList *SL, int Key){
	RedPath *MyPath = getWithPath(SL, Key);		//find and store the red path
	
	ListOfSkipNodes *TraverseRP = MyPath->ListOfNodes;
	
	while(TraverseRP->Next != NULL){
		
		TraverseRP = TraverseRP->Next;
		
	}
	
	if(TraverseRP->Node->Date <= Key){			//if current node is <= the key, return that node
		return TraverseRP->Node;
	} else if(TraverseRP->Node->Left->Date != 0 && TraverseRP->Node->Left->Date <= Key){		//else the left should be the floor of the key we are looking for
		return TraverseRP->Node->Left;
	} else return NULL;							//else it doesn't exist, return null
	 

}

SkipNode* subMap(SkipList *SL, int Key1, int Key2){
	
	SkipNode *Ceiling = ceilingEntry(SL, Key1);
	SkipNode *Floor = floorEntry(SL, Key2);
	
	if(Floor != NULL && Ceiling != NULL){		//if both are not NULL, return ceiling of the first entry, stop at the floor of second entry
		return Ceiling;
	} else return NULL;							//else return NULL
}

void displayAllEvents(SkipList *SL){
	int ListNum = SL->Height;

	SkipNode *Temp = SL->Top;
	SkipNode *Traverse;
	if(Temp->Down == NULL && Temp->Right->Date == 9999){									//if date starts at the end, doesn't exist in the list, return NULL
		printf("none");
	} else {
		while(Temp != NULL){	
			Traverse = Temp;
			if(ListNum == 0){																//same as printskiplist, just print the bottom without s(n) format and only the bottom "row"
				while(Traverse != NULL){
					if(Traverse->Right != NULL && Traverse->Right->Date == 9999){			//if at the end of the list, don't include the extra space
						printf("%.4d:%s", Traverse->Date, Traverse->EventName);	
					}
					else if(Traverse->Date != 0 && Traverse->Date != 9999 ){		
						printf("%.4d:%s ", Traverse->Date, Traverse->EventName);			
					}
					Traverse = Traverse->Right; 
				}
			}
			ListNum--;
			Temp = Temp->Down;																//move down below the bottom list to end the loop
				

		}
	}
	printf("\n");
}




