#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits.h>
#include <algorithm>



using namespace std;


struct Graph
{
	int v;
	int e;
	int **w;
	vector<vector<int > > adj;
};



// Utility for creating a new graph
struct Graph* newGraph(int v, int e)
{
	//struct Graph* graph = new Graph;
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->v = v;
	graph->e = e;
	graph->w = new int*[v];
	for (int i=0; i<v;  i++){
		graph->w[i] = new int[v];
		for (int j = 0; j<v; j++){
			if (i == j)
				graph->w[i][j] = 0;	
			else
				graph->w[i][j] = INT_MAX;
		}
	}
	
	return graph;
}

// Read graph from file
struct Graph* readGraph(string filename)
{
	string line;
	int n, m, u, v, w;
	ifstream file;
	file.open(filename);
		
	getline(file, line);
	istringstream iss(line);
	
	iss >> n >> m;
	
	struct Graph* graph = newGraph(n, m);
	vector<vector<int > > adj(n, vector<int>(0));

	while(getline(file, line)){
		istringstream iss(line);
		if (!(iss >> u >> v >> w))
			w =  1;

		adj[v-1].push_back(u);
		graph->w[u-1][v-1] = w;
	} 
	graph->adj = adj;
	
	return graph;
}



struct Path
{	
	int size;
	int *pre;
	int **dist;
};


struct Path* newPath(int size)
{
	struct Path* path = (struct Path*) malloc(sizeof(struct Path));
	path->size = size;
	path->pre = (int*) malloc(size * sizeof(int));
	path->dist = new int*[size - 1];
	for (int i=0; i<size; i++){
		path->pre[i] = -1;
	}

	for (int i=0; i<size-1; i++){
		path->dist[i] = new int[size];
		for (int j=0; j<size; j++){
			path->dist[i][j] = INT_MAX;
		}	
	}
	return path;
}




struct Path* bellman(struct Graph* graph, int v)
{	
	struct Path* path;
	int best, new_best;
	
	path = newPath(graph->v);

	// initialize distance vector
	path->dist[0][v-1] = 0; // weight 0 for path v to himself
	path->pre[v-1] = v;

	for(int l=1; l<graph->v-1; l++){
		for(int k=0; k<graph->v; k++){
			best = path->dist[l-1][k]; // best distance from v to k with l-1 edges
			// For all adjacents to k 
			for(int i=0; i<graph->adj[k].size(); i++){
				// If i and k are adjacents
				if (path->dist[l-1][graph->adj[k][i]-1] != INT_MAX){
					new_best = path->dist[l-1][graph->adj[k][i]-1] + graph->w[graph->adj[k][i]-1][k]; 
					if (new_best < best){
						path->pre[k] = graph->adj[k][i]; // update predecessor
						best = new_best;
					}
				}
			}
			path->dist[l][k] = best; // update best path
		}
	}
	return path;
}


// Utility for getting command line arguments
char* getCmdOption(char** begin, char** end, const string & option)
{
    char** itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}


bool cmdOptionExists(char** begin, char** end, const string& option)
{
    return std::find(begin, end, option) != end;
}


void displayHelp()
{	
	cout << "-h" << string(24, ' ') << ": mostra o help" << endl;
	cout << "-o <arquivo>" << string(14, ' ') << ": redireciona a saida para o ''arquivo''" << endl;
	cout << "-f <arquivo>" << string(14, ' ') << ": indica o ''arquivo'' que contém o grafo de entrda" << endl;
	cout << "-s" << string(24, ' ') << ": mostra a solução (em ordem crescente)" << endl;
	cout << "-i" << string(24, ' ') << ": vértice inicial" << endl;
	cout << "-l" << string(24, ' ') << ": vértice final" << endl;
}

void writeToFile(string filename, int start, int end, bool showSolution, struct Path* path, struct Graph* graph)
{
	ofstream file;
	file.open(filename);
	// Print distnce from start to end verteces
	if (end)
		file << path->dist[graph->v-2][end-1];
	// Print the solution tree 
	else if (showSolution){
		for (int i=0; i<graph->v; i++){
			if (i+1 != start){
				file << "("<< path->pre[i] << ","<< i+1 << ") ";
			}
		}
	}
	// Print distance from starting vetrex to all others veteces
	else{
		for (int i=0; i<graph->v; i++){
			if (path->dist[graph->v-2][i] == INT_MAX)
				file << i+1 << ":inf ";
			else
				file << i+1 << ":" << path->dist[graph->v-2][i] << ' ';
		}	
	}
	file.close();
}


void writeToScreen(int start, int end, bool showSolution, struct Path* path, struct Graph* graph)
{
	// Print distnce from start to end verteces
	if (end)
		cout << path->dist[graph->v-2][end-1];
	// Print the solution tree 
	else if (showSolution){
		for (int i=0; i<graph->v; i++){
			if (i+1 != start){
				cout << "("<< path->pre[i] << ","<< i+1 << ") ";
			}
		}
	}
	// Print distance from starting vetrex to all others veteces
	else{
		for (int i=0; i<graph->v; i++){
			if (path->dist[graph->v-2][i] == INT_MAX)
				cout << i+1 << ":inf ";
			else
				cout << i+1 << ":" << path->dist[graph->v-2][i] << ' ';
		}	
	}
	cout << endl;
}


int main(int argc, char* argv[])
{
	if (cmdOptionExists(argv, argv+argc, "-h")){
		displayHelp();
		return 0;	
	}

	int start, end;
	bool showSolution = cmdOptionExists(argv, argv+argc, "-s");

	char* filename = getCmdOption(argv, argv+argc, "-f");
	char* i = getCmdOption(argv, argv+argc, "-i");
	char* l = getCmdOption(argv, argv+argc, "-l");
	char* fileout = getCmdOption(argv, argv+argc, "-o");

	start = 0;
	end = 0;
	if (i)
		start = (int)*i - 48;
	if (l)
		end = (int)*l - 48;

	if (filename && start){
		struct Graph* graph = readGraph(filename);
		struct Path* path = bellman(graph, start);
		if (fileout)
			writeToFile(fileout, start, end, showSolution, path, graph);
		else
			writeToScreen(start, end, showSolution, path, graph);
	}
	return 0;
}
