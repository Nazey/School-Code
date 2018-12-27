#include "PQInterface.h"


void Initialize(PriorityQueue *PQ){	
	PQ->Count = 0;
}

int IsEmpty(PriorityQueue *PQ){
	return (PQ->Count == 0);
}

int IsFull(PriorityQueue *PQ){
	return (PQ->Count == MAXCOUNT);
}

void Insert(PQItem Item, PriorityQueue *PQ){
	int ChildLoc;														//location of current child
	int ParentLoc;														//parent of current child
	
	(PQ->Count)++;
	ChildLoc = PQ->Count;												//Caution: insertion does not
	ParentLoc = ChildLoc/2;												//guard against overflow
	
	while(ParentLoc != 0){												//while a parent still exists
		if(Item.Key >= PQ->ItemArray[ParentLoc].Key){
			PQ->ItemArray[ChildLoc] = Item;									//Store item
			return;															//and return
		} else {
			PQ->ItemArray[ChildLoc] = PQ->ItemArray[ParentLoc];
			ChildLoc = ParentLoc;
			ParentLoc = ParentLoc/2;
		}
	}
	PQ->ItemArray[ChildLoc] = Item; 									//put item in final resting place
}

PQItem RemoveMin(PriorityQueue *PQ){
	int CurrentLoc;														//location currently being examined
	int ChildLoc;														//a child of CurrentLoc
	PQItem ItemToPlace;													//an Item value to relocate
	PQItem ItemToReturn;												//the removed Item value to return
		
	//Initializations
	ItemToReturn = PQ->ItemArray[1];									//value to return later
	ItemToPlace = PQ->ItemArray[PQ->Count];								//last leaf's value
	(PQ->Count)--;														//delete last leaf in level order
	CurrentLoc = 1;														//CurrentLoc starts at root
	ChildLoc = 2*CurrentLoc;											//ChildLoc starts at root's left child
		
	while(ChildLoc <= PQ->Count){										//while a child still exists
		
		//Set ChildLoc to location of smaller child of CurrentLoc
		if(ChildLoc < PQ->Count){										//if right child exists
			if(PQ->ItemArray[ChildLoc+1].Key < PQ->ItemArray[ChildLoc].Key){
				ChildLoc++;
			}
		}
		
		//if item at ChildLoc is smaller than ItemToPlace, 
		//move this smaller item to CurrentLoc, and move CurrentLoc down
		if(PQ->ItemArray[ChildLoc].Key >= ItemToPlace.Key){
			PQ->ItemArray[CurrentLoc] = ItemToPlace;
			return ItemToReturn;
		} else {
			PQ->ItemArray[CurrentLoc] = PQ->ItemArray[ChildLoc];
			CurrentLoc = ChildLoc;
			ChildLoc = 2*CurrentLoc;
		}
	}
	//Final placement of ItemToPlace
	PQ->ItemArray[CurrentLoc] = ItemToPlace;

	//return item originally at root
		return ItemToReturn;
}

PQItem GetMin(PriorityQueue *PQ){
	return PQ->ItemArray[1];
}
