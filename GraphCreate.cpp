//
// Created by Rui on 24/01/2022.
//

#include "GraphCreate.h"
#include <math.h>


list<string> GraphCreate::readLines() {
    list<string> lines;
    ifstream file("dataset/lines.csv");
    string line;
    string linecode;
    string line1;
    int i = 0;
    while(getline(file,line)){
        cout << endl;
        i++;
        if (i == 1) continue;
        int pos = line.find_first_of(',');
        string linecode = line.substr(0,pos);

        for(int dir = 0; dir <= 1; dir++) {
            string linha = "line_" + linecode + "_" + to_string(dir) + ".csv";
            lines.push_back(linha);
        }
    }
    return lines;
}

list<string> GraphCreate::readStopsinLine(list<string> lines, int i) {
    auto front = lines.begin();
    advance(front,i);
    list<string> stops;
    ifstream file("dataset/" + *front);
    string stop;
    int j = 0;
    while(getline(file,stop,'\n')){
        j++;
        if (j == 1) continue;
        stops.push_back(stop);
    }
    return stops;
}

Graph GraphCreate::CreateGraph(list<string> lines,map<string,int> StopsToInt,list<double> StopsLat, list<double> StopsLong) {
    int src;
    int dest;
    double weight;
    std::string line;
    Graph graph(2488, true);
    for (int i = 0; i < lines.size(); i++) {
        list<string> stops = readStopsinLine(lines, i);
        for (auto it = stops.begin(); it != stops.end(); it++) {

            if (it == stops.end()) break;
            //if (lit == stops.end()) break;
            auto et = StopsToInt.find((*it));
            if (et != StopsToInt.end()) {
                src = et->second;
            }
            it++;
            if (it == stops.end()) break;
            auto ot = StopsToInt.find((*it));
            if (ot != StopsToInt.end()) {
                dest = ot->second;
            }
            weight = haversine(StopsLong,StopsLat,src,dest);
            graph.addEdge(src, dest, weight);
        }
    }
    return graph;
}

map<string,int> GraphCreate::StopsToMap() {
    ifstream file("dataset/stops.csv");
    string line;
    string line1;
    map<string,int> StopsToInt;
    int i = 0;
    int j = 0;
    while(getline(file,line)){
        i++;
        if (i == 1) continue;
        int pos = line.find_first_of(',');
        string stopsCode = line.substr(0,pos);
        StopsToInt.insert({stopsCode,j});
        j++;
    }
    return StopsToInt;
}

list<double> GraphCreate::StopsLat() {
    ifstream file("dataset/stops.csv");
    string part;
    string line1;
    int finalpos;
    int pos;
    list<double> StopsLat;
    int i = 0;
    int j = 0;
    while(getline(file,part,',')){
        i++;
        j++;
        if (i == 1 || i == 2 || i == 3 || i == 4 ||i == 5)  continue;
        if (j == 8 || j == 4) {
            j = 0;
            StopsLat.push_back(stod(part));
        }
    }
    return StopsLat;
}

list<double> GraphCreate::StopsLong() {
    ifstream file("dataset/stops.csv");
    string line;
    string line1;
    list<double> StopsLong;
    int i = 0;
    int j = 0;
    while(getline(file,line)){
        i++;
        if (i == 1) continue;
        int pos = line.find_last_of(',');
        double stopsLong = stod(line.substr(pos+1));
        StopsLong.push_back(stopsLong);
        j++;
    }
    return StopsLong;
}


double GraphCreate::haversine(list<double> StopsLong, list<double> StopsLat, int src, int dest) {
    auto frontLat1 = StopsLat.begin();
    advance(frontLat1,src);
    double lat1 = *frontLat1;

    auto frontLat2 = StopsLat.begin();
    advance(frontLat2,dest);
    double lat2 = *frontLat2;

    auto frontLong1 = StopsLong.begin();
    advance(frontLong1,src);
    double lon1 = *frontLong1;

    auto frontLong2 = StopsLong.begin();
    advance(frontLong2,src);
    double lon2 = *frontLong2;


    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}