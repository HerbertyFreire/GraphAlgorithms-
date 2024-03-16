#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>

#include "../utils/graph.h"

/*!
 * @function    kruskal
 * @abstract    Implements Kruskal's algoritm and put the results in a passed tuple vector.
 * @param       edgeList   Vector of tuples with the graph edges.
 * @param       result     Pointer to a tuples vector that will receive the edges of the result.
 * @param       gSize      Size of the graph. 
*/
void kruskal(vector <tuple <int, int, int>> edgeList, vector <tuple <int, int, int>>* result, int gSize);

/*!
 * @function    findSet
 * @abstract    Find the main parent of a vertex.
 * @param       v          Number of the vertex.
 * @param       parent     Pointer to a int vector whith the parents of vertices.
 * @result      Integer with the main parent of the given vertex.
*/
int findSet(int v, int* parent);

/*!
 * @function    unionSet
 * @abstract    Set a union between two vertices.
 * @param       v          First vertex.
 * @param       u          Second vertex.
 * @param       kRank      Pointer to a int vector whith the k ranks of vertices.
 * @param       parent     Pointer to a int vector whith the parents of vertices.
*/
void unionSet(int v, int u, int* kRank, int* parent);

#endif