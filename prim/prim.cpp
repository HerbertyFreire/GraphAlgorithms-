#include "prim.h"
#include <bits/stdc++.h>
typedef pair<int, int> Pair;


Grafo::Grafo(int vertices) {
    this->vertices = vertices;
    for (int i = 0; i <= vertices; i++) {
        this->adj.push_back(NULL);
    }
}

void Grafo::adcAresta(int vertc1, int vertc2, int peso) {
    node* edge = (node*) malloc(sizeof(node));
    edge->destino = vertc2;
    edge->peso = peso;
    edge->next = adj[vertc1];
    adj[vertc1] = edge;
}

int custo_total(vector<int> custos){
    int total = 0;
    for(int i=1; i<custos.size(); i++) {
        total += custos[i];
    }
    return total;
}

void Grafo::Prim(Grafo grafo, int inicial, const char* output, bool solution) {
    int v = grafo.vertices;
    vector<node*> arestas = grafo.adj; 
    vector<int> custos;
    vector<int> prev;
    vector<bool> visitados;

    for(int i=0; i <= grafo.vertices; i++){
        custos.push_back(INF);
        prev.push_back(-1);  
        visitados.push_back(false);
    }

    priority_queue<pair<int,int>, vector <pair<int,int>>, greater<pair<int,int>>> min_heap;

    custos[inicial] = 0;
    min_heap.push(make_pair(custos[inicial], inicial));

    while(min_heap.size() > 0) {
        int u = min_heap.top().second; 
        min_heap.pop();
        visitados[u] = true;  
        node *current = arestas[u];
        while(current != NULL) {
            int peso = current->peso;
            int destino = current->destino;

            if(!visitados[destino] && custos[destino] > peso){
                custos[destino] = peso;
                prev[destino] = u; 
                min_heap.push(make_pair(custos[destino], destino));
            }
            current = current->next;
        }
    }
    
    if (output) {
        ofstream output_file;
        output_file.open(output);
        if (solution) {
            for (int i = 0; i < prev.size(); i++) {  
                if (prev[i] == -1) continue;
				output_file << "(" << prev[i] << "," << i << ") ";
            }
            output_file << endl;
        } else {
            output_file << custo_total(custos) << endl;
        }
        output_file.close();
    } else {
        if (solution) {
            for (int i = 0; i < prev.size(); i++) {  
                if (prev[i] == -1) continue;
				cout << "(" << prev[i] << "," << i << ") ";
            }
            cout << endl;
        } else {
            cout << custo_total(custos) << endl;
        }
    }
}