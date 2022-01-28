#ifndef PROJ2AED_AUXILIARFUNCTIONS_H
#define PROJ2AED_AUXILIARFUNCTIONS_H

#include "Graph.h"
#include "menu.h"
#include <cmath>

using namespace std;

double haversine(double lat1, double lon1, double lat2, double lon2);

void uniteNearStops(Graph& graph,double distance);

void printPath(list<Node> list1);

void bestPathLessLineChange(int src, int dest);

string chooseStopByCoordinates(Graph graph, double latitude, double longitude);

void checkInput(double& var, string message);

void checkInput(string & var, string message);

void checkInput(int & var);

#endif //PROJ2AED_AUXILIARFUNCTIONS_H
