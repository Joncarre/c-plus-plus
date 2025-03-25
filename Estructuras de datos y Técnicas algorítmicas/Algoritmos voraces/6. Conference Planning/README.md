# Conference planning

The Imposing University has to plan a cultural event consisting of a series of lectures. For each lecture we know the start and end times set by the speakers. The IT Department has been asked to plan the lectures by distributing them among the various rooms available, so that, of course, no two lectures are held in the same room at the same time. The aim is to minimize the number of rooms used, so as to cause as little disruption as possible to other academic activities.

**Input**

The input consists of a series of test cases. Each one starts with a line with the number N of conferences (1 <= N <= 250,000). Next, N lines appear, each with two numbers representing the start and end time of one of the conferences (the start time is always strictly less than the end time). These times are integers between 0 and 10^9. The entry will end with a case without conferences, which should not be processed.

**Output**

For each test case a line will be written with the minimum number of rooms needed for the scheduling of the lectures, so that no lectures overlap within the same room. It can be assumed that the Imposing University will always have enough rooms available.

**Input example**

    3
    1 5
    3 10
    6 12
    2
    5 10
    1 5
    3
    1 5
    2 6
    3 7
    0

**Output example**

    2
    1
    3

**Author:** Alberto Verdejo.
