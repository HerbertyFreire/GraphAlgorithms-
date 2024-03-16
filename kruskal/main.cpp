#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <utility>
using namespace std;

#include "../utils/utils.h"
#include "../utils/graph.h"
#include "kruskal.h"

int main(int argc, char** argv) {
  Argument args;
  bool sucess = get_arguments(argc, argv, &args);

  if (sucess) {
    if (args.help) {
      help_arguments("The Kruskal algorithm finds a minimum spanning forest of an undirected edge-weighted graph.", false, false);
    } else {
      Graph graph = create_graph(args.input);

      vector <tuple <int, int, int>> result;
      vector <tuple <int, int, int>> edgeList;

      for(int i = 0; i < graph.getSize(); i++) {
        Node* currentNode = graph.getHead()[i];        

        while (currentNode != nullptr) {    
          edgeList.push_back(make_tuple(currentNode->cost, i, currentNode->value));          
          currentNode = currentNode->next;
        }
      }

      sort(edgeList.begin(), edgeList.end());      
      
      kruskal(edgeList, &result, graph.getSize());
    
      sort(result.begin(), result.end());  

      int acum = 0;

      if(args.solution) {        
        for(auto edge : result) {
          *args.output << "(" << get<0>(edge) + 1 << "," << get<1>(edge) + 1 << ")" << " : " << get<2>(edge) << endl;
          acum += get<2>(edge);
        }
        
        *args.output << "Total cost: " << acum << endl;
      } else {
        for(auto edge : result) {          
          acum += get<2>(edge);
        }
        *args.output << acum << endl;
      }      
    }
  } else {
    cout << "The arguments entered are invalid!" << endl;
  }

  return 0;
}