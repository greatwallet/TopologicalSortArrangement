#include <iostream>
#include <iomanip>
#include <chrono>
#include "DiGraph.h"
#include "algo_v.h"
#include "sort_four.h"
#include <string>
using namespace std;

#define FILE_NAME "DAG.txt"

int main()
{
	// timer
	chrono::time_point<chrono::steady_clock> tic;
	chrono::time_point<chrono::steady_clock> toc;
	double elapsed_time;

	// Create a graph given in the above diagram 
	DiGraph g(FILE_NAME);

	// algorithm recursively
	cout << "All Topological sorts Recursively\n";
	tic = chrono::high_resolution_clock::now();
	g.alltopologicalSortRecursive();
	toc = chrono::high_resolution_clock::now();
	elapsed_time = chrono::duration<double>(toc - tic).count();
	cout << "[Recursive] Time Cost = " << fixed << setprecision(5) << elapsed_time << "s" << endl;

	// algorithm K
	cout << "All Topological sorts_K\n";
	list<list<int>> sort_list;

	tic = chrono::high_resolution_clock::now();
	int code = g.all_topological_sorts_K(sort_list);
	if (code != 0)
	{
		cout << "Error taking place in top_sort_K" << endl;
		return -1;
	}

	//for (auto const& sort : sort_list) {
	//	for (auto const& e : sort) 
	//		cout << e << " ";
	//	cout << endl;
	//}
	toc = std::chrono::high_resolution_clock::now();
	elapsed_time = chrono::duration<double>(toc - tic).count();
	cout << "[K] Time Cost = " << fixed << setprecision(5) << elapsed_time << "s" << endl;
	cout << sort_list.size() << endl;

	//for (auto const& sort : sort_list) {
	//	for (auto const& e : sort) 
	//		cout << e << " ";
	//	cout << endl;
	//}
	
	// method 2 for using algorithm V
	 algo_v V(FILE_NAME);
	 tic = chrono::high_resolution_clock::now();
	 V.all_topological_sorts_K();
	 // V.show_result();
	 toc = std::chrono::high_resolution_clock::now();
	 elapsed_time = chrono::duration<double>(toc - tic).count();
	 cout << "[V] Time Cost = " << fixed << setprecision(5) << elapsed_time << "s" << endl;
    test("DAG_08.txt","result_14.txt",SJTOrder,7);
	return 0;

}
