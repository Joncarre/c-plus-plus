# Is the Tree Balanced?

A binary tree is balanced if it is either empty or if the height difference between its two children is at most 1, and both children are also balanced.

**Input**

The input begins with the number of cases that follow. Each test case consists of a line of characters describing a binary tree: an empty tree is represented by a dot (.); a non-empty tree is represented by an R (denoting the root) followed by the description of the left child and the right child. Trees will never contain more than 20,000 nodes.

**Output**

For each tree, a line will be written with "SI" (YES) if the tree is balanced and "NO" if it is not.

**Example Input**

    3
    RRR..R..R.R..
    RR.R..RR..R.R..
    RR..RR..R.R..

**Example Output**

    SI
    SI
    NO
 
 **Problem Author:** Alberto Verdejo.
