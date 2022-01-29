#include "readFiles.h"
#include <fstream>

/**
 * @brief reads all stops and their data and puts them into nodes
 * @param graph
 */
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
    // Until stops is empty
    while(!stops.eof()){
        Node node;
        // Gets code
        getline(stops,code,',');
        // Gets stopName
        getline(stops,stopName,',');
        // Gets zone
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
        // Adds node
        nodes.push_back(node);
        // Adds code-vectorPos to the map
        mapNodes[code]= vectorPos;
        vectorPos++;
    }
    // Sets map
    graph.setMap(mapNodes);
    // Sets nodes
    graph.setNodes(nodes);
    // Closes file
    stops.close();
}

/**
 * @brief for each line, reads its stops and adds the edges to the nodes, taking the sequence of the stops into account
 */
void addLines(Graph& graph,Graph& graphN,Graph& graphD){
    vector<Node> n;
    ifstream lines("../codigo/dataset/lines.csv");
    string firstLine;
    getline(lines,firstLine);
    string beginDocDir= "../codigo/dataset/line_";
    string lineCode;
    int PosN = 0, PosD = 0;
    map<string ,int> mapNodes = graph.getMap();
    map<string, int> mapNodesD;
    map<string ,int> mapNodesN;
    vector<Node> nodes = graph.getNodes();
    // Until lines is empty
    while(!lines.eof()){
        getline(lines,lineCode,',');
        string lineName;
        getline(lines,lineName);
        // Gets the file of lines in the direction 1
        string docDir_1 = beginDocDir + lineCode + "_1.csv";
        /// Gets the file of lines in the direction 0
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
        // For all stops in the line in the direction 0
        for (int i=0; i<numberOfStops_0;i++){
            Node node;
            string stopCode;
            line_0 >> stopCode;
            line_0.ignore(1);
            int pos = mapNodes[stopCode];
            // Checks if the stop is in a Day line
            if(lineName.find("M")!=string::npos){
                if (graphN.getMap().count(nodes[pos].code) <= 0) {
                    mapNodesN[nodes[pos].code] = PosN;
                    PosN++;
                    graphN.addNode(nodes[pos]);
                    // Sets maps
                    graphN.setMap(mapNodesN);
                }
            }
            // Checks if the stop is in a Night line
            else {
                if (graphD.getMap().count(nodes[pos].code)<=0) {
                    mapNodesD[nodes[pos].code] = PosD;
                    PosD++;
                    graphD.addNode(nodes[pos]);
                    // Sets maps
                    graphD.setMap(mapNodesD);
                }

            }
            if(i>0){
                // Gets weight between pos1 and pos
                double weight = haversine(nodes[pos1].latitude,nodes[pos1].longitude,nodes[pos].latitude,nodes[pos].longitude);
                graph.addEdge(pos1,pos,weight,lineName);
                // Checks if it is a night line
                if(lineName.find("M")!=string::npos){
                    // Adds the edge
                    graphN.addEdge(graphN.getMap()[oldStopCode],graphN.getMap()[stopCode],weight,lineName);

                }
                else {
                    // Adds the edge
                    graphD.addEdge(graphD.getMap()[oldStopCode],graphD.getMap()[stopCode],weight,lineName);
                }
            }
            oldStopCode=stopCode;
            pos1=pos;
        }
        // Closes file
        line_0.close();
        // For all stops in the line in the direction 1
        for (int i=0; i<numberOfStops_1;i++){
            Node node;
            string stopCode;
            line_1 >> stopCode;
            line_1.ignore(1);
            int pos = mapNodes[stopCode];
            if(lineName.find("M")!=string::npos){
                if (graphN.getMap().count(nodes[pos].code) <= 0) {
                    mapNodesN[nodes[pos].code] = PosN;
                    PosN++;
                    graphN.addNode(nodes[pos]);
                    // Sets maps
                    graphN.setMap(mapNodesN);
                }
            }
            else {
                if (graphD.getMap().count(nodes[pos].code)<=0) {
                    mapNodesD[nodes[pos].code] = PosD;
                    PosD++;
                    graphD.addNode(nodes[pos]);
                    // Sets maps
                    graphD.setMap(mapNodesD);
                }
            }


            if(i>0){
                // Gets weight between pos1 and pos
                double weight = haversine(nodes[pos1].latitude,nodes[pos1].longitude,nodes[pos].latitude,nodes[pos].longitude);
                graph.addEdge(pos1,pos,weight,lineName);
                // Checks if it is a night line
                if(lineName.find("M")!=string::npos){
                    // Adds the edge
                    graphN.addEdge(graphN.getMap()[oldStopCode],graphN.getMap()[stopCode],weight,lineName);
                }
                else {
                    // Adds the edge
                    graphD.addEdge(graphD.getMap()[oldStopCode],graphD.getMap()[stopCode],weight,lineName);
                }
            }
            oldStopCode=stopCode;
            pos1=pos;
        }
        // Closes file
        line_1.close();
    }


}