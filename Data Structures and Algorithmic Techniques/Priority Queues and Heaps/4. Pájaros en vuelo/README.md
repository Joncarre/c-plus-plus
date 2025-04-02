# Birds in flight

It is well known that some species of birds fly creating a V-formation. The reason is simple: in this way the birds behind take advantage of the slipstream of those in front. This implies that the bird that makes more effort is the one that goes first occupying the vertex of the V, so it is important to choose well who it is.

Some species are placed in order of age from left to right, so that the bird in the center is the one that is neither too young nor too old. In this way they avoid the one that leads the way being underdeveloped or too tired to pull the group. When more birds join the flock, they take their place and, if necessary, the bird leading the way changes.

For example, let's imagine that there is a flock in flight with birds aged 10, 20 and 30 months. In that case, the 20-month-old bird would be the first to occupy the first place. If now two new birds arrive, one 25 months old and the other 35 months old, both will take their place and the first one will become the 25 months old. If later a 40 month old grandfather arrives with his 5 month old grandson, they will occupy the extremes and the first place will not change.

What we want is to simulate the formation of one of these flocks of birds that starts with a single bird and to which new pairs are added. Each time a new pair is added we want to determine the age of the bird at the top of the flock.

**Input**

The input will consist of a series of test cases, each containing information about the creation of a flock of birds. Each case consists of two lines: the first line contains the age of the first bird to fly followed by the number of pairs that will join later (at least one and up to 100,000 pairs); the next line contains the ages of each pair. It is guaranteed that the ages of each of the birds entering the flock are different. For this purpose they are expressed in seconds, and will never be a number greater than 100,000,000. The entry ends with a line with two zeros.

**Output**

For each test case a line will be written with as many numbers as pairs joining the flock, indicating the age of the bird that occupies the first position after each pair joins the flock.

**Input example**

    30 3
    10 20 35 25 5 40
    0 0

**Output example**

    20 25 25

**Author:** Alberto Verdejo.
