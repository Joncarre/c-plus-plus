# Rescuing Climbers

Binary trees can be used to represent paths on a mountainside. The root of the tree represents the summit from which one or two routes emerge. The different routes, as the mountainside widens, split into two forming paths that will never reconnect. A climber is at the mountain summit (root of the tree) and realizes that at different intersections (marked in the tree with 'X') there are friends who need help climbing up. They must go down to each 'X' and help them climb up one by one.

A program is presented that, given one of these binary trees, returns the time it will take the climber to help all these friends if each intersection segment takes one hour to traverse (in both directions).

It is important to consider that:

- Empty nodes are represented with '.'
- Nodes where there are friends are represented with 'X'
- Nodes where there are no friends and are not leaves are represented with 'N'

**Example Input**

    5
    N N X . . N . . X N . . X . .
    N N N . . N . . X N . . N . .
    N X N . . X . . X X . . X . .
    N X X . . X . . X X . . X . .
    N X . . N . .

**Example Output**

    4
    1
    5
    6
    1
