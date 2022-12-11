#include <catch2/catch_test_macros.hpp>
#include "MusaeGraph.h"
#include <map>

// Tests for MusaeGraph::getRecommendedUsersToFollow() can be found in main.cpp

// TEST 1

TEST_CASE("test1_edge_and_node_counts", "[weight=20], [test=1], [construct]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);
  
  REQUIRE(m.getCountEdges() == 13);
  REQUIRE(m.getCountNodes() == 10);
}

TEST_CASE("test1_get_username", "[weight=20], [test=1], [construct]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  REQUIRE(m.getUsername(0) == "Zero");
  REQUIRE(m.getUsername(1) == "One");
  REQUIRE(m.getUsername(2) == "Two");
  REQUIRE(m.getUsername(3) == "Three");
  REQUIRE(m.getUsername(9) == "Nine");
  REQUIRE(m.getUsername(8) == "Eight");
}

// BFS Test Cases

TEST_CASE("test1_bfs_degree0", "[weight=20], [test=1], [bfs]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::map<unsigned int, std::vector<unsigned int>> bfs = m.bfs_traversal(1, 0);

  REQUIRE(bfs.size() == 0);
}

TEST_CASE("test1_bfs_degree1", "[weight=20], [test=1], [bfs]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::map<unsigned int, std::vector<unsigned int>> bfs = m.bfs_traversal(3, 1);

  REQUIRE(bfs.size() == 1);

  std::set<unsigned int> correct_degree1 = {1, 2, 4, 7};
  std::set<unsigned int> result_degree1;
  for (auto user_id : bfs[1]) {
    result_degree1.insert(user_id);
  }
  REQUIRE(result_degree1 == correct_degree1);
}

TEST_CASE("test1_bfs_degree2", "[weight=20], [test=1], [bfs]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::map<unsigned int, std::vector<unsigned int>> bfs = m.bfs_traversal(1, 2);

  REQUIRE(bfs.size() == 2);

  std::set<unsigned int> correct_degree1 = {2, 3, 4, 9};
  std::set<unsigned int> correct_degree2 = {5, 6, 7};
  std::set<unsigned int> result_degree1;
  for (auto user_id : bfs[1]) {
    result_degree1.insert(user_id);
  }
  std::set<unsigned int> result_degree2;
  for (auto user_id : bfs[2]) {
    result_degree2.insert(user_id);
  }
  REQUIRE(result_degree1 == correct_degree1);
  REQUIRE(result_degree2 == correct_degree2);
}

// Djikstra Test Cases

TEST_CASE("test1_djikstra_self", "[weight=20], [test=1], [djikstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> djikstra = m.djikstra(7, 7);
  std::vector<unsigned int> correct1_self = {7};

  REQUIRE(djikstra.size() == 2);
  REQUIRE(djikstra == correct1_self);


}

TEST_CASE("test1_djikstra_1connection", "[weight=20], [test=1], [djikstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> djikstra = m.djikstra(7, 3);
  std::vector<unsigned int> correct1_1connection = {7, 3};

  REQUIRE(djikstra.size() == 2);
  REQUIRE(djikstra == correct1_1connection);


}

TEST_CASE("test1_djikstra_2connections", "[weight=20], [test=1], [djikstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> djikstra = m.djikstra(6, 1);
  std::vector<unsigned int> correct1_2connections = {6, 9, 1};

  REQUIRE(djikstra.size() == 3);
  REQUIRE(djikstra == correct1_2connections);

  djikstra = m.djikstra(8, 4);
  std::vector<unsigned int> correct2_2connections = {8, 5, 4};

  REQUIRE(djikstra.size() == 3);
  REQUIRE(djikstra == correct2_2connections);

  djikstra = m.djikstra(0, 9);
  std::vector<unsigned int> correct3_2connections = {0, 6, 9};

  REQUIRE(djikstra.size() == 3);
  REQUIRE(djikstra == correct3_2connections);
}

// TEST 2

TEST_CASE("test2_edge_and_node_counts", "[weight=15], [test=2]") {
  std::string edges_csv = "../tests/test2_edges.csv";
  std::string target_csv = "../tests/test2_target.csv";
  std::string features_json = "../tests/test2_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);
  
  REQUIRE(m.getCountEdges() == 22); // duplicate edges check
  REQUIRE(m.getCountNodes() == 14); // skipped user id check
}

// BFS Test Cases

TEST_CASE("test2_bfs_degree3", "[weight=15], [test=2], [bfs]") {
  std::string edges_csv = "../tests/test2_edges.csv";
  std::string target_csv = "../tests/test2_target.csv";
  std::string features_json = "../tests/test2_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::map<unsigned int, std::vector<unsigned int>> bfs = m.bfs_traversal(1, 3);

  REQUIRE(bfs.size() == 3);

  std::set<unsigned int> correct_degree1 = {2, 3, 4, 5, 9};
  std::set<unsigned int> correct_degree2 = {7, 8, 11, 12, 16};
  std::set<unsigned int> correct_degree3 = {13, 15};
  std::set<unsigned int> result_degree1;
  for (auto user_id : bfs[1]) {
    result_degree1.insert(user_id);
  }
  std::set<unsigned int> result_degree2;
  for (auto user_id : bfs[2]) {
    result_degree2.insert(user_id);
  }
  std::set<unsigned int> result_degree3;
  for (auto user_id : bfs[3]) {
    result_degree3.insert(user_id);
  }
  REQUIRE(result_degree1 == correct_degree1);
  REQUIRE(result_degree2 == correct_degree2);
  REQUIRE(result_degree3 == correct_degree3);
}

// Djikstra Test Cases

TEST_CASE("test2_djikstra_3connections", "[weight=20], [test=1], [djikstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> djikstra = m.djikstra(4, 14);
  std::vector<unsigned int> correct1_3connections = {4, 7, 13, 14};

  REQUIRE(djikstra.size() == 4);
  REQUIRE(djikstra == correct1_3connections);

  djikstra = m.djikstra(1, 15);
  std::vector<unsigned int> correct2_3connections1 = {1, 5, 8, 15};
  std::vector<unsigned int> correct2_3connections2 = {1, 2, 8, 15};
  std::vector<unsigned int> correct2_3connections3 = {1, 9, 11, 15};

  REQUIRE(djikstra.size() == 4);

  bool check = false;
  if (djikstra == correct2_3connections1 || djikstra == correct2_3connections2 || djikstra == correct2_3connections3) {
    check = true;
  }

  REQUIRE(check == true);

}

TEST_CASE("test2_djikstra_4connections", "[weight=20], [test=1], [djikstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> djikstra = m.djikstra(1, 14);
  std::vector<unsigned int> correct1_4connections1 = {1, 4, 7, 13, 14};
  std::vector<unsigned int> correct1_4connections2 = {1, 4, 16, 13, 14};
  std::vector<unsigned int> correct1_4connections3 = {1, 3, 7, 13, 14};

  REQUIRE(djikstra.size() == 5);

  bool check = false;
  if (djikstra == correct1_4connections1 || djikstra == correct1_4connections2 || djikstra == correct1_4connections3) {
    check = true;
  }
  
  REQUIRE(check == true);

}

// Test All Nodes for Djikstras

TEST_CASE("test2_bigdjikstra", "[weight=20], [test=1], [djikstra]") {
  std::string edges_csv = "../tests/testallnodes_edges.csv";
  std::string target_csv = "../tests/testallnodes_target.csv";
  std::string features_json = "../tests/testallnodes_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::map<unsigned int, std::vector<unsigned int>> djikstra = m.djikstra(1);

  std::vector<unsigned int> correct1_big = {1};
  std::vector<unsigned int> correct3_big = {1, 3};
  std::vector<unsigned int> correct4_big = {1, 3, 4}; 
  std::vector<unsigned int> correct2_big = {1, 3, 4, 2};
  std::vector<unsigned int> correct5_big = {1, 3, 4, 5};

  std::vector<unsigned int> result1_big = djikstra[1];
  std::vector<unsigned int> result3_big = djikstra[3];
  std::vector<unsigned int> result4_big = djikstra[4];
  std::vector<unsigned int> result2_big = djikstra[2];
  std::vector<unsigned int> result5_big = djikstra[5];
  
  REQUIRE(result1_big == correct1_big);
  REQUIRE(result3_big == correct3_big);
  REQUIRE(result4_big == correct4_big);
  REQUIRE(result2_big == correct2_big);
  REQUIRE(result5_big == correct5_big);


}


// TEST_CASE("bfs_test_2_degree5", "[weight=15], [bfs]") {

//   std::string edges_csv = "../tests/bfs_test2_edges.csv";
//   std::string target_csv = "../tests/bfs_test1_target.csv";
//   std::string features_json = "../tests/test1_features.json";
//   MusaeGraph m(edges_csv, target_csv, features_json);

  

//   std::vector<std::set<unsigned int>> bfs = m.bfs_traversal(8, 5);



//   REQUIRE(m.getCountEdges() == 22);
//   REQUIRE(m.getCountNodes() == 14);


  
//   REQUIRE(bfs.at(0).size() == 3);
//   REQUIRE(bfs.at(1).size() == 5);
//   REQUIRE(bfs.at(2).size() == 3);
//   REQUIRE(bfs.at(3).size() == 1);
//   REQUIRE(bfs.at(4).size() == 1);



//   REQUIRE(bfs.at(0).count(15) == 1);
//   REQUIRE(bfs.at(0).count(2) == 1);
//   REQUIRE(bfs.at(0).count(5) == 1);


  

//   REQUIRE(bfs.at(1).count(11) == 1);
//   REQUIRE(bfs.at(1).count(9) == 1);
//   REQUIRE(bfs.at(1).count(4) == 1);
//   REQUIRE(bfs.at(1).count(1) == 1);
//   REQUIRE(bfs.at(1).count(3) == 1);

//   REQUIRE(bfs.at(2).count(12) == 1);
//   REQUIRE(bfs.at(2).count(16) == 1);
//   REQUIRE(bfs.at(2).count(7) == 1);
  

//   REQUIRE(bfs.at(3).count(13) == 1);
//   REQUIRE(bfs.at(4).count(14) == 1);
  
  
// }

// MUSAE GITHUB DATASET

TEST_CASE("musae_gh_get_username", "[weight=10], [musae_gh], [construct]") {
  std::string edges_csv = "../data/git_web_ml/musae_git_edges.csv";
  std::string target_csv = "../data/git_web_ml/musae_git_target.csv";
  std::string features_json = "../data/git_web_ml/musae_git_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  // This tests the integrity of the provided dataset files and that all user 
  // IDs map to a username. It also indirectly proves that no user IDs are 
  // skipped.
  unsigned int array_size = m.getCountNodes();
  for (unsigned int i = 0; i < array_size; ++i) {
    REQUIRE(m.getUsername(i) != "");
  }