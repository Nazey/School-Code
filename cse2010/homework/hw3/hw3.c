/*

  Author: Brian Massino
  Email: bmassino2017@my.fit.edu
  Course: CSE 2010
  Section: 4
  Description: hw3
  note: ** means modified line
  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct TreeNode{						//individual TreeNodes, containing the name of the "company",
	struct TreeNode *Parent;				    //the TreeNode pointer to the parent node,the TreeNode list of children
	char *Name;									//a next node, to point to the other nodes under the current parent node, as well as 
	int Rank;									//an integer Rank to signify the ranking of each treenode.
	struct TreeNode *NextSibling;
	struct TreeNode *Children;

}TreeNode;

typedef struct TreeRoot{						//typedef the root of the tree, to easily identify trees, contains the first node.
	TreeNode *HeadChildren;						//contains first treenode.

}TreeRoot;

TreeNode* CreateTreeNode(char *N);										//returns a treenode based on the name of the "company"
TreeNode* FindNode(char *N, TreeNode *CurrentNode);						//returns the node matching with the corresponding string, and starts "looking" for the node from "CurrentNode".
void AddChild(TreeNode* P, TreeNode *C);								//adds a child node to the parent node (both are passed through).
TreeNode* GetParent(TreeNode *C);										//returns the pointer node to the parent of the passed node.
TreeNode* GetChildren(TreeNode *P);										//returns the pointer node to the beginning of the "children" for that parent.
void DirectSupervisor(char *SubordinateName);							//prints the direct supervisor of the given supervisor string.
void DirectSubordinates(char *SupervisorName);							//prints the direct subordinates of the given supervisor string.
void AllSupervisors(char *SubordinateName);								//prints every supervisor given the string name of the subordinate.	
void AllSubordinates(TreeNode *Node);									//prints all subordinates of a given node recursively, using preorder traversal.
void NumberOfAllSupervisors(char *SubordinateName);						//prints the number of all supervisors given the string name of subordinate.
void NumberOfAllSubordinates(char *SupervisorName);						//prints the number of all subordinates given the string name of supervisor.
void CountAllSubordinates(TreeNode *Node);								//helper function to count all of the subordinates recursively, under the given node.
void IsSupervisor(char *SubordinateName, char *SupervisorName);			//checks to see if the given string name of a supervisor is a supervisor of the given string name of the suboridnate, if it is, prints yes, if not, prints no.
void IsSubordinate(char *SupervisorName, char *SubordinateName);		//checks to see if the given string of a subordinate name is a subordinate of the given string of the supervisor name, if it is, prints yes, if not, prints no.
void CompareRank(char *Entity1, char *Entity2);							//compares the rank of 2 given strings of "companies" included in the tree and prints higher (lower/same) if entity1 has a higher (lower/same) rank than entity2.
TreeNode* ClosestCommonSupervisor(char *Entity1, char *Entity2);		//finds the closest common supervisor given 2 strings of "companies" that are inside of the tree and returns the closest common supervisor among them.

TreeRoot *Root = NULL;							//declaring root of the tree.
int NumSubordinates = 0;						//variable to aid the CountAllSubordinates function.

int main(int argc, char *argv[]){

	Root = (TreeRoot*) malloc(sizeof(TreeRoot));	
	FILE *fin = fopen(argv[1], "r");						//opening file with read permission.
	char parent[200];										//declaring parent and children strings, to store them in the tree,
	char child[200];										//also declaring an int to implement rank within the tree.
	int RankCounter = 1;	
	
	fscanf(fin, "%s", parent);								//since we know the first line will be the parent, just scan in one string.
	Root->HeadChildren = CreateTreeNode(parent);			//creating the root of the tree, rank 1, now increment to 2.
	Root->HeadChildren->Rank = RankCounter;
	RankCounter++;
    
			
	char CurrentParent[200];								//CurrentParent will help us figure out when to 
	strcpy(CurrentParent, parent);							//increment rank counter and to move on to a different treenode

	
	 while(!feof(fin)){															//while file is not finished reading,
		strcpy(parent, "");														//**setting child string and parent string to empty
		strcpy(child, "");
		fscanf(fin, "%s %s", parent, child);									//scan in the parents and children 
		if(strcmp(parent, "") == 0 && strcmp(child, "") == 0){					//**if the child and parent strings are empty, that means it is the end of the file, break out
			break;
		}
		if(strcmp(parent, CurrentParent) != 0){									//if the parent scanned in and current parent do not match, 
			strcpy(CurrentParent, parent);										//the current parent has no more children, so update rank and the parent.
			RankCounter++;			
		}	
		
		TreeNode *FoundNode = FindNode(CurrentParent, Root->HeadChildren);			//find the current node we are on, create a new child,				
		TreeNode *NewNode = CreateTreeNode(child);									//and add that child to the parent.
		NewNode->Rank = RankCounter;	
		AddChild(FoundNode, NewNode);
		
	} 
	
	fclose(fin);													//closing data file.
	
	fin = fopen(argv[2], "r");										//opening second file, input file.
	
	char input[300]; 												//storing input for the input file.
	
	while(!feof(fin)){												//while file is not finished reading, get each line of the input.
		strcpy(input, "");											//set the input string to nothing **
		fgets(input, sizeof(input), fin); 	
		if(input[strlen(input)-1] == '\n'){							//this essentially removes the trailing \n character from each line, 
				input[strlen(input)-1] = '\0';						//**unless the line is the last line in the file, in which case it does not have a \n. 
		}
		if(strcmp(input,"") == 0){									//**if the input is empty, break out of the loop (end of file)
			break;
		} 
		char *s = strtok(input, " ");								//using strtok to parse out the words in each line of input, Entity will be 
		char Entity[200] = "";										//used when there is more than 1 entity needed.
			
		if(strcmp(s, "DirectSupervisor") == 0){						//if they ask for a direct supervisor, print out a direct supervisor.
			s = strtok(NULL, " ");
			DirectSupervisor(s); 
		
		} else if(strcmp(s, "DirectSubordinates") == 0){			//if they ask for the direct subordinates, print out the direct subordinates.
			s = strtok(NULL, " ");
			DirectSubordinates(s);			
			
		} else if(strcmp(s, "AllSupervisors") == 0){				//if they ask for all supervisors, print out all supervisors.
			s = strtok(NULL, " ");
			AllSupervisors(s);
		} else if(strcmp(s, "AllSubordinates") == 0){				//if they ask for all subordinates, find the the node given the string, then print out the subordinates recursively
			s = strtok(NULL, " ");
			TreeNode *Found = FindNode(s, Root->HeadChildren);
			printf("AllSubordinates ");
			AllSubordinates(Found);
			printf("\n");
		} else if(strcmp(s, "NumberOfAllSupervisors") == 0){		//if they ask for the number of all supervisors, print out  the number of all supervisors.
			s = strtok(NULL, " ");
			NumberOfAllSupervisors(s);
		} else if(strcmp(s, "NumberOfAllSubordinates") == 0){		//if they ask for the number of all subordinates, print out  the number of all subordinates.
			s = strtok(NULL, " ");
			NumberOfAllSubordinates(s);
		} else if(strcmp(s, "IsSupervisor") == 0){					//if they ask if 1 entity is a supervisor of another, print out yes/no.
			s = strtok(NULL, " ");
			strcpy(Entity, s);
			s = strtok(NULL, " ");
			IsSupervisor(Entity, s);
		} else if(strcmp(s, "IsSubordinate") == 0){					//if they ask if 1 entity is a subordinate of another, print out yes/no.
			s = strtok(NULL, " ");
			strcpy(Entity, s);
			s = strtok(NULL, " ");
			IsSubordinate(Entity, s);
		} else if(strcmp(s, "CompareRank") == 0){					//if they ask for a rank comparison between 2 entities, print higher/lower/same.
			s = strtok(NULL, " ");
			strcpy(Entity, s);
			s = strtok(NULL, " ");
			CompareRank(Entity, s);
		} else if(strcmp(s, "ClosestCommonSupervisor") == 0){		//if they ask for the closest common supervisor, print out the closest common supervisor.
			TreeNode *CommonSupervisor;
			s = strtok(NULL, " ");
			strcpy(Entity, s);
			s = strtok(NULL, " ");
			CommonSupervisor = ClosestCommonSupervisor(Entity, s);
			printf("ClosestCommonSupervisor %s %s %s\n", Entity, s, CommonSupervisor->Name);
		} 
	} 
	fclose(fin); 
}

TreeNode* CreateTreeNode(char *N){									

	TreeNode *result = (TreeNode*) malloc(sizeof(TreeNode));			//fairly basic, just allocating memory for each treenode and returning the result.
	result->Parent = NULL;
	result->Children = NULL;
	result->NextSibling = NULL;
	result->Name = (char*) malloc(sizeof(char)*strlen(N));
	result->Rank = 0;
	strcpy(result->Name, N);

	return result;
}

TreeNode* FindNode(char *N, TreeNode *Node){
    if(strcmp(Node->Name, N) == 0){                        				//base case, when we have found the node, return it.
		return Node;
    } else if(Node->Children == NULL){                     		 		//if node is a leaf, return NULL, we haven't found the node yet
        return NULL;
    } else {
        TreeNode *ChildNode = Node->Children;
			TreeNode *FoundNode = NULL;
			while(FoundNode == NULL && ChildNode != NULL){				//else run through the tree until we have found the node, or when there are no more subtrees to traverse.
            FoundNode = FindNode(N, ChildNode);
            ChildNode = ChildNode->NextSibling;
        }
        return FoundNode;
    }
}

void AddChild(TreeNode* P, TreeNode *C){								//Essntially checking 3 cases:
																		//case 1: list is empty, c is now p->children.
	C->Parent = P;														//case 2: the first word is alphabetically greater than the child word, insert at beginning.								
	if(P->Children == NULL){											//case 3: insert somewhere inside of the middle of the list, or at the end	.																	
		P->Children = C;												
		C->NextSibling = NULL;
	}  else if(strcmp(C->Name, P->Children->Name) < 0 ){
		C->NextSibling = P->Children;
		P->Children = C;
	}  else { 
		TreeNode *Traverse = P->Children;
		while(Traverse->NextSibling != NULL && strcmp(C->Name, Traverse->NextSibling->Name) > 0){
			Traverse = Traverse->NextSibling;	
		}
		C->NextSibling = Traverse->NextSibling;
        Traverse->NextSibling = C;	 

	}

}
	
TreeNode* GetParent(TreeNode *C){										//returns the parent of given child node.
	return C->Parent;
}

TreeNode* GetChildren(TreeNode *P){										//returns the beginning pointer to the childnodes of the given parent node.
	return P->Children;
}

void DirectSubordinates(char *SupervisorName){									//finds the node of the supervisor string, traverses through the list and prints out each child.
	
	TreeNode *Traverse = FindNode(SupervisorName, Root->HeadChildren);
	Traverse = Traverse->Children;
	printf("DirectSubordinates %s ", SupervisorName);
	if(Traverse == NULL){
		printf("No children\n");
	} else {
		while(Traverse != NULL){
			printf("%s ", Traverse->Name);
			Traverse = Traverse->NextSibling;
		}
	}
	printf("\n");
}
void DirectSupervisor(char *SubordinateName){												//prints the direct supervisor of the given subordinate node.
	TreeNode *SubordinateNode = FindNode(SubordinateName, Root->HeadChildren);
	if(SubordinateNode->Parent == NULL){
		printf("DirectSupervisor %s NULL (Root Node)\n", SubordinateName);
	} else printf("DirectSupervisor %s %s\n", SubordinateName, SubordinateNode->Parent->Name);
}

void AllSupervisors(char *SubordinateName){													//finds the node of the given subordinate string, goes through and prints each parent until the Supervisor node is null.
	TreeNode *Supervisor = FindNode(SubordinateName, Root->HeadChildren);					//each parent until the Supervisor node is null.
	printf("AllSupervisors %s ", SubordinateName);
	Supervisor = Supervisor->Parent;
	while(Supervisor != NULL){
		printf("%s ", Supervisor->Name);
		Supervisor = Supervisor->Parent;
	}
	printf("\n");
}

void AllSubordinates(TreeNode *Node){
    printf("%s ", Node->Name);         					//base case, print out node name.
    
    if(Node->Children == NULL){          				//if leaf node, get out of recursion.
        return;
    } else {
        TreeNode *ChildNode = Node->Children;
        
        while(ChildNode != NULL){        			    //while there are still subtrees to traverse, keep printing subordinates.
            AllSubordinates(ChildNode);
            ChildNode = ChildNode->NextSibling;
        }
		
    }
	
}

void NumberOfAllSupervisors(char *SubordinateName){									//finds the node of the given subordinate string, goes through and counts each parent until the Supervisor node is null.
	TreeNode *Supervisor = FindNode(SubordinateName, Root->HeadChildren);			//each parent until the Supervisor node is null.
	printf("NumberOfAllSupervisors %s ", SubordinateName);
	int count = 0;
	Supervisor = Supervisor->Parent;
	while(Supervisor != NULL){
		count++;
		Supervisor = Supervisor->Parent;
	}
	printf("%d\n", count);
}

void NumberOfAllSubordinates(char *SupervisorName){								//finds the node of the given subordinate string, puts it into the count all subordinates function
	TreeNode *SupervisorNode = FindNode(SupervisorName, Root->HeadChildren);	//and prints the number of subordinates. -1 to NumSubordinates to not include the supervisor, because of the nature recursion
	printf("NumberOfAllSubordinates %s ", SupervisorName);
	NumSubordinates = -1;
	CountAllSubordinates(SupervisorNode);
	printf("%d\n", NumSubordinates);
}

void CountAllSubordinates(TreeNode *Node){
    NumSubordinates++;								    //base case, ++ to NumSubordinates (global variable).
    
    if(Node->Children == NULL){          				//leaf node, get out of recursion
        return;
    } else {
        TreeNode *ChildNode = Node->Children;
        
        while(ChildNode != NULL){        			    //while there are still subtrees to traverse, keep counting.
           CountAllSubordinates(ChildNode);
           ChildNode = ChildNode->NextSibling;
        }
		
    }

	
}
void IsSupervisor(char *SubordinateName, char *SupervisorName){					//finds subordinate node given subordinate string.
	TreeNode *Subordinate = FindNode(SubordinateName, Root->HeadChildren);		//goes through every parent to see if the SupervisorName matches with subordinate->parent->name and prints yes if it finds it.
	
	printf("IsSupervisor %s %s ", SubordinateName, SupervisorName);
	while(Subordinate->Parent != NULL){
		if(strcmp(Subordinate->Parent->Name, SupervisorName) == 0 ){
			printf("yes\n");
			return;
		}
		Subordinate = Subordinate->Parent;
	}
	printf("no\n");
}

void IsSubordinate(char *SupervisorName, char *SubordinateName){				//gets the supervisor node based on the supervisor name, uses find node to check to see if 
	TreeNode *Supervisor = FindNode(SupervisorName, Root->HeadChildren);		//the subordinate was found under the supervisor, prints yes/no.
	TreeNode *Result = FindNode(SubordinateName, Supervisor);
	printf("IsSubordinate %s %s ", SupervisorName, SubordinateName);
	
	if(Result != NULL){
		printf("yes\n");
	} else {
		printf("no\n");
	}
	
}

void CompareRank(char *Entity1, char *Entity2){									//gets both first entity node and second entity node, 
	TreeNode *Entity1Node = FindNode(Entity1, Root->HeadChildren);				//compares the rank values and prints a corresponding result higher/lower/same.
	TreeNode *Entity2Node = FindNode(Entity2, Root->HeadChildren);
	printf("CompareRank %s %s ", Entity1, Entity2);
	if(Entity1Node->Rank < Entity2Node->Rank){
		printf("higher\n");
	} else if(Entity1Node->Rank > Entity2Node->Rank){
		printf("lower\n");
	} else {
		printf("same\n");
	}
}

TreeNode* ClosestCommonSupervisor(char *Entity1, char *Entity2){						//gets both first entity node and second entity node, 
	TreeNode *Entity1Node = FindNode(Entity1, Root->HeadChildren);						//loops through each parent of the first entity and each parent of the second entity
	TreeNode *Entity2Node = FindNode(Entity2, Root->HeadChildren);						//until it can find a common supervisor.
	TreeNode *TempNode = Entity2Node;
	
	 while(Entity1Node->Parent != NULL){
		while(Entity2Node->Parent != NULL){
			if(strcmp(Entity1Node->Parent->Name, Entity2Node->Parent->Name) == 0 ){
				return Entity1Node->Parent;
			}
			
			Entity2Node = Entity2Node->Parent;
		}  
		Entity1Node = Entity1Node->Parent;
		Entity2Node = TempNode;															//resets entity 2 to the beginning node again, to compare with the parent of entity 1.
		
	} 
}






