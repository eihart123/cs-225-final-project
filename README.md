# GitHub Social Network Graph
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
2. To run the test cases, run "./test" in the command terminal

**Compiling and Running main.cpp**
1. To compile code for main.cpp run "make" in the command terminal
2. To run main.cpp for finding recommended followers for a given user:

```
./main <edges_file> <target_file> <features_json> {false|true} recommended <username>
```

3. To run main.cpp for finding Github communities:

```
./main <edges_file> <target_file> <features_json> {false|true} communities
```

4. To run main.cpp for raw algorithm results:

```
./main <edges_file> <target_file> <features_json> {false|true} algorithm <source_username> <destination_username>
```

For an example of our algorithms on a large scale, run this command in the /build directory:

```
./main ../data/git_web_ml/musae_git_edges.csv ../data/git_web_ml/musae_git_target.csv ../tests/git_web_ml/musae_git_features.json true algorithm lnsongxf beedo
```

### Help Menu ###

```
Usage: ./main <edges_csv> <target_csv> <features_json> <reduce> <option> [source user] [destination user]
<edges_csv> - edges file to use
<target_csv> - target file to use
<features_json> - features file to use
<reduce> - {false|true}: whether to reduce the dataset to only ML developers
<option> - {recommended|communities|algorithm}:
        recommended - find recommended users for [source user]
        communities - split a community into two communities based on [sources user]
        algorithm - test run time of each of the implemented algorithms, requires [source user] and [destination user]
[source user] - username of source profile
[destination user] - username of destination profile

Example run:
        ./main ../data/git_web_ml/musae_git_edges.csv ../data/git_web_ml/musae_git_target.csv ../tests/git_web_ml/musae_git_features.json true algorithm lnsongxf beedo
```
