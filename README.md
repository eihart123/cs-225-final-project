# cs-225-final-project

## GitHub Organization ##

1. **Tests** The test cases for this project are under the ./tests folder in the base directory of the the repository and the file is labeled ./tests.cpp. The test data (edges, features, and target) are all in the ./tests folder in the project directory and make up all other files besides ./tests.cpp.

2. **Data** The data for this project are under the ./data/git_web_ml folder in the base directory of the the repository. The file ./musae_git_edges.csv gives the edges in the graph, where each line is the first user id followed by a comma and the second user id. The ./musae_git_features.json displays a user followed by all neighbors. The ./musae_git_target.csv file contains the user id, followed by the username, and then a binary number, 1 indicating they are involved with machine learning.

3. **Code** Our primary code is inside our ./src folder in the base directory of the the repository. This folder contains ./MusaeGraph.h which is our header file for our graph implementation and it contains our graph class, MusaeGraph and all its declarations. This folder also contains ./Musaegraph.cpp which is our cpp file for our graph implementation and contains the definitions for our graph class, MusaeGraph. Our main.cpp file used for running our code, is located in the ./entry folder in the base directory of the the repository.

4. **Written Report** Our written report is located in the project directory and is the ./results.md file.

5. **Presentation Video** Our video is located in ....

## Running Instructions ##

### Building Executable

**Creating build file**
1. In the base directory of the repository run "mkdir build"
2. Then run "cd ./build"
3. Next run "cmake .." to initialize the build directory

**Compiling and Running Test Cases**
1. To compile code for test cases run "make test" in the command terminal
2. To run the test cases, run "./test

**Compiling and Running main.cpp**
1. To compile code for main.cpp run "make" in the command terminal
2. To run main.cpp, run "./main
