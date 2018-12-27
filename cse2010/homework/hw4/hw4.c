/*

  Author: Brian Massino	
  Email: bmassino2017@my.fit.edu
  Course: CSE2010	
  Section: 4 
  Description: hw4

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "PQInterface.h"

typedef struct Customer{		//struct to define a customer, with a name and 10 rated songs, as well as the distance
	char Name[11];
	int RatedSongs[10];
	double Distance;
}Customer;
														
void InsertCustomer(Customer *CustomerList[100], char CustomerNameToAdd[11], 								//function inserts customer alphabetically into the given list of customers
int CustomerRatedSongs[10], int Size);	
																	
Customer* FindCustomer(Customer *CustomerList[100], char CustomerNameToFind[11], int SizeOfCustomerList);	//finds given customer name based on the given list of customers (binary search)

double FindDistance(Customer *TargetCustomer, Customer *ComparingCustomer);									//returns the distance between target customer and the closest customer

void PrintCustomerDistanceRatings(Customer *CustomerList[100], int 
SizeOfCustomerList, char TargetCustomerName[11]);	
																											//Prints customer distance ratings from the given list of customer, the size of the list, and the name of the target customer
void CalculateInitialDistancesAndAddToHeap(Customer *CustomerList[100], PriorityQueue *CQ,
 int SizeOfCustomerList, char TargetCustomerName[11]);														//calculates the distances of each customer and adds it to the heap

void RecommendSongs(Customer *CustomerList[100], PriorityQueue *CQ, int SizeOfCustomerList, Customer *TC);  //prints the closest song along with the rating (4 or 5)
																											//found a song to reccomend, or 0 if it wasn't successful

int main(int argc, char* argv[]){
	Customer *AllCustomers[100];			//initializing the array of structs as well
	PriorityQueue CustomerQueue;			//as the heap to store the smallest/closest customer to the TargetCustomer
	Initialize(&CustomerQueue);
	
	for(int i = 0; i < 100; i++){
		AllCustomers[i] = NULL;
	}
	
	FILE *fin = fopen(argv[1], "r");		//opening data file with initial customers and song ratings
	char TargetCustomerName[11];			//all variables are used to create a customer struct and insert it into the list of customer structs
	char CustomerName[11];
    int RatedSongs[10];
	int size = 0;
	fscanf(fin, "%s", TargetCustomerName);
	
	while(!feof(fin)){

		fscanf(fin, "%s %d %d %d %d %d %d %d %d %d %d", CustomerName, &RatedSongs[0], &RatedSongs[1], &RatedSongs[2],			//Since we know that there will be a string 
		&RatedSongs[3], &RatedSongs[4], &RatedSongs[5], &RatedSongs[6], &RatedSongs[7], &RatedSongs[8], &RatedSongs[9]);		//followed by 10 numbers, just fscanf all of it in																							
		InsertCustomer(AllCustomers, CustomerName, RatedSongs, size);															//insert the customer into the array
		size++;	
	}
	fclose(fin);		//closing first data file

	CalculateInitialDistancesAndAddToHeap(AllCustomers, &CustomerQueue, size, TargetCustomerName);		//calculate the distances now that we know the target 
																										//customer is inside of the array of pointers
																				
	fin = fopen(argv[2], "r");			//opening input file
	char buffer[50];					//buffer stores each line from the input file
	Customer *TargetCustomer = FindCustomer(AllCustomers, TargetCustomerName, size);
	
	while(!feof(fin)){
		fgets(buffer, sizeof(buffer), fin); 		
		if(buffer[strlen(buffer)-1] == '\n'){							//removes the trailing \n character from each line, 
				buffer[strlen(buffer)-2] = '\0';						//unless the line is the last line in the file, in which case it does not have a \n
		}
		char *parse = strtok(buffer, " ");
		if(strcmp(parse, "AddCustomer") == 0){							//if we need to add a customer, parse the name and 10 songs out, calculate the distance, 
			Customer *NewCustomer = NULL;								//increase size of, insert into the list alphabetically, and insert that new customer into the heap
			parse = strtok(NULL, " ");
			strcpy(CustomerName, parse);
			printf("AddCustomer %s", CustomerName);
			parse = strtok(NULL, " ");
			for(int i = 0; i < 10; i++){
				RatedSongs[i] = atoi(parse);
				printf(" %d", RatedSongs[i]);
				parse = strtok(NULL, " ");
			}
			printf("\n");
			
			InsertCustomer(AllCustomers, CustomerName, RatedSongs, size);		//insert customer into the array, increase the size, find 
			size++;																//that customer, then calculate the distance
			NewCustomer = FindCustomer(AllCustomers, CustomerName, size);
			NewCustomer->Distance = FindDistance(TargetCustomer, NewCustomer);	//find the distance, put it into the heap
			
			if(NewCustomer->Distance != 999){									//if the distance was calculated, add the newcustomer to the heap		
				PQItem NewEntry;												//No point in adding a customer who doesn't have a distance												
				NewEntry.Key = NewCustomer->Distance;
				strcpy(NewEntry.Name, NewCustomer->Name);
				Insert(NewEntry, &CustomerQueue);
			}			 
	
		} else if(strcmp(parse, "PrintCustomerDistanceRatings") == 0){				//print out the current customer distance ratings
			PrintCustomerDistanceRatings(AllCustomers, size, TargetCustomerName);
		} else if(strcmp(parse, "RecommendSongs") == 0){							//else print out recommended songs (if any)
			RecommendSongs(AllCustomers, &CustomerQueue, size, TargetCustomer); 
		} 
		
	}
	for(int n = 1; n <= 10; n++){
		printf("%s %f\n", CustomerQueue.ItemArray[n].Name, CustomerQueue.ItemArray[n].Key);
	}
	

	fclose(fin);	//closing input file
	
}

void InsertCustomer(Customer *CustomerList[100], char CustomerNameToAdd[11], int CustomerRatedSongs[10], int SizeOfCustomerList){	
	Customer *NewCustomer = (Customer*) malloc(sizeof(Customer));										//inserts a new customer into the customer list passed through, 
	strcpy(NewCustomer->Name, CustomerNameToAdd);														//given the name of the customer, the size of the AllCustomers list and 				
																										//the rated songs
	for(int i = 0; i < 10; i++){
			NewCustomer->RatedSongs[i] = CustomerRatedSongs[i];
	}
	
	if(CustomerList[0] == NULL){												//case 1: the list is empty, make the first element the new customer
		CustomerList[0] = NewCustomer;											//case 2: the first element in the list is alphabetically greater than the new customer element,
		return;																	//so shift the array over and set the first element to the new customer
	} else if(strcmp(NewCustomer->Name, CustomerList[0]->Name) < 0 ){			//case 3: else, insert somewhere in the middle of the list, or at the end
		
		for (int k = SizeOfCustomerList; k > 0; k--){        
			CustomerList[k] = CustomerList[k-1];
		}
		CustomerList[0] = NewCustomer;
		return;
	} else {		
		int i = 0;
		while(CustomerList[i] != NULL && strcmp(NewCustomer->Name, CustomerList[i]->Name) > 0){
			i++; 
		}
		for (int k = SizeOfCustomerList; k > i; k--){        
			CustomerList[k] = CustomerList[k-1];
		}
		CustomerList[i] = NewCustomer;
		return;
	}  
		
}

Customer* FindCustomer(Customer *CustomerList[100], char CustomerNameToFind[11], int SizeOfCustomerList){	//finds the given customer given size of AllCustomers and 
	int left = 0, right = SizeOfCustomerList, middle;														//the name of the customer we are looking for

	
 	while (left <= right) { 
        int middle = left + (right-left)/2; 
  
        if (strcmp(CustomerList[middle]->Name, CustomerNameToFind) == 0) 		//Check if N is present at midpoint 
            return CustomerList[middle]; 
        else if (strcmp(CustomerList[middle]->Name, CustomerNameToFind) < 0) 	//If N is greater alphabetically, ignore left half, search right half				
            left = middle + 1; 
        else																	//If N is smaller alphabetically, ignore right half, search left half 
            right = middle - 1; 
    } 
      
    return NULL;  																//If this runs, element was not found
	
}

double FindDistance(Customer *TargetCustomer, Customer *ComparingCustomer){						//we want to find the total number of songs that both have in common (both rated) and then the 
	double NumSongsCommon = 0;																	//averages of the differences in ratings 
	double DiffInRatings = 0;

	for(int i = 0; i < 10; i++){																//for each song that TargetCustomer rated and ComparingCustomer rated, 
		if (TargetCustomer->RatedSongs[i] != 0 && ComparingCustomer->RatedSongs[i] != 0){		//add numsongscommon++ and add the difference in ratings
			NumSongsCommon++;
			DiffInRatings += fabs(TargetCustomer->RatedSongs[i] - ComparingCustomer->RatedSongs[i]);;
		}
	}
	
	if(NumSongsCommon != 0){										//if there was at least one comparable song, return the distance
		DiffInRatings = (DiffInRatings/fabs(NumSongsCommon));
		NumSongsCommon = (1/fabs(NumSongsCommon));
		
		return (NumSongsCommon + DiffInRatings);
	} else return 999;												//else distance was not able to be calculated, return 999 as a specifier
		
}

void PrintCustomerDistanceRatings(Customer *CustomerList[100], int SizeOfCustomerList, char TargetCustomerName[11]){
   
    int Count = 0;
	Customer *TargetCustomer = FindCustomer(CustomerList, TargetCustomerName, SizeOfCustomerList-1);
																								//printing the spaces along with the name of the customer and their song ratings 
	printf("PrintCustomerDistanceRatings\n");													//(they do not have a distance to themselves)
	printf("%5s %-10s", "", TargetCustomer ->Name);
		
	for(int i = 0; i < 10; i++){
		printf(" %d", TargetCustomer ->RatedSongs[i]);			
	}
	printf("\n");	
	
	while(CustomerList[Count] != NULL){		
		if(strcmp(CustomerList[Count]->Name, TargetCustomerName) != 0){
			if(CustomerList[Count]->Distance != 999){											//if distance was able to be calculated, print distance
				printf("%.3f %-10s", CustomerList[Count]->Distance, CustomerList[Count]->Name);
			} else {																			//else print -'s to represent no distance
				printf("----- %-10s", CustomerList[Count]->Name);
			}
			
			for(int i = 0; i < 10; i++){														//print out each song rating
				printf(" %d", CustomerList[Count]->RatedSongs[i]);			
			}
			
			printf("\n");
		}
		Count++;
	}
}

void CalculateInitialDistancesAndAddToHeap(Customer *CustomerList[100], PriorityQueue *CQ, int SizeOfCustomerList, char TargetCustomerName[11]){	
																										//calculates distances based on the data
	int Count = 0;																						//file, as well as adds them to the heap 
	Customer *TargetCustomer = FindCustomer(CustomerList, TargetCustomerName, SizeOfCustomerList-1);	//finds the customer to compare to each entry inside of the array of pointers
	
	while(CustomerList[Count] != NULL){																	//while there are still items in the array
		CustomerList[Count]->Distance = FindDistance(TargetCustomer, CustomerList[Count]);				//find the distance, put it into the heap, as long
		if(CustomerList[Count]->Distance != 999){
			PQItem NewEntry;																			//as it isn't the targetcustomer
			NewEntry.Key = CustomerList[Count]->Distance;
			strcpy(NewEntry.Name, CustomerList[Count]->Name);
			if(strcmp(CustomerList[Count]->Name, TargetCustomerName) != 0)
				Insert(NewEntry, CQ);
		}
		Count++;			
		
	}	
	
}

void RecommendSongs(Customer *CustomerList[100], PriorityQueue *CQ, int SizeOfCustomerList, Customer *TC){
	Customer *ComparingCustomer = FindCustomer(CustomerList, GetMin(CQ).Name, 
	SizeOfCustomerList);																	//customer to get the songs to recommend
	Customer *TargetCustomer = TC;															//customer to recommend songs to
	int SongRecommended = 0;
	int SongIndex[10], Rating, SongDifference = 0, NumSongsRecommended = -1;				//start NumSongsRecommended at -1, so that we can each song index in to the array of song indexes
	
	while(SongRecommended == 0){
		ComparingCustomer = FindCustomer(CustomerList, GetMin(CQ).Name, SizeOfCustomerList);		
		Rating = 0; 
		SongDifference = 0; 
		NumSongsRecommended = -1;
	
	
		for(int i = 0; i < 10; i++){
			if(ComparingCustomer->RatedSongs[i] > 3 && TargetCustomer->RatedSongs[i] == 0){	//if the rating is 4 or 5 and the customer did not rate that song
				if(ComparingCustomer->RatedSongs[i] == Rating){
					NumSongsRecommended++;
					Rating = ComparingCustomer->RatedSongs[i];
					SongIndex[NumSongsRecommended] = i;
					SongRecommended = 1;
				} else if(ComparingCustomer->RatedSongs[i] > Rating){						//else reset the array, start back at the new highest rating (5), and continue
					Rating = 0;																//to see if there are any more songs we can recommend
					for(int j = 0; j <= NumSongsRecommended; j++){
						SongIndex[j] = 0;
					}
					NumSongsRecommended = 0;
					Rating = ComparingCustomer->RatedSongs[i];
					SongIndex[NumSongsRecommended] = i;
					SongRecommended = 1;
				}
			}
		}
		if(SongRecommended == 0 && !IsEmpty(CQ)){					//make sure the heap isn't empty, then remove, else there was not a song we could recommend, so end the loop
			RemoveMin(CQ);
		} else break;
	}
	
	if(SongRecommended != 0){										//if the function was able to find a customer to compare to, print out the songs
		printf("RecommendSongs %s", ComparingCustomer->Name);
		for(int k = 0; k <= NumSongsRecommended; k++)
			printf(" song%d %d", SongIndex[k], Rating);
		printf("\n");
	} else printf("RecommendSongs none\n");							//else there wasn't a song we could recommend  

}

