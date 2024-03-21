#include "prim.h"
#include "../utils/utils_.h"
#include "main.h"

using namespace std;

int main(int argc, char** argv) {
    Argument args;
    bool param = get_arguments(argc, argv, &args);
    if (param) {
        if (args.help) {
            help_arguments("O algoritmo de Prim encontra a AGM (Árvore geradora mínima) do grafo, com complexidade O(|E| log|V|).", true);
        } else if (args.input) {
            Grafo grafo = read_graph_file(args.input);
            if (args.initial != -1) {
                grafo.Prim(grafo, args.initial, args.output, args.solution);
            } else {
                grafo.Prim(grafo, 1, args.output, args.solution);
            }
        } else {
            Grafo grafo = read_graph_file("graph.in");
            if (args.initial != -1) {
                grafo.Prim(grafo, args.initial, args.output, args.solution);
            } else {
                grafo.Prim(grafo, 1, args.output, args.solution);
            }
        }
    }
    return 0;
}