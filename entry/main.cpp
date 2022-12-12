#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "MusaeGraph.h"

int main(int argc, char** argv)
{

    std::string functionality = argv[4];

    if ((argc != 6 || functionality != "recommended") && (argc != 5 || functionality != "communities") && (argc != 7 || functionality != "algorithm")) {
        std::cout << "Run format for finding follower recommendations: ./main <edges_file> <target_file> <features_json> recommended <username>" << std::endl;
        std::cout << "Run format for finding GitHub communities: ./main <edges_file> <target_file> <features_json> communities" << std::endl;
        std::cout << "Run format for algorithm results: ./main <edges_file> <target_file> <features_json> algorithm <source_username> <destination_username>" << std::endl;
        return 0;
    }

    if (functionality == "recommended") {
        std::string edges_file = argv[1];
        std::string target_file = argv[2];
        std::string features_json = argv[3];
        std::string username = argv[5];

        MusaeGraph githubNetwork = MusaeGraph(edges_file, target_file, features_json);

        unsigned int user_id = githubNetwork.getIdFromUsername(username);

        if (user_id == INT_MAX) {
            std::cout << "User does not exist" << std::endl;
            return 0;
        }

        std::map<unsigned int, unsigned int> recommendations = githubNetwork.getRecommendedUsersToFollow(user_id, 3, 5);

        std::cout << "Users we think " << username << " will love: " << std::endl;
        for (std::pair<unsigned int, unsigned int> user : recommendations) {
            std::cout << githubNetwork.getUsernameFromId(user.first) << " (degree " << std::to_string(user.second) << ")" << std::endl;
        }

    }

    if (functionality == "communities") {
        std::string edges_file = argv[1];
        std::string target_file = argv[2];
        std::string features_json = argv[3];

        MusaeGraph githubNetwork = MusaeGraph(edges_file, target_file, features_json);
        std::vector<std::vector<unsigned int>> communities = githubNetwork.calculateCommunities();

        for (unsigned int community = 0; community < communities.size(); community++) {
            std::cout << "Community " << std::to_string(community + 1) << ":" << std::endl;
            for (unsigned int community_member : communities[community]) {
                std::cout << "\t" << githubNetwork.getUsernameFromId(community_member) << std::endl;
            }
        }
    }

    return 0;
}