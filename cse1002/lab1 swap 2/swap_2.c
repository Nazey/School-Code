/* 
 * Author: Brian Massino, bmassino2017@my.fit.edu 
 * Course: CSE 1002, Section 01, Spring 2018 
 * Project: swap 
 */
 
#include <stdio.h>

//reads in each array value from the user's input 
void read_array(int length, int array[]);

//prints out an array given its length
void print_array(int length, int array[]);

//swaps values x and y without using a temp variable
void swap_single(int *x, int *y); 

//swaps values x and y using a temp variable
void swap_single_temp(int *x, int *y); 

//swaps the two arrays without using a temp variable
void swap_array(int length, int array1[], int array2[]);

//swaps the two arrays using a temp variable
void swap_array_temp(int length, int array1[], int array2[]); // In this function you can use a temp array.
 
int main(void){
	 //type input is the user's input for what they will input
	 int type_input;
	 printf("Type of inputs (0: integer, 1: arrays of integer): ");
	 scanf("%d", &type_input);
	 if (type_input == 0) {
		//x and y being the two variables to swap with each other
		int x, y;
		
		printf("Enter the x variable: ");
		scanf(" %d", &x);
		printf("Enter the y variable: ");
		scanf(" %d", &y);
		
		//swapping the first values without temp
		swap_single(&x, &y);
		printf("\nOutput after swap:\n x = %d\n y = %d\n", x, y);
		
		//swapping the values again to return them to their previous state for the next swap, but this time using a temp variable
		swap_single(&x, &y);
		swap_single_temp(&x, &y);
		printf("Using temp:\n x = %d\n y = %d", x, y); 
	 } else {
		int length;
		printf("Enter length of the arrays: ");
		scanf("%d", &length);
		
		int arr1[length];
		int arr2[length];
		
		printf("Please enter the first array as array1: ");
		read_array(length, arr1);
		printf("Please enter the second array as array2: ");
		read_array(length, arr2);
		//swapping the arrays without temp
		swap_array(length, arr1, arr2);
		
	    printf("The output after the swap:\n");
		printf("array 1 = ");
		print_array(length, arr1);
	    printf("array 2 = ");
	    print_array(length, arr2);
		
		//swapping the array values again to their previous state, so that the next swap will work the same
		swap_array(length, arr1, arr2);
		swap_array_temp(length, arr1, arr2);
		
	    printf("The output using temp:\n");
		printf("array 1 = ");
		print_array(length, arr1);
	    printf("array 2 = ");
		print_array(length, arr2);
	 }
     
	 return 0;
 }
 
void read_array(int length, int array[]){
	for(int i=0; i<length; i++){
		scanf("%d", &array[i]);
	}
}
 
void print_array(int length, int array[]){
	for(int i=0; i<length; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}
 
void swap_single(int *x, int *y){
	//essentially using simple math to solve the problem, add x and y to x, set y to x - y, which would give you x,
	//then set x to x - y, which would give you the y value, swapping the two
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void swap_single_temp(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;	
}
 
void swap_array(int length, int array1[], int array2[]){
	for(int i=0; i<length; i++){
		//same logic as swap_single, but now with array values
		array1[i] = array1[i] + array2[i];
		array2[i] = array1[i] - array2[i];
		array1[i] = array1[i] - array2[i];
	}
}
 
void swap_array_temp(int length, int array1[], int array2[]){
	int temp[length];
	
	for(int i=0; i<length; i++){
		temp[i]=array1[i];
		array1[i]=array2[i];
		array2[i]=temp[i];
	}
}