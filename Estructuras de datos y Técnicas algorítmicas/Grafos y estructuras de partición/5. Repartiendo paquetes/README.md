# Repartiendo paquetes

La comarca de Dispersion de Arriba esta formada por multitud de bonitas casas repartidas por laderas y colinas. Las casas estan conectadas por carreteras, carreterillas, caminos o senderos, dependiendo de las zonas y de la importancia de sus dueños. Las caracterısticas de estas conexiones son muy variadas, desde anchas carreteras practicamente planas a empinados senderos en ocasiones embarrados y muy poco transitables, sobre todo cuesta arriba.

La oficina de la empresa de transportes que atiende a la comarca esta situada en una de estas casas. Cada dıa,
un unico repartidor debe entregar los paquetes recibidos y para ello cuenta con una moto cuyo compartimento de carga es tan pequeño que solamente puede llevar un paquete cada vez. Con estas restricciones, la rutina del sufrido repartidor consiste en tomar uno de los paquetes, llevarlo hasta la casa del destinatario, y volver a la oficina a por el siguiente paquete. Debido a las condiciones de las vıas, hay ocasiones en que interesa, o es incluso inevitable, que el camino de vuelta siga una ruta distinta al de ida.

Conociendo el esfuerzo que supone para el repartidor viajar por las distintas vıas en cada sentido transitable, y las casas donde debe entregar paquetes un dıa concreto, ¿puedes ayudarle a decidir la mejor forma (la de menor esfuerzo total) de repartir los paquetes? El repartidor tiene total libertad para elegir en que orden reparte los paquetes y que rutas sigue, tanto para ir como para volver.

**Entrada**

La entrada esta compuesta por diversos casos de prueba, ocupando cada uno de ellos varias lıneas. La primera lınea contiene el numero N (entre 1 y 10.000) de casas en la comarca y la segunda el numero C (entre 1 y 100.000) de conexiones directas entre casas. A continuacion, aparecen C lıneas cada una con tres enteros, origen destino esfuerzo, que indican que se puede ir directamente desde la casa origen hasta la casa destino (las casas estan numeradas desde 1 hasta N) con el consiguiente esfuerzo (un valor entre 1 y 10.000). Ten en cuenta que si una conexion es transitable en ambos sentidos aparecera dos veces, con el origen y el destino intercambiados y con un esfuerzo posiblemente distinto para cada sentido (al fin y al cabo, no es lo mismo subir que bajar).

Tras la descripcion de la comarca, aparece una lınea con dos enteros: O es el numero de la casa
donde se encuentra la oficina (el repartidor debe comenzar y terminar su jornada laboral en esta casa) y P (entre 1 y N) es el numero de paquetes a repartir; y otra lınea con los P numeros de las casas donde viven los destinatarios.

**Salida**

Para cada caso de prueba el programa debe escribir una lınea con el esfuerzo mınimo necesario para repartir todos los paquetes de ese dıa. Se garantiza que este valor nunca sera mayor que 10^9 . Si para un dıa el reparto es imposible porque no existen suficientes conexiones para construir las rutas necesarias, el programa escribira Imposible.

**Entrada de ejemplo**

    4
    5
    1 2 5
    2 3 2
    3 1 8
    1 4 2
    4 1 3
    1 3
    2 3 4
    4
    3
    1 3 2
    3 1 3
    3 4 5
    1 2
    2 3

**Salida de ejemplo**

    35
    Imposible

**Autor del problema:** Alberto Verdejo.
