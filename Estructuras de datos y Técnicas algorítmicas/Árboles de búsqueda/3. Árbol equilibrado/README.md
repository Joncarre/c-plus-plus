# Balanced Tree

Binary search trees perform better when they are balanced. A balanced tree is one where the size of its left child and right child differ by at most one unit, and both subtrees are also balanced. This presents a binary tree class that incorporates a new method that determines in **linear** time whether the binary tree is balanced.

**Example Input**

    3
    2 1 -1 -1 3 -1 4 -1 -1
    1 -1 3 2 -1 -1 4 -1 -1
    4 1 -1 -1 3 -1 2 -1 -1

**Example Output**

    YES
    NO
    NO
