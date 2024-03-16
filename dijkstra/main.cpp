#include <iostream>
using namespace std;

#include "../utils/utils.h"
#include "../utils/graph.h"
#include "dijkstra.h"

int main(int argc, char** argv) {
  Argument args;
  bool sucess = get_arguments(argc, argv, &args);

  if (sucess) {
    if (args.help) {
      help_arguments("The Dijkstra algorithm is an algorithm for finding the shortest paths between nodes in a graph.");
    } else {
      if(args.initial != -1) {
        Graph graph = create_graph(args.input);
        
        int gSize = graph.getSize();
        int distance[gSize];
        int predecessor[gSize];

        dijkstra(&graph, distance, predecessor, args.initial - 1);        

        if(args.final != -1) {
          if(distance[args.final - 1] != -1) {
            if(args.solution) {
              printPath(args.output, args.initial - 1, args.final - 1, gSize, predecessor);
              *args.output << endl;
              *args.output << distance[args.final - 1] << endl;
            } else {
              *args.output << distance[args.final - 1] << endl;
            }    
          } else {
            *args.output << "There is not a path available between " << args.initial << " and " << args.final << "!" << endl;
          }
        } else {
            if(args.solution) {
              for (int i = 0; i < gSize; i++) {
                printPath(args.output, args.initial - 1, i, gSize, predecessor);                
                *args.output << " : " << distance[i] << endl;
              }
            } else {
              for (int i = 0; i < gSize; i++) {
                *args.output << i+1 << ":" << distance[i] << " ";
              }
              *args.output << endl;
            }
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