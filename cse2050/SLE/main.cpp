/*

  Author: Brian	Massino
  Email: bmassino2017@my.fit.edu
  Course: CSE 2050
  Description: main.cpp


 */
#include <iostream>
#include <fstream>
#include <string>
#include "linear.h"
#include <sstream> 

using namespace std;

vector<int> getNumbers(string s) { //takes string in, returns a vector with all the numbers for easy assignment
	vector<int> nums;

	stringstream ss;
	
	//this algorithm was adapted for use in my program, all credit goes to geeksforgeeks.org. 
	//https://www.geeksforgeeks.org/extract-integers-string-c/
	
	/* Storing the whole string into string stream */
	ss << s;

	/* Running loop till the end of the stream */
	string temp;
	int found;
	while (!ss.eof()) {
		
		/* extracting word by word from stream */
		ss >> temp;

		/* Checking the given word is integer or not */
		if (stringstream(temp) >> found)
			nums.push_back(found);

		/* To save from space at the end of string */
		temp = "";
	}
	return nums;
}

int main(int argc, char * argv[]) {
	int dimension, numVectors;	
	string line;
	ifstream myfile(argv[1]);
	
	if (myfile.is_open()) {
		int val = 0;
		getline(myfile, line);
		dimension = stoi(line);									//dimension for matrix val x val
		getline(myfile, line);
		numVectors = stoi(line);								//number of vectors in file
		
		linear SLE = linear(dimension, numVectors);
		for (int i = 0; i < SLE.dimension; ++i) {						//take in the matrix
			getline(myfile, line);
			vector<int> numbers = getNumbers(line);

			for (int k = 0; k < SLE.dimension; ++k) {
				SLE.Mat[i][k] = numbers[k];
			}
		}
			
		for (int i = 0; i < numVectors; ++i) {							//take in the vectors line by line
			for (int k = 0; k < SLE.dimension; ++k) {
				getline(myfile, line);
				val = stoi(line);
				SLE.ListOfVectors[i][k] = val;

			}

		}

		SLE.ComputeUnknowns();									//solve the system
	}
	else cout << "File not found\n";								//no file found if it hits this
	
	myfile.close();											//close file
	return 0;
}