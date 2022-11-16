#include <catch2/catch_test_macros.hpp>
#include "MusaeGraph.h"

#include <string>

TEST_CASE("test_edge_and_node_counts", "[weight=15], [part=1]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  REQUIRE(m.getCountEdges() == 5);
  REQUIRE(m.getCountNodes() == 6);
}

// TODO: Add test case that tests the actual data structure in nodes_ variable

TEST_CASE("bfs_test_1_degree1", "[weight=15], [bfs]") {

  std::string edges_csv = "../tests/bfs_test1_edges.csv";
  std::string target_csv = "../tests/bfs_test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  REQUIRE(m.getCountEdges() == 11);
  // REQUIRE(m.getCountNodes() == 8);

  std::vector<std::set<unsigned int>> bfs = m.bfs_traversal(1, 1);

  REQUIRE(bfs.at(0).count(2) == 1);
  REQUIRE(bfs.at(0).count(3) == 1);
  REQUIRE(bfs.at(0).count(4) == 1);
  REQUIRE(bfs.at(0).count(9) == 1);


  
}

TEST_CASE("bfs_test_1_degree2", "[weight=15], [bfs]") {

  std::string edges_csv = "../tests/bfs_test1_edges.csv";
  std::string target_csv = "../tests/bfs_test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  

  std::vector<std::set<unsigned int>> bfs = m.bfs_traversal(1, 2);

  REQUIRE(bfs.at(1).count(5) == 1);
  REQUIRE(bfs.at(1).count(7) == 1);
  REQUIRE(bfs.at(1).count(8) == 0);
  REQUIRE(bfs.at(1).count(2) == 0);
  REQUIRE(bfs.at(1).size() == 2);
  

  


  
}

TEST_CASE("bfs_test_2_degree3", "[weight=15], [bfs]") {

  std::string edges_csv = "../tests/bfs_test2_edges.csv";
  std::string target_csv = "../tests/bfs_test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  

  std::vector<std::set<unsigned int>> bfs = m.bfs_traversal(1, 3);



  // REQUIRE(m.getCountEdges() == 5);
  // REQUIRE(m.getCountNodes() == 6);


  
  REQUIRE(bfs.at(0).size() == 5);
  REQUIRE(bfs.at(1).size() == 5);
  REQUIRE(bfs.at(2).size() == 2);



  REQUIRE(bfs.at(0).count(2) == 1);
  REQUIRE(bfs.at(0).count(3) == 1);
  REQUIRE(bfs.at(0).count(4) == 1);
  REQUIRE(bfs.at(0).count(5) == 1);
  REQUIRE(bfs.at(0).count(9) == 1);

  REQUIRE(bfs.at(1).count(7) == 1);
  REQUIRE(bfs.at(1).count(8) == 1);
  REQUIRE(bfs.at(1).count(12) == 1);
  REQUIRE(bfs.at(1).count(11) == 1);
  REQUIRE(bfs.at(1).count(16) == 1);

  REQUIRE(bfs.at(2).count(13) == 1);
  REQUIRE(bfs.at(2).count(15) == 1);

  REQUIRE(bfs.at(1).count(2) == 0);
  REQUIRE(bfs.at(2).count(16) == 0);
  
  
}


TEST_CASE("bfs_test_2_degree5", "[weight=15], [bfs]") {

  std::string edges_csv = "../tests/bfs_test2_edges.csv";
  std::string target_csv = "../tests/bfs_test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  

  std::vector<std::set<unsigned int>> bfs = m.bfs_traversal(8, 5);



  REQUIRE(m.getCountEdges() == 22);
  REQUIRE(m.getCountNodes() == 14);


  
  REQUIRE(bfs.at(0).size() == 3);
  REQUIRE(bfs.at(1).size() == 5);
  REQUIRE(bfs.at(2).size() == 3);
  REQUIRE(bfs.at(3).size() == 1);
  REQUIRE(bfs.at(4).size() == 1);



  REQUIRE(bfs.at(0).count(15) == 1);
  REQUIRE(bfs.at(0).count(2) == 1);
  REQUIRE(bfs.at(0).count(5) == 1);


  

  REQUIRE(bfs.at(1).count(11) == 1);
  REQUIRE(bfs.at(1).count(9) == 1);
  REQUIRE(bfs.at(1).count(4) == 1);
  REQUIRE(bfs.at(1).count(1) == 1);
  REQUIRE(bfs.at(1).count(3) == 1);

  REQUIRE(bfs.at(2).count(12) == 1);
  REQUIRE(bfs.at(2).count(16) == 1);
  REQUIRE(bfs.at(2).count(7) == 1);
  

  REQUIRE(bfs.at(3).count(13) == 1);
  REQUIRE(bfs.at(4).count(14) == 1);
  
  
}
