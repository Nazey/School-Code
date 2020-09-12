/*

  Author: Brian	Massino	
  Email: bmassino2017@my.fit.edu	
  Course: CSE 2050	
  Description: main program to test the matrix.cpp function
  
 */
#include <iostream>
#include <fstream>
#include <string>
#include "matrix.h"

using namespace std;

int main(int argc, char * argv[]) {
	int dimension;
	string line;
	ifstream myfile(argv[2]);									
	int number = stoi(argv[1]);									//number passed to multiplcation function

	if (myfile.is_open()) {
		getline(myfile, line);				
		dimension = stoi(line);									//dimension for matrix val x val
		int val = 0; 
		matrix myMatrix = matrix(dimension);					//initializing matrix

		for (int i = 0; i < myMatrix.dimension; ++i) {			//setting values to matrix from input file
			for (int k = 0; k < myMatrix.dimension; ++k) {
				getline(myfile, line);							//get each value and store it into the matrix
				val = stoi(line);
				myMatrix.Mat[i][k] = val;
			}		

		}
		cout << "Determinate:" << myMatrix.determinate();			//print determinate, transpose, multiplication, and inverse accordingly
		cout << "\nTranspose:\n";
		myMatrix.transpose();
		cout << "Element-wise multiplication:\n";
		myMatrix.multiplication(number);
		cout << "Inverse:\n";
		myMatrix.inverse();
		myfile.close();
	}
	else cout << "File not found\n";								//no file found if it hits this

	return 0;
}