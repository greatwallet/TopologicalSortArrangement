// https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/
#pragma once
#ifndef _DI_GRAPH_H_
#define _DI_GRAPH_H_

#include <iostream>
#include <deque>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class DiGraph
{
	int V;    // No. of vertices 

// Pointer to an array containing adjacency list 
	list<int> *adj;

	// Vector to store indegree of vertices 
	vector<int> indegree;

	// A function used by alltopologicalSortRecursive 
	void alltopologicalSortUtil(vector<int>& res,
		bool visited[]);
public:
	DiGraph(int V);   // Constructor 
	DiGraph(const string &fname);

	// function to add an edge to graph 
	void addEdge(int v, int w);

	// Prints all Topological Sorts 
	void alltopologicalSortRecursive();

	// Algorithm from [1] Knuth, Donald E., Szwarcfiter, Jayme L. (1974).
	//"A Structured Program to Generate All Topological Sorting Arrangements"
	//	Information Processing Letters, Volume 2, Issue 6, 1974, Pages 153 - 157,
	//	ISSN 0020 - 0190,
	//	https://doi.org/10.1016/0020-0190(74)90001-5.
	//Elsevier(North - Holland), Amsterdam
	int all_topological_sorts_K(list<list<int>> &sort_list);
};
#endif // !_DI_GRAPH_H_

