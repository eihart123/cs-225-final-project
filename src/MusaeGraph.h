#ifndef MUSAE_H
#define MUSAE_H

#include <stdexcept>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

#include <iostream>

class MusaeGraph {
public:
  struct Node {
    std::set<unsigned int> neighbors_;
  };
  struct NodeComparator {
    unsigned int id = 0;
    int distance = 0;

    NodeComparator(unsigned int i, unsigned int d) {
      id = i;
      distance = d;
    }
    bool operator<(const NodeComparator& other) const {
      return (distance < other.distance) || (distance == other.distance && id < other.id);
    }
    bool operator>(const NodeComparator& other) const {
      return (distance > other.distance) || (distance == other.distance && id > other.id);
    }
  };
  /**
   * @brief Construct a new MusaeGraph object
   * 
   * @param edges_csv The edges.csv file containing each edge, in format "id_1,id_2"
   * @param target_csv The target.csv file mapping IDs to usernames
   * @param features_json The features.json file (likely will not be used)
   */
  MusaeGraph(std::string edges_csv, std::string target_csv, std::string features_json);
  
  /**
   * @brief Get the username matching the user id
   * 
   * @param user_id 
   * @return String reprsenting the username
   */
  std::string getUsername(unsigned int user_id) const;

  /**
   * @brief Get the number of edges
   * 
   * @return Unsigned integer representing number of edges
   */
  unsigned int getCountEdges() const;

  /**
   * @brief Get the number of nodes
   * 
   * @return Unsigned integer representing number of nodes
   */
  unsigned int getCountNodes() const;

  /**
   * @brief Get the neighbors of a given user node
   * 
   * @return Set of unsigned integers representing neighbors of a node
   */
  std::set<unsigned> getNeighbors(unsigned user_id) const;

  /**
   * @brief 
   * 
   * @param user 
   * @param degree_connections 
   * @return Map of users that are degree_connections away from the provided user
   */
  std::map<unsigned int, std::vector<unsigned int>> bfs_traversal(unsigned int user, unsigned int degree_connections) const;

  /**
  * @brief Implement Djikstra's algorithm
  *
  * @return Vector of sets containing nodes up to degree-th degree of connection
  */
  std::vector<unsigned int> dijkstra(unsigned source, unsigned destination) const;
  std::map<unsigned int, std::vector<unsigned int>> dijkstra(unsigned int source) const;

  /**
  * @brief Use Djikstra's algorithm to find shortest path between two given nodes
  *
  * @return Unsigned integer representing number of nodes
  */
  unsigned int findShortestPath(Node source, Node destination) const;

  /**
   * @brief Finds a random subset of users that the user might be interested in following
   * 
   * @param user_id The user ID to find connections for
   * @param max_degree The max degree to search, must be greater than 1
   * @param reuqest_connection_count The number of users to randomly recommend (if less than 0, return all possible recommendations)
   * @return A mapping of keys "user_id" to their corresponding value "degree"
   */
  std::map<unsigned int, unsigned int> getRecommendedUsersToFollow(unsigned int user_id, unsigned int max_degree, int request_connection_count) const;  

  // GIRVAN-NEWMAN IMPLEMENTATION

  /**
   * @brief Calculates the betweenness centrality for each edge in a graph
   * 
   * @param nodes A reference to the graph adjacency list to use
   * @param edges A reference to a map of edges and their centrality
   * @return 0 if all edges are connected, n for number of edges that could not be computed for shortest path because it is now impossible
   */
  int betweennessCentrality(std::vector<Node>& nodes, std::map<std::string, unsigned int>& edges);

  /**
   * @brief Called after betweenness centrality is computed: remove the edge with the highest centrality
   * 
   * @param nodes A reference to the graph adjacency list to use
   * @param edges A reference to a map of edges and their centrality
   */
  void removeEdgeByCentrality(std::vector<Node>& nodes, std::map<std::string, unsigned int>& edges);

  /**
   * @brief Implementation of Girvan-Newman algorithm. Runs until two communites are created
   * 
   * @return std::vector<std::vector<unsigned int>> 
   */
  std::vector<std::vector<unsigned int>> girvan();

  std::vector<std::vector<unsigned int>> formatCommunities(std::vector<Node>& nodes);
  
private:
  /**
   * @brief Helper function to insert an edge to build the adjacency list
   * 
   * @param id_1 The first node in the edge
   * @param id_2 The second node in the edge
   */
  void insertEdge(unsigned int id_1, unsigned int id_2);

  unsigned int num_edges_;
  unsigned int num_nodes_;
  std::vector<Node> nodes_;
  std::vector<std::string> usernames_;
  // edges_ vector used only for Girvan-Newman
  // second is sp_count (number of shortet paths)
  std::map<std::string, unsigned int> edges_;
  
};

#endif