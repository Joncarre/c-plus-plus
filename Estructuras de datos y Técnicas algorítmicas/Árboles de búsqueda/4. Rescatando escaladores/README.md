# Rescantando escaladores

Se pueden utilizar los árboles binarios para representar los caminos en la falda de una montaña. La raíz del árbol representa la cima de la que salen una o dos rutas. Las distintas rutas según se va ensanchando la falda de la montaña se dividen en dos formando caminos que nunca se volverán a conectar. Un escalador está en la cima de la montaña (raíz del árbol) y se da cuenta de que en distintas intersecciones (marcadas en el árbol con 'X') hay amigos que necesitan su ayuda para subir. Tiene que bajar a cada una de las 'X' y ayudarles a subir de uno en uno.

Se presenta un programa que, dado uno de estos árboles binarios, devuelve el tiempo que tardará el escalador en ayudar a todos esos amigos si cada tramos de intersección lleva una hora en ser recorrido (en cada uno de los dos sentidos).

Es importante tener en cuenta que:

- Los nodos vacíos se representan con '.'
- Los nodos en los que hay amigos se representan con 'X'
- Los nodos en los que no hay amigos ni son hoja se representan con 'N'

**Entrada de ejemplo**

    5
    N N X . . N . . X N . . X . .
    N N N . . N . . X N . . N . .
    N X N . . X . . X X . . X . .
    N X X . . X . . X X . . X . .
    N X . . N . .

**Salida de ejemplo**

    4
    1
    5
    6
    1
