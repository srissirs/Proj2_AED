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
    vector<pair<int,list<int>>> paths = graph.bestPathLessLineChange(graph.getMap()["ESED2"],graph.getMap()["SAL4"]);

    for (auto i:paths){
        cout<<endl<< "NUMBER OF LINE GHANGE " <<i.first<<endl;
        for(auto k:i.second){
           cout<<graph.getNodes()[k].code<<endl;
        }
        cout<<endl<<endl;
    }

    return 0;

}
