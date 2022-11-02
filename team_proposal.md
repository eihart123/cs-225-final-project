## Leading Question

How can we connect more developer with each other to build better open source projects?

## Dataset Acquisition

Our source dataset is published on the Stanford SNAP group and consists of GitHub users who are active (have at least 10 starred repos) and are mutual followers (http://snap.stanford.edu/data/github-social.html).

### Data Format

The dataset is separated into three separate files for edges, features, and targets, in CSV format. It contains 37,700 users/nodes and 289,003 mutual follows/edges. In total the files take up ~10MB. We will use the entire dataset.

### Data Correction

If there are errors in the data or missing information (e.g. a node does not have an associated target/username), then we will label problematic nodes as having an issue (e.g. a node with no associated username will be displayed as "Unknown username." Otherwise, if ignoring the node/feature does not impact the resulting graph, we can simply ignore it.

### Data Storage

For storing our data, we will create an adjacancy matrix, which contains in the i'th column, the node representing the GitHub user, and in the j'th column, the node representing their mutual follows. This will create a runtime of O(number of nodes + number of edges).

## Algorithm 

We plan to use Dijkstra's algorithm to find the shortest path between a user and another user based on their mutual follows. For inputs into this algorithm, we will need to pass the user that we are starting with and the user that we are ending with. We will also continue to build the rest of the shortest paths between other users to display a list of recommended users to follow. This requires outputing an array of lists that contain users by their degree of connection (e.g. in the 0th indexed list, it contains users that are directly connected with the starting user, in the 1st indexed list, it contains users that are 1 connection away from the starting user). We will likely output a random subset of 2nd degree and 3rd degree connections so that suggestions are more relevant for the user. This function will have a time complexity of O(number of connections/edges log number of users), based on Dijkstra's time complexity. This will be our target runtime. For memory, our storage complexity is O(number of users).

## Timeline

- 2022-11-04: Finish project documents/goals
- 2022-11-11: Create the data structure to store our dataset
- 2022-11-18: (mid project check-in) Start implementing necessary graph algorithms to proccess dataset, as well as start creating tests to ensure the algorithm works
- 2022-11-25: Finish implementing graph algorithm as well as necessary helper functions
- 2022-12-02: Create output functions to display results and finish project
- 2022-12-08: (project due) Finish project if necessary
