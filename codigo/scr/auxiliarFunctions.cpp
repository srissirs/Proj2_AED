#include <algorithm>
#include <iomanip>
#include "auxiliarFunctions.h"


double haversine(double lat1, double lon1,
                        double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void uniteNearStops(Graph& graph) {
    vector<Node> nodes = graph.getNodes();
    for (int i=0; i<nodes.size()-1;i++){
        for (int j=i+1; j< nodes.size();j++ ){
            double distance = haversine(nodes[i].latitude,nodes[i].longitude,nodes[j].latitude,nodes[j].longitude);
            if(distance<=0.150 and !graph.exists(i,j,distance)){
                graph.addEdge(i,j,distance,"walking");
            }

            else if(distance<=0.150 and !graph.exists(j,i,distance)){
                graph.addEdge(j,i,distance,"walking");
            }
        }
    }
}





void printPath(list<Node> list1) {
    vector<double> prices={1.25,1.6,2.00,2.4,2.85,3.25,3.65,4.05};
    list<string> zones;
    if (list1.empty()) {
        cout << "The two stops can't be connected";
    }else{
        cout << "There will be " << list1.size() << " stops.";
        Node node1;
        Node node2 = list1.front();
        zones.push_front(node2.zone);
        while (list1.size() != 1) {
            node1 = node2;
            list1.pop_front();
            node2 = list1.front();
            if (find(zones.begin(), zones.end(), node2.zone) == zones.end()) {
                zones.push_front(node2.zone);
            }
            if (node2.line == "walking") {
                cout << endl << endl << "Walk from " << node1.code << "(" << node1.zone << ")" << " to " << node2.code
                     << "(" << node2.zone << ")";
            }else if (node2.line != node1.line) {
                        cout << endl << endl << "Take the " << node2.line << " line" << endl;
                cout << node1.code << "(" << node1.zone << ")" << "->" << node2.code << "(" << node2.zone << ")";
                }else{
                cout << "->" << node2.code << "(" << node2.zone << ")";
                }
             }
        if (find(zones.begin(), zones.end(), "walking") == zones.end()) {
            cout << "\nThe total price will be " << prices[zones.size() - 1]<<" euros";
        }else{
            cout << "\nThe total price will be " << prices[zones.size()]<<" euros";
        }
        }
    }


string chooseStopByCoordinates(Graph graph, double latitude, double longitude){
    vector<Node> nodes = graph.getNodes();
    vector<pair<double,Node>> distances;
    for (int i=0; i<graph.getNodes().size();i++) {
        Node node=graph.getNodes()[i];
        distances.push_back({haversine(latitude,longitude,node.latitude,node.longitude),node});
    }

    std::sort(distances.begin(), distances.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    cout<<"Closest bus stops:"<<endl;
    for(int j=0;j<5;j++){
        cout<<"["<<j+1<<"]"<<" "<<distances[j].second.code<<" - "<< distances[j].second.stopName << " " <<distances[j].first<<"Km"<<endl;
    }
    cout << "[0] Go back\n";
    int pos;
    string busStopCode;
    cout<<endl<<"Choose one of the bus stops:";
    cin>>pos;
    if (cin.peek() != '\n' or pos < 0 or pos > 5) {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Error! Try again\n";
        cout<<endl<<"Choose one of the bus stops:";
        cin>>pos;
    }
    if (pos == 0) {
        return "0";
    }
    return distances[pos-1].second.code;
}



