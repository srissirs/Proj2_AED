#include "Graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}



// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight,string line) {
    if (src<0 || src>n || dest<0 || dest>n) return;
    if(exists(src,dest, weight,line)) return;
    nodes[src].adj.push_back({src,dest, weight,line});
    if (!hasDir) nodes[dest].adj.push_back({src,dest, weight,line});
}

bool Graph::exists(int src, int dest, double weight,string line){
    for( auto edge: nodes[src].adj){
        if (edge.weight==weight and edge.dest == dest and edge.line==line)
            return true;
    }
    return false;
}

bool Graph::exists(int src, int dest, double weight){
    for( auto edge: nodes[src].adj){
        if (edge.weight==weight and edge.dest == dest)
            return true;
    }
    return false;
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

bool Graph::bfs(int src,int dest){
    list<int> queueu;
    for(Node& node : nodes){
        node.visited=false;
        node.pred=-1;
    }
    nodes[src].visited=true;
    queueu.push_back(src);
    while(!queueu.empty()){
        int u =queueu.front();
        queueu.pop_front();
        for(auto &edge :nodes[u].adj){
            int d =edge.dest;
            if(!nodes[d].visited){
                nodes[d].visited=true;
                nodes[d].pred=u;
                queueu.push_back(d);
                if(d==dest) return true;
            }
        }
    }
    return false;
}
