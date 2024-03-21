#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <fstream>
using namespace std;

void dfs(int no, vector<int> &visitado, vector<int> adj[], stack<int> &pilha)
{
    visitado[no] = 1;
    for (auto vizinho : adj[no])
    {
        if (!visitado[vizinho])
        {
            dfs(vizinho, visitado, adj, pilha);
        }
    }
    pilha.push(no);
}

void dfs_inverso(int no, vector<int> &visitado, vector<int> adjInvertido[], vector<int> &componente)
{
    visitado[no] = 1;
    componente.push_back(no);
    for (auto vizinho : adjInvertido[no])
    {
        if (!visitado[vizinho])
        {
            dfs_inverso(vizinho, visitado, adjInvertido, componente);
        }
    }
}

void kosaraju(int n, vector<int> adj[], vector<vector<int>> &cfcs)
{
    vector<int> visitado(n, 0); // vetor de visitados
    stack<int> pilha;      // pilha para armazenar a ordem dos vértices

    // DFS
    for (int i = 0; i < n; i++)
    {
        if (!visitado[i])
        {
            dfs(i, visitado, adj, pilha);
        }
    }

    vector<int> adjInvertido[n]; // transposição do grafo (arestas invertidas)
    for (int i = 0; i < n; i++)
    {
        visitado[i] = 0;
        for (auto j : adj[i])
        {
            adjInvertido[j].push_back(i);
        }
    }

    while (!pilha.empty())
    {
        int no = pilha.top();
        pilha.pop();
        if (!visitado[no])
        {
            vector<int> componente;
            dfs_inverso(no, visitado, adjInvertido, componente);
            cfcs.push_back(componente);
        }
    }

    return;
}

int main(int argc, char *argv[])
{
    int no_inicial = 1;
    string arquivo_entrada = "";
    string arquivo_saida = "null";

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Ajuda" << endl;
            cout << "-h: mostra ajuda" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            arquivo_saida = argv[i + 1];
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            arquivo_entrada = argv[i + 1];
        } else if(strcmp(argv[i], "-i") == 0){
            no_inicial = atoi(argv[i+1]);
        }
    }

    if (arquivo_entrada == "")
    {
        cout << "Nenhum arquivo de entrada especificado. Use o parâmetro -f" << endl;
        return 1;
    }

    ifstream fin(arquivo_entrada);
    if (!fin)
    {
        cerr << "Não foi possível abrir o arquivo de entrada: " << arquivo_entrada << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<int> adj[n];

    for (int i = 0; i < m; i++)
    {
        int v1, v2;
        fin >> v1 >> v2;

        // Ajustar índices para começar a partir do 0
        v1--;
        v2--;

        adj[v1].push_back(v2); // Adicionar aresta à lista de adjacência
    }

    vector<vector<int>> cfcs;
    kosaraju(n, adj, cfcs);

    if (arquivo_saida != "null")
    {
        ofstream fout(arquivo_saida);
        if (!fout)
        {
            cerr << "Não foi possível abrir o arquivo de saída: " << arquivo_saida << endl;
            return 1;
        }
        for (const auto &cfc : cfcs)
        {
            int contador = 0;
            for (int no : cfc)
            {
                if (contador == cfc.size() - 1) {
                    fout << no + 1;
                } else {
                    fout << no + 1 << " ";
                }
                contador++;
            }
            fout << endl;
        }

        fout.close();
    } else {
        for (const auto &componente : cfcs) {
            for (int no : componente) {
                cout << no+1 << " ";
            }
            cout << endl;
        }

    }

    return 0;
}
