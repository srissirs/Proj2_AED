#include <iostream>
#include "scr/Graph.h"
#include "scr/readFiles.h"
#include "scr/auxiliarFunctions.h"
#include <map>

using namespace std;

int main() {
    Graph graph = Graph(2787,true);
    readDataStops(graph);
    addLines(graph);
    uniteNearStops(graph);
    int aa = graph.getMap()["HSJ12"], b = graph.getMap()["SAL4"];
    list<Node> list1 = graph.dijkstra_pathNodes(aa, b);



     printPath( list1);
     /*
      int pos = graph.getMap()["ESED1"];

    displayMenu();

    graph.bfs(graph.getMap()["ETRP2"],graph.getMap()["PDC"]);
    printPath(graph,graph.getMap()["PDC"]);



   for(auto p:graph.getNodes().operator[](pos).adj){
       cout<<p.line<<endl<<graph.getNodes()[p.src].code<<endl<<graph.getNodes()[p.dest].code<<endl<<p.weight<<endl<<endl;

   }
*/
    return 0;

}
