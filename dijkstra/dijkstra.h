#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../utils/graph.h"

/*!
 * @function    dijkstra
 * @abstract    Implements Dijkstra's algoritm and put the results in a passed int vector.
 * @param       graph       Pointer to a graph.
 * @param       distance    Pointer to a int vector that will receive the results.
 * @param       predecessor Pointer to a int vector that stores the predecessors of the vertices.
 * @param       start       Start vertex of the paths.
*/
void dijkstra(Graph* graph, int* distance, int* predecessor, int start);

/*!
 * @function    findShorterDistance
 * @abstract    Find the vertex with the shorter distance at the moment.
 * @param       distance    Pointer to a int vector that stores the distances.
 * @param       visited     Pointer to a int vector that stores the vertices that have been already visited.
 * @param       gSize       Size of the graph. 
*/
int findShorterDistance(int* distance, int* visited, int gSize);

/*!
 * @function    printPath
 * @abstract    Print the path between two vertices.
 * @param       output      Pointer to the current used form of output.
 * @param       initial     Initial vertex of the path.
 * @param       final       Final vertex of the path.
 * @param       gSize       Size of the graph. 
 * @param       predecessor Pointer to a int vector that stores the predecessors of the vertices. 
*/
void printPath(ostream* output, int initial, int final, int gSize, int* predecessor);

#endif