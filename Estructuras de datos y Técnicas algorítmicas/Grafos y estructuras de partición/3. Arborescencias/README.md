# Arborescencias

Un grafo dirigido es una arborescencia si existe un vertice, llamado raız, desde el que se puede alcanzar cualquier otro vertice a traves de un camino unico.

**Entrada**

La entrada esta compuesta por diversos casos de prueba. Para cada caso, la primera lınea contiene el
numero de vertices del grafo, V (entre 1 y 10.000), y la segunda el numero de aristas dirigidas, A (entre 0
y 100.000). A continuacion aparecen A lıneas, cada una con dos enteros que representan el origen y el
destino de cada una de las aristas (valores entre 0 y V-1). Los grafos no contienen aristas de un vertice
a sı mismo ni aristas repetidas.

**Salida**

Para cada caso de prueba se escribira SI seguido del vertice raız, si el grafo es arborencencia, y se
escribira NO en caso contrario.

**Entrada de ejemplo**

    4
    3
    0 1
    0 2
    2 3
    6
    5
    0 2
    0 3
    1 0
    1 4
    1 5
    5
    5
    0 1
    1 2
    2 3
    3 4
    4 0

**Salida de ejemplo**

    SI 0
    SI 1
    NO

**Autor del problema:** Alberto Verdejo.
