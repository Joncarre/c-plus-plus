<!--Creado por Jonathan Carrero -->

**Uno solo**
==============
----------

**Introducción**

En este solitario, se empieza con un tablero en modo rejilla con piezas colocadas sobre las casillas. El jugador debe mover una pieza en cada turno. Las piezas sólo pueden moverse "saltando" sobre otra dicha hasta una casilla libre de forma que la pieza sobre la que se salta es eliminada del tablero, como en las damas. Sólo se puede saltar una pieza, y el salto debe ser en horizontal o en vertical, nunca en diagonal. El objetivo del juego es eliminar todas las piezas, dejando sólo una en el tablero. Además, en esta versión del juego, la última pieza debe acabar en una casilla específica.

**Descripción**

El programa implementará la dinámica del juego, y para dibujar el tablero utilizará caracteres con distintos colores de fondo para las fichas. La siguiente imagen muestra un tablero donde las celdas en negro son nulas (no forman parte del tablero "jugable"), las que están en verde apagado están vacías y las que estén en verde brillante son celdas con ficha. La celda que tiene el símbolo en blanco en el centro representa la meta.

![enter image description here](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/3_1.png)

Como vemos, se nos muestra los movimiento que podemos realizar (contando con todas las fichas que tenemos disponibles).

También se desea cargar y guardar un juego de una determinada partida. Esto se hace a través de un fichero .txt que deberá tener la siguiente estructura.

![enter image description here](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/3_2.png)

