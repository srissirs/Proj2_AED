#ifndef PROJ2AED_AUXILIARFUNCTIONS_H
#define PROJ2AED_AUXILIARFUNCTIONS_H

#include "Graph.h"
#include <cmath>

using namespace std;


double haversine(double lat1, double lon1, double lat2, double lon2);

void uniteNearStops(Graph& graph);


void printPath(list<Node> list1);


void bestPathLessLineChange(int src, int dest);

string chooseStopByCoordinates(Graph graph, double latitude, double longitude);

#endif //PROJ2AED_AUXILIARFUNCTIONS_H
