#include <catch2/catch_test_macros.hpp>
#include "MusaeParser.h"

#include <string>

TEST_CASE("test_parser_correct_num_edges", "[weight=15]") {
  std::string edges_csv;
  std::string target_csv;
  std::string features_json;
  MusaeParser m(edges_csv, target_csv, features_json);

  REQUIRE(m.getCountEdges() == 5);
  
}