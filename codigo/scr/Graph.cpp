#include "Graph.h"
#include <climits>
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

int Graph::getWeight(int src,int dest,string line){
    if(nodes[src].line==line)  return 0;
    else return 1;
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------


// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].dist == INT_MAX) return -1;
    return nodes[b].dist;
}

list<list<int>> Graph::bestPathLessLineChange(int src, int dest){
    vector<pair<int,list<int>>> v;
    for (auto edge: nodes[src].adj){
        nodes[src].line = edge.line;
        v.push_back({dijkstra_distance(src,dest), dijkstra_path(src,dest)});
    }
    int minWeight= INF;
    list<list<int>> paths;
    for (auto p :v){
        if(p.first<minWeight)
            minWeight = p.first;
    }
    for (auto p :v){
        if(p.first==minWeight)
            paths.push_back(p.second);
    }
    return paths;
}
// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
    list<int> path;
    if(nodes[b].dist==INF) return path;
    path.push_back(b);
    int v = b;
    while (v!=a){
        v=nodes[v].pred;
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

int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}
/*
void Graph::dijkstra(int src) {
    MinHeap<int,int> q(n,-1);
    for (int v=0; v<n; v++){
        nodes[v].dist =INF;
        q.insert(v,INF);
        nodes[v].visited = false;
    }
    nodes[src].dist = 0;
    q.decreaseKey(src,0);
    nodes[src].pred = src;
    while (q.getSize()>0){
        int u = q.removeMin();
        nodes[u].visited= true;
        for (auto  edge:nodes[u].adj){
            int dest = edge.dest;
            int weigh = getWeight(u,dest,edge.line);
            if (!nodes[dest].visited && nodes[u].dist + weigh < nodes[dest].dist){
                nodes[dest].dist = nodes[dest].dist + weigh;
                q.decreaseKey(dest, nodes[dest].dist);
                nodes[dest].line = edge.line;
                nodes[dest].pred = u;
            }
        }
    }
   

}

*/
