# Find the kth Element in an AVL Tree

Extend the implementation of AVL trees to maintain a new attribute tam_i in each node that stores the number of nodes in the left child plus one. Make the necessary changes so that the functions that modify the trees maintain the value of this attribute coherently.

Implement a method to locate the kth smallest element in the tree in logarithmic time (with respect to the size of the tree).

**Input**

The input consists of various test cases. Each case spans four lines. The first line contains the number N of keys (between 1 and 50,000), not necessarily distinct, to insert into the tree. Next, on a single line, are those keys (integers between 1 and 1,000,000), separated by spaces, in the order in which they should be inserted. (For this problem, the value associated with each key is irrelevant.) The next line contains the number M of elements to be consulted (between 1 and N). And on the last line are, separated by spaces, the M positions (ordinals) of the elements to query (numbers between 1 and N). The input ends when a tree has no elements (N is 0).

**Output**

For each test case, the queried elements will be written on separate lines, if they exist. If there is no element at the queried position, "??" will be written instead. After processing each case, one more line with "----" will be written.

**Example Input**

    4
    15 20 25 30
    2
    1 3
    5 16 8 4 4 32
    3
    2 4 5
    0

**Example Output**

    15
    25
    ----
    8
    32
    ??
    ----
 
 **Problem Author:** Alberto Verdejo.
