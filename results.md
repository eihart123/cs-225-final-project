# The output and correctness of each algorithm:
### BFS: ###

- We used breadth-first search to traverse the graph to find the users within a certain number of degrees of connection of a given user. BFS visits a node and then visits all of its neighbors until there are no more nodes to visit. We take in the graph, the user that we want to find the degrees of connection for, and the number of degrees of connection we want to find, and output a map of vectors containing the users within each degree of connections between 1 and the number of degrees input.
- Our test cases checked to see if our map was outputting the correct neighbors within our connections using multiple test graphs. We checked for edge cases by having our graph include cycles and having specific nodes have multiple connections, and made sure our map would still output the right users.

```
BFS results for lnsongxf for 3 degrees:
=======================================
1: {1358, 4002}
2: {560, 601, 686, 1258, 1418, 2614, 2747, 3363, 4069}
3: {641, 3757, 1573, 450, 1160, 2330, 3278, 3917, 4523}
Execution time: 577 microseconds
=======================================
```

When using the user "lnsongxf" and the degree connections "3", as inputs for the bfs traversal, our output is the map above, where the keys are connections from 1 to 3, and the values are vectors containing all the indices in our stored node vector that match up to resulting nodes that are the key distance away from the orginal user.

Our worstcase runtime is O(n + m), where n is the number of nodes, and m is the number of edges. We can infer that our BFS algorithm follows this runtime as our execution time is 577 microseconds.


### Dijkstras Algorithm: ###

- We used Dijkstra's algorithm to find the shortest path from one node to another. Dijkstra's algorithm begins at the starting node visits a node and its adjacent neighbors and determines which route is shortest, repeating the process until it reaches the destination node or it is determined that the destination node is not present. 
- Our test cases check to see if the shortest path was properly constructed. We prioritize paths with consecutive numbers: for example, if there were two shortest paths, {1, 2, 3, 4, 5} and {1, 2, 4, 3, 5}, which have the same cost, {1, 2, 3, 4, 5} would be prioritized. If there is no path from one node to another, we expect an empty vector to be output. If two of the same node are input for both the start and end of the path, we expect a vector containing just that node once to be output.

```
Dijkstra's Algorithm results from lnsongxf to beedotkiran:
=======================================
 {4467, 1358, 686, 3757, 506, 4184, 166, 4871}
 {lnsongxf, StefanKarpinski, Sumegh-git, nishnik, shashankg7, nemaniarjun, mohanarunachalam, beedotkiran}
Execution time: 4346 microseconds
=======================================
```

When using the users "lnsongxf" and "beedotkiran", as inputs for the Dijkstra's Algorithm, our output is the vector above, which is the shortest path between the two given users. Although there are multiple paths between the two users, dikjstra's utilizes a priority queue to find the shortest path following a runtime of O(number of users * log(number of users)). We can once again infer that this runtime has been met because our exectution time is 4346 microseconds.


### Girvan-Newman Algorithm: ###

 *Betweenness Centrality:*

- We used betweenness centrality to determine which edges to remove in our Girvan-Newman algorithm. To find betweenness centrality we calculated how many shortest paths of every node combination (using dijkstra's algorithm) that go through each edge. We save these values and use the betweenness to calculate which edges to remove.
- We tested this algorithm inside our girvan-newman algorithm test cases. We tested to make sure that it removed the proper edge in our test3 graph by checking if either node was a neighbor or each other. We also did the process with our test4 graph and ensured that it removed both edges in the correct order.

 *Girvan-Newman Implementation:*
 
- We used the Girvan-Newman Algorithm to find communities of connected users. Girvan-Newman works by reducing the size of the graph to only machine learning users and then finds the node with the most neighbors and uses that connected component for the rest of the algorithm. We perform a bfs on that node and create a new vector of nodes. We then find the betweenness centrality of all edges in that graph. We then remove an edge with the highest betweenness and recalculate the betweenness centrality of all edges and repeat that process of removing an edge and recalculating betweenness centrality until there are two connected components. We then run a bfs from the 1st node in the new vector of nodes and add it into a vector of sets of integers which will be returned at the end. We then iterate until we find a node that is not in that first set and perform bfs on that to get our second connected components. We add that to the vector of sets and return it as our final output.
- We tested this algorithm using two different graphs called test3 and test4. test3 tests a single edge removal and tests specifically the neighbors of each nodes to make sure the edge was removed properly. We also tested our calculate community function which returns the vector of sets of user ids to make sure that was returning the two correct subgraphs. With test4 we tested multi edge removal by checking the neighbors of each nodes to ensure that all edges were removed.

```
Communities created by Girvan-Newman Algorithm
=======================================
[*] Found most popular user: 56
[*] Total number of users: 1315
[*] Total number of edges: 294
[*] Local number of users: 163
[*] Local number of edges: 366
[*] Girvan-Newman Iteration 0
[*] Girvan-Newman Iteration 1
[+] Completed Girvan-Newman!
Community 1 (134 members):
        [TarrySingh, Bjoux2, francisfsjiang, mohanarunachalam, ilija139, GTmac, KinglittleQ, Torreshan, Separius, MrGemy95, animesh-chouhan, dcanones, shaddygarg, HolenYHR, shashankg7, sbarman-mi9, FangYang970206, kyzhouhzau, mjhendrickson, Koprvhdix, floringogianu, tegg89, Abmiester, thealphadollar, asiagood, GengDavid, Sumegh-git, bhargavvader, IKKIson, hualin95, furkanonder, KimHunJin, ktaebum, EmmaSRH, airalcorn2, Prabhat-IIT, ji-a-kang, lipengyuan1994, Feiyu-Zhang, caldmet70, lijiansong, Hwhitetooth, StefanKarpinski, byt3bl33d3r, rohan-singh, Arctanxy, MaximumEntropy, escapeanaemia, Goldesel23, AshishKumar4, shiba24, stormraiser, kleincup, giglf, jcyk, pengshuang, raorao1994, bearpaw, MichaelXSChen, nikhiljangam, Joechann0831, nishathussain, SaiBiswas, luopeixiang, dogukankotan, AnirudhDagar, n01z3, ZS167275, eaglewarrior, danielhanchen, rvlobato, shakingkelly, Sid2697, MarkSecada, paulyang1990, haofeixu, neilyoyoyoyo, nasimrahaman, YapengTian, terryum, robi56, darthbhyrava, karthikziffer, sinomiko, Mukosame, alokkshukla, rava-dosa, KrishnaManeeshaDendukuri, Jennifer1996, JKeun, shiyi001, aru31, chenyangh, chenhsuanlin, sam179, eccstartup, carlgogo, haoransh, AguacateVelarde, ovcharenkoo, kychern, sjchoi86, nishnik, ssydasheng, kabartay, DmitryUlyanov, ShikharJ, khui, FangGet, FrozenGene, Wuie, lakshmiDRIP, Amanbhandula, DukeEnglish, chenyuntc, chituma110, Neelesh7544, nemaniarjun, ankeshanand, dimenwarper, romellfudi, AshishMehtaIO, duducheng, ankahira, lnsongxf, Raghavsalotra, bobbyshashin, blissray, huangzhii, beedotkiran, BotYue, QingSimon, louisblythe, gunanksood, ]
Community 2 (29 members):
        [mingkin, adichad, apetresc, numanyilmaz, gomesfellipe, Subhraj07, holdenk, ognis1205, karthikrk1, jjerphan, kootenpv, ericxiao251, erikbern, psinger, emakhov, olekscode, shawnau, gdequeiroz, giopagliari, mozzarellaV8, scouvreur, bradleyboehmke, moneyDboat, djsaunde, smafjal, Asurada2015, chezou, saikatbsk, bhamadicharef, ]
Execution time: 76873847 microseconds
=======================================
```

The output of girvan newman displays two different communities with the usernames of all users apart of the group. These two communities are found by using the machine learning subgraph with the most popular user (most number of neighbors) which is the user with userid 56 and running girvan newman on that smaller subgraph to get a readable and practical output.

The worst case runtime of this algorithm is O((# of edges)^2 * # of users). It meets our expected worst case runtime and the long microsecond time is attributed to the many recursive dijkstra's calls and massive dataset.  


### Leading Question ###

Our leading question was "How can we connect more developers with each other to build better open source projects?"

We answered this question in two main ways. First we created a function that will find all recommended users within a chosen degree of a user. This will output user follower suggestions and enable to a github user to connect with other github users with mutual followers. Second we created a function that will find two unqiue communities of users that have strong connections with one another. The function also gives the option to only include machine learning users as seen in our ouput which creates a very specific group of communities. This function could create some sort of github group feature where github users can find other github users in their same sub group. We discovered a way to find more friends easily, and to find new users you would never know wanted to follow you. We also discovered a new way of grouping large amounts of users with like interests and connections.
