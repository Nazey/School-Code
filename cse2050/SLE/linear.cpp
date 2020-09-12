/*
     This class is used to solve systems of linear equations using matrices
*/

#include <string.h>
#include <vector>
#include "linear.h"
#include <iostream>
using namespace std;

linear::linear(int Dim, int NumConstant): matrix(Dim){
	ListOfVectors.resize(Dim);		//resizing the vectors to accept length of Dim
	Unknowns.resize(Dim);
	numConstants = NumConstant;
	for (int i = 0; i < Dim; ++i) {		//resize the 2d vector of constants and unknowns to dim length 
		ListOfVectors[i].resize(Dim);		
	}
	for (int i = 0; i < NumConstant; ++i) {		//resize the 2d vector of constants and unknowns to dim length 
		Unknowns[i].resize(Dim);
	}
		
}


void linear::ComputeUnknowns(){
	vector<vector<double>> InverseMatrix;
	InverseMatrix = inverse();							//first, compute inverse
	
	int temp = 0;									//then, multiply the inverse by every row of constants
	for (int i = 0; i < numConstants; ++i) {					//first loop, how many solutions we want to multiply/add by
		for (int matr = 0; matr < InverseMatrix.size(); ++matr) {		//second, have a double for loop going through each row and multiplying it by the corresponding vector row, adding to the resultant vector
			for (int matc = 0; matc < InverseMatrix.size(); ++matc) {
				Unknowns[i][matr] += InverseMatrix[matr][matc]*ListOfVectors[i][matc];
			}
		}
	}	

	for (int i = 0; i < numConstants; ++i) {	//print everything out
		for (int k = 0; k < Unknowns.size(); ++k) {
			printf("%.2f ", Unknowns[i][k]);
		}
		cout << "\n";
	}
	

};