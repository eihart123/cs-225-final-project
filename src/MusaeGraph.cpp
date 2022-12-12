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

std::set<unsigned> MusaeGraph::getNeighbors(unsigned int user_id) const {
  return nodes_[user_id].neighbors_;
}

std::string MusaeGraph::getUsernameFromId(unsigned int user_id) const {
  if (user_id >= usernames_.size()) {
    std::string error_msg = "Invalid user id: " + std::to_string(user_id);
    error_msg += " (usernames_.size() == " + std::to_string(usernames_.size()) + ")";
    throw std::invalid_argument(error_msg);
  }
  return usernames_.at(user_id);
}

unsigned int MusaeGraph::getIdFromUsername(std::string username) const {
  for (unsigned int id = 0; id < usernames_.size(); id++) {
    if (usernames_.at(id) == username) {
      return id;
    }
  }
  return INT_MAX;
  std::string error_msg = "Username not found: " + username;
  throw std::invalid_argument(error_msg);
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

std::vector<unsigned int> MusaeGraph::dijkstra(unsigned int source, unsigned int destination) const {
  return dijkstra(nodes_, source, destination);
}

std::vector<unsigned int> MusaeGraph::dijkstra(const std::vector<Node>& nodes, unsigned int source, unsigned int destination) const {
  bool reverse_at_end = true;
  if (source == destination) {
    std::vector<unsigned int> path;
    path.push_back(source);
    return path;
  } else if (source > destination) {
    reverse_at_end = false;
    unsigned int temp = source;
    source = destination;
    destination = temp;
  }
  
  std::vector<unsigned int> previous;
  std::vector<bool> visited;
  previous.resize(nodes.size(), INT_MAX);
  visited.resize(nodes.size(), false);

  std::priority_queue<NodeComparator, std::vector<NodeComparator>, std::greater<NodeComparator>> pq;
  pq.push(NodeComparator(source, 0));

  // traverse the graph
  while (!pq.empty() && pq.top().id != destination) {
    NodeComparator curr = pq.top();
    pq.pop();
    unsigned int curr_id = curr.id;
    for (unsigned int neighbor_id : nodes[curr_id].neighbors_) {
      if (visited[neighbor_id] == false) {
        // add the neighbor to the priority queue, with distance +1
        pq.push(NodeComparator(neighbor_id, curr.distance + 1));
        if (previous[neighbor_id] == INT_MAX) {
          previous[neighbor_id] = curr_id;
        }
      }
    }
    visited[curr_id] = true;
  }

  std::vector<unsigned int> path;
  // if we cannot find the shortest path
  if (pq.empty()) {
    return path;
  }

  // create the path now that we have found our destination
  unsigned int curr = destination;
  while (curr != source) {
    path.push_back(curr);
    curr = previous[curr];
  }
  path.push_back(source);
  if (reverse_at_end) {
    std::reverse(path.begin(), path.end());
  }

  return path;
}

std::map<unsigned int, std::vector<unsigned int>> MusaeGraph::dijkstra(unsigned int source) const {
  std::map<unsigned int, std::vector<unsigned int>> connections;
  for (unsigned int i = 0; i < nodes_.size(); i++) {
    auto path = dijkstra(source, i);
    connections[i] = path;
  }
  return connections;
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

int MusaeGraph::betweennessCentrality(std::vector<Node>& nodes) {
  int num_bad_edges = 0;
  // reset centrality (shortest path count) for all edges
  for (auto e : edges_) {
    edges_[e.first] = 0;
  }
  // iterate through every node
  for (unsigned int i = 0; i < nodes.size(); i++) {
    for (unsigned int j = 0; j < nodes.size(); j++) {
      if (i == j) {
        continue;
      }
      std::vector<unsigned int> path = dijkstra(nodes, i, j);
      // if the path size is 0, then no shortest path could be found, which means that the two nodes are in disjoint graphs
      if (path.size() == 0) {
        num_bad_edges += 1;
      }
      // for each edge in the path
      for (unsigned int k = 1; k < path.size(); k++) {
        std::string edge_name = makeEdgeName(path.at(k-1), path.at(k));
        // add 1 to the centrality of the edge (since there is a shortest path using the edge)
        edges_[edge_name] += 1;
      }
    }
  }
  return (num_bad_edges); // divided by 2 because we process each node undirected (however this does not guarantee the same sortest path)
}

void MusaeGraph::removeEdgeByCentrality(std::vector<Node>& nodes) {
  // initializes the max with the first string in the map of edges
  std::string max_edge;
  for (auto i : edges_) {
    max_edge = i.first;
    break;
  }
  // iterates through the map of edges and finds the edge with the highest betweenness centrality and sets it to max_edge
  for (auto i : edges_) {
    if (edges_.at(max_edge) < i.second) {
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
  // removes the node from each neighbor set
  if (nodes[n1].neighbors_.find(n2) == nodes[n1].neighbors_.end() ||
      nodes[n2].neighbors_.find(n1) == nodes[n2].neighbors_.end()) {
    throw std::invalid_argument("Attempted to remove non-existent neighbors in nodes_");
  }
  nodes[n1].neighbors_.erase(nodes[n1].neighbors_.find(n2));
  nodes[n2].neighbors_.erase(nodes[n2].neighbors_.find(n1));
}

std::vector<MusaeGraph::Node> MusaeGraph::girvan(bool print_debug) {
  // make a deep copy of nodes_
  std::vector<Node> nodes;
  for (unsigned int i = 0; i < nodes_.size(); i++) {
    Node temp;
    temp.neighbors_ = nodes_.at(i).neighbors_;
    nodes.push_back(temp);
  }
  // perform iterative steps of Girvan-Newman
  unsigned int count = 0;
  unsigned int betweenness_status = betweennessCentrality(nodes);;
  while (betweenness_status == 0) {
    if (print_debug) {
      std::cout << "Iteration " << std::to_string(count) << " of Girvan-Newman" << std::endl;
    }
    removeEdgeByCentrality(nodes);
    betweenness_status = betweennessCentrality(nodes);
    count++;
  }
  return nodes;
}

std::vector<std::vector<unsigned int>> MusaeGraph::calculateCommunities() {
  std::vector<Node> nodes = girvan(true);
  std::cout << "Completed Girvan-Newman" << std::endl;
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
