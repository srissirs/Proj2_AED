#include <iostream>
#include "scr/Graph.h"
#include "scr/readFiles.h"
#include "scr/menu.h"
#include <map>

using namespace std;

void run(Graph graph);

int main() {
    Graph graph = Graph(0,true);
    Graph graphN = Graph(0,true);
    Graph graphD = Graph(0,true);
    readDataStops(graph);
    addLines(graph, graphN, graphD);
    uniteNearStops(graph);
    uniteNearStops(graphN);
    uniteNearStops(graphD);
    Graph chosenGraph(0,true);
    int menuOption;

    displayTimeOfTheDay();
    cin>>menuOption;
    if(menuOption==0) run(graph);
    else if(menuOption==1) run(graphD);
    else if(menuOption==2) run(graphN);

    return 0;
}


void run(Graph graph){
    int menuOption;
    string stopCodeSrc;
    string stopCodeDest;
    displayMainMenu();
    cin>>menuOption;

    if(menuOption==0){
        cout<<"---------Stops Codes---------"<<endl;
        cout<<"Source stop code:";
        cin>>stopCodeSrc;
        cout<<"Destination stop code:";
        cin>>stopCodeDest;

    }
    else if(menuOption==1){
        double srcLatitude;
        double srcLongitude;
        cout<<"--------SRC COORDINATES-------"<<endl;
        cout<<"Source Latitude:";
        cin>>srcLatitude;
        cout<<"Source Longitude:";
        cin>>srcLongitude;
        cout<<endl;
        stopCodeSrc=chooseStopByCoordinates(graph,srcLatitude,srcLongitude);
        cout<<endl;

        cout<<"-------DEST COORDINATES------"<<endl;
        double DestLatitude;
        double DestLongitude;
        cout<<"Destination Latitude:";
        cin>>DestLatitude;
        cout<<"Destination Longitude:";
        cin>>DestLongitude;
        cout<<endl;
        stopCodeDest=chooseStopByCoordinates(graph,DestLatitude,DestLongitude);
    }
    int chosenMethod;
    cout<<endl;
    displaysMethods();
    cin>>chosenMethod;
    int src = graph.getMap()[stopCodeSrc];
    int dest=graph.getMap()[stopCodeDest];
    if(chosenMethod==0){
        list<Node> list = graph.dijkstra_pathNodes(src, dest,3);
        printPath(list);
    }
    if(chosenMethod==1){
        vector<pair<int,list<Node>>> paths = graph.bestPathLessLineChange(src, dest);
        list<Node> list;
        for(int i=0;i<paths.size();i++){
            list = paths[i].second;
            list.front().line = "";
            cout<<endl<<"------OPTION "<<i+1<<"-------"<<endl;
            printPath(list);
        }
    }
    if(chosenMethod==2){
        list<Node> list = graph.bfs_path(src, dest);
        printPath(list);
    }
    if(chosenMethod==3){
        list<Node> list = graph.dijkstra_pathNodes(src, dest,2);
        printPath(list);
    }
}
