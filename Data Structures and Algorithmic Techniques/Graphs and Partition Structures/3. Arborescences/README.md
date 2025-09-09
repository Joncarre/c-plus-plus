# Arborescences

A directed graph is an arborescence if there exists a vertex, called root, from which any other vertex can be reached through a unique path.

**Input**

The input is composed of several test cases. For each case, the first line contains the number of vertices of the graph, V (between 1 and 10,000), and the second the number of directed edges, A (between 0 and 100,000). Next appear A lines, each with two integers representing the origin and destination of each edge (values between 0 and V-1). The graphs do not contain edges from one vertex to itself nor repeated edges.

**Output**

For each test case, YES followed by the root vertex will be written if the graph is an arborescence, and NO will be written otherwise.

**Input example**

    4
    3
    0 1
    0 2
    2 3
    6
    5
    0 2
    0 3
    1 0
    1 4
    1 5
    5
    5
    0 1
    1 2
    2 3
    3 4
    4 0

**Output example**

    YES 0
    YES 1
    NO

**Author:** Alberto Verdejo.
