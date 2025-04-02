# Is it an AVL Tree?

An AVL tree (named after the initials of its inventors' surnames, Georgii Adelson Velskii and Yevgeniy Landis) is a binary search tree that is balanced in the sense that for every subtree, the difference between the heights of its two children is at most 1. Additionally, being a search tree, the key stored at the root of any subtree is greater than all keys in its left child and less than all keys in its right child.

**Input**

The input begins with the number of cases that follow. Each test case consists of a line describing a binary tree: first is its root (a non-negative integer), followed by the description of the left child and then the right child. The number –1 indicates an empty tree. Trees will never contain more than 20,000 nodes.

**Output**

For each tree, "SI" (YES) will be written if the tree is an AVL tree and "NO" if it is not.

**Example Input**

    3
    2 1 -1 -1 3 -1 4 -1 -1
    1 -1 3 2 -1 -1 4 -1 -1
    4 1 -1 -1 3 -1 2 -1 -1

**Example Output**

    YES
    NO
    NO
 
 **Problem Author:** Alberto Verdejo.
