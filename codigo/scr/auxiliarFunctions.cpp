#include <algorithm>
#include <iomanip>
#include "auxiliarFunctions.h"


using namespace std;

/**
 * @brief Returns the distance in kilometers from two coordinates
 */
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


/**
 * @brief Unites all near nodes in the graph with distance smaller than dist
 */
void uniteNearStops(Graph& graph, double dis) {
    vector<Node> nodes = graph.getNodes();
    // Searches all nodes
    for (int i=0; i<nodes.size()-1;i++){
        for (int j=i+1; j< nodes.size();j++ ){
            double distance = haversine(nodes[i].latitude,nodes[i].longitude,nodes[j].latitude,nodes[j].longitude);
            /// If the stops have a distance smaller than dist and doesn't already exist a edge that connects them
            if(distance<=dis and !graph.exists(i,j,distance)){
                graph.addEdge(i,j,distance,"walking");
            }else if(distance<=dis and !graph.exists(j,i,distance)){
                graph.addEdge(j,i,distance,"walking");
            }
        }
    }
}


/**
 * @brief Prints the path showing the number of stops and price
 */
void printPath(int choice, int weight, list<Node> list1) {
    vector<double> prices={1.25,1.25,1.6,2.00,2.4,2.85,3.25,3.65,4.05};
    list<string> zones;
    if (list1.empty()) {
        cout << "The two stops can't be connected";
    }else{
        switch (choice) {
            case 1:
                cout << "You change zones "<< weight<< " time(s)";
                break;
            case 2:
                cout << "You change lines "<< weight << " time(s)";
                break;
            case 3:
                cout << "There will be " << weight << " stops.";
                break;
            case 4:
                cout << "Total distance traveled is "<< weight << " km";
                break;
        }
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

/**
 * @brief Shows the nearest 5 stops to the latitude and longitude and returns the code of the stop chosen by the user or 0 if they want to go back
 */
string chooseStopByCoordinates(Graph graph, double latitude, double longitude){
    vector<Node> nodes = graph.getNodes();
    vector<pair<double,Node>> distances;
    // Goes through all the nodes and adds them to a vector of pairs with the distance of the stop and the node
    for (int i=0; i<graph.getNodes().size();i++) {
        Node node=graph.getNodes()[i];

        distances.push_back({haversine(latitude,longitude,node.latitude,node.longitude),node});
    }
    // Sorts by distance
    std::sort(distances.begin(), distances.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    cout<<"Closest bus stops:"<<endl;
    // Prints the information of the closest bus stops
    for(int j=0;j<5;j++){
            cout<<"["<<j+1<<"]"<<" "<<distances[j].second.code<<" - "<< distances[j].second.stopName << " " <<distances[j].first<<"Km"<<endl;
    }
    cout << "[0] Go back\n";
    int pos;
    string busStopCode;
    cout<<endl<<"Choose one of the bus stops:";
    cin>>pos;
    // Checks if the pos is in the right format
    while (cin.peek() != '\n' or pos < 0 or pos > 5) {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Error! Try again\n";
        cout<<endl<<"Choose one of the bus stops:";
        cin>>pos;
    }
    // In case the user wants to go back
    if (pos == 0) {
        return "0";
    }
    return distances[pos-1].second.code;
}

/**
 * @brief Checks input
 */
void checkInput(double & var, string message){
    while (cin.peek() != '\n') {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Error! Try again\n";
        cout<<message;
        cin>>var;
    }
}

/**
 * @brief Checks input
 */
void checkInput(string & var, string message){
    while (cin.peek() != '\n') {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Error! Try again\n";
        cout<<message;
        cin>>var;
    }
}

/**
 * @brief Checks input
 */
void checkInput(int & var){
    while (cin.peek() != '\n' or var > 4) {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Error! Try again\n";
        displaysMethods();
        cin >> var;
    }
}



