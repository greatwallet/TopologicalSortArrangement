#pragma once
#ifndef _ALGO_V_H_
#define _ALGO_V_H_

#include <iostream>
#include <vector>
using namespace std;

struct tp {
	int b;
	int e;
};

class algo_v
{
	int seq_len = 0; // Sequence length
	vector<int> a;
	vector<int> a_inv; // inverse of a is to exchange the value and index for each element in a
	vector<tp> cons; // Constrain list; b,e -> a_inv[b] < a_inv[e]
	vector<vector<int>> all_top_sorts;

	// Check if certern begin_index & end_index is in the constrain.
	bool in_tp(int _b, int _e);

	// Print certain input, usually to print a and a_inv;
	void print(vector<int> const& input);

	// Filter out the zero element in sorts
	vector<int> filter_out();

	// check if current topological sort has been found
	bool founded(vector<int> const& a_);

public:
	// Initialize
	algo_v(const string& fname);

	// main algorithm
	void all_topological_sorts_K();

	// print all the sorts
	void show_result();
};
#endif // !_ALGO_V_H_
#pragma once
