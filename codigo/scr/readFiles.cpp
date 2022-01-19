#include "readFiles.h"
#include <fstream>
#include "Graph.h"


vector<Node> readDataStops(){
    ifstream stops("../codigo/dataset/stops.csv");
    ifstream lines("../codigo/dataset/lines.csv");
    string firstLine;
    getline(stops,firstLine);
    double latitude;double longitude;
    int dirPos; /// Position of the stop in a specific line
    int dir;       ///Direction in a line
    string zone;
    string stopName;
    list<string> line;
    string code;
    vector<Node> nodes;
    while(!stops.eof()){
        Node node;
        getline(stops,code,',');
        getline(stops,stopName,',');
        getline(stops,zone,',');
        stops>>latitude;
        stops.ignore(1);
        stops>>longitude;
        stops.ignore(1);
        node.code=code;
        node.stopName=stopName;
        node.zone=zone;
        node.latitude=latitude;
        node.longitude=longitude;
        nodes.push_back(node);
    }
    cout<<nodes.size();
    stops.close();
    return nodes;
}