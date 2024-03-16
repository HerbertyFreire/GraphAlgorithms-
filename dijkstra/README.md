# Algoritmo de Dijkstra

O Algoritmo de Dijkstra (E.W. Dijkstra) é um dos algoritmos que calcula o caminho de custo mínimo entre vértices de um grafo. Escolhido um vértice como raiz da busca, este algoritmo calcula o custo mínimo deste vértice para todos os demais vértices do grafo. Ele é bastante simples e com um bom nível de performance.

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

``./dijkstra``

Como citado acima, é conveniente utilizar um arquivo de entrada e informar através do parâmetro ``-f``. Também é possível informar um arquivo para a saída com o parâmetro ``-o``.

Para indicar os vértices de início e fim, utilizar ``-i`` e ``-l``, respectivamente, seguidos de um inteiro entre 1 e v. O parâmetro ``-l`` é opcional e se não informado serão calculadas as distâncias entre o vértice informado após ``-i`` e todos os outros. Também é possível exibir o caminho com o parâmetro ``-s``, que, de forma análoga, mostra apenas o caminho para o vértice final se ``-l`` for informado e para todos os outros se não for. Para ajuda durante a execução, utilizar ``-h``

Logo, uma execução do algoritmo informando o vértice inicial (obrigatório) e um arquivo de entrada (da entrada de exemplo), além de pedir a solução (caminho encontrado) seria do tipo:

``./dijkstra -f arquivo-entrada.dat -i 1 -s``

Com o retorno:

```
1 : 0
1 -> 2 : 5
1 -> 3 : 4
1 -> 4 : 2
1 -> 3 -> 5 : 10
1 -> 4 -> 6 : 3
```

## Saída

A saída pode variar de acordo com os parâmetros informados:
 1. Se ``-l`` for informado e ``-s`` for utilizado, será informada uma linha no formato ``i -> ... -> v -> ... -> l : d``, onde i é o início e l é o final do caminho, com os vértices v que fazem parte deste caminho, além de d, que é a distância total.
 2. Se ``-l`` for informado e ``-s`` não for utilizado, será um inteiro indicando a distância do caminho encontrado
 3. Se ``-l`` não for informado e ``-s`` for utilizado, será informada uma linha para cada vértice do grafo, no formato ``i -> ... -> v -> ... -> l : d``, onde i é o início e l é o final do caminho, com os vértices v que fazem parte deste caminho, além de d, que é a distância total.
 4. Se ``-l`` não for informado e ``-s`` não for utilizado, serão pares do tipo ``a:b``, onde a é um vértice e b a distância entre o vértice inicial e a. 
 
 Obs: se o caminho não existir, será informado -1 no lugar da distância nos casos 3 e 4. Nos casos 1 e 2 será informada uma mensagem: ``There is not a path available between {i} and {l}!``
