#ifndef _WEIGHTEDMINHASH_CPP
#define _WEIGHTEDMINHASH_CPP

#include "WeightedMinHash.h"

//input weighted_set uses 1) column as instance, and 2) row as feature;
//in class WeightedMinHash, the member weighted_set uses 1) row as instance, and 2) column as feature;
WeightedMinHash::WeightedMinHash(vector<vector<double> > weighted_set, int dimension_num, int seed = 1)
{
	if (weighted_set.size() <= 0)
	{
		this->feature_num = 0;
		this->instance_num = 0;
	}
	else
	{
		this->feature_num = weighted_set.size();
		if (weighted_set[0].size() <= 0)
			this->instance_num = 0;
		else this->instance_num = weighted_set[0].size();
	}

	this->dimension_num = dimension_num;
	this->seed = seed;
	this->rng.seed(this->seed);

	clear_2d_vector(this->weighted_set);
	vector<vector<double> > temp_weighted_set(instance_num);

	for (int i = 0; i < instance_num; i++)
	{
		vector<double> temp_instance(feature_num);

		for (int j = 0; j < feature_num; j++)
		{
			temp_instance[j] = weighted_set[j][i];
		}
		temp_weighted_set[i] = temp_instance;
	}

	this->weighted_set = temp_weighted_set;
	return;
}

WeightedMinHash::~WeightedMinHash()
{
	clear_2d_vector(this->weighted_set);
	return;
}

ResultTuple WeightedMinHash::pcws()
{
	clock_t start, stop;

	vector<vector<double> > fingerprints_k = generate_zero_matrix(instance_num, dimension_num);
	vector<vector<double> > fingerprints_y = generate_zero_matrix(instance_num, dimension_num);

	start = clock();

	vector<vector<double> > beta = generate_random_uniform_matrix(feature_num, dimension_num);
	vector<vector<double> > x = generate_random_uniform_matrix(feature_num, dimension_num);
	vector<vector<double> > u1 = generate_random_uniform_matrix(feature_num, dimension_num);
	vector<vector<double> > u2 = generate_random_uniform_matrix(feature_num, dimension_num);
	
	for (int i = 0; i < instance_num; i++)
	{
		vector<int> feature_id;
		for (int j = 0; j < feature_num; j++)
		{
			if (weighted_set[i][j] > 0)
			{
				feature_id.push_back(j);
			}
		}

		vector<vector<double> > gamma(feature_id.size());
		for (int j = 0; j < (int)feature_id.size(); j++)
		{
			int fid = feature_id[j];
			vector<double> temp_gamma(dimension_num);
			for (int k = 0; k < dimension_num; k++)
			{
				temp_gamma[k] = -log(u1[fid][k] * u2[fid][k]);
			}
			gamma[j] = temp_gamma;
		}

		vector<vector<double> > t_matrix(feature_id.size());
		for (int j = 0; j < (int)feature_id.size(); j++)
		{
			int fid = feature_id[j];
			vector<double> temp_t_matrix(dimension_num);
			for (int k = 0; k < dimension_num; k++)
			{
				temp_t_matrix[k] = floor((log(weighted_set[i][fid]) / gamma[j][k]) + beta[fid][k]);
			}
			t_matrix[j] = temp_t_matrix;
		}
		
		vector<vector<double> > y_matrix(feature_id.size());
		for (int j = 0; j < (int)feature_id.size(); j++)
		{
			int fid = feature_id[j];
			vector<double> temp_y_matrix(dimension_num);
			for (int k = 0; k < dimension_num; k++)
			{
				temp_y_matrix[k] = exp(gamma[j][k] * (t_matrix[j][k] - beta[fid][k]));
			}
			y_matrix[j] = temp_y_matrix;
		}

		vector<vector<double> > a_matrix(feature_id.size());
		for (int j = 0; j < (int)feature_id.size(); j++)
		{
			int fid = feature_id[j];
			vector<double> temp_a_matrix(dimension_num);
			for (int k = 0; k < dimension_num; k++)
			{
				temp_a_matrix[k] = (-log(x[fid][k])) / (y_matrix[j][k] / u1[fid][k]);
			}
			a_matrix[j] = temp_a_matrix;
		}

		vector<int> min_position(dimension_num);
		for (int j = 0; j < dimension_num; j++)
		{
			int temp_min_position = 0;
			for (int k = 1; k < (int)feature_id.size(); k++)
			{
				if (a_matrix[k][j] < a_matrix[temp_min_position][j])
				{
					temp_min_position = k;
				}
			}
			min_position[j] = temp_min_position;
		}

		for (int j = 0; j < dimension_num; j++)
		{
			fingerprints_k[i][j] = feature_id[min_position[j]];
			fingerprints_y[i][j] = y_matrix[min_position[j]][j];
		}
	}

	stop = clock();

	double elapsed = (double)((double)stop - (double)start) / (double)CLOCKS_PER_SEC;
	ResultTuple ret(fingerprints_k, fingerprints_y, elapsed);
	return ret;
}

vector<vector<double> > WeightedMinHash::get_weighted_set()
{
	return this->weighted_set;
}

void WeightedMinHash::clear_2d_vector(vector<vector<double> > &v)
{
	for (int i = 0; i < (int)v.size(); i++)
	{
		v[i].clear();
		vector<double>().swap(v[i]);
	}
	v.clear();
	vector<vector<double> >().swap(v);
	return;
}

void WeightedMinHash::print_2d_vector(vector<vector<double> > &v)
{
	for (int i = 0; i < (int)v.size(); i++)
	{
		for (int j = 0; j < (int)v[i].size(); j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void WeightedMinHash::print_1d_vector(vector<int> &v)
{
	for (int i = 0; i < (int)v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	return;
}

vector<vector<double> > WeightedMinHash::generate_zero_matrix(int row_num, int column_num)
{
	vector<vector<double> > v(row_num);
	for (int i = 0; i < row_num; i++)
	{
		vector<double> w(column_num, 0);
		v[i] = w;
	}
	return v;
}

vector<vector<double> > WeightedMinHash::generate_random_uniform_matrix(int row_num, int column_num)
{
	vector<vector<double> > v(row_num);
	for (int i = 0; i < row_num; i++)
	{
		vector<double> w(column_num);
		for (int j = 0; j < column_num; j++)
		{
			w[j] = rng.nextClosed();
		}
		v[i] = w;
	}
	return v;
}

void WeightedMinHash::specific_test_case(vector<vector<double> > &beta, vector<vector<double> > &x, vector<vector<double> > &u1, vector<vector<double> > &u2)
{
	beta[0][0] = 4.17022005e-01;
	beta[0][1] = 7.20324493e-01;
	beta[1][0] = 1.14374817e-04;
	beta[1][1] = 3.02332573e-01;
	beta[2][0] = 1.46755891e-01;
	beta[2][1] = 9.23385948e-02;
	beta[3][0] = 1.86260211e-01;
	beta[3][1] = 3.45560727e-01;

	x[0][0] = 0.39676747;
	x[0][1] = 0.53881673;
	x[1][0] = 0.41919451;
	x[1][1] = 0.6852195;
	x[2][0] = 0.20445225;
	x[2][1] = 0.87811744;
	x[3][0] = 0.02738759;
	x[3][1] = 0.67046751;

	u1[0][0] = 0.4173048;
	u1[0][1] = 0.55868983;
	u1[1][0] = 0.14038694;
	u1[1][1] = 0.19810149;
	u1[2][0] = 0.80074457;
	u1[2][1] = 0.96826158;
	u1[3][0] = 0.31342418;
	u1[3][1] = 0.69232262;

	u2[0][0] = 0.87638915;
	u2[0][1] = 0.89460666;
	u2[1][0] = 0.08504421;
	u2[1][1] = 0.03905478;
	u2[2][0] = 0.16983042;
	u2[2][1] = 0.8781425;
	u2[3][0] = 0.09834683;
	u2[3][1] = 0.42110763;
}

#endif