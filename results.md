# The output and correctness of each algorithm:
### BFS: ###

- We used breadth-first search to traverse the graph to find the users within a certain number of degrees of connection of a given user. BFS visits a node and then visits all of its neighbors until there are no more nodes to visit. We take in the graph, the user that we want to find the degrees of connection for, and the number of degrees of connection we want to find, and output a map of vectors containing the users within each degree of connections between 1 and the number of degrees input.
- Our test cases checked to see if our map was outputting the correct neighbors within our connections using multiple test graphs. We checked for edge cases by having our graph include cycles and having specific nodes have multiple connections, and made sure our map would still output the right users.

### Dijkstras Algorithm: ###

- We used Dijkstra's algorithm to find the shortest path from one node to another. Dijkstra's algorithm begins at the starting node visits a node and its adjacent neighbors and determines which route is shortest, repeating the process until it reaches the destination node or it is determined that the destination node is not present. 
- Our test cases check to see if the shortest path was properly constructed. We prioritize paths with consecutive numbers: for example, if there were two shortest paths, {1, 2, 3, 4, 5} and {1, 2, 4, 3, 5}, which have the same cost, {1, 2, 3, 4, 5} would be prioritized. If there is no path from one node to another, we expect an empty vector to be output. If two of the same node are input for both the start and end of the path, we expect a vector containing just that node once to be output.

### Betweenness Centrality: ###

- We used betweenness centrality to determine which edges to remove in our Girvan-Newman algorithm. To find betweenness centrality we calculated how many shortest paths of every node combination (using dijkstra's algorithm) that go through each edge. We save these values and use the betweenness to calculate which edges to remove.
- We tested this algorithm inside our girvan-newman algorithm test cases. We tested to make sure that it removed the proper edge in our test3 graph by checking if either node was a neighbor or each other. We also did the process with our test4 graph and ensured that it removed both edges in the correct order.

### Girvan-Newman Algorithm: ###

- We used the Girvan-Newman Algorithm to find communities of connected users. Girvan-Newman works by reducing the size of the graph to only machine learning users and then finds the node with the most neighbors and uses that connected component for the rest of the algorithm. We perform a bfs on that node and create a new vector of nodes. We then find the betweenness centrality of all edges in that graph. We then remove an edge with the highest betweenness and recalculate the betweenness centrality of all edges and repeat that process of removing an edge and recalculating betweenness centrality until there are two connected components. We then run a bfs from the 1st node in the new vector of nodes and add it into a vector of sets of integers which will be returned at the end. We then iterate until we find a node that is not in that first set and perform bfs on that to get our second connected components. We add that to the vector of sets and return it as our final output.
- We tested this algorithm using two different graphs called test3 and test4. test3 tests a single edge removal and tests specifically the neighbors of each nodes to make sure the edge was removed properly. We also tested our calculate community function which returns the vector of sets of user ids to make sure that was returning the two correct subgraphs. With test4 we tested multi edge removal by checking the neighbors of each nodes to ensure that all edges were removed.

