#ifndef PRIM_H
#define PRIM_H

#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int, int> Pair;

typedef struct Node node;

struct Node{
    int destino;
    int peso;
    node* next;
};

class Grafo {
    int vertices;
    vector <node*> adj;
public:
    Grafo(int vertice);
    void adcAresta(int vertc1, int vertc2, int peso);
    void Prim(Grafo grafo, int inicial, const char* output, bool solution);
};

#endif