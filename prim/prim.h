#ifndef PRIM_H
#define PRIM_H

#include "../utils/graph.h"

/*!
 * @function    solution_graph
 * @abstract    Create a square matrix with (size * size) elements equal to INT_MAX
 * @param       size    Size o matrix.
 * @result      Square matrix with (size * size) elements equal to INT_MAX
*/
int** solution_graph(int size);

/*!
 * @function    prim
 * @abstract    Prim algorithm.
 * @param       graph       Pointer to a graph.
 * @param       src         Source node.
 * @param       solution    Boolean informing if the solution will be presented.
 * @param       output      Pointer to the output data.
 * @result      Cost of minimum spanning tree.
*/
int prim(Graph* graph, int src, bool solution, ostream* output);

#endif