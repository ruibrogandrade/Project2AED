//
// Created by Rui on 24/01/2022.
//

#include "GraphCreate.h"
#include <math.h>
#include <algorithm>


list<string> GraphCreate::readLines() {
    list<string> lines;
    ifstream file("dataset/lines.csv");
    string linecode;
    string line;
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

Graph GraphCreate::CreateGraph(list<string> lines, list<string> LinesCode, map<string,int> StopsToInt,list<double> StopsLat, list<double> StopsLong) {
    int src;
    int dest;
    double weight;
    std::string line;
    Graph graph(2486, true);
    for (int i = 0; i < LinesCode.size(); i++) {
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

            auto frontLines = LinesCode.begin();
            advance(frontLines,i);
            string lineCode = *frontLines;
            it--;
            graph.addEdge(src,dest,lineCode,weight);
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


list<string> GraphCreate::StopsCode() {
    ifstream file("dataset/stops.csv");
    string line;
    list<string> stopsCode;
    int i = 0;
    while(getline(file,line)){
        i++;
        if (i == 1)  continue;
        int pos = line.find_first_of(',');
        stopsCode.push_back(line.substr(0,pos));
    }
    return stopsCode;
}

list<string> GraphCreate::StopsName() {
    ifstream file("dataset/stops.csv");
    string part;
    list<string> stopsName;
    int i = 0;
    int j = 0;
    while(getline(file,part,',')){
        i++;
        j++;
        if (i == 1 || i == 2 || i == 3 || i == 4 ||i == 5)  continue;
        if (j == 6 || j == 4) {
            j = 0;
            stopsName.push_back(part);
        }
    }
    return stopsName;
}

list<string> GraphCreate::StopsZone() {
    ifstream file("dataset/stops.csv");
    string part;
    list<string> stopsZone;
    int i = 0;
    int j = 0;
    while(getline(file,part,',')){
        i++;
        j++;
        if (i == 1 || i == 2 || i == 3 || i == 4 ||i == 5 ||i == 6)  continue;
        if (j == 7 || j == 4) {
            j = 0;
            stopsZone.push_back(part);
        }
    }
    return stopsZone;
}

list<string> GraphCreate::LinesName() {
    ifstream file("dataset/lines.csv");
    string line;
    string line1;
    list<string> linesName;
    int i = 0;
    while(getline(file,line)) {
        i++;
        if (i == 1) continue;
        int pos = line.find_first_of(',');
        string name = line.substr(pos+1);
        linesName.push_back(name);
    }
    return linesName;
}

list<string> GraphCreate::LinesCode() {
    string line;
    ifstream file("dataset/lines.csv");
    int i = 0;
    list<string> LinesCode;
    while(getline(file,line)) {
        cout << endl;
        i++;
        if (i == 1) continue;
        int pos = line.find_first_of(',');
        string linecode = line.substr(0, pos);
        LinesCode.push_back(linecode);
    }
    return LinesCode;
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

    // apply formula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


double GraphCreate::haversine2(double lat1, double lon1, double lat2, double lon2) {

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


string GraphCreate::NodeToListIndex(int nodeNumber, list<string> StopsCode) {
    auto frontStopsCode = StopsCode.begin();
    advance(frontStopsCode,nodeNumber);
    string StopCode = *frontStopsCode;
    return StopCode;
}

list<double> GraphCreate::NodeToListIndexDouble(int nodeNumber, list<double> StopsLat, list<double> StopsLong) {
    auto frontStopsLat = StopsLat.begin();
    auto frontStopsLong = StopsLong.begin();
    advance(frontStopsLat,nodeNumber);
    advance(frontStopsLong,nodeNumber);
    double StopLat = *frontStopsLat;
    double StopLong = *frontStopsLong;
    list<double> result;
    result.push_back(StopLat);
    result.push_back(StopLong);
    return result;
}


list<string> GraphCreate::CoordinatesNearByDistance(double distance,double lat,double longi, list<double> Lats, list<double> Longis, list<string> StopsName) {
    list<string> result;
    map<int,string> map;
    int i = 0;
    for(auto it = Lats.begin(); it !=  Lats.end(); it++) {
        auto et = Longis.begin();

        double dist = abs(haversine2(*it,*et,lat,longi));
        if (dist < distance) map.insert({i,NodeToListIndex(i,StopsName)});
        i++;
        et++;
    }

    for (auto ut = map.begin(); ut != map.end(); ut++) {
        auto pt = find(result.begin(), result.end(), ut->second);
        if (pt == result.end() || result.empty()) {
            result.push_back(ut->second);
        }
    }
    return result;
}


list<string> GraphCreate::CoordinatesNearByNumberOfStops(int numStops,double lat,double longi, list<double> Lats, list<double> Longis, list<string> StopsName) {
    list<string> result;
    list<double> distanceList;
    multimap<double,int> map;

    int i = 0;
    for(auto it = Lats.begin(); it !=  Lats.end(); it++) {
        auto et = Longis.begin();

        double dist = abs(haversine2(*it,*et,lat,longi));
        map.insert({dist,i});
        i++;
        et++;
    }
    auto ut = map.begin();
    for(int j = 0; j < numStops; j++) {
        string stopName = NodeToListIndex((*ut).second,StopsName);
        auto pt = find(result.begin(), result.end(),stopName);
        if (pt == result.end() || result.empty()) {
            result.push_back(NodeToListIndex((*ut).second,StopsName));
        }
        else {
            j--;
        }
        ut++;
    }

    return result;
}


/* recebe um lista dos nomes das paragens de um certo caminho, a lista das zonas das paragens e dos nomes das paragens
 * compara os nomes com a lista que contem todos os nomes para sacar o index e ir buscar a zona da paragem
 * se for uma zona nova, adiciona a a lista de zonas
 * no fim, retorna o numero de zonas por onde passa um certo caminho
 * */
list<string> GraphCreate::zonesPassed(list<string> stopsPassed, list<string> stopsZone, list<string> StopsName) {
    list<string> zones;
    for(auto & it : stopsPassed) {
        int i = 0;
        for(auto & et : StopsName) {
            if (it == et) {
                for(auto ot = zones.begin(); ot != zones.end(); ot++){
                    if (*ot != NodeToListIndex(i,stopsZone)){
                        zones.push_back(NodeToListIndex(i,stopsZone));
                    }
                }
            }
            i++;
        }
    }
    return zones;
}


list<double> GraphCreate::StopCodeOrNameToCoords(list<string> StopNames, list<string> StopCodes,list<double> StopsLat,list<double> StopsLong) {
    while(true) {
        cout << "Insira o nome ou código da stop:";
        string nome;
        cin.clear();
        cin.sync();
        getline(cin,nome);
        cout << endl;
        list<double> latAndLong;
        list<double> result;
        int i = 0;
        for (auto it = StopNames.begin(); it != StopNames.end(); it++) {
            if ((*it) == nome) {
                result = NodeToListIndexDouble(i, StopsLat, StopsLong);
            }
        }
        for (auto it = StopCodes.begin(); it != StopCodes.end(); it++) {
            if ((*it) == nome) {
                result = NodeToListIndexDouble(i, StopsLat, StopsLong);
            }
        }
        if (!result.empty()) {
            return result;
        }
        else {
            cout << "Input Invalido! Por favor tente de novo." << endl;
        }
    }
}

list<string> GraphCreate::StopCheck(string stop, list<string> StopsCode, list<string> StopsName) {
    list<string> similarStops;
    list<string> result;
    int num;
    int i = 0;
    bool flag = false;
    for(auto it = StopsCode.begin(); it != StopsCode.end(); it++) {
        if(*it == stop) {
            result.push_back(*it);
            flag = true;
            break;
        }
    }

    if(!flag) {
        for (auto et = StopsName.begin(); et != StopsName.end(); et++) {
            if (*et == stop) {
                similarStops.push_back(NodeToListIndex(i, StopsCode));
            }
            i++;
        }

        while (true) {
            int j = 0;
            cout << "Que paragem e que deseja escolher?" << endl;
            for (auto ut = similarStops.begin(); ut != similarStops.end(); ut++) {
                cout << j << "- " << *ut << endl;
                j++;
            }

            cin >> num;

            if (num > similarStops.size() - 1) {
                result.push_back(NodeToListIndex(num, similarStops));
                break;
            } else {
                cout << "Input Invalido! Por favor tente de novo." << endl;
            }
        }
    }
    return result;
}