#include <iostream>
#include "scr/Graph.h"
#include "scr/readFiles.h"
#include "scr/auxiliarFunctions.h"
#include <map>

using namespace std;

int main() {
    Graph graph = Graph(0,false);
    readDataStops(graph);
    addLines(graph);
    //uniteNearStops(graph);

    return 0;

}
