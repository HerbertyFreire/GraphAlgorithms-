# Algoritmo de Kruskal

O algoritmo de Kruskal é um algoritmo em teoria dos grafos que busca uma árvore geradora mínima para um grafo conexo com pesos. Isto significa que ele encontra um subconjunto das arestas que forma uma árvore que inclui todos os vértices, onde o peso total, dado pela soma dos pesos das arestas da árvore, é minimizado. Se o grafo não for conexo, então ele encontra uma floresta geradora mínima (uma árvore geradora mínima para cada componente conexo do grafo). O algoritmo de Kruskal é um exemplo de um algoritmo guloso (também conhecido como ganancioso ou greedy).

## Compilação

Para compilar, utilizar o comando abaixo na pasta do algoritmo:

``make build``

## Entrada

A entrada deve ser dada por dois inteiros **v** e **e**, indicando respectivamente o número de vértices e de arestas. Na sequência, devem ser informadas **e** linhas contendo três inteiros: **a**, **b** e **c**, onde **a** e **b** são os vértices nas extremidades da aresta e **c** é o peso (ou custo) da aresta (opcional). Importante salientar que 1 <= a, b <= v. Caso o custo da aresta não seja informado, será considerado 1.

Abaixo é possível visualizar um exemplo de entrada de um grafo com 7 vértices e 11 arestas:

```
7 11
1 2 7
1 4 5
2 4 9
2 3 8
2 5 7
3 5 5
4 5 15
4 6 6
5 6 8
6 7 11
5 7 9
```

Obs: Para maior conveniência, utilizar um arquivo de entrada (como o ``arquivo-entrada.dat`` já presente no projeto) e informar no momento da execução através do parâmetro ``-f arquivo-entrada.dat``.

## Execução

O comando base de execução do algoritmo é (após compilado):

``./kruskal``

Como citado acima, é conveniente utilizar um arquivo de entrada e informar através do parâmetro ``-f``. Também é possível informar um arquivo para a saída com o parâmetro ``-o``.

Também é possível exibir as arestas da árvore geradora com o parâmetro ``-s``, que também apresenta o custo de cada aresta. Para ajuda durante a execução, utilizar ``-h``

Logo, uma execução do algoritmo informando um arquivo de entrada (da entrada de exemplo), além de pedir a solução (arestas da árvore) seria do tipo:

``./kruskal -f arquivo-entrada.dat -s``

Com o retorno:

```
(1,2) : 7
(1,4) : 5
(2,5) : 7
(3,5) : 5
(4,6) : 6
(5,7) : 9
Total cost: 39
```

## Saída

A saída pode variar de acordo com os parâmetros informados:
 1. Se ``-s`` for utilizado, serão informadas v - 1 linhas no formato ``(u,v) : w``, onde u e v são as extremidades da aresta e w é o custo dela. Ao final também é informado o  custo total da árvore (ou floresta) geradora encontrada.
 2. Se ``-s`` não for utilizado, será retornado um inteiro com o custo total da árvore (ou floresta) geradora encontrada.