#ifndef PROJ2AED_READFILES_H
#define PROJ2AED_READFILES_H
#include "Graph.h"
#include <map>
#include "auxiliarFunctions.h"

vector<Node> readDataStops(map<string, int>& mapNodes);

void addLines(Graph& graph,map<string, int>& mapNodes);


#endif //PROJ2AED_READFILES_H
