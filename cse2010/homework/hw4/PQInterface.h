#include "PQTypes.h"

extern void Initialize(PriorityQueue *PQ);					
extern int IsEmpty(PriorityQueue *PQ);						//True if PQ is full
extern int IsFull(PriorityQueue *PQ);						//True if PQ is full
extern void Insert(PQItem Item, PriorityQueue *PQ);			//Puts item into PQ
extern PQItem RemoveMin(PriorityQueue *PQ);					//Removes item from PQ
extern PQItem GetMin(PriorityQueue *PQ);					//returns the minimum item from PQ without removing it
