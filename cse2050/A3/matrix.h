#include <string.h>
#include <vector>
using namespace std;

class matrix {

public:
	vector<vector<int>> Mat;				//stored matrix, with dimension
	int dimension;

	matrix(int);						
	double determinate();					//computes determinate, transpose, multiplication by an int, and inverse
	void transpose();
	void multiplication(int);
	vector<vector<double>> inverse();
	void printMatrix(vector<vector<double>> matrix);

};
