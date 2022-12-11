#include "MusaeGraph.h"

MusaeGraph::MusaeGraph(std::string edges_csv, std::string target_csv, std::string features_json) {
  num_edges_ = 0;
  num_nodes_ = 0;
  // create nodes_ from edges_csv
  nodes_ = std::vector<Node>();
  std::ifstream edges_file(edges_csv);
  if (edges_file.fail()) {
    std::string error_msg = "Could not open file \"" + edges_csv + "\". Check that the file exists and proper permissions are set.";
    throw std::invalid_argument(error_msg);
  }
  std::string edges_id1, edges_id2;
  std::string edge;
  // skip first line since it contains headers
  if (edges_file.is_open()) {
    std::getline(edges_file, edge);
  }
  if (edges_file.is_open()) {
    while (std::getline(edges_file, edge)) {
      // edge = "id_1,id_2"
      std::stringstream ss(edge);
      std::getline(ss, edges_id1, ',');
      std::getline(ss, edges_id2, ',');
      // unsigned int id_1 = std::stoi(edge.substr(0, edge.find(",")));
      // unsigned int id_2 = std::stoi(edge.substr(edge.find(",") + 1));
      insertEdge(std::stoi(edges_id1), std::stoi(edges_id2));
    }
  }
  
  // create usernames_ from target_csv
  usernames_ = std::vector<std::string>(num_nodes_);
  std::ifstream usernames_file(target_csv);
  if (usernames_file.fail()) {
    std::string error_msg = "Could not open file \"" + target_csv + "\". Check that the file exists and proper permissions are set.";
    throw std::invalid_argument(error_msg);
  }
  std::string target_id, target_name, target_ml_target;
  std::string line;
  // skip first line since it contains headers
  if (usernames_file.is_open()) {
    std::getline(usernames_file, line);
  }
  if (usernames_file.is_open()) {
    while (std::getline(usernames_file, line)) {
      // line = "id,name,ml_target"
      std::stringstream ss(line);
      std::getline(ss, target_id, ',');
      std::getline(ss, target_name, ',');
      usernames_.at(std::stoi(target_id)) = target_name;
    }
  }
}

void MusaeGraph::insertEdge(unsigned int id_1, unsigned int id_2) {
  // resize the nodes_ vector if necessary
  if (id_1 >= nodes_.size()) {
    nodes_.resize(id_1 + 1);
  }
  if (id_2 >= nodes_.size()) {
    nodes_.resize(id_2 + 1);
  }
  // add the edge (to both nodes since we are dealing with an undirected graph)
  nodes_[id_1].neighbors_.insert(id_2);
  nodes_[id_2].neighbors_.insert(id_1);
  // add edge for Girvan-Newman
  std::string edge_name = makeEdgeName(id_1, id_2);
  edges_[edge_name] = 0;
  // update node and edge count
  num_edges_++;
  num_nodes_ = nodes_.size();
}

std::string MusaeGraph::getUsername(unsigned int user_id) const {
  if (user_id >= usernames_.size()) {
    std::string error_msg = "invalid user id: " + std::to_string(user_id);
    error_msg += " (usernames_.size() == " + std::to_string(usernames_.size()) + ")";
    throw std::invalid_argument(error_msg);
  }
  return usernames_.at(user_id);
}

unsigned int MusaeGraph::getCountEdges() const {
  return num_edges_;
}

unsigned int MusaeGraph::getCountNodes() const {
  return num_nodes_;
}

std::map<unsigned int, std::vector<unsigned int>> MusaeGraph::bfs_traversal(unsigned int user, unsigned int degree_connections) const {
  std::map<unsigned int, std::vector<unsigned int>> map;

  std::vector<bool> visited_;
  visited_.resize(nodes_.size(), false);

  std::queue<std::vector<unsigned int>> queue;
  std::vector<unsigned int> vect;

  vect.push_back(user);
  queue.push(vect);
  while (!queue.empty()) {
    std::vector<unsigned int> front_vect = queue.front();
    unsigned int front_val = front_vect.at(front_vect.size() - 1);
    visited_.at(front_val) = true;
    queue.pop();

    if ((front_vect.size() - 1) >= 1 && (front_vect.size() - 1) <= degree_connections) {
      std::map<unsigned int, std::vector<unsigned int>>::iterator lookup = map.find(front_vect.size() - 1);
      if (lookup == map.end()) {
        map[front_vect.size() - 1] = {front_val};
      } else {
        map[front_vect.size() - 1].push_back(front_val);
      }
    }

    std::set<unsigned int> front_neighbors = nodes_.at(front_val).neighbors_;

    std::set<unsigned int>::iterator it;
    for (it = front_neighbors.begin(); it != front_neighbors.end(); it++) {
      if (!(visited_.at(*it))) {
        visited_.at(*it) = true;
        std::vector<unsigned int> new_front_vect = front_vect;
        new_front_vect.push_back(*it);
        queue.push(new_front_vect);
      }
    }
  }

  return map;
}

// std::map<MusaeGraph::Node, unsigned int> MusaeGraph::djikstra(Node source) const {
//   // TODO: complete implementation

//   std::map<Node, unsigned int> dist;
//   std::map<Node, Node> prev;

//   // foreach (Vertex v : G):
//   for (Node node : nodes_) {
//     //   d[v] = +inf
//     dist[node] = INT_MAX;
//     //   p[v] = NULL
//     prev[node] = NULL;
//   }
//   //   d[s] = 0
//   int dist[source] = 0;

//   // PriorityQueue Q // min distance, defined by d[v]
//   priority_queue<Node> p_queue;

//   //   Q.buildHeap(G.vertices())
//   p_queue.buildHeap(nodes_);

//   //   Graph T // "labeled set"
//   std::set<Node> labeled_set;

//   //   repeat n times:
//   while (!p_queue.empty()) {
//     //   Vertex u = Q.removeMin()
//     Node curr = p_queue.removeMin();

//     //   T.add(u)
//     labeled_set.add(curr);

//     //   foreach (Vertex v : neighbors of u not in T):
//     for (Node node : curr.neighbors_) {
//       //   if cost(v, m) < d[v]:
//       if (dist[curr] + cost(curr, node) < dist[node]) {
//         //   d[v] = cost(v, m)
//         dist[node] = cost(curr, node)
//         //   p[v] = m
//         prev[node] = curr;
//       }
//     }
//   }
//   return dist;
// }

unsigned int MusaeGraph::findShortestPath(Node source, Node destination) const {
  // TODO: implement
  // std::map<Node, unsigned int> connections = djikstra(source);
  return 1;
}

std::map<unsigned int, unsigned int> MusaeGraph::getRecommendedUsersToFollow(unsigned int user_id, unsigned int max_degree, int request_connection_count) const {
  if (max_degree <= 1) {
    std::string error_msg = "max_degree must be greater than 1, provided: " + std::to_string(max_degree);
    throw std::invalid_argument(error_msg);
  }
  std::map<unsigned int, std::vector<unsigned int>> connections = bfs_traversal(user_id, max_degree);
  // skip connections that are degree 0 or 1 since they are already connected
  // technically, bfs_traversal should not return degree 0, but "just in case"
  connections.erase(0);
  connections.erase(1);
  std::map<unsigned int, unsigned int> random_users;
  // count number of connections and create a vector of possible degrees to choose from later
  int actual_connection_count = 0;
  std::vector<unsigned int> possible_degrees;
  for (auto it = connections.begin(); it != connections.end(); it++) {
    actual_connection_count += (*it).second.size();
    possible_degrees.push_back((*it).first);
  }
  // check that we are not requesting for a count greater than the actual number
  // and that the request count is greater than and equal to 0
  if (actual_connection_count >= request_connection_count && request_connection_count >= 0) {
    // sample random users
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < request_connection_count; i++) {
      // find random degree from the potential degrees
      std::uniform_int_distribution<int> dist_degree(0, possible_degrees.size() - 1);
      unsigned int random_degree_idx = dist_degree(mt);
      unsigned int random_degree = possible_degrees[random_degree_idx];
      // find random user id
      std::uniform_int_distribution<int> dist_id(0, connections[random_degree].size() - 1);
      unsigned int random_id_idx = dist_id(mt); // std::rand() % connections[random_degree].size();
      unsigned int random_id = connections[random_degree].at(random_id_idx);
      // remove the user id so we don't pick it again
      connections[random_degree].erase(connections[random_degree].begin() + random_id_idx);
      // if we've already picked all the users under a degree, remove the degree from the potential degrees vector
      if (connections[random_degree].size() == 0) {
        possible_degrees.erase(possible_degrees.begin() + random_degree_idx);
      }
      // save our random user and their corresponding degree
      random_users[random_id] = random_degree;
    }
  // otherwise return all possible users within degree constraint
  } else {
    for (auto it = connections.begin(); it != connections.end(); it++) {
      auto degree = (*it).first;
      if (degree == 1) {
        continue;
      }
      auto connections_in_degree = (*it).second;
      for (auto connection : connections_in_degree) {
        random_users[connection] = degree;
      }
    }
  }
  return random_users;
}

int MusaeGraph::betweennessCentrality(std::vector<Node>& nodes, std::map<std::string, unsigned int>& edges) {
  int num_bad_edges = 0;
  // reset centrality (shortest path count) for all edges
  for (auto e : edges) {
    edges[e.first] = 0;
  }
  // iterate through every node
  for (unsigned int i = 0; i < nodes.size(); i++) {
    for (unsigned int j = 0; j < nodes.size(); j++) {
      if (i == j) {
        continue;
      }
      // std::vector<unsigned int> path = findShortestPath();
      std::vector<unsigned int> path;
      // if the path size is 0, then no shortest path could be found, which means that the two nodes are in disjoint graphs
      if (path.size() == 0) {
        num_bad_edges += 1;
      }
      // for each edge in the path
      for (unsigned int k = 0; k < path.size() - 1; k++) {
        std::string edge_name = makeEdgeName(path[k], path[k+1]);
        // add 1 to the centrality of the edge (since there is a shortest path using the edge)
        edges[edge_name] += 1;
      }
    }
  }
  return (num_bad_edges); // divided by 2 because we process each node undirected (however this does not guarantee the same sortest path)
}

void MusaeGraph::removeEdgeByCentrality(std::vector<Node>& nodes, std::map<std::string, unsigned int>& edges) {
  // initializes the max with the first string in the map of edges
  std::string max_edge;
  for (auto i : edges) {
    max_edge = i.first;
    break;
  }
  // iterates through the map of edges and finds the edge with the highest betweenness centrality and sets it to max_edge
  for (auto i : edges) {
    if (edges.at(max_edge) < i.second) {
      max_edge = i.first;
    }
  }

  // parses the string and converts each string into an integer
  std::string node1, node2;
  std::stringstream ss(max_edge);
  std::getline(ss, node1, '-');
  std::getline(ss, node2, '-');
  unsigned int n1 = std::stoi(node1);
  unsigned int n2 = std::stoi(node2);
  // std::set<unsigned int> neighbors1 = nodes[n1].neighbors_;
  // std::set<unsigned int> neighbors2 = nodes[n2].neighbors_;

  // removes the node from each neighbor set
  if (nodes[n1].neighbors_.find(n2) == nodes[n1].neighbors_.end() ||
      nodes[n2].neighbors_.find(n1) == nodes[n2].neighbors_.end()) {
    throw std::invalid_argument("nodes reference did not match edges reference");
  }
  nodes[n1].neighbors_.erase(nodes[n1].neighbors_.find(n2));
  nodes[n2].neighbors_.erase(nodes[n1].neighbors_.find(n1));

  // removed the edge from the map of edges
  edges.erase(edges.find(max_edge));
}

std::vector<std::vector<unsigned int>> MusaeGraph::girvan() {
  // initialize variables to use
  // make a deep copy of nodes_
  std::vector<Node> nodes;
  std::map<std::string, unsigned int>& edges = edges_;
  for (unsigned int i = 0; i < nodes_.size(); i++) {
    Node temp;
    temp.neighbors_ = nodes_.at(i).neighbors_;
    nodes.push_back(temp);
  }
  // end initialization
  unsigned int betweenness_status = betweennessCentrality(nodes, edges);;
  while (betweenness_status == 0) {
    removeEdgeByCentrality(nodes, edges);
    betweenness_status = betweennessCentrality(nodes, edges);
  }
  return formatCommunities(nodes);
}

std::vector<std::vector<unsigned int>> MusaeGraph::formatCommunities(std::vector<Node>& nodes) {
  // std::map<unsigned int, std::vector<unsigned int>> bfs = bfs_traversal()
  std::vector<std::vector<unsigned int>> returnVect;
  std::set<unsigned int> firstSet;

  for (unsigned int i = 0; i < nodes.size(); i++) {
    // auotmatically does bfs from first node | if the node at the current index is not in the first vector it will perform bfs from that node 
    if (i == 0 || firstSet.count(i) == 0) {
      
      // initializes data structures for bfs
      std::set<unsigned int> node1;
      std::queue<unsigned int> q;
      std::vector<unsigned int> vect;

      q.push(i);
      while (!q.empty()) {
        // pops and saves top node into node
        unsigned int node = q.front();
        q.pop();

        if (node1.count(node) != 0) {
          // if the node is not in the set it will add it and add all neighbors
          node1.insert(node);
          std::set<unsigned int> s = nodes[node].neighbors_;
          std::set<unsigned int>::iterator it;
          for (it = s.begin(); it != s.end(); it++) {
            q.push(*it);
          }
        }
      }
      std::set<unsigned int>::iterator it;
      // converts set to vector
      for (it = node1.begin(); it != node1.end(); it++) {
        vect.push_back(*it);
      }
      firstSet = node1;
      returnVect.push_back(vect);

      if (returnVect.size() > 1) {
        // breaks from loop if this is the second vector added
        break;
      }
    }
  }
  return returnVect;
}


/**
 * @brief Helper function to create edge name string for edges_
 * 
 * @param id_1 
 * @param id_2 
 * @return std::string Computed edge name, in format "number-number", where the first number is the lowest id of the passed arguments
 */
std::string makeEdgeName(unsigned int id_1, unsigned int id_2) {
  std::string edge_name;
  if (id_1 < id_2) {
    edge_name = std::to_string(id_1) + "-" + std::to_string(id_2);
  } else {
    edge_name = std::to_string(id_2) + "-" + std::to_string(id_1);
  }
  return edge_name;
}