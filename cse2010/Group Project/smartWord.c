/*

  Authors (group members): Brian Massino, Brandon DuPree, Zachary Holcomb, Edouard Gruyters
  Email addresses of group members: bmassino2017@my.fit.edu, bdupree2017@my.fit.edu, zholcomb2017@my.fit.edu, egruyters2017@my.fit.edu
  Group name:

  Course: CSE 2010
  Section: 4

  Description of the overall algorithm:


*/


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "smartWord.h"

#define STR_LEN 100 
#define LIST_LEN 26

/*
  Description for each function, parameter, and return value (if any)
 */
typedef struct word_node {
	unsigned short pop; //Word's Popularity
	struct word_node *next; //Pointer to the next word
	char *word; //Holds the word
}word_node;

typedef struct prev_word {
	struct prev_word *next; //Pointer to the next word
	char *word; //Holds the word
}prev_word;

word_node *list[LIST_LEN]; //Array to hold the different linked list for each letter
char target[STR_LEN] = ""; //Holds the word that is being typed in
word_node *start = NULL; //Pointer to the start of the first occurence of the word with the same first letters
word_node *guess[3]; //Holds 3 pointers to the 3 most frequently used words
prev_word *prev = NULL; //List to hold all the used words

void insertWord(char *word); //Insert the word into the linked lists
void insertPrevWord(char *word); //Insert the word to the already used word list

// initialize smartWord by process a file of English dictionary words
void initSmartWord(char *wordFile) {
	FILE *words = fopen(wordFile, "r"); //Open the word.txt file
	char str[STR_LEN] = "\0"; //Temp to hold the word
	char index = 0; //Index to assign the words to the letter list
	char currentChar = 'a'; //Current character of which list to add the word to
	word_node *current = NULL; //Hold the last used word_node
	while(fscanf(words, "%s", str) != EOF) { //Cycle through all the word
		if(str[0] >= 'A' && str[0] <= 'Z') { //If the first letter of string is uppercase
			str[0] += 32; //Convert capital 
		}
		if(str[0] > currentChar) { //If the first character of the word is greater then the current char
			index++; //Increment the index
			currentChar++; //Increment the character
		}
		
		word_node *new_word = (word_node *)malloc(sizeof(word_node)); //Malloc the word
		new_word->pop = 0; //Set the popularity
		new_word->next = NULL;
		new_word->word = (char*) malloc(sizeof(char)*strlen(str));
		strcpy(new_word->word, str); //Copy the word to created struct
		
		if(list[index] == NULL) { //Check if the start of the list is empty
			list[index] = new_word; //Add the node to the start of the list
			current = list[index]; //Upadate the current to the start of the list
		} else {
			current->next = new_word; //Add the node to the end of the list
			current = current->next; //Move to the end of the list
		}
	}
	fclose(words); //Close the file
}


// process old messages from oldMessageFile
void procOldMsgSmartWord(char *oldMessageFile) {
	FILE *oldMessage = fopen(oldMessageFile, "r"); //Open the old messages
	char str[STR_LEN] = "\0"; //Holds the copied word
	while(fscanf(oldMessage, "%s", str) != EOF) { //Loop through all the words in the file
		for(int i = 0; i < strlen(str); i++) { //Cycle through the letters
			if(str[i] > 64 && str[i] < 91) { //If the first letter of string is uppercase
				str[i] += 32; //Convert capital 
			} else if(str[i] > 'z' || str[i] < 'a') { //Check if letter is not in the alphabet
				for(int j = i; j < strlen(str); j++) { //Loop through the remaining letters in the string
					str[j] = str[j + 1]; //Shift all the letter to the left
				}
				i--; //Decrement to prevent any non-alphabetical characters from being skipped
			}
		}
		char flag = 1; //Flag to check if the word exists within our dictionary
		if(str[0] - 'a' >= 0) { //Check if the word exists
			word_node *current = list[str[0] - 'a']; //Get the start of the appropriate list of words.
			while(current != NULL && flag) { //Loop through all the words and whilest the flag is true
				if(strcmp(str, current->word) == 0) { //Check if the word from the file is equal to the word in the dictionary
					current->pop++; //Increase the words popularity
					flag = 0; //Set the flag to false
				}
				current = current->next; //Move to the next word
			}
		}
		if(flag) { //If the flag is still true
			insertWord(str); //Insert the word into the word list
		}
	}
	
	//Remove duplicate words
	for(int i = 0; i < LIST_LEN; i++) { //Cycle through the letter array
		word_node *current = list[i]; //Pointer to the start of the letter linked list
		while(current->next != NULL) { //Cycle through the linked list
			if(strcmp(current->word, current->next->word) == 0) { //If the sequencial words are the same
				word_node *temp = current->next; //Get the duplicate word
				current->pop += temp->pop; //Add the duplicates frequentcy
				current->next = temp->next; //Set next's pointer to temp's next
				temp->next = NULL; //Set the next pointer to NULL
				free(temp); //Remove the duplicate entry
			} else { //Prevents duplicate words from being skipped
				current = current->next; //Move 
			}
		}
	}
	fclose(oldMessage); //Close the file
}

// Given:
//   letter: letter typed in by the user (a-z, A-Z)
//   letterPosition:  position of the letter in the word, starts from 0
//   wordPosition: position of the word in a message, starts from 0
// Return via a parameter:
//   gueses: NUM_GUESSES (3) word guesses (case-insensive comparison is used) 

void guessSmartWord(char letter, int letterPosition, int wordPosition, char guesses[NUM_GUESSES][MAX_WORDLEN+1]) {
	for(int i = 0; i < NUM_GUESSES; i++) { //Go through all the guesses
		guess[i] = NULL; //Clear the guess
	}
	if(letter > 64 && letter < 91) { //If the first letter of string is uppercase
		letter += 32; //Convert capital 
	}
	target[letterPosition] = letter; //Add the letter to the word
	
	if(start == NULL) { //Check if this is the first letter
		start = list[letter - 'a']; //Get the start of the appropriate list of words
		word_node *current = start; //Get the start of the list of words
		while(current != NULL) { //Loop through the list of word
			if(guess[0] == NULL) { //Check if the first guess is empty
				guess[0] = current; //Insert the word into the first guess
			} else if(guess[1] == NULL) { //Check if the second guess is empty
				guess[1] = current; //Insert the word into the second guess
			} else if(guess[2] == NULL) { //Check if the third guess is empty
				guess[2] = current; //Insert the word into the third guess
			} else if(guess[0]->pop < current->pop) { //Check if the first guesses popularity is less than the current's popularity
				guess[0] = current; //Set the first guess to the word
			} else if(guess[1]->pop < current->pop) { //Check if the second guesses popularity is less than the current's popularity
				guess[1] = current; //Set the second guess to the word
			} else if(guess[2]->pop < current->pop) { //Check if the third guesses popularity is less than the current's popularity
				guess[2] = current; //Set the third guess to the word
			}
			current = current->next; //Move to the next word
		}
		
	} else {
		word_node *current = start; //Get the start of the list
		while(strncmp(current->word, target, letterPosition + 1) < 0) { //Loop until we reached the first word with equal letters
			current = current->next; //Move to the next word
		}
		start = current; //Set the start to the current word
		
		while(current != NULL && strncmp(current->word, target, letterPosition + 1) <= 0) { //Loop through the words and check if the words have the same letters
			char flag = 1;
			prev_word *current2 = prev; //Start of the prev list
			while(current2 != NULL && flag) { //Loop through all the used words
				if(strcmp(current2->word, current->word) == 0) { //Check if the word has been used before
					flag = 0; //Set flag to false
				}
				current2 = current2->next; //Move to the next word
			}
			if(flag) { //If word hasn't been used before
				if(guess[0] == NULL) { //Check if the first guess is empty
					guess[0] = current; //Insert the word into the first guess
				} else if(guess[1] == NULL) { //Check if the second guess is empty
					guess[1] = current; //Insert the word into the second guess
				} else if(guess[2] == NULL) { //Check if the third guess is empty
					guess[2] = current; //Insert the word into the third guess
				} else if(guess[0]->pop < current->pop) { //Check if the first guesses popularity is less than the current's popularity
					guess[0] = current; //Set the first guess to the word
				} else if(guess[1]->pop < current->pop) { //Check if the second guesses popularity is less than the current's popularity
					guess[1] = current; //Set the second guess to the word
				} else if(guess[2]->pop < current->pop) { //Check if the third guesses popularity is less than the current's popularity
					guess[2] = current; //Set the third guess to the word
				}
			}
			current = current->next; //Move to the next word
		}
	}
	
	// just to show how to return 3 (poor) guesses
	if(guess[0] != NULL) { //Check if the first guess exists
		strcpy(guesses[0], guess[0]->word);
		insertPrevWord(guess[0]->word); //Add the word to the already used list
	} else {
		char temp[STR_LEN] = ""; //Create an empty string
		strcpy(temp, target); //Copy the target guessing word to created string
		strcat(temp, "ing"); //Add the plural ending
		strcpy(guesses[0], temp); //Give a spaceholder suggestion
	}
	if(guess[1] != NULL) { //Check if the second guess exists
		strcpy(guesses[1], guess[1]->word);
		insertPrevWord(guess[1]->word); //Add the word to the already used list
	} else {
		char temp[STR_LEN] = ""; //Create an empty string
		strcpy(temp, target); //Copy the target guessing word to created string
		strcat(temp, "ed"); //Add the plural ending
		strcpy(guesses[1], temp); //Give a spaceholder suggestion
	}
	if(guess[2] != NULL) { //Check if the third guess exists
		strcpy(guesses[2], guess[2]->word);
		insertPrevWord(guess[2]->word); //Add the word to the already used list
	} else {
		char temp[STR_LEN] = ""; //Create an empty string
		strcpy(temp, target); //Copy the target guessing word to created string
		strcat(temp, "s"); //Add the plural ending
		strcpy(guesses[2], temp); //Give a spaceholder suggestion
	}
}





// feedback on the 3 guesses from the user
// isCorrectGuess: true if one of the guesses is correct
// correctWord: 3 cases:
// a.  correct word if one of the guesses is correct
// b.  null if none of the guesses is correct, before the user has typed in 
//            the last letter
// c.  correct word if none of the guesses is correct, and the user has 
//            typed in the last letter
// That is:
// Case       isCorrectGuess      correctWord   
// a.         true                correct word
// b.         false               NULL
// c.         false               correct word

// values for bool: true (1), false (0)  
void feedbackSmartWord(bool isCorrectGuess, char *correctWord) {
	if(correctWord != NULL) {
		if(isCorrectGuess) {
			if(guess[0] != NULL && strcmp(guess[0]->word, correctWord) == 0) { //Check if the first guess is equal to the correct word
				guess[0]->pop++; //Increase the popularity of the word
			} else if(guess[1] != NULL && strcmp(guess[1]->word, correctWord) == 0) { //Check if the second guess is equal to the correct word
				guess[1]->pop++; //Increase the popularity of the word
			} else if(guess[2] != NULL && strcmp(guess[2]->word, correctWord) == 0) { //Check if the third guess is equal to the correct word
				guess[2]->pop++; //Increase the popularity of the word
			} else {
				insertWord(correctWord); //Insert the word into the word list
			}
		} else {
			insertWord(correctWord); //Insert the word into the word list
		}
		for(int i = 0; i < STR_LEN; i++) { //Loop through all the letters of the target string
			target[i] = '\0'; //Reset the letters in the target string
		}
		while(prev != NULL) { //Cycle through all the used words
			prev_word *toRemove = prev; 
			prev = prev->next;
			toRemove->next = NULL; //Set next to NULL
			free(toRemove); //Remove the word
		}
		start = NULL; //Set the start to NULL
	}
}

//Insert the word into array of linked lists
void insertWord(char *word) {
	if(word[0] - 'a' >= 0) {
		word_node *new_word = (word_node *)malloc(sizeof(word_node)); //Malloc the word
		new_word->pop = 1; //Set the popularity
		new_word->next = NULL; //Set the next to NULL
		new_word->word = (char*) malloc(sizeof(char)*strlen(word)); //Create a word struct
		strcpy(new_word->word, word); //Copy the word to created struct
				
		if(strcmp(list[word[0] - 'a']->word, word) > 0) { //Add to the head of the list
			new_word->next = list[word[0] - 'a']; //Set the word next to the head
			list[word[0] - 'a'] = new_word; //Set the list head to the word
		} else { //Insert to the list
			word_node *current2 = list[word[0] - 'a']; //Get the start of the appropriate list of words.
			while(current2->next != NULL) { //Loop through the words
				if(strcmp(current2->next->word, word) > 0) { //Check if the word is less than the current word
					new_word->next = current2->next; //Insert the word into the list
					current2->next = new_word;
					break; //End the while loop
				}
				current2 = current2->next; //Move to te next word
			}
		}
	}
}

void insertPrevWord(char *word) {
	prev_word *temp = (prev_word *)malloc(sizeof(prev_word)); //Malloc the prev word
	temp->next = NULL; //Set next to NULL
	temp->word = (char*) malloc(sizeof(char)*strlen(word)); //Create a word struct
	strcpy(temp->word, word); //Copy the word to
	
	if(prev == NULL) { //If list is empty
		prev = temp; //Initialize list
	} else {
		temp->next = prev;
		prev = temp; //Add to the front
	}
}

//Keep track of the last used word, prevent duplicating words
//Check for captilization depending on the position within the sentence
//Keep an average of word length