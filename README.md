# cs-225-final-project

### GitHub Organization ###

1. **Tests** The test cases for this project are under the ./tests folder in the directory and the file is labeled ./tests.cpp. The test data (edges, features, and target) are all in the ./tests folder in the project directory and make up all other files besides ./tests.cpp.

2. **Data** The data for this project are under the ./data/git_web_ml folder. The file ./musae_git_edges.csv gives the edges in the graph, where each line is the first user id followed by a comma and the second user id. The ./musae_git_features.json displays a user followed by all neighbors. The ./musae_git_target.csv file contains the user id, followed by the username, and then a binary number, 1 indicating they are involved with machine learning.

3. **Code** Our primary code is inside our ./src folder. This folder contains ./MusaeGraph.h which is our header file for our graph implementation and it contains our graph class, MusaeGraph and all its declarations. This folder also contains ./Musaegraph.cpp which is our cpp file for our graph implementation and contains the definitions for our graph class, MusaeGraph.

4. **Written Report** Our written report is located in the project directory and is the ./results.md file.
