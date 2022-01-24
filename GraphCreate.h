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
    void CreateGraph(list<string> result, map<string, int> StopsToInt);
};


#endif //PROJETO2AED_GRAPHCREATE_H
