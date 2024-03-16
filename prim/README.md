# Algoritmo de Prim

O Algoritmo de Prim é um algoritmo guloso (greedy algorithm) empregado para encontrar uma árvore geradora mínima (minimal spanning tree) num grafo conectado, valorado e não direcionado. Isso significa que o algoritmo encontra um subgrafo do grafo original no qual a soma total das arestas é minimizada e todos os vértices estão interligados. O algoritmo foi desenvolvido em 1930 pelo matemático Vojtěch Jarník e depois pelo cientista da computação Robert Clay Prim em 1957 e redescoberto por Edsger Dijkstra em 1959.

## Compilação

Para compilar, utilizar o comando abaixo na pasta do algoritmo:

``make build``

## Entrada

A entrada deve ser dada por dois inteiros **v** e **e**, indicando respectivamente o número de vértices e de arestas. Na sequência, devem ser informadas **e** linhas contendo três inteiros: **a**, **b** e **c**, onde **a** e **b** são os vértices nas extremidades da aresta e **c** é o peso (ou custo) da aresta (opcional). Importante salientar que 1 <= a, b <= v. Caso o peso da aresta não seja informado, será considerado 1.

Abaixo é possível visualizar um exemplo de entrada de um grafo com 6 vértices e 8 arestas:

```
6 8
1 2 5
1 3 4
1 4 2
1 6 6
2 4 1
2 5 7
3 5 6
4 6 1
```

Obs: Para maior conveniência, utilizar um arquivo de entrada (como o ``arquivo-entrada.dat`` já presente no projeto) e informar no momento da execução através do parâmetro ``-f arquivo-entrada.dat``.

## Execução

O comando base de execução do algoritmo é (após compilado):

``./prim``

Como citado acima, é conveniente utilizar um arquivo de entrada e informar através do parâmetro ``-f``. Também é possível informar um arquivo para a saída com o parâmetro ``-o``.

Para indicar o vértice de início utilize ``-i``, seguido de um inteiro entre 1 e v. Também é possível exibir a árvore com o parâmetro ``-s``. Para ajuda durante a execução, utilizar ``-h``.

Logo, uma execução do algoritmo informando o vértice inicial (obrigatório) e um arquivo de entrada (da entrada de exemplo), além de pedir a solução (árvore encontrada) seria do tipo:

``./prim -f arquivo-entrada.dat -i 1 -s``

Com o retorno:

```
(1,3) (1,4) (3,5) (4,2) (4,6)
```

## Saída

A saída pode variar de acordo com os parâmetros informados:
 1. Se ``-s`` for utilizado, será informada uma linha no formato ``(a,b) (a,c) ... (b, a) ... (v, v)``, onde a, b, c e v são vértices que formam arestas na árvore geradora mínima.
 2. Se ``-s`` não for utilizado, será mostrada apenas o custo da árvore geradora mínima.
