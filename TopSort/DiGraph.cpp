#include "DiGraph.h"
#include <fstream>
#include <map>
using namespace std;

#define MAX(a, b) (a > b ? a : b)

//  Main recursive function to print all possible 
//  topological sorts 
void DiGraph::alltopologicalSortUtil(vector<int>& res, bool visited[])
{
	// To indicate whether all topological are found 
	// or not 
	bool flag = false;

	for (int i = 0; i < V; i++)
	{
		//  If indegree is 0 and not yet visited then 
		//  only choose that vertex 
		if (indegree[i] == 0 && !visited[i])
		{
			//  reducing indegree of adjacent vertices 
			list<int>::iterator j;
			for (j = adj[i].begin(); j != adj[i].end(); j++)
				indegree[*j]--;

			//  including in result 
			res.push_back(i);
			visited[i] = true;
			alltopologicalSortUtil(res, visited);

			// resetting visited, res and indegree for 
			// backtracking 
			visited[i] = false;
			res.erase(res.end() - 1);
			for (j = adj[i].begin(); j != adj[i].end(); j++)
				indegree[*j]++;

			flag = true;
		}
	}

	//  We reach here if all vertices are visited. 
	//  So we print the solution here 
	if (!flag)
	{
		for (int i = 0; i < res.size(); i++)
			cout << res[i] << " ";
		cout << endl;
	}
}

//  Constructor of graph 
DiGraph::DiGraph(int V)
{
	this->V = V;
	adj = new list<int>[V];

	// Initialising all indegree with 0 
	for (int i = 0; i < V; i++)
		indegree.push_back(0);
}

DiGraph::DiGraph(const string & fname)
{
	ifstream fin(fname);
	// map<int, int> nodeCount;
	int max_id = -1;
	int left, right;
	while (fin >> left >> right)
	{
		if (MAX(left, right) > max_id)
			max_id = MAX(left, right);
	}
	V = max_id + 1;
	adj = new list<int>[V];
	// Initialising all indegree with 0 
	for (int i = 0; i < V; i++)
		indegree.push_back(0);
	fin.clear();
	fin.seekg(ios::beg);
	while (fin >> left >> right)
	{
		addEdge(left, right);
	}
	fin.close();
}

//  Utility function to add edge 
void DiGraph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v's list. 

// increasing inner degree of w by 1 
	indegree[w]++;
}

//  The function does all Topological Sort. 
//  It uses recursive alltopologicalSortUtil() 
void DiGraph::alltopologicalSortRecursive()
{
	// Mark all the vertices as not visited 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	vector<int> res;
	alltopologicalSortUtil(res, visited);
}

// Algorithm from [1] Knuth, Donald E., Szwarcfiter, Jayme L. (1974).
//"A Structured Program to Generate All Topological Sorting Arrangements"
//	Information Processing Letters, Volume 2, Issue 6, 1974, Pages 153 - 157,
//	ISSN 0020 - 0190,
//	https://doi.org/10.1016/0020-0190(74)90001-5.
//Elsevier(North - Holland), Amsterdam
int DiGraph::all_topological_sorts_K(list<list<int>> &sort_list)
{
	// vertices with indegree 0
	deque<int> D;
	for (size_t i = 0; i < indegree.size(); ++i) {
		if (indegree[i] == 0)
		{
			D.push_back(i);
		}
	}
	// the names of count and D are chosen to match the global variables in [1]
	//  number of edges originating in a vertex v
	vector<int> count(indegree);
	// stack of first value chosen at a position k in the topological sort
	stack<int> bases;
	// output 
	list<int> current_sort;

	// do-while construct
	while (true)
	{
		// TODO: add assertion to D's indegree == 0's constraint
		if(current_sort.size() == V)
		{ 
			sort_list.push_back(current_sort);
			
			// clean up stack
			while (current_sort.size() > 0)
			{
				if (current_sort.size() != bases.size())
					throw "current_sort.size() != bases.size()";
				int q = current_sort.back();
				current_sort.pop_back();

				// "restores" all edges (q, x)
				// NOTE: it is important to iterate over edges instead
				// of successors, so count is updated correctly in multigraphs

				for (auto const& nbr : adj[q])
				{
					count[nbr] ++;
					if (count[nbr] < 0) return -1;
				}
				// remove entries from D
				while (D.size() > 0 && count[D.back()] > 0)
					D.pop_back();

				// corresponds to a circular shift of the values in D
				// if the first value chosen (the base) is in the first
				// position of D again, we are done and need to consider the
				// previous condition
				D.push_front(q);
				if (D.back() == bases.top())
					//  all possible values have been chosen at current position
					// remove corresponding marker
					bases.pop();
				else
					// there are still elements that have not been fixed
					// at the current position in the topological sort
					// stop removing elements, escape inner loop
					break;				
			}
		}
		else
		{
			if (D.empty())
			{
				throw "Graph contains a cycle.";
				return -1;
			}

			// choose next node
			int q = D.back();
			D.pop_back();

			// "erase" all edges (q, x)
			// NOTE: it is important to iterate over edges instead
			// of successors, so count is updated correctly in multigraphs
			for (auto const& nbr : adj[q])
			{
				count[nbr] --;
				if (count[nbr] < 0) return -1;
				if (count[nbr] == 0)D.push_back(nbr);
			}
			current_sort.push_back(q);

			// base for current position might _not_ be fixed yet
			if (bases.size() < current_sort.size())
				bases.push(q);

		}

		if (bases.empty()) break;
	}
	
	return 0;
}
