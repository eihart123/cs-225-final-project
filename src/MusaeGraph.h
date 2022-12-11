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
   * @return Unsigned integer represnting number of edges
   */
  unsigned int getCountEdges() const;

  /**
   * @brief Get the number of nodes
   * 
   * @return Unsigned integer represnting number of nodes
   */
  unsigned int getCountNodes() const;

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
  std::vector<unsigned int> djikstra(unsigned source, unsigned destination);
  std::map<unsigned int, std::vector<unsigned int>> djikstra(unsigned int source) const;

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

  // TODO: Implement Girvan_Newman to view generated communities
  
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
};

#endif