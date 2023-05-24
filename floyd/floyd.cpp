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

	while(getline(file, line)){
		istringstream iss(line);
		if (!(iss >> u >> v >> w))
			w =  1;
		graph->w[u-1][v-1] = w;
	} 
	
	return graph;
}


/*
void displayGraph(struct Graph *graph)
{
	for (int i=0; i<graph->v; i++){
		cout << "[ ";
		for (int j=0; j<graph->v; j++){
			if (graph->w[i][j] == INT_MAX){
				cout << "inf ";
			}
		       	else{	
				cout << ' ' << graph->w[i][j] << "  ";
			}
		}
		cout << " ]" << endl;
	}

}
*/

struct Path
{	
	int size;
	int **pre;
	int **dist;
};


struct Path* newPath(int size)
{
	struct Path* path = (struct Path*) malloc(sizeof(struct Path));
	path->size = size;
	path->pre = new int*[size];
	path->dist = new int*[size];
	for (int i=0; i<size; i++){
		path->pre[i] = new int[size];
		path->dist[i] = new int[size];
	}
	return path;
}




struct Path* floyd(struct Graph* graph)
{	
	struct Path* path;
	int best, new_best;
	
	path = newPath(graph->v);

	// initialize distance vector
	for (int i=0; i<graph->v; i++){
		for (int j=0; j<graph->v; j++){
			path->dist[i][j] = graph->w[i][j];
			if(graph->w[i][j] == INT_MAX)
				path->pre[i][j] = -1;	
			else
				path->pre[i][j] = j+1;	
		}
	}

	for(int k=1; k<graph->v; k++){
		for(int i=0; i<graph->v; i++){
			for(int j=0; j<graph->v; j++){
				new_best = path->dist[i][k] + path->dist[k][j];
				if (new_best < path->dist[i][j] && path->dist[i][k] != INT_MAX && path->dist[k][j] != INT_MAX){
					path->dist[i][j] = new_best;
					path->pre[i][j] = path->pre[i][k];
				}
			}
		}
	}

	return path;
}


/*
void displayPath(struct Path* path, int u, int v)
{
	cout << u;
	if (u != v && path->pre[u-1][v-1] != -1){
		cout << " -> ";
		displayPath(path, path->pre[u-1][v-1], v);
	}
}
*/

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
	// Print distance from starting to ending veretex
	if (end)
		file << path->dist[start-1][end-1];

	// Print the solution tree 
	else if (showSolution){
		for (int i=0; i<graph->v; i++){
			if (i+1 != start){	
				file << "("; 
				if (path->pre[start-1][i] == i+1){
					file << start << "," << i+1 << ") ";
				}
				else {	
					file << path->pre[start-1][i] << "," << i+1 << ") ";
				}
			}
		}
	}
	
	// Print distance from starting vetrex to all others veteces
	else{
		
		for (int i=0; i<graph->v; i++){
			if (path->dist[start-1][i] == INT_MAX)	
				file << i+1 << ":inf ";
			else
				file << i+1 << ":" << path->dist[start-1][i] << ' ';
		}
	}
	file.close();
}


void writeToScreen(int start, int end, bool showSolution, struct Path* path, struct Graph* graph)
{
	// Print distance from starting to ending veretex
	if (end)
		cout << path->dist[start-1][end-1];

	// Print the solution tree 
	else if (showSolution){
		for (int i=0; i<graph->v; i++){
			if (i+1 != start){	
				cout << "("; 
				if (path->pre[start-1][i] == i+1){
					cout << start << "," << i+1 << ") ";
				}
				else {	
					cout << path->pre[start-1][i] << "," << i+1 << ") ";
				}
			}
		}
	}	
	// Print distance from starting vetrex to all others veteces
	else{
		
		for (int i=0; i<graph->v; i++){
			if (path->dist[start-1][i] == INT_MAX)	
				cout << i+1 << ":inf ";
			else
				cout << i+1 << ":" << path->dist[start-1][i] << ' ';
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
		struct Path* path = floyd(graph);
		if (fileout)
			writeToFile(fileout, start, end, showSolution, path, graph);
		else
			writeToScreen(start, end, showSolution, path, graph);
	}
	return 0;
}
