#include <iostream>
#include "scr/Graph.h"
#include "scr/readFiles.h"
#include "scr/auxiliarFunctions.h"
#include <map>

using namespace std;

int main() {
    Graph graph = Graph(0,true);
    readDataStops(graph);
    addLines(graph);
    uniteNearStops(graph);
    displayMenu();

    graph.bfs(graph.getMap()["ETRP2"],graph.getMap()["PDC"]);
    printPath(graph,graph.getMap()["PDC"]);



    return 0;

}
