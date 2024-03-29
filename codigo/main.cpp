#include <iostream>
#include "Graph.h"
#include "readFiles.h"
#include <map>

using namespace std;

void run(Graph graph);

int main() {
    Graph graph = Graph(0,true);
    Graph graphN = Graph(0,true);
    Graph graphD = Graph(0,true);
    readDataStops(graph);
    addLines(graph, graphN, graphD);
    int menuOption;
    displayTimeOfTheDay();
    cin>>menuOption;
    double walkingDistance;
    cout << "What's your max walking distance (km) :";
    cin>>walkingDistance;
    checkInput(walkingDistance,"What's your max walking distance (km) :");
    // Chooses the graph
    if(menuOption==0){
        uniteNearStops(graph, walkingDistance);
        run(graph);}
    else if(menuOption==1){
        uniteNearStops(graphD,walkingDistance);
        run(graphD);
    }
    else if(menuOption==2){
        uniteNearStops(graphN,walkingDistance);
        run(graphN);
    }
    return 0;
}


void run(Graph graph){
    int menuOption=-1;
    string stopCodeSrc;
    string stopCodeDest;
    while (menuOption != 0) {
        displayMainMenu();
        cin>>menuOption;
        while (cin.peek() != '\n' or menuOption<0 or menuOption>2) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Error! Try again\n";
            displayMainMenu();
            cin>>menuOption;
        }
        // By stop code
        if(menuOption==1){
            cout<<"---------Stops Codes---------"<<endl;
            cout<<"Source stop code ( 0 to go back):";
            cin>>stopCodeSrc;
            checkInput(stopCodeSrc,"Source stop code ( 0 to go back):");
            while (graph.getMap().count(stopCodeSrc) == 0 and stopCodeSrc != "0") {
                cout << "Stop code is nonexistent\nSource stop code ( 0 to go back):";
                cin >> stopCodeSrc;
                checkInput(stopCodeSrc,"Source stop code ( 0 to go back):");
            }
            if (stopCodeSrc == "0") continue;

            cout<<"Destination stop code ( 0 to go back):";
            cin>>stopCodeDest;
            checkInput(stopCodeDest,"Destination stop code ( 0 to go back):");

            while (graph.getMap().count(stopCodeDest) == 0 and stopCodeDest!="0") {
                cout << "Stop code is nonexistent\nSource stop code ( 0 to go back):";
                cin >> stopCodeDest;
                checkInput(stopCodeDest,"Destination stop code ( 0 to go back):");
            }
            if (stopCodeDest == "0") continue;
        // Latitude and longitude
        }else if(menuOption==2){
            double srcLatitude;
            double srcLongitude;
            cout<<"--------SRC COORDINATES-------"<<endl;
            cout<<"Source Latitude:";
            cin>>srcLatitude;
            checkInput(srcLatitude,"Source Latitude:");

            cout<<"Source Longitude:";
            cin>>srcLongitude;
            checkInput(srcLongitude,"Source Longitude:");

            stopCodeSrc=chooseStopByCoordinates(graph,srcLatitude,srcLongitude);
            if (stopCodeSrc == "0") continue;

            cout<<endl;
            cout<<"-------DEST COORDINATES------"<<endl;
            double destLatitude;
            double destLongitude;
            cout<<"Destination Latitude:";
            cin>>destLatitude;
            checkInput(destLatitude,"Destination Latitude:");

            cout<<"Destination Longitude:";
            cin>>destLongitude;
            checkInput(destLongitude,"Destination Longitude:");

            cout<<endl;
            stopCodeDest=chooseStopByCoordinates(graph,destLatitude,destLongitude);
            if (stopCodeDest == "0") continue;

        }

        int chosenMethod=-1;
        while (chosenMethod != 0 and menuOption!=0) {
            cout<<endl;

            displaysMethods();
            cin>>chosenMethod;
            checkInput(chosenMethod);

            int src = graph.getMap()[stopCodeSrc];
            int dest=graph.getMap()[stopCodeDest];
            // Cheaper route
            if(chosenMethod==1){
                list<Node> list = graph.dijkstra_pathNodes(src, dest,3);
                int weight = graph.dijkstra_distance(src,dest,3);
                printPath(1,weight,list);
            }
            // Path with less change of line
            else if(chosenMethod==2){
                pair<int,list<Node>> path = graph.bestPathLessLineChange(src, dest);
                printPath(2,path.first,path.second);
            }
            // Path with less bus stops
            else if(chosenMethod==3){
                list<Node> list = graph.bfs_path(src, dest);
                printPath(3,list.size(),list);
            }
            // Path with less distance
            else if(chosenMethod==4){
                list<Node> list = graph.dijkstra_pathNodes(src, dest,2);
                int weight = graph.dijkstra_distance(src,dest,2);
                printPath(4,weight,list);
            }
        }
    }
}