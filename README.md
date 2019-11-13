# Dijkstras_Algorithm
Implementing a undirected weighted Graph ADT and performing Dijkstra's Algorithm to find the shortest path between two vertices. Your graph can be implemented using either an adjacency list, adjacency matrix, or an incidence matrix. Your graph will implement methods that add and remove vertices, add and remove edges, and calculate the shortest path. Each vertex in your graph will have a string label that will help identify that vertex to you and the test file.

Example of functionality:
std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
std::vector<std::tuple<std::string, std::string, unsigned long>>
edges1 = { {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3",
10}, {"2", "4", 15}, {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6},
{"5", "6", 9} };
for (const auto label : vertices1) g.addVertex(label);
for (const auto &tuple : edges1) g.addEdge(std::get<0>(tuple),
std::get<1>(tuple), std::get<2>(tuple));
g.shortestPath("1", "5", path); // == 20
g.shortestPath("1", "5", path); // = { "1", "3", "6", "5" }
