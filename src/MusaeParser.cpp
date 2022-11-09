#include "MusaeParser.h"

MusaeParser::MusaeParser(std::string edges_csv, std::string target_csv, std::string features_json) {
  std::ifstream edges_file(edges_csv);
  std::string edge;
  // skip first line since it contains headers
  std::getline(edges_file, edge);
  if (edges_file.is_open()) {
    while (getline(edges_file, edge)) {
      // edge = "id_1,id_2"
      unsigned int id_1 = std::stoi(edge.substr(0, edge.find(",")));
      unsigned int id_2 = std::stoi(edge.substr(edge.find(",") + 1));
      insertEdge(id_1, id_2);
    }
  }
}

void MusaeParser::insertEdge(unsigned int id_1, unsigned int id_2) {
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

unsigned int MusaeParser::getCountEdges() const {
  return num_edges_;
}

unsigned int MusaeParser::getCountNodes() const {
  return num_nodes_;
}