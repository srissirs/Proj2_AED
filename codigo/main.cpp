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
    list<list<int>> paths = graph.bestPathLessLineChange(graph.getMap()["CMV"],graph.getMap()["COB3"]);

    for (auto i:paths){
        for(auto k:i){
           cout<<graph.getNodes()[k].code<<endl;
        }
        cout<<endl<<endl;
    }

    return 0;

}
