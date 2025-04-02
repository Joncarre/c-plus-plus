# Cross References

Given a text organized by lines, the cross-references problem consists of producing an alphabetically ordered list of words, where each word in the text is accompanied by a list of references containing the line numbers where the word appears, ordered from lowest to highest.

**Input**

The input consists of several test cases. Each case begins with the number N of lines (between 1 and 1,000). Next are N lines with words (between 1 and 30) of text, with punctuation and accents omitted. The input ends when N is 0.

**Output**

For each test case cross references will be written, where only words with more than 2 letters will be taken into account and capital letters will not be taken into account. In the lists of line numbers there will be no repetitions (even if the word appears several times in the same line). After processing each case one more line will be written with ----.

**Example Input**

    2
    Pablito clavo un clavito en la calva de un calvito
    en la calva de un calvito clavo un clavito Pablito
    4
    Guerra tenia una parra y Parra tenia una perra
    la perra de Parra rompio la parra de Guerra y Guerra aporreo con la porra a la perra
    Si la perra de Parra no hubiera roto la parra de Guerra
    este no hubiera aporreado con la porra a la perra de Parra
    0


**Example Output**

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
 
 **Problem Author:** Alberto Verdejo.
