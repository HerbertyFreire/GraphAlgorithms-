#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "graph.h"

Graph::Graph(Edge edges[], int e_count, int v_count) {
  this->head = new Node*[v_count]();
  this->size = v_count;

  for (int i = 0; i < v_count; ++i) {
    head[i] = nullptr;
  }

  for (unsigned i = 0; i < e_count; i++) {
    int src_ver = edges[i].src;
    int dest_ver = edges[i].dest;
    int weight_ver = edges[i].weight;

    Node* new_node = addNode(dest_ver, weight_ver, this->head[src_ver]);
    this->head[src_ver] = new_node;
  }
}

Graph::~Graph() {
  for (int i = 0; i < size; i++) {
    delete[] head[i];
  }
  delete[] head;
}

Node* Graph::addNode(int value, int weight, Node* head) {
  Node* new_node = new Node;
  new_node->value = value;
  new_node->cost = weight;
  new_node->next = nullptr;

  if (head != nullptr) {
    if (head->cost > new_node->cost) {
      new_node->next = head;
    } else {
      Node* prev_node = head;
      Node* current_node = prev_node->next;

      while (current_node != nullptr && (current_node->cost < new_node->cost)) {
        prev_node = current_node;
        current_node = current_node->next;
      }

      prev_node->next = new_node;
      new_node->next = current_node;

      return head;
    }
  }

  return new_node;
}

void Graph::display(ostream* output) {
  for (int i = 0; i < this->size; i++) {
    Node* currentNode = this->head[i];

    while (currentNode != nullptr) {
      *output << "(" << i + 1 << ", " << currentNode->value + 1 << ", " << currentNode->cost << ") ";
      currentNode = currentNode->next;
    }
    
    if (this->head[i] != nullptr) {
      *output << endl;
    }
  }
}

Graph create_graph(istream* input, bool undirected) {
  int v_count, e_count;
  *input >> v_count >> e_count;

  if (undirected) {
    e_count *= 2;
  }

  string line;
  getline(*input, line);

  Edge edges[e_count] = {};
  for (int i = 0; i < e_count; i += undirected ? 2 : 1) {
    getline(*input, line);
    
    istringstream line_cin(line);
    int src, dest, weight = 1;
    line_cin >> src >> dest >> weight;

    edges[i] = {src - 1, dest - 1, weight};

    if (undirected) {
      edges[i + 1] = {dest - 1, src - 1, weight};
    }
  }

  return Graph(edges, e_count, v_count);
}