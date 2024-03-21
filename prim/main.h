#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

void split(string line, int* source, int* dest, int* weight) {
    string delimiter = " "; 
    size_t pos = 0;
    string token;
    vector <int> values;
    line = line + " ";
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        values.push_back(stoi(token));
        line.erase(0, pos + delimiter.length());
    }

    *source = values[0];
    *dest = values[1];
    
    (values.size() == 2) ? *weight = 1 : *weight = values[2];
}

Grafo read_graph_file(const char* file){

    ifstream input_file(file);
    if (input_file.is_open()){
        string line;
        getline(input_file, line);
        int edges, vertexes, temp;
        split(line, &vertexes, &edges, &temp);
        Grafo grafo(vertexes);
        while (getline(input_file,line)) {
            int source, dest, weight;
            split(line, &source, &dest, &weight);
            grafo.adcAresta(source, dest, weight);
            grafo.adcAresta(dest, source, weight);
        }
        input_file.close();
        return grafo;
    }
    else {
        cout << "Não foi possível abrir o arquivo de entrada" << endl;
    }
    return 0;
}