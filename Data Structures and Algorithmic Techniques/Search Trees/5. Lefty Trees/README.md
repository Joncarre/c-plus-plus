# Lefty Trees

Given a binary tree, the *minimum height* of the tree is defined as the shortest distance from the root to an empty subtree. It can be formally specified using the equations:

    hmin(empty)           = 0
    hmin(cons(l, x, r))   = 1 + min(hmin(l), hmin(r))
    
A binary tree is called *lefty* if it is either empty, or if it's not empty, both children are lefty and the minimum height of the left child is never less than that of the right child.

A solution with linear cost relative to the number of nodes is presented, which determines whether a given binary tree is lefty or not.

**Example Input**

     6
     0 0 0 -1 -1 -1 -1 
     0 0 -1 -1 0 -1 -1 
     0 0 0 -1 -1 -1 0 -1 -1 
     0 0 -1 -1 0 0 -1 -1 -1
     0 0 -1 0 -1 -1 0 -1 -1
     0 -1 0 -1 0 -1 -1

**Example Output**

     YES
     YES
     YES
     YES
     NO
     NO
