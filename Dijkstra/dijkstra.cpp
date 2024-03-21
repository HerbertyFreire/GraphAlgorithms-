#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

const int INFINITO = 1000000;

string dijkstra(vector<vector<pair<int, int>>> &grafo, int inicio) {
    int tamanho = grafo.size();
    vector<int> distancia(tamanho, INFINITO);
    distancia[inicio] = 0;
    vector<bool> visitado(tamanho, false);

    for (int i = 0; i < tamanho; ++i) {
        int u = -1;
        for (int j = 0; j < tamanho; ++j) {
            if (!visitado[j] && (u == -1 || distancia[j] < distancia[u])) {
                u = j;
            }
        }

        visitado[u] = true;

        for (int j = 0; j < grafo[u].size(); ++j) {
            int v = grafo[u][j].first;
            int peso = grafo[u][j].second;

            if (distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
            }
        }
    }

    string distancias = "";
    for (int i = 1; i < tamanho; ++i) {
        if(distancia[i] != INFINITO) {
            distancias += to_string(i) + ":" + to_string(distancia[i]) + " ";
        }
        else {
            distancias += to_string(i) + ":" + "-1" + " ";
        }
    }
    return distancias;
}

int main(int argc, char *argv[]) {
    string arquivoEntrada = "";
    string arquivoSaida = "";
    int noInicial = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda" << endl;
            cout << "-h: Mostra a ajuda" << endl;
            cout << "-o <arquivo>: Redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: Lê o grafo do arquivo" << endl;
            cout << "-i : Define o vértice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            arquivoSaida = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0) {
            arquivoEntrada = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0) {
            noInicial = atoi(argv[i + 1]);
        }
    }

    if (arquivoEntrada == "") {
        cout << "Nenhum arquivo de entrada especificado. Use o parâmetro -f" << endl;
        return 1;
    }

    ifstream entrada(arquivoEntrada);
    if (!entrada) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << arquivoEntrada << endl;
        return 1;
    }

    int n, m; // número de vértices e arestas
    entrada >> n >> m; // lendo n e m
    vector<vector<pair<int, int>>> grafo(n + 1); // criando a matriz que emula um grafo

    for (int i = 0; i < m; i++) {
        int u, v, w; 
        entrada >> u >> v >> w; // lendo os vértices entre as arestas
        grafo[u].push_back(make_pair(v, w)); // adicionando v nos vizinhos de u
        grafo[v].push_back(make_pair(u, w)); // adicionando u nos vizinhos de v
    }

    entrada.close();

    string distancias = dijkstra(grafo, noInicial);

    if (!(arquivoSaida == "")) {
        ofstream saida(arquivoSaida);
        if (!saida) {
            cerr << "Não foi possível abrir o arquivo de saída: " << arquivoSaida << endl;
            return 1;
        }
        saida << distancias;
        saida << endl;
        saida.close();
    }
    cout << distancias << endl;
    return 0;
}
