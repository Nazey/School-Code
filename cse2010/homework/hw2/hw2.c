/*

  Author: Brian	Massino	
  Email: bmassino2017@my.fit.edu	
  Course: CSE 2010	
  Section: 4
  Description: hw2.c

  
  GROUP HELP UPDATED
  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define LEN 10000


typedef struct wordList{ //defining the struct for the linked list, will contain a string
		char phrase[LEN];
		struct wordList *next;
}wordList;


int isPalindrome(char *s, int size); //returns 1 if string is a palindrome, 0 if not a palindrome.

int isPalDriver(char *s, int b, int e); //takes in a string, condenses it to no spaces.

void computePermutations(int PL, char *phrase); //recursive function to find all the variations of the string given palLength.

void addList(wordList **list, char *s); //adds a string to the specified linked list

void sortAlphabetically(wordList **list); //uses mergesort on the linked list and strcmp to sort the linked list recursively

wordList* sAHelper(wordList *a, wordList *b); //helper function for sortAlphabetically

void split(wordList *source, wordList **frontRef, wordList **backRef); //splits the list into 2 parts in order to make the sorting more efficient

wordList* copyList(wordList **list); //returns a copy of the passed through wordList, as another wordList

int checkDuplicate(char *string); //checks to see if a string has more than 1 word inside of it, which in this case is NOT a permutation.

void print(wordList **list); //function to print out all elements in list

int palLength = 0; //number of words in each permutation

wordList *head = NULL; //Linked list containing all of the words taken in from input file

wordList* permutationsOfPalindromes = NULL; //linked list containing the final list of palindromes of palLength words, sorted alphabetically

int main(int argc, char *argv[]){
   
	FILE *fin = fopen(argv[1], "r"); //opening file from command line
	
	char input[35] = ""; //buffer for file inputs
	
	palLength = atoi(argv[2]); //setting palLength to user input.
	
	 while(!feof(fin)){ //taking in input, line by line, and storing it in the linked list for future use.
		fscanf(fin, "%s", input); 
		addList(&head, input);
	} 	
	fclose(fin); //closing file
	
    char tempString[100] = ""; //setting up a temp string to be able to contain the phrases inside of.
    computePermutations(palLength, tempString);
    
	sortAlphabetically(&permutationsOfPalindromes); //sort the palindromes alphabetically.
     //print the palindromes.
    print(&permutationsOfPalindromes); 
  
}

int isPalindrome(char *s, int size){ //first sets up a copy of the string to manipulate.
	char *newString = (char*) malloc(sizeof(char)*size);
	int space = 0;
		
	for(int i = 0; i<strlen(s); i++){ //use a for loop to copy each character to the new string
		if(isspace(s[i])){
			space++;
		} else {
			newString[i-space] = s[i]; //if there is a space, subtract i by space, so that the string stays the same, but without spaces.
		}
	}
	newString[strlen(s)-space] = '\0'; //set null character.
	
	return isPalDriver(newString, 0, strlen(newString)-1);
	
}

int isPalDriver(char *s, int b, int e){ //takes in a string, condenses it to no spaces. b = beginning of string position, e = end of string posistion
	
	if(b == e || ((e-b == 1) && s[b] == s[e])){ //base case, if each character in the string matches up with each other,
		return 1;								//it is a palindrome, return 1. Accounts for 1 char strings like 'i' 
	}
	
	if(s[b] == s[e]){ //if both characters are matching, recursively call again until base case, else it's not a palindrome.
		return isPalDriver(s, b+1, e-1);
	} else {
		return 0;
	}
	
	
}

void addList(wordList **list, char *s){ //adds a new string to the specified wordList.
	wordList *tempnode, *newnode;
    newnode = (wordList*) malloc(sizeof(wordList));    
	newnode->next = NULL; 
	strcpy(newnode->phrase, s);
    
    if(*list == NULL){ //if empty, set list = newnode
        *list = newnode;
    } else { //traverse through list, add to end
        tempnode = *list; 
        while(tempnode->next!=NULL){
             tempnode = tempnode->next;
        }
        tempnode->next = newnode;
        
    }
	
}

void computePermutations(int PL, char *thePhrase){ //recursive function to find all permutations
	
	
	if(PL == 0){ //base case, if there are no more words to compute permutation of
		if(isPalindrome(thePhrase, strlen(thePhrase)) == 1){ //if it is a palindrome
            if(checkDuplicate(thePhrase) != 1){ //make sure it is not a duplicate phrase
                addList(&permutationsOfPalindromes, thePhrase); //add to the list of palindromes
            }
        }
	} else { //inductive case, find all permutations of current word
		wordList *traverse; //traversing through the list
	    traverse = head;
		
		while(traverse != NULL){ 
			if(traverse->next == NULL)
				break;
			int index = strlen(thePhrase); //finding last index of thePhrase   
			if(strcmp(thePhrase, "") != 0){ //checks to see if it isnt an empty word before adding a space
				strcat(thePhrase, " ");
			}
			strcat(thePhrase, (traverse)->phrase); //copy phrase into thePhrase
			computePermutations(PL-1, thePhrase); //recursively call on itself			
            thePhrase[index] = '\0'; //make sure it is a "string"			
		    traverse = traverse->next; //on to the next word
		}		
	} 
}

void sortAlphabetically(wordList **list){ //using mergesort
	wordList *head = *list; 
    wordList *a; 
    wordList *b; 
  
    
	if ((head == NULL) || (head->next == NULL)) { //base case, if = 0 or 1
		return; 
	} 
  
   
    split(head, &a, &b); //split into 2 sublists 
  

	sortAlphabetically(&a); //sorting the first list
	sortAlphabetically(&b); //sorting the second list
 
	
	*list = sAHelper(a, b); //merge the two lists together
}

wordList* sAHelper(wordList *a, wordList *b) { //does merging of 2 lists
	wordList *result = NULL; 
  

	if(a == NULL){ 	//base case, if a is NULL, there is only b left, return b
		return(b); 
	} else if(b == NULL){ //if b is NULL, there is only a left, return a
		return(a); 
	} 
		
	
	if(strcmp(a->phrase, b->phrase) <= 0) { //inductive
		result = a; 
		result->next = sAHelper(a->next, b); 
	} else { 
		result = b; 
		result->next = sAHelper(a, b->next); 
	} 
	
	return(result); 	
}

void split(wordList *source, wordList **frontRef, wordList **backRef){ 
    wordList *slow; 
    wordList *fast; 
    slow = source; 
    fast = source->next; 
 
    while (fast != NULL){  //fast will be 2 nodes ahead slow 1 node
		fast = fast->next; 
		if (fast != NULL){ 
			slow = slow->next; 
			fast = fast->next; 
		} 
    }
	
    *frontRef = source; //slow is before midpoint, so split at slow
    *backRef = slow->next; 
    slow->next = NULL; 
} 

int checkDuplicate(char *string){ //finds duplicate strings 
    char stemp[LEN];
    char stringArray[palLength][LEN];
    strcpy(stemp, string); //copying the string so we can modify it
    char *token = strtok(stemp, " ");
	
    for(int i = 0; i< palLength; i++){ //dividing up the string into an array of strings to check for duplicates
        strcpy(stringArray[i], token);
        token = strtok(NULL, " ");
    }
    
    for(int i = 0; i < palLength; i++){ 
        for(int j = 0; j < palLength; j++){
            if(i != j){ //if i == j dont compare, it is the same string!
                if(strcmp(stringArray[i], stringArray[j]) == 0){ //if it is a duplicate, return 1
					return 1;
					
                } 
            }
        }
    }
    
    return 0; //else it's not a duplicate
    
}


void print(wordList **list){ //takes in wordList to traverse
    wordList *tempnode;
	
    if(*list != NULL){ //check first if list is empty
        tempnode = *list;
        while(tempnode != NULL){ //while list not null, traverse and print through.
			printf("%s\n", tempnode->phrase);
            tempnode = tempnode->next;
        }
       
    }
}
