#include <iostream>
#include <string>
#include <chrono>
#include <bits/stdc++.h>

#include "MusaeGraph.h"

int main(int argc, char** argv)
{

    unsigned int MAX_USER_ID = 5000;

    std::string functionality = argv[5];

    if ((argc != 7 || functionality != "recommended") && (argc != 6 || functionality != "communities") && (argc != 8 || functionality != "algorithm")) {
        std::cout << "Usage: ./main <edges_csv> <target_csv> <features_json> <reduce> <option> [source user] [destination user]" << std::endl;
        std::cout << "<edges_csv> - edges file to use" << std::endl;
        std::cout << "<target_csv> - target file to use" << std::endl;
        std::cout << "<features_json> - features file to use" << std::endl;
        std::cout << "<reduce> - {false|true}: whether to reduce the dataset to only ML developers" << std::endl;
        std::cout << "<option> - {recommended|communities|algorithm}:" << std::endl;
        std::cout << "\trecommended - find recommended users for [source user]" << std::endl;
        std::cout << "\tcommunities - split a community into two communities based on [sources user]" << std::endl;
        std::cout << "\talgorithm - test run time of each of the implemented algorithms, requires [source user] and [destination user]" << std::endl;
        std::cout << "[source user] - username of source profile" << std::endl;
        std::cout << "[destination user] - username of destination profile" << std::endl << std::endl;

        std::cout << "Example run:" << std::endl;
        std::cout << "\t./main ../data/git_web_ml/musae_git_edges.csv ../data/git_web_ml/musae_git_target.csv ../tests/git_web_ml/musae_git_features.json true algorithm lnsongxf beedo" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    // run and print recommended followers for user input using Breadth-First Search
    if (functionality == "recommended") {
        std::string edges_file = argv[1];
        std::string target_file = argv[2];
        std::string features_json = argv[3];
        std::string username = argv[6];
        std::string include_ml = argv[4];

        MusaeGraph githubNetwork = MusaeGraph(MAX_USER_ID, edges_file, target_file, features_json);

        if (include_ml == "true") {
            githubNetwork = MusaeGraph(MAX_USER_ID, true, edges_file, target_file, features_json);
        }
       
        unsigned int user_id = githubNetwork.getIdFromUsername(username);

        if (user_id == INT_MAX) {
            std::cout << "[!] Error: User does not exist" << std::endl;
            return 0;
        }

        std::map<unsigned int, unsigned int> recommendations = githubNetwork.getRecommendedUsersToFollow(user_id, 3, 5);

        std::cout << "[+] Users we think " << username << " will love: " << std::endl;
        for (std::pair<unsigned int, unsigned int> user : recommendations) {
            std::cout << githubNetwork.getUsernameFromId(user.first) << " (degree " << std::to_string(user.second) << ")" << std::endl;
        }

    }

    // determine and print if two given users are in the same community using Girvan-Newman and Dijkstra's Algorithm
    if (functionality == "communities") {
        std::string edges_file = argv[1];
        std::string target_file = argv[2];
        std::string features_json = argv[3];
        std::string include_ml = argv[4];

        MusaeGraph githubNetwork = MusaeGraph(MAX_USER_ID, edges_file, target_file, features_json);

        if (include_ml == "true") {
            githubNetwork = MusaeGraph(MAX_USER_ID, true, edges_file, target_file, features_json);
        }
        
        std::vector<std::set<unsigned int>> communities = githubNetwork.calculateCommunities();

        for (unsigned int community = 0; community < communities.size(); community++) {
            std::cout << "Community " << std::to_string(community + 1) << ":" << std::endl;
            for (unsigned int community_member : communities[community]) {
                std::cout << "\t" << githubNetwork.getUsernameFromId(community_member) << std::endl;
            }
        }
    }

    // run and print output of all the algorithm results (BFS, Dijkstra's Algorithm, and Girvan-Newman Algorithm)
    if (functionality == "algorithm") {
        std::string edges_file = argv[1];
        std::string target_file = argv[2];
        std::string features_json = argv[3];
        std::string include_ml = argv[4];
        std::string source_username = argv[6];
        std::string destination_username = argv[7];        
        
        MusaeGraph githubNetwork = MusaeGraph(MAX_USER_ID, edges_file, target_file, features_json);

        if (include_ml == "true") {
            githubNetwork = MusaeGraph(MAX_USER_ID, true, edges_file, target_file, features_json);
        }
        
        unsigned int source_user_id = githubNetwork.getIdFromUsername(source_username);
        unsigned int destination_user_id = githubNetwork.getIdFromUsername(destination_username);

        std::cout << "BFS results for " << source_username << " for 3 degrees:" << std::endl;
        std::cout << "=======================================" << std::endl;

        auto start_time = std::chrono::high_resolution_clock::now();
        std::map<unsigned int, std::vector<unsigned int>> degrees = githubNetwork.bfs_traversal(source_user_id, 3);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        for (auto it = degrees.begin(); it != degrees.end(); it++) {
            std::cout << (*it).first << ": {";
            auto vect = (*it).second;
            for (auto id : vect) {
                std::cout << std::to_string(id);
                if (id != vect[vect.size() - 1]) {
                    std::cout << ", ";
                }
            }
            std::cout << "}" << std::endl;
        }
        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "=======================================" << std::endl << std::endl;

        std::cout << "Dijkstra's Algorithm results from " << source_username << " to " << destination_username << ":" << std::endl;
        std::cout << "=======================================" << std::endl;
        
        start_time = std::chrono::high_resolution_clock::now();
        std::vector<unsigned int> shortestPath = githubNetwork.dijkstra(source_user_id, destination_user_id);
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        std::cout << " {";
        for (unsigned int id : shortestPath) {
            std::cout << std::to_string(id);
            if (id != shortestPath[shortestPath.size() - 1]) {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;
        std::cout << " {";
        for (unsigned int id : shortestPath) {
            std::cout << githubNetwork.getUsernameFromId(id);
            if (id != shortestPath[shortestPath.size() - 1]) {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;

        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "=======================================" << std::endl << std::endl;

        std::cout << "Communities created by Girvan-Newman Algorithm" << std::endl;
        std::cout << "=======================================" << std::endl;
        start_time = std::chrono::high_resolution_clock::now();
        std::vector<std::set<unsigned int>> communities = githubNetwork.calculateCommunities();
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        for (unsigned int community = 0; community < communities.size(); community++) {
            std::cout << "Community " << std::to_string(community + 1) << " (" << communities[community].size() << " members):" << std::endl << "\t" << "[";
            for (unsigned int community_member : communities[community]) {
                std::cout << githubNetwork.getUsernameFromId(community_member) << ", ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "=======================================" << std::endl << std::endl;

    }

    return 0;
}