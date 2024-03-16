# Projeto De Teoria Dos Gráfos
Trabalho necessário para a obtenção de nota referente à AB2 da disciplina de Teoria dos Grafos, no curso de Ciência da Computação promovido pela Universidade Federal de Alagoas (UFAL).

# Equipe:

José Herberty De Oliveira Freire
Leonardo Barbosa Barros

# 💻Descrição
O projeto tem como objetivo aplicar a implementação de 5 algoritmos nas linguagens C ou C++ envolvendo gráficos. Os referidos foram os seguintes:

# KOSARAJU:
O algoritmo de Kosaraju é utilizado para encontrar componentes fortemente conexos em um grafo direcionado. Ele opera em duas passagens:
Passagem Direta (DFS): Realiza uma travessia em profundidade (DFS) no grafo, registrando os vértices em uma pilha em ordem de finalização.
Passagem Reversa: Inverte as direções das arestas do grafo original e executa uma DFS a partir dos vértices na ordem determinada pela pilha da passagem direta.
Ao final, os vértices alcançados em cada execução da DFS formam componentes fortemente conexos. Esse algoritmo é eficiente, com complexidade de tempo linear em relação ao número de vértices e arestas do grafo. É uma ferramenta valiosa em várias aplicações, como compiladores, análise de redes sociais e roteamento em redes de computadores.

# PRIM:  
É um algoritmo guloso empregado para encontrar uma árvore geradora mínima num grafo conectado, valorizado e não direcionado.

# KRUSKAL:
O algoritmo de Kruskal é um algoritmo em teoria dos grafos que busca uma árvore geradora mínima para um grafo conexo com pesos. Isto significa que ele encontra um subconjunto das arestas que forma uma árvore que inclui todos os vértices, onde o peso total, dado pela soma dos pesos das arestas da árvore, é minimizado. Se o grafo não for conexo, então ele encontra uma floresta geradora mínima (uma árvore geradora mínima para cada componente conexo do grafo). O algoritmo de Kruskal é um exemplo de um algoritmo guloso (também conhecido como ganancioso ou greedy).

# DIJKSTRA:
O Algoritmo de Dijkstra (E.W. Dijkstra) é um dos algoritmos que calcula o caminho de custo mínimo entre vértices de um grafo. Escolhido um vértice como raiz da busca, este algoritmo calcula o custo mínimo deste vértice para todos os demais vértices do grafo. Ele é bastante simples e com um bom nível de performance.

# BELLMAN:
O algoritmo calculará o vetor de pais de um CPT ou anunciará que o gráfico tem um ciclo negativo.
