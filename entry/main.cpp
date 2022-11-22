#include "MusaeGraph.h"

int main() {
  // TODO: Add ability to read filenames from arguments

  std::string edges_csv = "../tests/test1_edges.csv";
  std::string target_csv = "../tests/test1_target.csv";
  std::string features_json = "../tests/test1_features.json";
  MusaeGraph m(edges_csv, target_csv, features_json);
  std::map<unsigned int, std::vector<unsigned int>> degrees = m.bfs_traversal(1, 3);

  std::cout << "BFS content print" << std::endl;
  std::cout << "=======================================" << std::endl;
  for (auto it = degrees.begin(); it != degrees.end(); it++) {
    std::cout << (*it).first << ": {";
    auto vect = (*it).second;
    for (auto id : vect) {
      std::cout << std::to_string(id) << ", ";
    }
    std::cout << "}" << std::endl;
  }
  std::cout << "=======================================" << std::endl << std::endl;

  std::cout << "getRecommendedUsersToFollow() (pick 3 random)" << std::endl;
  std::cout << "=======================================" << std::endl;
  auto users_to_follow = m.getRecommendedUsersToFollow(1, 3, 3);
  for (auto it = users_to_follow.begin(); it != users_to_follow.end(); it++) {
    std::cout << "Degree: " << std::to_string((*it).second) << ", ID: " << std::to_string((*it).first) << ", Username: " << m.getUsername((*it).first) << std::endl;;
  }
  std::cout << "=======================================" << std::endl << std::endl;

  std::cout << "getRecommendedUsersToFollow() (complete)" << std::endl;
  std::cout << "=======================================" << std::endl;
  users_to_follow = m.getRecommendedUsersToFollow(1, 3, -1);
  for (auto it = users_to_follow.begin(); it != users_to_follow.end(); it++) {
    std::cout << "Degree: " << std::to_string((*it).second) << ", ID: " << std::to_string((*it).first) << ", Username: " << m.getUsername((*it).first) << std::endl;;
  }
    std::cout << "=======================================" << std::endl;
  
  return 0;
}