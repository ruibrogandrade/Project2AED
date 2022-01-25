//
// Created by Rui on 24/01/2022.
//

#ifndef PROJETO2AED_GRAPHCREATE_H
#define PROJETO2AED_GRAPHCREATE_H

#include <iostream>
#include <fstream>
#include <map>
#include "graph.h"
#include <list>
#include <string>

class GraphCreate {
public:
    list<string> readLines();
    list<string> readStopsinLine(list<string> result, int i);
    map<string, int> StopsToMap();
    Graph CreateGraph(list<string> lines, map<string, int> StopsToInt, list<double> StopsLat, list<double> StopsLong);

    list<double> StopsLat();
    list<double> StopsLong();

    double haversine(list<double> StopsLong, list<double> StopsLat, int src, int dest);
};


#endif //PROJETO2AED_GRAPHCREATE_H
