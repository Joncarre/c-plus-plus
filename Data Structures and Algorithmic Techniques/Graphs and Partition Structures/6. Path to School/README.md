# Path to School

Lucas goes to school by bike every day. Since it's extremely difficult for him to get up in the morning, he's always in a hurry and has to take the shortest path. But he gets bored always taking the same path, so he alternates, but always traveling the same minimum distance, so as not to be late. Since he's a bit reckless, he doesn't respect the traffic direction of the streets, so he's able to travel any of them in both directions. Now he wonders in how many different ways he can go from his house to school without traveling even a centimeter more.

**Input**

The input is composed of several test cases, each occupying several lines. The first line shows the number N (between 1 and 10,000) of intersections in Lucas's town, and the second line shows the number C (between 0 and 100,000) of streets (between intersections). Next, one line appears for each street with three integers, indicating the numbers of the intersections that the street connects (numbers between 1 and N) and its length (a value between 1 and 100,000). There is never a street that connects an intersection to itself, nor two streets that connect the same pair of intersections. Lucas's house is always located at intersection number 1 and his school is located at intersection number N.

**Output**

For each test case, a line will be written with the number of different ways to go from Lucas's house to school traveling the minimum possible distance. This number will be 0 if it is impossible to reach the school from Lucas's house using the existing streets.

**Input example**

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

**Output example**

    4

**Author:** Alberto Verdejo.
