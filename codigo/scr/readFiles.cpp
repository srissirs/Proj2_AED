#include "readFiles.h"
#include <fstream>
#include "Graph.h"
#include <map>


vector<Node> readDataStops(){
    ifstream stops("../codigo/dataset/stops.csv");
    ifstream lines("../codigo/dataset/lines.csv");
    string firstLine;
    getline(stops,firstLine);
    double latitude;double longitude;
    int dir;       ///Direction in a line
    string zone;
    string stopName;
    list<string> line;
    string code;
    vector<Node> nodes;
    map<string, int> mapNodes;
    int vectorPos=0;
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
        mapNodes[code]= vectorPos;
        vectorPos++;
    }
    getline(lines,firstLine);
    string beginDocDir= "../codigo/dataset/line_";
    string lineCode;
    while(!lines.eof()){
        getline(lines,lineCode,',');
        string lineName;
        getline(lines,lineName);
        string docDir_1 = beginDocDir + lineCode + "_1.csv";
        string docDir_0 = beginDocDir + lineCode + "_0.csv";
        ifstream line_0(docDir_0);
        ifstream line_1(docDir_1);
        int numberOfStops_0,numberOfStops_1;
        line_0 >> numberOfStops_0;
        line_1 >> numberOfStops_1;
        line_0.ignore(1);
        line_1.ignore(1);
        for (int i=0; i<numberOfStops_0;i++){
            Node node;
            string stopCode;
            line_0 >> stopCode;
            line_0.ignore(1);
            int pos = mapNodes[stopCode];
            node = nodes[pos];
            node.lines.push_back({lineCode,0,i});
            nodes[pos] = node;
        }
        line_0.close();
        for (int i=0; i<numberOfStops_1;i++){
            Node node;
            string stopCode;
            line_1 >> stopCode;
            line_1.ignore(1);
            int pos = mapNodes[stopCode];
            node = nodes[pos];
            node.lines.push_back({lineCode,1,i});
            nodes[pos] = node;
        }
        line_1.close();
    }
    /*
    cout << nodes[1].code +" " + nodes[0].stopName + " ";
    cout << nodes[100].dir<<endl;
    stops.close();
    for(auto p:nodes[1].lines){
        cout<<get<0>(p)<<endl;
        cout<<get<1>(p)<<endl;
        cout<<get<2>(p)<<endl;
    }
    cout<< nodes.size();
     */
    return nodes;
}