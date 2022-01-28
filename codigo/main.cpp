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
    int menuOption;

    displayTimeOfTheDay();
    cin>>menuOption;
    if(menuOption==0) run(graph);
    else if(menuOption==1) run(graphD);
    else if(menuOption==2) run(graphN);

    return 0;
}


void run(Graph graph){
    int menuOption=-1;
    string stopCodeSrc;
    string stopCodeDest;
    while (menuOption != 0) {
        displayMainMenu();
        cin>>menuOption;
        while (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Error! Try again\n";
            displayMainMenu();
            cin>>menuOption;
        }
        if (menuOption == 0) {
            break;
        }else if(menuOption==1){
            cout<<"---------Stops Codes---------"<<endl;
            cout<<"Source stop code ( 0 to go back):";
            cin>>stopCodeSrc;
            while (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                cout<<"Source stop code ( 0 to go back):";
                cin>>stopCodeSrc;
            }
            while (graph.getMap().count(stopCodeSrc) == 0 and stopCodeSrc != "0") {
                cout << "Stop code is nonexistent\nSource stop code:";
                cin >> stopCodeSrc;
            }
            if (stopCodeSrc == "0") {
                continue;
            }

            cout<<"Destination stop code ( 0 to go back):";
            cin>>stopCodeDest;
            while (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                cout<<"Destination stop code ( 0 to go back):";
                cin>>stopCodeDest;
            }
            while (graph.getMap().count(stopCodeDest) == 0 and stopCodeDest!="0") {
                cout << "Stop code is nonexistent\nSource stop code:";
                cin >> stopCodeDest;
            }
            if (stopCodeDest == "0") {
                continue;
            }
        }else if(menuOption==2){
            double srcLatitude;
            double srcLongitude;
            cout<<"--------SRC COORDINATES-------"<<endl;
            cout<<"Source Latitude:";
            cin>>srcLatitude;
            while (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                cout << "Source Latitude:";
                cin >> srcLatitude;
            }
            cout<<"Source Longitude:";
            cin>>srcLongitude;
            cout<<endl;
            while (cin.peek() != '\n') {

                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                cout << "Source Longitude:";
                cin >> srcLongitude;
            }
            stopCodeSrc=chooseStopByCoordinates(graph,srcLatitude,srcLongitude);
            if (stopCodeSrc == "0") {
                continue;
            }
            cout<<endl;

            cout<<"-------DEST COORDINATES------"<<endl;
            double DestLatitude;
            double DestLongitude;
            cout<<"Destination Latitude:";
            cin>>DestLatitude;
            while (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                cout<<"Destination Latitude:";
                cin>>DestLatitude;
            }
            cout<<"Destination Longitude:";
            cin>>DestLongitude;
            while (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                cout<<"Destination Longitude:";
                cin>>DestLongitude;
            }
            cout<<endl;
            stopCodeDest=chooseStopByCoordinates(graph,DestLatitude,DestLongitude);
            if (stopCodeDest == "0") {
                continue;
            }
        } else {
            cout << "Error! Try again\n";
            continue;
        }

        int chosenMethod=-1;
        while (chosenMethod != 0) {
            cout<<endl;
            displaysMethods();
            cin>>chosenMethod;
            while (cin.peek() != '\n' or chosenMethod > 4) {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Error! Try again\n";
                displaysMethods();
                cin >> chosenMethod;
            }
            int src = graph.getMap()[stopCodeSrc];
            int dest=graph.getMap()[stopCodeDest];
            if (chosenMethod == 0) {
                break;
            }
            if(chosenMethod==1){
                list<Node> list = graph.dijkstra_pathNodes(src, dest,3);
                printPath(list);
            }
            if(chosenMethod==2){
                vector<pair<int,list<Node>>> paths = graph.bestPathLessLineChange(src, dest);
                list<Node> list;
                for(int i=0;i<paths.size();i++){
                    list = paths[i].second;
                    list.front().line = "";
                    cout<<endl<<"------OPTION "<<i+1<<"-------"<<endl;
                    printPath(list);
                }
            }
            if(chosenMethod==3){
                list<Node> list = graph.bfs_path(src, dest);
                printPath(list);
            }
            if(chosenMethod==4){
                list<Node> list = graph.dijkstra_pathNodes(src, dest,2);
                printPath(list);
            }
        }

    }

}
