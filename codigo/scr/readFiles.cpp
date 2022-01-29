#include "readFiles.h"
#include <fstream>

void readDataStops(Graph& graph){
    map<string, int> mapNodes = graph.getMap();
    ifstream stops("../codigo/dataset/stops.csv");
    string firstLine;
    getline(stops,firstLine);
    double latitude;double longitude;
    string zone;
    string stopName;
    list<string> line;
    string code;
    vector<Node> nodes;
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
    graph.setMap(mapNodes);
    graph.setNodes(nodes);
    stops.close();
}

void addLines(Graph& graph,Graph& graphN,Graph& graphD){
    ifstream lines("../codigo/dataset/lines.csv");
    string firstLine;
    getline(lines,firstLine);
    string beginDocDir= "../codigo/dataset/line_";
    string lineCode;
    map<string ,int> mapNodes = graph.getMap();
    map<string, int> mapNodesD;
    map<string ,int> mapNodesN;
    vector<Node> nodes = graph.getNodes();
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
        int pos1;
        string oldStopCode;

        for (int i=0; i<numberOfStops_0;i++){
            Node node;
            string stopCode;
            line_0 >> stopCode;
            line_0.ignore(1);
            int pos = mapNodes[stopCode];
            if(lineName.find("M")!=string::npos){
                if (graphN.getMap().count(nodes[pos].code) <= 0) {
                    mapNodesN[nodes[pos].code] = graphN.getNodes().size();
                    graphN.addNode(nodes[pos]);
                    graphN.setMap(mapNodesN);
                }
            }
            else {
                if (graphD.getMap().count(nodes[pos].code)<=0) {
                    mapNodesD[nodes[pos].code] = graphD.getNodes().size();
                    graphD.addNode(nodes[pos]);
                    graphD.setMap(mapNodesD);
                }

            }
            if(i>0){
                double weight = haversine(nodes[pos1].latitude,nodes[pos1].longitude,nodes[pos].latitude,nodes[pos].longitude);
                graph.addEdge(pos1,pos,weight,lineName);

                if(lineName.find("M")!=string::npos){
                    graphN.addEdge(graphN.getMap()[oldStopCode],graphN.getMap()[stopCode],weight,lineName);

                }
                else {
                    graphD.addEdge(graphD.getMap()[oldStopCode],graphD.getMap()[stopCode],weight,lineName);
                }
            }
            oldStopCode=stopCode;
            pos1=pos;
        }
        line_0.close();

        for (int i=0; i<numberOfStops_1;i++){
            Node node;
            string stopCode;
            line_1 >> stopCode;
            line_1.ignore(1);
            int pos = mapNodes[stopCode];
            if(lineName.find("M")!=string::npos){
                if (graphN.getMap().count(nodes[pos].code) <= 0) {
                    mapNodesN[nodes[pos].code] = graphN.getNodes().size();
                    graphN.addNode(nodes[pos]);
                    graphN.setMap(mapNodesN);
                }
            }
            else {
                if (graphD.getMap().count(nodes[pos].code)<=0) {
                    mapNodesD[nodes[pos].code] = graphD.getNodes().size();
                    graphD.addNode(nodes[pos]);
                    graphD.setMap(mapNodesD);
                }
            }


            if(i>0){
                double weight = haversine(nodes[pos1].latitude,nodes[pos1].longitude,nodes[pos].latitude,nodes[pos].longitude);
                graph.addEdge(pos1,pos,weight,lineName);
                if(lineName.find("M")!=string::npos){
                    graphN.addEdge(graphN.getMap()[oldStopCode],graphN.getMap()[stopCode],weight,lineName);
                }
                else {
                    graphD.addEdge(graphD.getMap()[oldStopCode],graphD.getMap()[stopCode],weight,lineName);
                }
            }
            oldStopCode=stopCode;
            pos1=pos;
        }
        line_1.close();
    }

}