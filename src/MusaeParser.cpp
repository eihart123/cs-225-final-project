#include "MusaeParser.h"

MusaeParser::MusaeParser(std::string edges_csv, std::string target_csv, std::string features_json) {
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

std::vector<std::set<Node>> MusaeParser::djikstra(Node source, int degree) const {
  std::vector<bool> visited(num_nodes_, false);
  std::set<Node> unvisited_nodes(nodes_.begin(), nodes_.end());
}

unsigned int MusaeParser::findShortestPath(Node source, Node destination) const {
  std::vector<std::set<Node>> connections = djikstra(source, );
}

std::vector<Node> MusaeParser::getRecommendedFollowers(Node source) {

}