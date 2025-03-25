# Holes in the hose

This summer Susana has a plague of ants in the garden that have taken her by storm with the watering hose. So much so that they have already managed to make a few holes to get water and cool off.

After taking care of the ants, Susana has decided to fix the hose by plugging the holes. To do this, she has to buy rectangular patches that are placed lengthwise over the hose and whose width completely encloses it. A patch can cover several holes (if a patch is of length L it can cover holes that are spaced up to that distance apart) and they can overlap.

When Susana goes to the gardening store she prefers to buy flowers, so she wants to spend as little as possible buying patches. Can you calculate how many patches at least Susana needs to cover all the holes in the hose?

**Input**

The input consists of a series of test cases. Each case starts with a line with the number N of holes in the hose (1 <= N <= 100,000) and the length L of the patches (1 <= L <= 1,000). Next appears a line with N integers representing the positions where the holes are located (integers between 1 and 10^9), measured from the beginning of the hose (point 0) and given in increasing order from that beginning.

**Output**

For each test case a line will be written with the minimum number of patches needed to cover all the holes.

**Input example**

    3 2
    1 6 10
    3 5
    1 6 10
    8 10
    3 8 8 9 20 45 55 90

**Output example**

    3
    2
    4
    
 
 **Author:** Alberto Verdejo.
