#include <catch2/catch_test_macros.hpp>
#include "MusaeGraph.h"
#include <map>

// Tests for MusaeGraph::getRecommendedUsersToFollow() can be found in main.cpp

/*
============================================
TEST 1
============================================
*/

TEST_CASE("test1_edge_and_node_counts", "[weight=20], [test=1], [construct]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);
  
  REQUIRE(m.getCountEdges() == 13);
  REQUIRE(m.getCountNodes() == 10);
}

TEST_CASE("test1_getUsernameFromId", "[weight=20], [test=1], [construct]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  REQUIRE(m.getUsernameFromId(0) == "Zero");
  REQUIRE(m.getUsernameFromId(1) == "One");
  REQUIRE(m.getUsernameFromId(2) == "Two");
  REQUIRE(m.getUsernameFromId(3) == "Three");
  REQUIRE(m.getUsernameFromId(9) == "Nine");
  REQUIRE(m.getUsernameFromId(8) == "Eight");
}

TEST_CASE("test1_getIdFromUsername", "[weight=20], [test=1], [construct]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  REQUIRE(m.getIdFromUsername("Zero") == 0);
  REQUIRE(m.getIdFromUsername("One") == 1);
  REQUIRE(m.getIdFromUsername("Two") == 2);
  REQUIRE(m.getIdFromUsername("Three") == 3);
  REQUIRE(m.getIdFromUsername("Nine") == 9);
  REQUIRE(m.getIdFromUsername("Eight") == 8);
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

// Dijkstra Test Cases

TEST_CASE("test1_dijkstra_self", "[weight=20], [test=1], [dijkstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> dijkstra = m.dijkstra(7, 7);
  std::vector<unsigned int> correct1_self = {7};

  REQUIRE(dijkstra.size() == 1);
  REQUIRE(dijkstra == correct1_self);


}

TEST_CASE("test1_dijkstra_1connection", "[weight=20], [test=1], [dijkstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> dijkstra = m.dijkstra(7, 3);
  std::vector<unsigned int> correct1_1connection = {7, 3};

  REQUIRE(dijkstra == correct1_1connection);


}

TEST_CASE("test1_dijkstra_2connections", "[weight=20], [test=1], [dijkstra]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> dijkstra = m.dijkstra(6, 1);
  std::vector<unsigned int> correct1_2connections = {6, 9, 1};

  REQUIRE(dijkstra.size() == 3);
  REQUIRE(dijkstra == correct1_2connections);

  dijkstra = m.dijkstra(8, 4);
  std::vector<unsigned int> correct2_2connections = {8, 5, 4};

  REQUIRE(dijkstra.size() == 3);
  REQUIRE(dijkstra == correct2_2connections);

  dijkstra = m.dijkstra(0, 9);
  std::vector<unsigned int> correct3_2connections = {0, 6, 9};

  REQUIRE(dijkstra.size() == 3);
  REQUIRE(dijkstra == correct3_2connections);
}

/*
============================================
TEST 2
============================================
*/

TEST_CASE("test2_edge_and_node_counts", "[weight=15], [test=2]") {
  std::string edges_csv = "../tests/test2_edges.csv";
  std::string target_csv = "../tests/test2_target.csv";
  std::string features_json = "../tests/test2_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);
  
  REQUIRE(m.getCountEdges() == 22); // duplicate edges check
  // REQUIRE(m.getCountNodes() == 14); // skipped user id check
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

// Dijkstra Test Cases

TEST_CASE("test2_dijkstra_3connections", "[weight=20], [test=2], [dijkstra]") {
  std::string edges_csv = "../tests/test2_edges.csv";
  std::string target_csv = "../tests/test2_target.csv";
  std::string features_json = "../tests/test2_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> correct1_3connections = {4, 7, 13, 14};
  std::vector<unsigned int> correct2_3connections = {1, 2, 8, 15};

  REQUIRE(m.dijkstra(4, 14) == correct1_3connections);
  REQUIRE(m.dijkstra(1, 15) == correct2_3connections);
}

TEST_CASE("test2_dijkstra_4connections", "[weight=20], [test=2], [dijkstra]") {
  std::string edges_csv = "../tests/test2_edges.csv";
  std::string target_csv = "../tests/test2_target.csv";
  std::string features_json = "../tests/test2_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<unsigned int> correct1_4connections = {1, 3, 7, 13, 14};
  REQUIRE(m.dijkstra(1, 14) == correct1_4connections);
}

/*
============================================
TEST 3
============================================
*/

TEST_CASE("test3_bigdijkstra", "[weight=20], [test=3], [dijkstra]") {
  std::string edges_csv = "../tests/test3_edges.csv";
  std::string target_csv = "../tests/test3_target.csv";
  std::string features_json = "../tests/test3_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::map<unsigned int, std::vector<unsigned int>> dijkstra = m.dijkstra(1);

  std::vector<unsigned int> correct0_big = {1, 3, 4, 5, 0};
  std::vector<unsigned int> correct1_big = {1};
  std::vector<unsigned int> correct2_big = {1, 3, 4, 2};
  std::vector<unsigned int> correct3_big = {1, 3};
  std::vector<unsigned int> correct4_big = {1, 3, 4};
  std::vector<unsigned int> correct5_big = {1, 3, 4, 5};

  std::vector<unsigned int> result0_big = dijkstra[0];
  std::vector<unsigned int> result1_big = dijkstra[1];
  std::vector<unsigned int> result2_big = dijkstra[2];
  std::vector<unsigned int> result3_big = dijkstra[3];
  std::vector<unsigned int> result4_big = dijkstra[4];
  std::vector<unsigned int> result5_big = dijkstra[5];
  
  REQUIRE(result0_big == correct0_big);
  REQUIRE(result1_big == correct1_big);
  REQUIRE(result2_big == correct2_big);
  REQUIRE(result3_big == correct3_big);
  REQUIRE(result4_big == correct4_big);
  REQUIRE(result5_big == correct5_big);
}

// Girvan-Newman Test Cases

TEST_CASE("test3_girvan", "[weight=20], [test=3], [girvan]") {
  std::string edges_csv = "../tests/test3_edges.csv";
  std::string target_csv = "../tests/test3_target.csv";
  std::string features_json = "../tests/test3_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<MusaeGraph::Node> n = m.girvan();

  // Test for connections we still want to exist
  REQUIRE(n[0].neighbors_.count(5));
  REQUIRE(n[1].neighbors_.count(3));
  REQUIRE(n[2].neighbors_.count(4));
  REQUIRE(n[3].neighbors_.count(1));
  REQUIRE(n[4].neighbors_.count(2));
  REQUIRE(n[4].neighbors_.count(5));
  REQUIRE(n[5].neighbors_.count(0));

  // Test for connections we no longer want to exist
  REQUIRE(!n[3].neighbors_.count(4));
  REQUIRE(!n[4].neighbors_.count(3));
}

/*
============================================
TEST 4
============================================
*/

TEST_CASE("test4_girvan", "[weight=20], [test=4], [girvan]") {
  std::string edges_csv = "../tests/test4_edges.csv";
  std::string target_csv = "../tests/test4_target.csv";
  std::string features_json = "../tests/test4_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);

  std::vector<MusaeGraph::Node> n = m.girvan();

  // test for connections we still want to exist
  REQUIRE(n[1].neighbors_.count(2));
  REQUIRE(n[2].neighbors_.count(1));
  REQUIRE(n[1].neighbors_.count(3));
  REQUIRE(n[3].neighbors_.count(1));
  REQUIRE(n[2].neighbors_.count(4));
  REQUIRE(n[4].neighbors_.count(2));
  REQUIRE(n[3].neighbors_.count(4));
  REQUIRE(n[4].neighbors_.count(3));
  REQUIRE(n[5].neighbors_.count(6));
  REQUIRE(n[6].neighbors_.count(5));
  REQUIRE(n[5].neighbors_.count(7));
  REQUIRE(n[7].neighbors_.count(5));
  REQUIRE(n[6].neighbors_.count(8));
  REQUIRE(n[8].neighbors_.count(6));
  REQUIRE(n[7].neighbors_.count(8));
  REQUIRE(n[8].neighbors_.count(7));
  
  // test for connections we no longer want to exist
  REQUIRE(!n[1].neighbors_.count(5));
  REQUIRE(!n[5].neighbors_.count(1));
  REQUIRE(!n[4].neighbors_.count(8));
  REQUIRE(!n[8].neighbors_.count(4));
}

/*
============================================
MUSAE GH DATASET
============================================
*/

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
    REQUIRE(m.getUsernameFromId(i) != "");
  }
}