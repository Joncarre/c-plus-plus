# Encontrar el k-ésimo elemento en un árbol AVL

Extender la implementacion de arboles AVL de manera que se mantenga en cada nodo un nuevo atributo tam i que almacene el numero de nodos en el hijo izquierdo mas uno. Hacer los cambios necesarios para que las funciones que modifican los arboles mantengan coherente el valor de dicho atributo.

Implementar un metodo para localizar el k-esimo elemento mas pequeño en el arbol en tiempo logarıtmico (respecto al tamaño del arbol).

**Entrada**

La entrada esta formada por diversos casos de prueba. Cada caso ocupa cuatro lıneas. En la primera
aparece el numero N de claves (entre 1 y 50.000), no necesariamente distintas, a insertar en el arbol. A continuacion, en una misma lınea, aparecen esas claves (numeros enteros entre 1 y 1.000.000), separadas por espacios, en el orden en que deben ser insertadas. (Para este problema el valor asociado a cada clave es indiferente.) En la siguiente lınea aparece el numero M de elementos que se van a consultar (entre 1 y N). Y en la ultima lınea aparecen, separadas por espacios, las M posiciones (ordinales) de los elementos a consultar (numeros entre 1 y N). La entrada termina cuando un arbol no tiene elementos (N es 0).

**Salida**

Para cada caso de prueba se escribiran, en lıneas separadas, los elementos consultados, si existen. Si no hay elemento en la posicion consultada, se escribira ?? en su lugar. Tras procesar cada caso se escribira una lınea mas con ----.

**Entrada de ejemplo**

    4
    15 20 25 30
    2
    1 3
    5 16 8 4 4 32
    3
    2 4 5
    0

**Salida de ejemplo**

    15
    25
    ----
    8
    32
    ??
    ----
 
 **Autor del problema:** Alberto Verdejo.
