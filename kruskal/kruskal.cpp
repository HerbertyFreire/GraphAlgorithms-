#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <tuple>
using namespace std;

#include "kruskal.h"

#include "../utils/graph.h"

typedef pair <int,int> pairInt;

void kruskal(vector <tuple <int, int, int>> edgeList, vector <tuple <int, int, int>>* result, int gSize) {
  int parent[gSize];
  int kRank[gSize];

  for(int i = 0; i < gSize; i++) {
    parent[i] = i;
	  kRank[i] = 0;
  }

  for(auto edge : edgeList) {
    if(findSet(get<1>(edge), parent) != findSet(get<2>(edge), parent)) {        
        result->push_back(make_tuple(min(get<1>(edge),get<2>(edge)), max(get<1>(edge),get<2>(edge)), get<0>(edge)));
        unionSet(findSet(get<1>(edge), parent), findSet(get<2>(edge), parent), kRank, parent);
      }
  }    
}

int findSet(int v, int* parent) {
  if(parent[v] != v) {
    parent[v] = findSet(parent[v], parent);
  }

  return parent[v];
}

void unionSet(int v, int u, int* kRank, int* parent) {
  if(kRank[v] >= kRank[u]) {
    parent[u] = v;
    if(kRank[v] == kRank[u]) {
      kRank[v]++;
    }
  } else {
    parent[v] = u;
  }
}