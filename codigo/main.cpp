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
    int pos = graph.getMap()["ESED1"];

    for(auto p:graph.getNodes().operator[](pos).adj){
        cout<<p.line<<endl<<graph.getNodes()[p.src].code<<endl<<graph.getNodes()[p.dest].code<<endl<<p.weight<<endl<<endl;

    }

    return 0;

}
