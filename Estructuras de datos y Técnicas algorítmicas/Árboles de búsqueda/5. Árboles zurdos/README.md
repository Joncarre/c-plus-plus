# Árboles zurdos

Dado un árbol binario, se llama *altura mínima* del árbol a la menor de sus distancias desde la raíz a un subárbol vacío. Se puede especificar formalmente mediante las ecuaciones:

    hmin(avacio)          = 0
    hmin(cons(i, x, d))   = 1 + min(hmin(i), hmin(d))
    
Se dice que un árbol binario es *zurdo* si o, bien es vacío, o si no lo es, ambos hijos son zurdos y la altura mínima del hijo izquierdo nunca es menor que la del hijo derecho.

Se presenta una solución de coste lineal respecto al número de nodos que, dado un árbol binario, determina si es o no zurdo.

**Entrada de ejemplo**

     6
     0 0 0 -1 -1 -1 -1 
     0 0 -1 -1 0 -1 -1 
     0 0 0 -1 -1 -1 0 -1 -1 
     0 0 -1 -1 0 0 -1 -1 -1
     0 0 -1 0 -1 -1 0 -1 -1
     0 -1 0 -1 0 -1 -1

**Salida de ejemplo**

     SI
     SI
     SI
     SI
     NO
     NO
