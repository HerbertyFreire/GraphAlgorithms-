#include <iostream>
using namespace std;

#include "prim.h"

#include "../utils/utils.h"
#include "../utils/graph.h"

int main(int argc, char** argv) {
  Argument args;
  bool sucess = get_arguments(argc, argv, &args);

  if (sucess) {
    if (args.help) {
      help_arguments("Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph.", true, false);
    } else {
      if (args.initial != -1) {
        Graph graph = create_graph(args.input, true);

        int cost = prim(&graph, args.initial - 1, args.solution, args.output);
        
        if (!args.solution) {
          *args.output << cost << endl;
        }
      } else {
        cout << "Missing start vertex argument (-i)!" << endl;
      }
    }
  } else {
    cout << "The arguments entered are invalid!" << endl;
  }

  return 0;
}