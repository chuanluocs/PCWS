#include "WeightedMinHash.h"
#include <vector>
#include <iostream>
using namespace std;

void init(vector<vector<double> > &v)
{
	vector<double> w;
	w.push_back(100);
	w.push_back(200);
	w.push_back(0);
	v.push_back(w);

	w.clear();
	vector<double>().swap(w);
	w.push_back(0);
	w.push_back(0);
	w.push_back(300);
	v.push_back(w);

	w.clear();
	vector<double>().swap(w);
	w.push_back(100);
	w.push_back(0);
	w.push_back(400);
	v.push_back(w);

	w.clear();
	vector<double>().swap(w);
	w.push_back(200);
	w.push_back(0);
	w.push_back(0);
	v.push_back(w);
	return;
}

void init2(vector<vector<double> > &v)
{
	int row_num = 1000;
	int column_num = 10000;

	Mersenne_rng rng;
	rng.seed(1);

	for (int i = 0; i < row_num; i++)
	{
		vector<double> w(column_num);
		for (int j = 0; j < column_num; j++)
		{
			w[j] = rng.next(1000);
		}
		v.push_back(w);
	}
	return;
}

void print_2d_vector(vector<vector<double> > v)
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int main(int argc, char** argv)
{
	/*
	int dimension_num = 2;
	int seed = 1;
	vector<vector<double> > data;
	init(data);
	*/

	int dimension_num = 10;
	int seed = 1;
	vector<vector<double> > data;
	init2(data);

	WeightedMinHash wmh(data, dimension_num, seed);
	ResultTuple ret = wmh.pcws();
	
	print_2d_vector(ret.fingerprints_k);
	print_2d_vector(ret.fingerprints_y);
	cout << ret.fingerprints_k.size() << " " << ret.fingerprints_k[0].size() << endl;
	cout << ret.fingerprints_y.size() << " " << ret.fingerprints_y[0].size() << endl;
	cout << ret.elapsed << endl;
	
	return 0;
}