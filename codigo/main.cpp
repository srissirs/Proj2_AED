#include <iostream>
#include "scr/Graph.h"
#include "scr/readFiles.h"
#include "scr/auxiliarFunctions.h"
#include "scr/menu.h"
#include <map>

using namespace std;

int main() {
    Graph graph = Graph(2787,true);
    readDataStops(graph);
    addLines(graph);
    uniteNearStops(graph);

  
  /*
    displayMenu();
    vector<pair<int,list<int>>> paths = graph.bestPathLessLineChange(graph.getMap()["ESED2"],graph.getMap()["SAL4"]);

    for (auto i:paths){
        cout<<endl<< "NUMBER OF LINE GHANGE " <<i.first<<endl;
        for(auto k:i.second){
           cout<<graph.getNodes()[k].code<<endl;
        }
        cout<<endl<<endl;
        */

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
        string stopCodeSrc=chooseStopByCoordinates(graph,srcLatitude,srcLongitude);
        cout<<endl;

        cout<<"-------DEST COORDINATES------"<<endl;
        double DestLatitude;
        double DestLongitude;
        cout<<"Destination Latitude:";
        cin>>DestLatitude;
        cout<<"Destination Longitude:";
        cin>>DestLongitude;
        cout<<endl;
        string stopCodeDest=chooseStopByCoordinates(graph,DestLatitude,DestLongitude);
    }
    int chosenMethod;
    cout<<endl;
    displaysMethods();
    cin>>chosenMethod;
    int scr=graph.getMap()[stopCodeSrc];
    int dest=graph.getMap()[stopCodeDest];
    if(chosenMethod==0){}
    if(chosenMethod==1){}
    if(chosenMethod==2){}
    if(chosenMethod==3){}

    return 0;

}
