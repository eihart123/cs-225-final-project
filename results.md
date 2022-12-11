The output and correctness of each algorithm:
BFS:
- We used breadth-first search to traverse the graph to find the users within a certain number of degrees of connection of a given user. BFS visits a node and then visits all of its neighbors until there are no more nodes to visit. We take in the graph, the user that we want to find the degrees of connection for, and the number of degrees of connection we want to find, and output a map of vectors containing the users within each degree of connections between 1 and the number of degrees input.
- Our test cases checked to see if our map was outputting the correct neighbors within our connections using multiple test graphs. We checked for edge cases by having our graph include cycles and having specific nodes have multiple connections, and made sure our map would still output the right users.

Djkistras Algorithm:

- 


