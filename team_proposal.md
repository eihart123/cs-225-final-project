# Project Proposal

## Leading Question

How can we connect more developer with each other to build better open source projects?

## Dataset Acquisition

Our source dataset is published on the Stanford SNAP group and consists of GitHub users who are active (have at least 10 starred repos) and are mutual followers (http://snap.stanford.edu/data/github-social.html).

### Data Format

The dataset is separated into three separate files for edges, features, and targets, in CSV format. It contains 37,700 users/nodes and 289,003 mutual follows/edges. In total the files take up ~10MB. We will use the entire dataset.

### Data Correction

If there are errors in the data or missing information (e.g. a node does not have an associated target/username), then we will label problematic nodes as having an issue (e.g. a node with no associated username will be displayed as "Unknown username." Otherwise, if ignoring the node/feature does not impact the resulting graph, we can simply ignore it.

### Data Storage

For storing our data, we will create an adjacancy list, which is represented by a vector of sets, where vector contains n sets (where n is the number of users) containing the node's immediate neighbors. The resulting storage complexity is O(number of users * 2 * number of edges). 

## Algorithm 

We plan to use breadth-first search to traverse the graph to find the users within a certain number of degrees of connection of a given user. BFS visits a node and then visits all of its neighbors until there are no more nodes to visit. We will take in the graph, the user that we want to find the degrees of connection for, and the number of degrees of connection we want to find, and output a vector of sets containing the users within each degree of connections between 1 and the number of degrees input. The function will have a time complexity of O(n + m), where n is the number of nodes, and m is the number of edges.

We plan to use Dijkstra's algorithm to find the shortest path between a user and another user based on their mutual follows. For inputs into this algorithm, we will need to pass the user that we are starting with and the user that we are ending with. We will also continue to build the rest of the shortest paths between other users to display a list of recommended users to follow. This requires outputing an array of lists that contain users by their degree of connection (e.g. in the 0th indexed list, it contains users that are directly connected with the starting user, in the 1st indexed list, it contains users that are 1 connection away from the starting user). We will likely output a random subset of 2nd degree and 3rd degree connections so that suggestions are more relevant for the user. This function will have a time complexity of O(number of connections/edges log number of users), based on Dijkstra's time complexity. This will be our target runtime. For memory, our storage complexity is O(number of users).

We will use the Girvan–Newman algorithm to find whether two users share a community on Github. The Girvan–Newman algorithm removes edges from a graph to determine the connections have the strongest betweenness centrality, whic would imply more relevance/influence in the network. First, the betweenness of each edge in the network is calculated. Then the edges of highest betweenness are removed. These steps are repeated until there are no more edges. During initialization, after parsing through the dataset and creating the graph, we will input the graph of Github accounts and store the communities found by the algorithm using a vector of sets. Then, when called, we will have a function that iterates through the communities and determines whether the two users are both in any of those communities together. The runtime of the Girvan–Newman algorithm is O(n^2 * m) where n is the number of nodes and m is the number of edges, which will be our target runtime for the initilization of the communities. The storage complexity of the algorithm is O(number of users). Because the results will already be stored in a vector of sets, the runtime of looking up whether two users share a community is O(1).

## Timeline

- 2022-11-04: Finish project documents/goals
- 2022-11-11: Acquire data and add it to repository, create the data structure to store our dataset, start implementing BFS, create test cases for BFS
- 2022-11-18: (mid project check-in) Finish implementing BFS, start implementing Dijkstra's algorithm, create test cases for Dijkstra's algorithm
- 2022-11-25: Finish implementing Djikstra's algorithm as well as necessary helper functions, begin implementing Girvan–Newman algorithm, create test cases for Girvan–Newman algorithm
- 2022-12-02: Finish implementing Girvan–Newman algorithm, create output functions to display results and finish project
- 2022-12-08: (project due) Finish project if necessary
