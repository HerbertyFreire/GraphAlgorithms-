#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "dijkstra.h"

#include "../utils/graph.h"

void dijkstra(Graph* graph, int* distance, int* predecessor, int start) {
  int gSize, count, vertex, adjacent;
  
  gSize = graph->getSize();
  count = gSize;

  int visited[gSize];
  
  for (int i = 0; i < gSize; i++) {
    predecessor[i] = -1;
    distance[i] = -1;
    visited[i] = 0;
  }

  distance[start] = 0;

  while(count > 0) {
    vertex = findShorterDistance(distance, visited, gSize);

    if(vertex == -1) {
      break;
    }

    visited[vertex] = 1;
    count--;

    Node* currentNode = graph->getHead()[vertex];        

    while (currentNode != nullptr) {
      adjacent = currentNode->value;

      if(distance[adjacent] < 0) {
        distance[adjacent] = distance[vertex] + currentNode->cost;
        predecessor[adjacent] = vertex;
      } else {
        if(distance[adjacent] > distance[vertex] + currentNode->cost) {
          distance[adjacent] = distance[vertex] + currentNode->cost;
          predecessor[adjacent] = vertex;
        }
      }

      currentNode = currentNode->next;
    }
  }      
}

int findShorterDistance(int* distance, int* visited, int gSize) {
  int shorterDistance = -1;
  bool first = true;

  for(int i = 0; i < gSize; i++) {
    if(distance[i] >= 0 && visited[i] == 0) {
      if(first) {
        shorterDistance = i;
        first = false;
      } else {
        if(distance[shorterDistance] > distance[i]) {
          shorterDistance = i;
        }
      }
    }
  }

  return shorterDistance;
}

void printPath(ostream* output, int initial, int final, int gSize, int* predecessor) {
  bool flag = false;
  int count = 0;
  int path[gSize];

  for(int i = 0; i < gSize; i++) {
    path[i] = -1;
  }
  
  int aux = final;
  while(aux != -1) {
    if(aux < 0) {        
      flag = true;
      break;
    }
    
    path[count] = aux + 1;
    aux = predecessor[aux];
    count++;
  }
  
  for(int i = count; i >= 0; i--) {
    if(path[i] != -1) {
      *output << path[i];
      if(path[i-1] != -1 && i > 0) {
        *output << " -> ";
      }
    }
  }  
}