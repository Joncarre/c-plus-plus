# Referencias cruzadas

Dado un texto organizado por lıneas, el problema de las referencias cruzadas consiste en producir un listado de palabras ordenado alfabeticamente, donde cada palabra del texto va acompañada de una lista de referencias que contiene los numeros de todas las lıneas del texto en las que aparece la palabra en cuestion, ordenados de menor a mayor.

**Entrada**

La entrada consta de diversos casos de prueba. Cada caso comienza con el numero N de lıneas que forman el texto (entre 1 y 1.000). A continuacion, aparecen N lıneas con las palabras (entre 1 y 30) del texto, donde se han omitido los signos de puntuacion o tildes. La entrada termina cuando N es 0.

**Salida**

Para cada caso de prueba se escribiran las referencias cruzadas, donde solamente se tendran en cuenta palabras con mas de 2 letras y no se tendran en cuenta las mayusculas. En las listas de numeros de lınea no habra repeticiones (aunque la palabra aparezca varias veces en la misma lınea). Tras procesar cada caso se escribira una lınea mas con ----.

**Entrada de ejemplo**

    2
    Pablito clavo un clavito en la calva de un calvito
    en la calva de un calvito clavo un clavito Pablito
    4
    Guerra tenia una parra y Parra tenia una perra
    la perra de Parra rompio la parra de Guerra y Guerra aporreo con la porra a la perra
    Si la perra de Parra no hubiera roto la parra de Guerra
    este no hubiera aporreado con la porra a la perra de Parra
    0


**Salida de ejemplo**

    calva 1 2
    calvito 1 2
    clavito 1 2
    pablito 1 2
    ----
    aporreado 4
    aporreo 2
    con 2 4
    este 4
    guerra 1 2 3
    hubiera 3 4
    parra 1 2 3 4
    perra 1 2 3 4
    porra 2 4
    rompio 2
    roto 3
    tenia 1
    una 1
    ----
 
 **Autor del problema:** Alberto Verdejo.
