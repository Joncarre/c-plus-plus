# Rango de claves

Dado un arbol binario de busqueda y dos claves k1 y k2, el problema consiste en producir una lista ordenada con las claves del arbol entre k1 y k2, ambas inclusive.

La implementacion debe ser lo mas eficiente posible tanto desde el punto de vista del recorrido del arbol (no se exploran partes del arbol en las que sea imposible encontrar claves en el rango) como de generacion de la lista resultado.

**Entrada**

La entrada esta formada por diversos casos de prueba. Cada caso ocupa tres lıneas. En la primera aparece el numero N de elementos en el arbol (un numero entre 1 y 100.000). A continuacion, en una misma lınea, aparecen esos elementos (numeros enteros entre 1 y 1.000.000), separados por espacios, y en el orden en el que tienen que ser insertados en el  arbol. En la siguiente lınea aparecen las dos claves, k1 <= k2 (numeros enteros entre 1 y 1.000.000) que delimitan el rango de claves a buscar. La entrada termina cuando un arbol no tiene elementos (N es 0).

**Salida**

Para cada caso de prueba se escribiran las claves del arbol entre k1 y k2, ambas inclusive, ordenadas, en una misma lınea y separadas por espacios. Si la lista de claves en el rango es vacıa, se dejara la lınea en blanco.

**Entrada de ejemplo**

    6
    15 20 25 30 35 40
    25 35
    6
    15 20 25 30 35 40
    26 29
    6
    25 15 30 20 40 35
    15 29
    0

**Salida de ejemplo**

    25 30 35
    15 20 25
 
 **Autor del problema:** Alberto Verdejo.
