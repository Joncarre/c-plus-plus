# Árbol de Huffman

**¿Qué se persigue?**

Es posible reducir significativamente el número de bits requeridos para representar un texto si, en lugar de emplear un código de longitud fija como ASCII, se emplea un codigo de longitud variable. En este caso, el número de bits requeridos puede variar de carácter en carácter. El objetivo es codificar los caracteres que aparecen más frecuentemente usando cadenas de bits más cortas. Sin embargo, cuando el código es de longitud variable se necesita algún método para determinar los bits de inicio y de fin de un código.

La técnica de los códigos de Huffman nos permite construir códigos sin prefijos, que además serán óptimos, en el sentido de que se elegirán las menores longitudes de código para aquellos caracteres que aparezcan un mayor número de veces. El método de compresión/descompresión de datos consiste en lo siguiente:

- Calcular las frecuencias de todos los caracteres de un mensaje dado (tablad e frecuencias).
- Construir el "árbol de Huffman" a partir de la tabla de frecuencias.
- Construir una tabla de código de longitud variable utilizando el "árbol de Huffman".
- Una vez obtenidos los código de cada carácter se codifica el mensaje.
- El mensaje codificado se decodifica de forma directa usando el árbol de Huffman.

**¿Cómo está implementado?**

Un "árbol de Huffman" es un árbol binario que, o bien es un nodo hoja que contiene un carácter y su frecuencia, o bien está construido a partir de otros dos árboles de Huffman A1 y A2, hijo izquierdo y hijo derecho respectivamente y como frecuencia de la nueva raíz la suma de las frecuencias de A2 y A2. El código de un carácter viene dado por el camino desde la raíz hasta la hoja que contenga al carácter, de forma que para cada bit del código, un "0" significa ir al hijo izquierdo y un "1" ir al hijo derecho. El árbol se construye de forma que los códigos más cortos se corresponden con caracteres más frecuentes. Para esto, se utiliza una "cola de prioridad", que inicialmente contendrá los árboles hoja de la tabla de frecuencias. Mientras haya más de un árbol en la cola, saldrán los dos árboles menores y se insertará uno nuevo construido a partir de estos dos. Tendremos definida una relación de orden respecto a los árboles (se ordenan de forma directa comparando las frecuencias de los nodos raíz).

Se presenta un diseño capaz de realiza la codificación de ficheros de texto utilizando la técnica descrita, y capaz de decodificar ficheros previamente codificados con dicha técnica, obteniéndose así un fichero con el texto original.


