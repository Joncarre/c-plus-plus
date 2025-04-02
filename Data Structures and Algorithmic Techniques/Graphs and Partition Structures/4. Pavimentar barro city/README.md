# Pavimentar barro city

Los residentes de Barro City son demasiado tacaños para pavimentar las calles de la ciudad; despues de todo, a nadie le gusta pagar impuestos. Sin embargo, tras varios meses de lluvias intensas empiezan a estar cansados de enfangarse los pies cada vez que salen a la calle.

Debido a su gran tacañerıa, en vez de pavimentar todas las calles de la ciudad, quieren pavimentar solamente las suficientes para poder ir de una interseccion a otra cualquiera de la ciudad siguiendo una ruta pavimentada y, ademas, quieren gastarse tan poco dinero como sea posible en la realizacion de esta obra. Y es que a los residentes de Barro City no les importa caminar mucho, si ello les permite ahorrar algun dinero. El alcalde tiene interes en
saber cual es el mınimo presupuesto que tiene que reservar de las arcas publicas para pavimentar la ciudad

Por ejemplo, en una ciudad como la del dibujo con 5 intersecciones y 7 calles, donde el numero que
aparece al lado de cada calle representa lo que costar ́ıa pavimentarla, convendrıa pavimentar las calles que aparecen mas gruesas.

**Entrada**

La entrada esta compuesta por diversos casos de prueba, ocupando cada uno de ellos varias lıneas. En la primera lınea aparece el numero N (entre 1 y 10.000) de intersecciones en la ciudad, y en la segunda lınea aparece el numero C (entre 0 y 100.000) de calles (entre intersecciones). A continuacion, aparece una lınea por cada calle con tres enteros, que indican los numeros de las intersecciones que une la calle (numeros entre 1 y N ) y lo que costarıa pavimentarla (un valor entre 1 y 100.000). Nunca hay una calle que conecte una interseccion consigo misma, ni dos calles que conecten el mismo par de intersecciones.

**Salida**

Para cada caso de prueba se escribira una lınea con el coste mınimo necesario para pavimentar la ciudad de tal forma que se pueda viajar de cualquier interseccion a cualquier otra por calles pavimentadas. Si tal pavimentacion no es posible, se escribira Imposible.

**Entrada de ejemplo**

    5
    7
    1 2 7
    1 3 6
    3 2 1
    1 4 10
    3 4 15
    3 5 3
    4 5 12
    4
    3
    1 3 2
    1 4 3
    3 4 5

**Salida de ejemplo**

    20
    Imposible

**Autor del problema:** Alberto Verdejo.
