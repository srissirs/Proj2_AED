#ifndef PROJ2AED_AUXILIARFUNCTIONS_H
#define PROJ2AED_AUXILIARFUNCTIONS_H

#include "Graph.h"
#include "menu.h"
#include <cmath>

using namespace std;

/**
 * @brief Returns the distance in kilometers from two coordinates
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Unites all near nodes in the graph with distance smaller than dist
 * @param graph
 * @param distance
 */
void uniteNearStops(Graph& graph,double distance);

/**
 * @brief Prints the path showing the number of stops and price
 * @param choice
 * @param weigh
 * @param list1
 */
void printPath(int choice, int weigh, list<Node> list1);

/**
 * @brief Shows the nearest 5 stops to the latitude and longitude and returns the code of the stop chosen by the user or 0 if they want to go back
 * @param graph
 * @param latitude
 * @param longitude
 */
string chooseStopByCoordinates(Graph graph, double latitude, double longitude);

/**
 * @brief Checks input
 * @param var
 * @param message
 */
void checkInput(double& var, string message);

/**
 * @brief Checks input
 * @param var
 * @param message
 */
void checkInput(string & var, string message);

/**
 * @brief Checks input
 * @param var
 */
void checkInput(int & var);

#endif //PROJ2AED_AUXILIARFUNCTIONS_H
