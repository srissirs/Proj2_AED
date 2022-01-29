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
    string line; /// The line which the edge that connect the stops belongs to
};
struct Node {
    list<Edge> adj; /// The list of outgoing edges (to adjacent nodes)
    double dist; /// The distance between the node and the node s in the algorithm of Dijkstra
    int pred; /// The precedent node in the algorithm od Dijkstra
    double latitude;
    double longitude;
    bool visited; /// If the node was visited in algorithm of Dijkstra
    string zone; /// The zone of the node
    string stopName; /// The name of the stop
    string code; /// The code of the stop
    string line; /// The line that connects this node to his precedent in the algorithm of Dijkstra
};
class Graph {
    int n;              /// Graph size (vertices are numbered from 1 to n)
    bool hasDir;        /// false: undirected; true: directed
    vector<Node> nodes; /// The list of nodes being represented
    map<string, int> mapNodes; /// The map of the code of the node and his position


    /**
     * @brief The algorithm of Dijkstra that takes the node where we start and the choice of search method to use
     * @param src
     * @param choice
     */
    void dijkstra(int src, int choice);


public:
    /**
     * @brief Constructor: nr nodes and direction (default: undirected)
     * @param nodes
     * @param dir
     */
    Graph(int nodes, bool dir = false);

    /**
     *     @brief Checks if the edge with the parameters exists in the graph
     *     @param dest
     *     @param line
     *     @param src
     *     @param weight
     */
    bool exists(int src, int dest, double weight, string line);

    /**
   *     @brief Checks if the edge with the parameters exists in the graph
     *     @param src
     *     @param weight
     *     @param dest
     *     */
    bool exists(int src, int dest, double weight);

    /**
     * @brief Add edge from source to destination with a certain weight
     * @param src
     * @param dest
     * @param weight
     * @param line
     */
    void addEdge(int src, int dest, double weight, string line);

    /**
     * @brief Add a node to the map
     * @param node
     */
    void addNode(Node node);

    /**
     * @brief Sets the vector node
     * @param newNodes
     */
    void setNodes(vector<Node> newNodes) {
        this->nodes = newNodes;
        this->n = newNodes.size();
    }

    /**
  * @brief Returns the vector nodes
  */
    vector<Node> &getNodes() { return nodes; }

    /**
  * @brief Sets the map of nodes
     * @param newMap
  */
    void setMap(map<string, int> newMap) { this->mapNodes = newMap; }

    /**
  * @brief Gets the map of nodes
  */
    map<string, int> &getMap() { return mapNodes; }

    /**
  * @brief Returns the weight of the edge depending on the method of the user's choice
     * @param src
     * @param choice
     * @param edge
  */
    double getWeight(int src,int choice,Edge edge);

    /**
  * @brief Returns the distance of the nodes in the Dijkstra algorithm on the method of the user's choice
     * @param choice
     * @param a
     * @param b
  */
    int dijkstra_distance(int a, int b, int choice);

    /**
  * @brief Returns the path of nodes from "a" stop to "b" stop with the method of search "choice" in the Dijkstra algorithm
  */
    list<Node> dijkstra_pathNodes(int a, int b, int choice);

    /**
  * @brief Returns the path of nodes from "src" stop to "dest" stop with the method of search bfs
   * @param choice
     * @param a
     * @param b
  */
    list<Node> bfs_path(int src,int dest);

    /**
  * @brief Implements the bfs method of search to connect "src" stop and "dest" stop and returning true if the stops can be connected and false if not
     * @param src
     *  @param dest
  */

    bool bfs(int src,int dest);

    /**
  * @brief Returns a vector of pairs of int with the distance of the scr to dest in the dijkstra algorithm and the path from scr to dest
  * The function returns a vector of pairs because the scr can start in different lines
     * @param dest
     *  @param src
      */

    vector<pair<int,list<Node>>> bestPathLessLineChange(int src, int dest);

};
#endif