#include <iostream>
#include "DiGraph.h"
using namespace std;

#define FILE_NAME "DAG.txt"
int main()
{
	// Create a graph given in the above diagram 
	//DiGraph g(6);
	//g.addEdge(5, 2);
	//g.addEdge(5, 0);
	//g.addEdge(4, 0);
	//g.addEdge(4, 1);
	//g.addEdge(2, 3);
	//g.addEdge(3, 1);
	DiGraph g(FILE_NAME);


	cout << "All Topological sorts Recursively\n";

	g.alltopologicalSortRecursive();

	cout << "All Topological sorts_K\n";
	list<list<int>> sort_list;
	int code = g.all_topological_sorts_K(sort_list);
	if (code != 0)
	{
		cout << "Error taking place in top_sort_K" << endl;
		return -1;
	}
	for (auto const& sort : sort_list) {
		for (auto const& e : sort) 
			cout << e << " ";
		cout << endl;
	}
	return 0;
}