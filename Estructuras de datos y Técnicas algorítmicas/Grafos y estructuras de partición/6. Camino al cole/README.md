# Camino al cole

Lucas va todos los dıas en bici al cole. Como le cuesta una barbaridad levantarse por las mañanas, siempre lleva prisa y tiene que ir por el camino mas corto. Pero le aburre ir siempre por el mismo camino, por lo que va alternando, eso sı, recorriendo siempre la misman distancia mınima, para no llegar tarde. Como es un poco temerario, no respeta el sentido de circulacion de las calles por lo que es capaz de recorrer cualquiera de ellas en ambos sentidos. Ahora se pregunta de cuantas formas distintas puede ir de su casa al colegio sin recorrer ni un centımetro de mas.

**Entrada**

La entrada esta compuesta por diversos casos de prueba, ocupando cada uno de ellos varias lıneas. En la primera lınea aparece el numero N (entre 1 y 10.000) de intersecciones en el pueblo de Lucas, y en la segunda lınea aparece el numero C (entre 0 y 100.000) de calles (entre intersecciones). A continuacion, aparece una lınea por cada calle con tres enteros, que indican los numeros de las intersecciones que une la calle (numeros entre 1 y N) y su longitud (un valor entre 1 y 100.000). Nunca hay una calle que conecte una interseccion consigo misma, ni dos calles que conecten el mismo par de intersecciones. La casa de Lucas siempre se encuentra en la interseccion numero 1 y su colegio esta situado en la interseccion numero N.

**Salida**

Para cada caso de prueba se escribira una lınea con el numero de formas distintas de ir desde la casa de Lucas al colegio recorriendo la mınima distancia posible. Este numero sera 0 si es imposible alcanzar el colegio desde la casa de Lucas utilizando las calles existentes.

**Entrada de ejemplo**

    7
    10
    1 2 5
    1 3 7
    2 4 10
    3 4 8
    2 5 30
    4 5 12
    4 7 25
    4 6 11
    5 7 13
    6 7 30

**Salida de ejemplo**

    4

**Autor del problema:** Alberto Verdejo.
