# Book sales

We want to implement an application to manage a system for selling books over the Internet. The implementation will make use of the type *Book* that represents with a string. The operations allowed are the following:

- newBook(x, n): adds n copies of a book (x) to the system. If n takes the value 0 it means that the book is in the system.
- buy(x): a user buys a book (x). It is checked that the book exists and that there are copies.
- thisBook(x): indicates if a book (x) has been added to the system.
- deleteBook(x): deletes book (x) from the system.
- numCopies(x): returns the number of copies of a book (x) available in the system.
- top10(): gets a list of the top 10 best selling books. *Important*: instead of the top 10 best sellers, the list of all the best sellers is displayed according to the number of sales of each one, from the best seller to the least sold.

**Input example**

    5
    nuevoLibro 20 Heidi
    nuevoLibro 30 Caperucita roja
    comprar Heidi
    numEjemplares Caperucita roja
    top10
    7
    nuevoLibro 1 La vuelta al mundo en 80 dias
    comprar La vuelta al mundo en 80 dias
    estaLibro La vuelta al mundo en 80 dias
    nuevoLibro 5 Viaje al centro de la tierra
    comprar Viaje al centro de la tierra
    comprar Viaje al centro de la tierra
    top10

**Output example**

    Existen 30 ejemplares del libro Caperucita roja
    ---
    Heidi
    ---
    ------
    El libro La vuelta al mundo en 80 dias esta en el sistema
    ---
    Viaje al centro de la tierra
    La vuelta al mundo en 80 dias
    ---
    ------
