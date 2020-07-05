#ifndef RESULTTUPLE_H
#define RESULTTUPLE_H

#include <vector>
using namespace std;

class ResultTuple
{
public:
	ResultTuple(vector<vector<double> > fingerprints_k, vector<vector<double> > fingerprints_y, double elapsed);
	~ResultTuple();

	vector<vector<double> > fingerprints_k;
	vector<vector<double> > fingerprints_y;
	double elapsed;
};

#endif