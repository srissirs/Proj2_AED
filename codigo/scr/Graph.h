#ifndef PROJ2AED_GRAPH_H
#define PROJ2AED_GRAPH_H

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>

using namespace std;

struct Edge {
    int src;
    int dest;   /// Destination node
    double weight; /// An integer weight
    string line; ///
};
struct Node {
    list<Edge> adj; /// The list of outgoing edges (to adjacent nodes)
    int dist;
    int pred;
    double latitude;
    double longitude;
    bool visited;
    string zone;
    string stopName;
    string code;
    string line;
};
class Graph {
    int n;              /// Graph size (vertices are numbered from 1 to n)
    bool hasDir;        /// false: undirect; true: directed
    vector<Node> nodes; /// The list of nodes being represented

    map<string, int> mapNodes;

    void dijkstra(int src);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    void setNode(int pos, const Node &node) {
        nodes[pos] = node;
    }

    bool exists(int src, int dest, double weight, string line);

    bool exists(int src, int dest, double weight);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight, string line);

    void setNodes(vector<Node> newNodes) {
        this->nodes = newNodes;
        this->n = newNodes.size();
    }

    vector<Node> &getNodes() { return nodes; }

    void setMap(map<string, int> newMap) { this->mapNodes = newMap; }

    map<string, int> &getMap() { return mapNodes; }

    int getWeight(int src, int dest, string line);

    list<list<int>> bestPathLessLineChange(int src, int dest);

    list<int> dijkstra_path(int a, int b);

    int dijkstra_distance(int a, int b);

};
#endif