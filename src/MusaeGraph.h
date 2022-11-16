<<<<<<< HEAD
#ifndef MUSAE_H
#define MUSAE_H

#include <fstream>
#include <set>
#include <string>
#include <vector>

class MusaeGraph {
public:
  struct Node {
    std::set<unsigned int> neighbors_;
  };
  /**
   * @brief Construct a new MusaeParser object
   * 
   * @param edges_csv The edges.csv file containing each edge, in format "id_1,id_2"
   * @param target_csv The target.csv file mapping IDs to usernames
   * @param features_json The features.json file (likely will not be used)
   */
  MusaeGraph(std::string edges_csv, std::string target_csv, std::string features_json);
  
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

  // TODO: Implement BFS, Djikstra, and Girvan_Newman

  std::vector<std::set<unsigned int>> bfs_traversal(unsigned int user, unsigned int degree_connections);

  /**
  * @brief Implement Djikstra's algorithm
  *
  * @return Vector of sets containing nodes up to degree-th degree of connection
  */
  std::map<Node, unsigned int> djikstra(Node source) const;

  /**
  * @brief Use Djikstra's algorithm to find shortest path between two given nodes
  *
  * @return Unsigned integer representing number of nodes
  */
  unsigned int findShortestPath(Node source, Node destination) const;

  /**
  * @brief Use Djikstra's algorithm to find recommended followers for user
  *
  * @return Vector of nodes with 2nd and 3rd degree connections to user
  */
  std::vector<Node> getRecommendedFollowers(Node source) const;  
  
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

};

=======
#ifndef MUSAE_H
#define MUSAE_H

#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <map>

class MusaeGraph {
public:
  struct Node {
    std::set<unsigned int> neighbors_;
  };
  /**
   * @brief Construct a new MusaeParser object
   * 
   * @param edges_csv The edges.csv file containing each edge, in format "id_1,id_2"
   * @param target_csv The target.csv file mapping IDs to usernames
   * @param features_json The features.json file (likely will not be used)
   */
  MusaeGraph(std::string edges_csv, std::string target_csv, std::string features_json);
  
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

  // TODO: Implement BFS, Djikstra, and Girvan_Newman

  std::map<unsigned int, std::vector<unsigned int>> bfs_traversal(unsigned int user, unsigned int degree_connections);
  

  
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

};

>>>>>>> 90d4abd1ba4ccb9585a9369cd306aa727beb7869
#endif