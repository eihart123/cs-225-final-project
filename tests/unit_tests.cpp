#include <catch2/catch_test_macros.hpp>
#include "MusaeParser.h"

#include <string>

TEST_CASE("test_edge_and_node_counts", "[weight=15], [part=1]") {
  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeParser m(edges_csv, target_csv, features_json);

  REQUIRE(m.getCountEdges() == 5);
  REQUIRE(m.getCountNodes() == 6);
}

// TODO: Add test case that tests the actual data structure in nodes_ variable