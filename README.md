
# Sliding block puzzle solver by different graph traversal algorithm: 

A sliding puzzle, sliding block puzzle, or sliding tile puzzle is a combination puzzle that challenges a player to slide (frequently flat) pieces along certain routes (usually on a board) to establish a certain end-configuration. The pieces to be moved may consist of simple shapes, or they may be imprinted with colors, patterns, sections of a larger picture (like a jigsaw puzzle), numbers, or letters.

- Input 

![Screenshot_20220625-151429_Sliding Puzzle Deluxe_2](https://user-images.githubusercontent.com/65499831/175772203-947fe885-ece9-48cb-b825-b6dd0b368679.jpg)

- Output

![Screenshot_20220625-165242_Sliding Puzzle Deluxe-1](https://user-images.githubusercontent.com/65499831/175772172-f3016e98-7de1-410a-8003-932bd6321978.jpg)

# Implemented traversal methods for sliding puzzle:

## 1) Implemented Uninformed Search Methods
### 1.1)Breadth First Search (BFS)
Examine all nodes in the search space. All nodes in search depth n are
examined before any node in search depth n + 1. We are guaranteed to
find the optimal solution if there is one. The disadvantage is the memory
requirement, we need to be able to hold at least two complete search depths
in memory at any one time, and having a way to detect duplicate positions
will require even more memory.

![Algorithm:](https://www.codeproject.com/KB/AI/368188/image003.png)

### 1.2)Depth First Search (DFS)
Examine the entire subtree before examining sibling nodes. The basic algorithm won’t work well on our problem, since the search space graph has
cycles. At the very least we need to avoid visiting nodes we visited in order
to reach the current node.

![Algorithm:](https://www.codeproject.com/KB/AI/368188/image004.png)

### 1.2) Iterative Deepening Depth Limited Depth First Search (IDFS)
erative-deepening is a technique that can be applied to depth-first search.
The depth-first search is run multiple times, starting with a maximum depth
of 1 which is increased by one for each run. When the algorithm terminates,
we have found the optimal solution. In the case where DFS and iterative
deepening DFS are run on trees, iterative deepening DFS is asymptotically
optimal with regard to space, runtime (nodes examined) and solution length
compared to BFS and DFS. One could think that it’s a waste of resources
to run repeated DFS’s for nodes of early depth, but the last iteration’s
runtime will dominate the cost.

![Algorithm:](https://www.codeproject.com/KB/AI/368188/image005.png)

## 2) Implemented Informed Search Methods
#### 2.1) A* with Misplaced Tiles Heuristic (A* Mis) & Manhattan Distance Heuristic (A* Man)

A* is a best-first search algorithm. At any time, the node with the lowest
f(x) = g(x) + h(x) among the unexplored nodes is expanded. Here, g(x) is
the actual cost of moving from the start position to node x, and h(x) is the
estimated distance from x to goal. In order for A* to find optimal solutions,
h(x) needs to be admissible, that is, it must never overestimate the cost from
x to a goal.

The efficiency of A* depends on the heuristic function h(x). Exponential
growth will occur, unless
h(x) − h*(x) ≤ O(log h∗(x)),
where h∗(x) is the true cost of getting from x to the goal . We don’t
expect to find a heuristic function satisfying this condition, and none of the
previous efforts managed to satisfy this condition for any of the problems
we’ve looked at.
In practice, the main drawback of A* is its memory usage, rather than
computation time. This makes A* unpractical for problems with huge search.

![Algorithm:](https://www.codeproject.com/KB/AI/368188/image006.png)

#### 2.2) IDA* (Iterative-deepening A*) 

IDA* works as follows. The search is done over several iterations. During
one iteration, a depth-first search is performed. IDA* does not expand nodes
having a total heuristic cost f = g +h higher than some cutoff p (also called
the pathlimit. If no solution was found during the iteration, the cutoff p is
increased and another iteration is run.
Given an admissible heuristic h, IDA* will find the optimal solution, if one
exists. If the search space graph is a tree, IDA* will expand approximately
the same number of nodes as A*. The search spaces we are looking at are
not that nice, however. In order for IDA* to avoid expanding the same
node twice, we need to keep track of previously visited nodes. In this case a
transposition table is often used.

## Author

- [@PrajwalHD58](https://github.com/PrajwalHD58)


## Features

- Taking input of any dimension below 5*5(25 cell) dimension.
- Check whether puzzle is valid or not. 
- Check puzzle is solvable or not, by counting no. of inversions using merge sort algorithm.
- Gives 5 option(BFS,DFS,IDFS,A*,IDA*) to get path or solve problem.
- Print path upto answer, with memory used & no. of iterations.

## Lessons Learned

- OOPs in C++
- Merge sort algorithm.
- Uninformed search(BFS,DFS,IDFS).
- Informed search(A*,IDA*).
- Comparision between memeory & time usage by different algorithms.


## Screenshots

![2022-06-25 (2)](https://user-images.githubusercontent.com/65499831/175771821-cbb26091-85d1-4ea8-afe0-30dc3b5b909d.png)

![2022-06-25 (7)](https://user-images.githubusercontent.com/65499831/175771831-e7f2bdce-bac3-41c1-ace0-944a52a1e155.png)
![2022-06-25 (3)](https://user-images.githubusercontent.com/65499831/175771833-8eb6336f-9a40-492c-bb86-80cf9621e06a.png)
![2022-06-25 (4)](https://user-images.githubusercontent.com/65499831/175771845-d6b7bfa9-aafc-4488-9986-c5c0573e5aa9.png)
![2022-06-25 (5)](https://user-images.githubusercontent.com/65499831/175771847-444f758d-e869-4f14-bb6f-b9e679e69af1.png)
![2022-06-25 (6)](https://user-images.githubusercontent.com/65499831/175771854-d4a18442-c788-4ad5-8ee5-f075518b2f19.png)



