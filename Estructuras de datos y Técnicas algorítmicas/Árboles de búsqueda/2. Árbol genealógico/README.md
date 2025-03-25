# Árbol genealógico

Dado un árbol binario de enteros, se entiende que es un árbol genealógico correcto si se cumplen las siguientes reglas, producto de interpretar el entero de cada nodo como el año de nacimiento del individuo, el hijo izquierdo como su primer hijo de un máximo de dos, y el hijo derecho como el segundo hijo.

- La edad del padre siempre supera en al menos 18 años las edades de cada uno de los hijos.
- La edad del segundo hijo (si existe) es al menos dos años menos que la del primer hijo (no hay hermanos gemelos/mellizos en estos árboles).
- Los árboles genealógicos de ambos hijos son también correctos.

Se implemente un programa capaz de averiguar si un árbol binario es o no genealógico correcto y, en caso de serlo, el número de generaciones distintas que hay en la familia.

**Entrada de ejemplo**

     5
     100 60 30 -1 -1 -1 58 -1 -1
     100 60 30 -1 -1 -1 59 -1 -1
     100 -1 -1
     100 83 -1 -1 -1
     100 82 -1 -1 -1

**Salida de ejemplo**

     SI 3
     NO
     SI 1
     NO
     SI 2
