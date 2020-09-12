#include <string.h>
#include <vector>
#include "matrix.h"
using namespace std;

class linear : public matrix {

public:
	int numConstants;			//how many constants we will have
	vector<vector<double>> ListOfVectors;	//vector list of how many n sized vectors we want to multiply inverse by
	vector<vector<double>> Unknowns;	//unknown/resultant vector

	linear(int, int);

	void ComputeUnknowns();
};
