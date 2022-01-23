#include "Graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}




// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight) {
    if (src<0 || src>n || dest<0 || dest>n) return;
    if(exists(src,dest, weight)) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

bool Graph::exists(int src, int dest, double weight){
    for( auto edge: nodes[src].adj){
        if (edge.weight==weight and edge.dest == dest)
            return true;
    }
    for( auto edge: nodes[dest].adj){
        if (edge.weight==weight and edge.dest == src)
            return true;
    }
    return false;
}

void Graph::addLine(tuple<string, int, int> line, int pos) {
    nodes[pos].lines.push_back(line);
}

// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    return -1;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    return path;
}
