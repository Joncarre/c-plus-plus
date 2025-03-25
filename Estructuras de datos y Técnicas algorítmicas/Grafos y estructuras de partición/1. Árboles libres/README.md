# Árboles libres

An undirected graph is said to be a free tree if it is acyclic and connected (or put another way, every pair of vertices is connected by exactly one path).

**Input**

The input is composed of several test cases. For each case, the first line contains the number of vertices of the graph, V (between 1 and 10,000), and the second the number of edges, A (between 0 and 100,000). Next, A lines appear, each with two integers representing the ends of each of the edges (values between 0 and V 1). The graphs do not contain edges from one vertex to itself and no more than one edge than one or more than one edge connecting the same pair of vertices.

**Output**

For each test case we will write YES if the network is a free tree and NO otherwise.

**Input example**

    6
    5
    0 5
    0 2
    2 1
    2 3
    4 3
    6
    5
    0 1
    1 2
    2 3
    3 0
    4 5

**Output example**

    SI
    NO

**Author:** Alberto Verdejo.
