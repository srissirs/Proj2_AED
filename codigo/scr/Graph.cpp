#include "Graph.h"
#include <climits>
#include <set>

#define INF (INT_MAX/2)


/**
     * @brief Constructor: nr nodes and direction (default: undirected)
     */
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

/**
    * @brief Add edge from source to destination with a certain weight
    */
void Graph::addEdge(int src, int dest, double weight,string line) {
    if (src<0 || src>n || dest<0 || dest>n) return;
    if(exists(src,dest, weight,line)) return;
    nodes[src].adj.push_back({src,dest, weight,line});
    if (!hasDir) nodes[dest].adj.push_back({src,dest, weight,line});
}
/**
 * @brief Add a node to the map
 */
void Graph::addNode(Node node){
    nodes.push_back(node);
    mapNodes[node.code]=nodes.size()-1;
    n++;
}

/**
 *     @brief Checks if the edge with the parameters exists in the graph
 */
bool Graph::exists(int src, int dest, double weight,string line){
    for( auto edge: nodes[src].adj){
        if (edge.weight==weight and edge.dest == dest and edge.line==line)
            return true;
    }
    return false;
}
/**
 *     @brief Checks if the edge with the parameters exists in the graph
 */
bool Graph::exists(int src, int dest, double weight){
    for( auto edge: nodes[src].adj){
        if (edge.weight==weight and edge.dest == dest)
            return true;
    }
    return false;
}
/**
* @brief Returns the weight of the edge depending on the method of the user's choice
*/
double Graph::getWeight(int src,int choice,Edge edge){
    // If the choice is to get the path with less change in lines
    if(choice==1){
        if(nodes[src].line==edge.line)  return 0;
        else return 1;
    }
    // If the choice is to get the path with less total distance
    else if(choice==2){
        return edge.weight;
    }
    // If the choice is to get the cheaper path, so it will prioritize going in the same zone
    else if(choice == 3){
        if(nodes[src].zone==nodes[edge.dest].zone) return 0;
        else return 1;
    }
    return -1;
}

/**
* @brief Returns the distance of the nodes in the Dijkstra algorithm on the method of the user's choice
*/
int Graph::dijkstra_distance(int a, int b,int choice) {
    dijkstra(a,choice);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

/**
* @brief Returns a vector of pairs of int with the distance of the scr to dest in the dijkstra algorithm and the path from scr to dest
* The function returns a vector of pairs because the scr can start in different lines
  */
vector<pair<int,list<Node>>> Graph::bestPathLessLineChange(int src, int dest){
    set<string> lineCodes;
    vector<pair<int,list<Node>>> v;
    // Adds all lines to the linecodes set from the edges of the adj vector of the node with the position src in the vector nodes
    for (auto edge: nodes[src].adj)
        lineCodes.insert(edge.line);
    // For each line is does the Dijkstra with the choice 1 (prioritizing not changing line) and adds he distance and the path to the v vector
    for (auto line: lineCodes){
        nodes[src].line = line;
        v.push_back({dijkstra_distance(src,dest,1), dijkstra_pathNodes(src,dest,1)});
    }
    int minWeight= INF;
    vector<pair<int,list<Node>>> paths;
    // Checks the minimum distance of the vector v
    for (auto p :v){
        if(p.first<minWeight)
            minWeight = p.first;
    }
    // Adds the paths that have minimum distance to the vector paths
    for (auto p :v){
        if(p.first==minWeight)
            paths.push_back({p.first,p.second});
    }
    return paths;
}

/**
* @brief Returns the path of nodes from "src" stop to "dest" stop with the method of search bfs
*/

list<Node> Graph::bfs_path(int src, int dest) {
    list<Node> path;
    if (bfs(src, dest)) {
        // The scr node as pred -1
        while(nodes[dest].pred!=-1){
            path.push_front(nodes[dest]);
            dest=nodes[dest].pred;
        }
        // Adds the first node
        path.push_front(nodes[dest]);
    }

    return path;
}



/**
* @brief Returns the path of nodes from "a" stop to "b" stop with the method of search "choice" in the Dijkstra algorithm
*/
list<Node> Graph::dijkstra_pathNodes(int a, int b,int choice) {
    list<Node> path;
    dijkstra(a, choice);
    if(nodes[b].dist==INF) return path;
    path.push_front(nodes[b]);
    int v = b;
    while (v!=a){
        v=nodes[v].pred;
        path.push_front(nodes[v]);
    }
    return path;
}



/**
 * @brief The algorithm of Dijkstra that takes the node where we start and the choice of search method to use (Complexity: O(|edge| log(v)) )
 */
void Graph::dijkstra(int s,int choice) {
    MinHeap<int, int> q(n, -1);
    // Sets everything
    for (int v=0; v<n; v++) {
        nodes[v].dist = INF;
        q.insert(v,INF);
        nodes[v].visited = false;
        nodes[v].line = "";
   }
    // Sets source
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        for (auto edge: nodes[u].adj) {
            double v = edge.dest;
            // Uses getWight to get the right weight depending on the user's choice in "choice"
            double w = getWeight(u, choice, edge);
            string l = edge.line;
            if (!nodes[v].visited && (nodes[u].dist + w )< nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
                nodes[v].line = l;
            }
        }
    }
}

/**
* @brief Implements the bfs method of search to connect "src" stop and "dest" stop and returning true if the stops can be connected and false if not (Complexity O(|V| + |E|))
*/

bool Graph::bfs(int src,int dest){
    list<int> queue;
    // Sets the nodes for the algorithm
    for(Node& node : nodes){
        node.visited=false;
        node.pred=-1;
        node.line="";
    }
    // Sets the node src
    nodes[src].visited=true;
    queue.push_back(src);
    while(!queue.empty()){
        int u =queue.front();
        queue.pop_front();
        for(auto &edge :nodes[u].adj){
            int d =edge.dest;
            if(!nodes[d].visited){
                nodes[d].visited=true;
                nodes[d].pred=u;
                nodes[d].line = edge.line;
                queue.push_back(d);
                // If finds the destination
                if(d==dest) return true;
            }
        }
    }
    // Didn't find the destination
    return false;
}
