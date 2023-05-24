#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits.h>
#include <algorithm>


#define MAX_CAPACITY 50

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
	// Initialize weight matrix with 0 on the diagonal and infinte on the other places 
	for (int i=0; i<v;  i++){
		graph->w[i] = new int[v];
		for (int j = 0; j<v; j++){
			if (i==j)
				graph->w[i][j] = 0;
			else
				graph->w[i][j] = INT_MAX;
		}
	}
	
	return graph;
}


struct Node
{
	int v;
	int dist;
};


struct Heap
{
	int size; // Actual size
	int capacity; // Maximum size
	struct Node **array;
};


// Utility for creating a new node
struct Node* newNode(int v, int dist)
{	
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->v = v;
	node->dist = dist;
	return node;
};


// Utility for creating a new heap
struct Heap* newHeap(int capacity)
{
	struct Heap* heap = (struct Heap*) malloc(sizeof(struct Heap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->array = (struct Node**) malloc(capacity * sizeof(struct Node*));
	
	return heap;
};



void swapNodes(struct Node**  a, struct Node** b)
{
	struct Node* temp = *a;
	*a = *b;
	*b = temp;
}



void heapify(struct Heap* heap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < heap->size && heap->array[left]->dist < heap->array[smallest]->dist)
		smallest = left;
	
	if (right < heap->size && heap->array[right]->dist < heap->array[smallest]->dist)
		smallest = right;

	if (smallest != idx){
		swapNodes(&heap->array[smallest], &heap->array[idx]);

		heapify(heap,  smallest);
	}
}



int isEmpty(struct Heap* heap)
{
	return heap->size == 0;
}


struct Node* removeRoot(struct Heap* heap)
{
	if (isEmpty(heap))
		return NULL;

	struct Node* root = heap->array[0];
	struct Node* lastNode = heap->array[heap->size-1];
	heap->array[0] = lastNode;

	heap->size--;
	heapify(heap, 0);

	return root;
}


void insert(struct Heap* heap, int v, int dist)
{
	int i;
	heap->array[heap->size] = newNode(v, dist); 	
	heap->size++;
	i = heap->size-1;
	while (i && heap->array[i]->dist < heap->array[(i-1)/2]->dist){	
		swapNodes(&heap->array[i], &heap->array[(i-1) / 2]);
		i = (i-1) / 2; 
	}
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

		adj[u-1].push_back(v);
		adj[v-1].push_back(u);
		graph->w[u-1][v-1] = w;
		graph->w[v-1][u-1] = w;
	}	
	graph->adj = adj;
	file.close();
	return graph;
}


// Structure to store the shortest path
struct Path
{	
	int size;
	int *pre;
	int *dist;
};


// Utility function to create a new path
struct Path* newPath(int size)
{
	struct Path* path = (struct Path*) malloc(sizeof(struct Path));
	path->size = size;
	path->pre = (int*) malloc(size * sizeof(int));
	path->dist = (int*) malloc(size * sizeof(int));
	for (int i=0; i<size; i++){
		path->pre[i] = -1;
		path->dist[i] = INT_MAX;	
	}
	return path;
}


struct Path* prim(struct Graph* graph, int s)
{
	struct Heap* heap;
	struct Path* path;
	path = newPath(graph->v);

	heap = newHeap(MAX_CAPACITY); // initialize heap
	//path->dist[s-1] = 0; // Starting vertex distance is 0
	//path->pre[s-1] = s;
	for (int i=0; i<graph->v; i++){
		insert(heap, i+1, path->dist[i]);
	}
	int u, v;
	while (!isEmpty(heap)){
		u = removeRoot(heap)->v;
		for (int i=0; i<graph->adj[u-1].size(); i++){
			v = graph->adj[u-1][i];
			if (path->dist[v-1] > graph->w[u-1][v-1]){
				path->dist[v-1] = graph->w[u-1][v-1];
				path->pre[v-1] = u;
				insert(heap, v, path->dist[v-1]); 
			}
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
}


void writeToFile(string filename, int start, bool showSolution, struct Path* path, struct Graph* graph)
{
	ofstream file;
	file.open(filename);
	if (showSolution){
		int prev;
		for (int i=0; i<graph->v; i++){
			prev = path->pre[i];
			if (!(i > prev && path->pre[prev-1]-1 == i))
				file << "("<< prev << ","<< i+1 << ") ";
		}
	}
	// Print MST weight
	else{
		int w = 0;
		int prev;
		for (int i=0; i<graph->v; i++){
			prev = path->pre[i];
			if (!(i > prev && path->pre[prev-1]-1 == i))
				w+=path->dist[i];
		}
		file << w;
	}
	file.close();
}


void writeToScreen(int start, bool showSolution, struct Path* path, struct Graph* graph)
{
	if (showSolution){
		int prev;
		for (int i=0; i<graph->v; i++){
			prev = path->pre[i];
			if (!(i > prev && path->pre[prev-1]-1 == i))
				cout << "("<< prev << ","<< i+1 << ") ";
		}
	}
	// Print MST weight
	else{
		int w = 0;
		int prev;
		for (int i=0; i<graph->v; i++){
			prev = path->pre[i];
			if (!(i > prev && path->pre[prev-1]-1 == i))
				w+=path->dist[i];
		}
		cout << w;
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
	char* fileout = getCmdOption(argv, argv+argc, "-o");	
	
	start = 0;
	if (i)
		start = (int)*i - 48;
	
	if (filename && start){
		struct Graph* graph = readGraph(filename);
		struct Path* path = prim(graph, start);
		if (fileout)
			writeToFile(fileout, start, showSolution, path, graph);
		else
			writeToScreen(start, showSolution, path, graph);
	}
	return 0;
}

