# ¿Es un árbol AVL?

Un arbol AVL (denominado ası por las iniciales de los apellidos de sus inventores, Georgii Adelson Velskii y Yevgeniy Landis) es un arbol binario de busqueda equilibrado en el sentido de que para todo subarbol se cumple que la diferencia entre las alturas de sus dos hijos es como mucho 1. Ademas, por ser de busqueda, tambien se cumple que la clave almacenada en la raız de cualquier subarbol es mayor que todas las claves en su hijo izquierdo y menor que todas las claves en su hijo derecho.

**Entrada**

La entrada comienza con el numero de casos que vienen a continuacion. Cada caso de prueba consiste en una lınea con la descripcion de un arbol binario: primero aparece su raız (un entero no negativo), y a continuacion la descripcion del hijo izquierdo y despues la del hijo derecho. El numero –1 indica el arbol vacıo. Los arboles nunca contendran mas de 20.000 nodos.

**Salida**

Para cada arbol se escribira SI si el arbol es AVL y NO en caso contrario.

**Entrada de ejemplo**

    3
    2 1 -1 -1 3 -1 4 -1 -1
    1 -1 3 2 -1 -1 4 -1 -1
    4 1 -1 -1 3 -1 2 -1 -1

**Salida de ejemplo**

    SI
    NO
    NO
 
 **Autor del problema:** Alberto Verdejo.
