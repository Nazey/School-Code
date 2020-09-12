#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

matrix::matrix(int d) {
	dimension = d;
	Mat.resize(d);					//resize the 2d vector to d 
	for (int i = 0; i < d; ++i)
		Mat[i].resize(d);
}

double matrix::determinate() {
	
	double size = Mat.size();			//size of the matrix to be copied
	int swappedRow = 1;
	vector<vector<double>> modify;		
	modify.resize(size, vector<double>(size));	//resizing due to compiler complaints

	for (int i = 0; i < size; ++i) {		//setting matrix for modification, due to original being of ints, and we need doubles for Gaussian elmination
		for (int k = 0; k < size; ++k) {
			modify[i][k] = Mat[i][k];
		}
	}

	for (int i = 0; i < size - 1; i++) {
		if (modify[i][i] == 0) {					//if 0 exists, swap rows until we reach end of the row
			for (int a = 0; a < size; a++) {
				double temp_val = modify[i][a];
				modify[i][a] = modify[i + 1][a];
				modify[i + 1][a] = temp_val;
			}
			swappedRow *= -1;					//multiply by negative 1, as per GE rules
		}
		for (int j = i + 1; j < size; j++) {
			double mul = (modify[j][i] / modify[i][i]);		//value to multiply by
			for (int a = 0; a < size; a++) {
				modify[j][a] -= (modify[i][a] * mul);
			}
		}
	}
	double result = modify[0][0];	
	for (int i = 1; i < modify.size(); i++) {				//multiply the diagonal, now that we are in row echelon form
		result *= modify[i][i];
	}
	return result * swappedRow;						//multiply by the number of times swapped (-1 or 1)
}

void matrix::transpose() {
	for (int i = 0; i < dimension; ++i) {					//go through the matrix and just print it "backwards"
		for (int k = 0; k < dimension; ++k) {
			cout << Mat[k][i] << " ";
		}
		cout << "\n";
	}
	return;
}

void matrix::multiplication(int a) {
	for (int i = 0; i < dimension; ++i) {
		for (int k = 0; k < dimension; ++k) {				//go through the matrix and multiply each index by the given int
			cout << Mat[i][k]*a << " ";
		}
		cout << "\n";
	}
	return;
}

vector<vector<double>> matrix::inverse() {
	int size = Mat.size();
	if (size <= 1 || this->determinate() == 0){				//if singular matrix or the determinate is 0, there is no inverse
		cout << "No inverse";
		vector<vector<double>> NOTHING;
		return NOTHING;
	}
	vector<vector<double>> matrix;
	vector<vector<double>> inverseMat;
	
	matrix.resize(size, vector<double>(size));
	inverseMat.resize(size, vector<double>(size));
	for (int i = 0; i < size; ++i) {					//setting matrix for modification again, due to original being of ints, 
		for (int k = 0; k < size; ++k) {				//and we need doubles for Gaussian elmination
			matrix[i][k] = Mat[i][k];
			inverseMat[i][k] = Mat[i][k];
		}

	}
	
	for (int i = 0; i < size; i++) {					//setting up identity matrix of all 0's and 1's on diagonal
		for (int k = 0; k < matrix.size(); k++) {	
			if (i == k)
				inverseMat[i][k] = 1;
			else inverseMat[i][k] = 0;
		}
	}
	for (int i = 0; i < size; i++) {
		if (matrix[i][i] == 0) {					//if a diagonal is 0, swap values with inverse matrix and base matrix
			for (int k = 0; k < size; k++) {
				double temporaryValue = matrix[i][k];
				matrix[i][k] = matrix[i + 1][k];
				matrix[i + 1][k] = temporaryValue;
				temporaryValue = inverseMat[i][k];
				inverseMat[i][k] = inverseMat[i + 1][k];
				inverseMat[i + 1][k] = temporaryValue;
			}
		}
		double multiply = matrix[i][i];					//dividing all of the values by current diagonal number
		for (int a = 0; a < size; a++) {
			matrix[i][a] /= multiply;
			inverseMat[i][a] /= multiply;
		}
		for (int j = 0; j < size; j++) {
			if (i != j) {
				double mul = matrix[j][i];			//if not diagonal values, go through each row and subtract values from begibnning of each diagonal row
				for (int a = 0; a < size; a++) {
					matrix[j][a] = (matrix[j][a] - mul * matrix[i][a]);
					inverseMat[j][a] = (inverseMat[j][a] - mul * inverseMat[i][a]);
				}

			}
		}
	}
	return inverseMat;
	
}

void matrix::printMatrix(vector<vector<double>> matrix) {		//basic print matrix function
	for (int i = 0; i < matrix.size(); ++i) {
		for (int k = 0; k < matrix.size(); ++k) {
			cout << matrix[i][k] << " ";
		}
		cout << "\n";
	}
}




