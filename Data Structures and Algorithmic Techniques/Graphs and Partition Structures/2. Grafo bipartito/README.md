# Grafo bipartito

An undirected graph is bipartite if its vertices can be distributed in two disjoint sets in such a way that all edges have an end in each of those sets. In other words, a graph is bipartite if its vertices can be colored using two colors such that there is no edge connecting two vertices of the same color.

**Input**

The input is composed of several test cases. For each case, the first line contains the number of vertices of the graph, V (between 1 and 10,000), and the second the number of edges, A (between 0 and 100,000). Next appear A lines, each with two integers representing the ends of each of the edges (values between 0 and V 1). The graphs do not contain edges from one vertex to itself nor more than one edge connecting the same pair of vertices.

**Output**

For each test case the word YES will be written in a separate line if the graph is bipartite and NO otherwise.

**Input example**

    7
    9
    0 2
    0 4
    1 6
    1 3
    2 6
    2 5
    4 6
    4 5
    4 3
    6
    8
    0 2
    0 3
    2 3
    2 4
    4 3
    3 1
    3 5
    1 5

**Output example**

    SI
    NO

**Author:** Alberto Verdejo.
