#ifndef PROJ2AED_READFILES_H
#define PROJ2AED_READFILES_H
#include "Graph.h"
#include <map>
#include "auxiliarFunctions.h"

/**
 * @brief reads all stops and their data and puts them into nodes
 * @param graph
 */
void readDataStops(Graph& graph);

/**
 * @brief for each line, reads its stops and adds the edges to the nodes, taking the sequence of the stops into account
 * @param graph
 * @param graphN
 * @param graphD
 */
void addLines(Graph& graph,Graph& graphN,Graph& graphD);


#endif //PROJ2AED_READFILES_H
