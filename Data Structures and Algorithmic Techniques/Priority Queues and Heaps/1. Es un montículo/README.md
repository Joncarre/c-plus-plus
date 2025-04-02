# Is it a heap?

A binary tree is complete when all its internal nodes have two non-empty children, and all its leaves are at the same level; and it is semi-complete if it is either complete or has vacant consecutive depositions of the last level starting from the right, such that filling these positions with new leaves results in a complete tree.

A minimal heap is a semi-complete binary tree where each element is less than or equal to its children (if any).

**Input**

The input starts with the number of cases that follow. Each test case consists of a line with the description of a binary tree: first appears its root (a non-negative integer), then the description of the left child and then the right child. The number -1 indicates the empty tree. Trees will never contain more than 20,000 nodes.

**Output**

For each tree, YES will be written if it is a minimum stack and NO otherwise.

**Input example**

    3
    15 20 34 -1 -1 44 -1 -1 17 40 -1 -1 -1
    15 20 34 -1 -1 44 -1 -1 17 -1 40 -1 -1
    15 41 34 -1 -1 20 -1 -1 17 40 -1 -1 -1

**Output example**

    SI
    NO
    NO

**Author:** Alberto Verdejo.
