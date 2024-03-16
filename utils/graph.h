#ifndef GRAPH_H
#define GRAPH_H

/*!
 * @typedef     Node
 *              Structure of a node.
 * @field       value    Destination vertex.
 * @field       cost     Vertex edge cost.
 * @field       ntext    Pointer to next node.
*/
struct Node {
  int value, cost;
  Node* next;
};

/*!
 * @typedef     Edge
 *              Structure of a edge.
 * @field       src       Source node.
 * @field       dest      Destination node.
 * @field       weight    Vertex edge weight.
*/
struct Edge {
  int src, dest, weight;
};

/**
 * Implementation of a Graph
 *
 * The graph is controlled by a variable that informs the number of vertices
 * and a pointer to the adjacency list.
 *
 */
class Graph {
  private:
    int size;
    Node** head;
  public:
    Graph(Edge edges[], int e_count, int v_count);
    ~Graph();

    int getSize() { return this->size; };
    Node** getHead() { return this->head; };

    Node* addNode(int value, int weight, Node* head);

    void display(ostream* output);
};

/*!
 * @function    create_graph
 * @abstract    Transforms the input text into a graph
 * @param       input         Data entry.
 * @param       undirected    Create an undirected graph.
 * @result      An object of class Graph
*/
Graph create_graph(istream* input, bool undirected = false);

#endif