#ifndef _RESULTTUPLE_CPP
#define _RESULTTUPLE_CPP

#include "ResultTuple.h"

ResultTuple::ResultTuple(vector<vector<double> > fingerprints_k, vector<vector<double> > fingerprints_y, double elapsed)
{
	this->fingerprints_k = fingerprints_k;
	this->fingerprints_y = fingerprints_y;
	this->elapsed = elapsed;
	return;
}

ResultTuple::~ResultTuple()
{
	for (int i = 0; i < (int)fingerprints_k.size(); i++)
	{
		fingerprints_k[i].clear();
		vector<double>().swap(fingerprints_k[i]);
		fingerprints_y[i].clear();
		vector<double>().swap(fingerprints_y[i]);
	}
	fingerprints_k.clear();
	vector<vector<double> >().swap(fingerprints_k);
	fingerprints_y.clear();
	vector<vector<double> >().swap(fingerprints_y);
	return;
}

#endif