#include <iostream>
#include "scr/Graph.h"
#include "scr/readFiles.h"
#include <map>

using namespace std;

int main() {
    map<string, int> mapNodes;
    vector<Node> nodes = readDataStops(mapNodes);
    Graph graph = Graph(nodes.size(),false);
    graph.setNodes(nodes);
    addLines(graph,mapNodes);
    return 0;

}
