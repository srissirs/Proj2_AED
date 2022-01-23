#ifndef PROJ2AED_GRAPH_H
#define PROJ2AED_GRAPH_H

#include "minHeap.h"
#include "auxiliarFunctions.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>

using namespace std;

struct Edge {
    int dest;   /// Destination node
    double weight; /// An integer weight
    //string line; ///
};
struct Node {
    list<Edge> adj; /// The list of outgoing edges (to adjacent nodes)
    int dist;
    int pred;
    double latitude;
    double longitude;
    int dirPos; /// Position of the stop in a specific line
    int dir;       ///Direction in a line
    bool visited;
    string zone;
    string stopName;
    list<tuple<string,int,int>> lines;     /// lineName /dir/dirPos
    string code;
};
class Graph {
    int n;              /// Graph size (vertices are numbered from 1 to n)
    bool hasDir;        /// false: undirect; true: directed
    vector<Node> nodes; /// The list of nodes being represented

    map<string, int> mapNodes;
    void dijkstra(int s);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    void setNode(int pos,const Node &node){
        nodes[pos] = node;
    }
    bool exists(int src, int dest, double weight);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight);

    void addLine(tuple<string,int,int> line, int pos);

    void setNodes(vector<Node> newNodes) {
        this->nodes = newNodes;
        this->n=newNodes.size();}

    vector<Node>& getNodes() { return nodes;}

    void setMap(map<string, int> newMap) { this->mapNodes = newMap;}

    map<string, int>& getMap() { return mapNodes;}

    // ----- Functions to implement in this class -----
    int dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);
};



#endif