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
#include <bits/stdc++.h>

#include <iostream>

/**
 * @brief A graph implementation for Musae datasets
 * 
 */
class MusaeGraph {
public:
  /**
   * @brief Node struct to keep track of neighbors and build adjacency list
   * 
   */
  struct Node {
    std::set<unsigned int> neighbors_;
  };
  /**
   * @brief NodeComparator struct for use with Dijkstra's
   * 
   */
  struct NodeComparator {
    unsigned int id = 0;
    int distance = 0;

    NodeComparator(unsigned int i, unsigned int d) {
      id = i;
      distance = d;
    }
    bool operator<(const NodeComparator& other) const {
      return (
        (distance < other.distance) || 
        (distance == other.distance && id < other.id)
      );
    }
    bool operator>(const NodeComparator& other) const {
      return (
        (distance > other.distance) ||
        (distance == other.distance && id > other.id)
      );
    }
  };
  /**
   * @brief Construct a new MusaeGraph object
   * 
   * @param edges_csv The edges.csv file containing each edge, in format "id_1,id_2"
   * @param target_csv The target.csv file mapping IDs to usernames
   * @param features_json The features.json file (currently not used)
   */
  MusaeGraph(std::string edges_csv, std::string target_csv, std::string features_json);
  
  /**
   * @brief Get the neighbors of a given user node
   * 
   * @param user_id 
   * @return Set of unsigned integers representing neighbors of a node
   */
  std::set<unsigned int> getNeighbors(unsigned int user_id) const;

  /**
   * @brief Get the username matching the user id
   * 
   * @param user_id 
   * @return String reprsenting the username
   */
  std::string getUsernameFromId(unsigned int user_id) const;

  /**
   * @brief Get the user ID matching the username
   * 
   * @param user_id 
   * @return Unsigned integer reprsenting the user ID
   */
  unsigned int getIdFromUsername(std::string username) const;

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
   * @brief Implementation of BFS traversal, used to find users that are 
   *        n-degrees away
   * 
   * @param user User to find connections for
   * @param degree_connections Max number of degrees to search for (inclusive)
   * @return Map of users that are degree_connections away from the user
   */
  std::map<unsigned int, std::vector<unsigned int>> bfs_traversal(unsigned int user, unsigned int degree_connections) const;

  /**
  * @brief Implementation of Dijkstra's algorithm, used to find shortest path 
  *        between two users
  *
  * @param nodes Adjacency list to use
  * @param source Starting user ID for shortest path
  * @param destination Ending user ID for shortest path
  * @return Shortest path of users to travel through to reach the destination 
  *         user from the source user. Includes the source and destination in 
  *         resulting vector. If the source and destination are the same, only 
  *         the single user ID is included. If the shortest path could not be 
  *         found (e.g. the users are part of disjoint graphs), return an 
  *         empty vector.
  */
  std::vector<unsigned int> dijkstra(const std::vector<Node>& nodes, unsigned int source, unsigned int destination) const;

  /**
   * @brief Default caller for Dijkstra's that uses the nodes_ adjacency list
   * 
   * @param source Starting user ID for shortest path
   * @param destination Ending user ID for shortest path
   * @return Shortest path of users to travel through to reach the destination 
   *         user from the source user
   */
  std::vector<unsigned int> dijkstra(unsigned int source, unsigned int destination) const;

  /**
   * @brief A function that iteratively calls dijkstra() for all possible 
   *        destinations
   * 
   * @param source Starting user ID for shortest path
   * @return A map of destinations and their corresponding shortest paths
   */
  std::map<unsigned int, std::vector<unsigned int>> dijkstra(unsigned int source) const;

  /**
   * @brief Finds a random subset of users that the user might be interested 
   *        in following
   * 
   * @param user_id The user ID to find connections for
   * @param max_degree The max degree to search, must be greater than 1
   * @param request_connection_count The number of users to randomly recommend 
   *                                 (if less than 0, return all possible 
   *                                 recommendations)
   * @return A mapping of keys "user_id" to their corresponding value "degree"
   */
  std::map<unsigned int, unsigned int> getRecommendedUsersToFollow(unsigned int user_id, unsigned int max_degree, int request_connection_count) const;  

  // GIRVAN-NEWMAN IMPLEMENTATION

  /**
   * @brief Helper function that calculates the betweenness centrality for each 
   *        edge in a graph and stores it into edges_
   * 
   * @param nodes A reference to the graph adjacency list to use
   * @return 0 if all edges are connected or n number of edges that did not 
   *         have shortest paths
   */
  int betweennessCentrality(std::vector<Node>& nodes);

  /**
   * @brief Helper function that remove the edge with the highest centrality
   * 
   * @param nodes A reference to the graph adjacency list to use
   */
  void removeEdgeByCentrality(std::vector<Node>& nodes);

  /**
   * @brief Implementation of Girvan-Newman algorithm
   * 
   * @param print_debug False to surpress output, true to print debug messages
   * @return An adjacency list of the resulting graph
   */
  std::vector<Node> girvan(bool print_debug);

  /**
   * @brief Default caller for Girvan-Newman, defaults to not printing debug
   * 
   * @return An adjacency list of the resulting graph
   */
  std::vector<Node> girvan() { return girvan(false); };
  
  /**
   * @brief Uses Girvan-Newman to split the graph into two distinct communities
   * 
   * @return A vector of vectors (communites) and their user IDs
   */
  std::vector<std::vector<unsigned int>> calculateCommunities();


private:
  /**
   * @brief Helper function to insert an edge to build the adjacency list
   * 
   * @param id_1 The first node in the edge
   * @param id_2 The second node in the edge
   */
  void insertEdge(unsigned int id_1, unsigned int id_2);

  /**
   * @brief Helper function to create edge name string for edges_
   * 
   * @param id_1 
   * @param id_2 
   * @return Computed edge name, in format "number-number", where the first 
   *         number is the lower user ID from the passed arguments (e.g. "0-5")
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

  unsigned int num_edges_;
  unsigned int num_nodes_;
  std::vector<Node> nodes_;
  std::vector<std::string> usernames_;
  // edges_ vector used only for Girvan-Newman
  // edge_name to count of shortest paths
  std::map<std::string, unsigned int> edges_;
};

#endif