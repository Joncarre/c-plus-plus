# What it costs to add up

Johnny Calculın can add numbers mentally at high speed, but the effort required to perform a sum depends on the value of the addends. Specifically, adding a plus b gives him an effort equal to a + b (regardless of the specific values of a and b).
of the concrete values of a and b). Simple.

When you have to add more than two numbers, things get more complicated, since the order in which you do the additions affects the total effort used. For example, if you have to add 1, 2 and 3, you can add 1 + 2 with an effort equal to 3, and then add 3 + 3 with an effort equal to 6, which means a total effort equal to 9. On the other hand, if you first add 2 + 3 with an effort equal to 5 and then 5 + 1 with an effort equal to 6, the total effort amounts to 11. Obviously the result of the addition is always 6, because of the commutative and associative properties of addition.

Johnny is preparing for an addition contest and wants to find out how he should go about adding the numbers to require the least effort. Can you help him?

**Input**

The input is composed of several test cases, each of them occupying two lines: the first line contains an integer N (between 1 and 100,000) representing the number of addends, and the second contains those N addends, integers between 1 and 1,000,000. The input ends with a case where N is 0 that should not be processed.

**Output**

For each test case a line should be written with the minimum effort needed to sum the input numbers.

**Input example**

    3
    1 2 3
    4
    3 1 4 2
    4
    3 4 5 6
    0

**Output example**

    9
    19
    36

**Author:** Alberto Verdejo.
