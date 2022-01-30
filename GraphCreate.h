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
    Graph CreateGraph(list<string> lines, list<string> LinesCode, map<string, int> StopsToInt, list<double> StopsLat, list<double> StopsLong);

    list<double> StopsLat();
    list<double> StopsLong();

    double haversine(list<double> StopsLong, list<double> StopsLat, int src, int dest);

    list<string> StopsCode();

    list<string> StopsName();

    list<string> LinesName();

    list<string> LinesCode();

    list<string> StopsZone();

    string NodeToListIndex(int nodeNumber, list<string> StopsCode);

    double haversine2(double lat1, double lon1, double lat2, double lon2);

    list<string> CoordinatesNearByDistance(double distance, double lat, double longi, list<double> Lats, list<double> Longis,
                            list<string> StopsName);

    list<string> zonesPassed(list<string> stopsPassed, list<string> stopsZone, list<string> StopsName);

    list<string>
    CoordinatesNearByNumberOfStops(int numStops, double lat, double longi, list<double> Lats, list<double> Longis,
                                   list<string> StopsName);

    list<double> StopCodeOrNameToCoords(list<string> StopNames, list<string> StopCodes,list<double> StopsLat,list<double> StopsLong);

    list<double> NodeToListIndexDouble(int nodeNumber, list<double> StopsLat, list<double> StopsLong);

    list<string> StopCheck(string stop, list<string> StopsCode, list<string> StopsName);
};


#endif //PROJETO2AED_GRAPHCREATE_H
