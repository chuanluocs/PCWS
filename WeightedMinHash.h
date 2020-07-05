#ifndef _WEIGHTEDMINHASH_H
#define _WEIGHTEDMINHASH_H

#include "mersenne_rng.h"
#include "ResultTuple.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

class WeightedMinHash
{
public:
	WeightedMinHash(vector<vector<double> > weighted_set, int dimension_num, int seed);
	~WeightedMinHash();
	ResultTuple pcws();
	vector<vector<double> > get_weighted_set();


private:
	void clear_2d_vector(vector<vector<double> > &v);
	void print_2d_vector(vector<vector<double> > &v);
	void print_1d_vector(vector<int> &v);
	vector<vector<double> > generate_zero_matrix(int row_num, int column_num);
	vector<vector<double> > generate_random_uniform_matrix(int row_num, int column_num);
	void specific_test_case(vector<vector<double> > &beta, vector<vector<double> > &x, vector<vector<double> > &u1, vector<vector<double> > &u2);

	vector<vector<double> > weighted_set;
	int dimension_num;
	int seed;
	int instance_num;
	int feature_num;
	Mersenne_rng rng;
};

#endif