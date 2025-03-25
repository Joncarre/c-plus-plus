# Family Tree

Given a binary tree of integers, it is considered a correct family tree if the following rules are met, where the integer in each node represents the birth year of the individual, the left child represents their first child of a maximum of two, and the right child represents the second child.

- The parent's age must be at least 18 years greater than the ages of each of their children.
- The second child's age (if they exist) must be at least two years less than that of the first child (there are no twins in these trees).
- The family trees of both children must also be correct.

A program is implemented to determine whether a binary tree is a correct family tree or not and, if it is, the number of different generations in the family.

**Example Input**

     5
     100 60 30 -1 -1 -1 58 -1 -1
     100 60 30 -1 -1 -1 59 -1 -1
     100 -1 -1
     100 83 -1 -1 -1
     100 82 -1 -1 -1

**Example Output**

     YES 3
     NO
     YES 1
     NO
     YES 2
