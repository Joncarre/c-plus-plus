# Paving Mud City

The residents of Mud City are too stingy to pave the city streets; after all, nobody likes to pay taxes. However, after several months of intense rain, they are starting to get tired of getting their feet muddy every time they go out on the street.

Due to their great stinginess, instead of paving all the city streets, they want to pave only enough to be able to go from one intersection to any other in the city following a paved route and, furthermore, they want to spend as little money as possible on this work. The residents of Mud City don't mind walking a lot if it allows them to save some money. The mayor is interested in knowing what is the minimum budget he has to reserve from public funds to pave the city.

For example, in a city like the one in the drawing with 5 intersections and 7 streets, where the number that appears next to each street represents what it would cost to pave it, it would be convenient to pave the streets that appear thicker.

**Input**

The input is composed of several test cases, each occupying several lines. The first line shows the number N (between 1 and 10,000) of intersections in the city, and the second line shows the number C (between 0 and 100,000) of streets (between intersections). Next, one line appears for each street with three integers, indicating the numbers of the intersections that the street connects (numbers between 1 and N) and what it would cost to pave it (a value between 1 and 100,000). There is never a street that connects an intersection to itself, nor two streets that connect the same pair of intersections.

**Output**

For each test case, a line will be written with the minimum cost necessary to pave the city so that you can travel from any intersection to any other through paved streets. If such paving is not possible, "Impossible" will be written.

**Input example**

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

**Output example**

    20
    Impossible

**Author:** Alberto Verdejo.
