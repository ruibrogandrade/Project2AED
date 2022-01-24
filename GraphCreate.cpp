//
// Created by Rui on 24/01/2022.
//

#include "GraphCreate.h"


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

    while(getline(file,stop,'\n')){
        stops.push_back(stop);
    }
    return stops;
}

void GraphCreate::CreateGraph(list<string> result,map<string,int> StopsToInt){
    int src;
    int dest;
    for(int i = 0; i < result.size(); i++) {
        list<string> stops = readStopsinLine(result,i);
        Graph linha(stoi(*stops.begin()), true);
        for(auto it = stops.begin(); it != stops.end(); it++) {
            if (it++ == stops.end()) break;
            auto et = StopsToInt.find((*it));
            if (et != StopsToInt.end()) {
                src = et->second;
            }
            auto ot = StopsToInt.find((*it++));
            if (ot != StopsToInt.end()) {
                dest = ot->second;
            }
            linha.addEdge(src,dest,1);
        }
    }
}

map<string,int> GraphCreate::StopsToMap() {
    ifstream file("dataset/stops.csv");
    string line;
    string line1;
    map<string,int> StopsToInt;
    int i = 0;
    int j = 0;
    while(getline(file,line)){
        cout << endl;
        i++;
        if (i == 1) continue;
        int pos = line.find_first_of(',');
        string stopsCode = line.substr(0,pos);
        StopsToInt.insert({stopsCode,j});
        j++;
    }
    return StopsToInt;
}