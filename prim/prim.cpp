#include <sstream>
#include <limits.h>
using namespace std;

#include "prim.h"

#include "../utils/graph.h"

int** solution_graph(int size) {
  int** graph = new int * [size];

  for (int i = 0; i < size; i++) {
    graph[i] = new int[size];

    for (int j = 0; j < size; j++) {
      graph[i][j] = -INT_MAX;
    }
  }

  return graph;
}

int prim(Graph* graph, int src, bool solution, ostream* output) {
  int cost = 0;
  int v_count = graph->getSize();

  int visited[v_count] = {};
  int n_visited = 1;
  visited[src] = 1;

  int** solution_list = solution_graph(v_count);

  while (n_visited < v_count) {
    int current_min = INT_MAX;
    int pos_i, pos_j = 0;

    for (int i = 0; i < v_count; i++) {
      if (visited[i]) {
        Node* current_node = graph->getHead()[i];

        while (current_node != nullptr) {
          int j = current_node->value;

          if (!visited[j]) {
            int curret_cost = current_node->cost;

            if (curret_cost < current_min) {
              current_min = curret_cost;
              pos_i = i;
              pos_j = j;
            }
          }

          current_node = current_node->next;
        }
      }
    }

    visited[pos_j] = current_min;
    n_visited += 1;

    solution_list[pos_i][pos_j] = current_min;

    cost += current_min;
  }

  if (solution) {
    for (int i = 0; i < v_count; i++) {
      for (int j = 0; j < v_count; j++) {
        if (solution_list[i][j] > -INT_MAX) {

          *output << "(" << i + 1 << "," << j + 1 << ") ";
        }
      }
    }
    *output << endl;
  }

  return cost;
}