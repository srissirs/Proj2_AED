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
            if(distance<=0.150){
                graph.addEdge(i,j,distance);
            }
        }
    }
}

void displayMenu() {
    cout << "MENU:"<<endl;
    cout << "[0] Exit" << endl;
}