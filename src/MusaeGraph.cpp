#include "MusaeGraph.h"
#include <queue>
#include <iostream>

MusaeGraph::MusaeGraph(std::string edges_csv, std::string target_csv, std::string features_json) {
  num_edges_ = 0;
  num_nodes_ = 0;
  nodes_ = std::vector<Node>();
  std::ifstream edges_file(edges_csv);
  std::string edge;
  // skip first line since it contains headers
  if (edges_file.is_open()) {
    std::getline(edges_file, edge);
  }
  if (edges_file.is_open()) {
    while (std::getline(edges_file, edge)) {
      // edge = "id_1,id_2"
      unsigned int id_1 = std::stoi(edge.substr(0, edge.find(",")));
      unsigned int id_2 = std::stoi(edge.substr(edge.find(",") + 1));
      insertEdge(id_1, id_2);
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
  // update node and edge count
  num_edges_++;
  num_nodes_ = nodes_.size();
}

unsigned int MusaeGraph::getCountEdges() const {
  return num_edges_;
}

unsigned int MusaeGraph::getCountNodes() const {
  return num_nodes_;
}


std::map<unsigned int, std::vector<unsigned int>> MusaeGraph::bfs_traversal(unsigned int user, unsigned int degree_connections) {
  
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

  // std::map<unsigned int, std::vector<unsigned int>>::iterator it;
  // for (it = map.begin(); it != map.end(); it++) {
  //   std::cout << "key: " << (*it).first << std::endl;
  //   std::cout << std::endl;
  //   for (size_t i = 0; i < (*it).second.size(); i++) {
  //     if (i == (*it).second.size() - 1) {
  //       std::cout << "val: " << (*it).second.at(i) << std::endl;
  //     } else {
  //       std::cout << "val: " << (*it).second.at(i) << ", ";
  //     }
      
  //   }
  //   std::cout << std::endl;
  // }

 return map;
  

}