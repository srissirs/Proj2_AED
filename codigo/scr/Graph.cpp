#include "Graph.h"
#define INF (INT_MAX/2)


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
    dijkstra(a);
    if (nodes[b].dist == INT_MAX) return -1;
    return nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
    list<int> path;
    if (nodes[b].dist == INT_MAX) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}




void Graph::dijkstra(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v,INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        for (auto edge: nodes[u].adj) {
            int v = edge.dest;
            int w = edge.weight;
            if (!nodes[v].visited && (nodes[u].dist + w )< nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }

}





