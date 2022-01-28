#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include "GraphCreate.h"

using namespace std;


int main() {
    GraphCreate CreateGraphs;
    list<string> lines = CreateGraphs.readLines();
    map<string,int> StopsToInt = CreateGraphs.StopsToMap();

    list<double> StopsLat = CreateGraphs.StopsLat();
    list<double> StopsLong = CreateGraphs.StopsLong();


    list<string> StopsCode = CreateGraphs.StopsCode();
    list<string> StopsName = CreateGraphs.StopsName();
    //list<string> LinesName = CreateGraphs.LinesName();
    list<string> LinesCode = CreateGraphs.LinesCode();
    //list<string> StopsZone = CreateGraphs.StopsZone();

    string whatdoestheuserwant;
    int parameter;
    int numberOfStops;
    double distance;
    double lat;
    double longi;
    cout << "What do you want to see?" << endl;
    cin >> whatdoestheuserwant;
    if (whatdoestheuserwant == "Coordinates") {
        cout << "Please, input your coordinates!" << endl;
        cout << "Latitude:";
        cin >> lat;
        cout << "Longitude:";
        cin >> longi;
        cout << "What Parameter do you want to use?" << endl;
        cout << "1) Distance" << endl;
        cout << "2) Number of Stops" << endl;
        cin >> parameter;
        if (parameter == 1) {
            cout << "What is the max distance that you, the user, might consider as the maximum relative to your current location?" << endl;
            cin >> distance;
            list<string> coords = CreateGraphs.CoordinatesNearDistance(distance,lat,longi,StopsLat,StopsLong, StopsName);
            CreateGraphs.printList(coords);
        }
        else if (parameter == 2) {
            cout << "How many nearby Stops do you want to see?" << endl;
            cin >> numberOfStops;
            for (int i = 0; i < numberOfStops; i++) {
                //doSomething(lat,longi);
            }
        }
        }
        else {
            cout << "That's not an option!";
    }
    if (whatdoestheuserwant == "") {

    }

    Graph graph = CreateGraphs.CreateGraph(lines,LinesCode,StopsToInt,StopsLat,StopsLong);

    string StopCode1 = "INF1";
    string StopCode2 = "MON3";
    int src;
    int dest;
    double walking;

    cout << "Where do you want to go from?" << endl;
    cin >> StopCode1;
    cout << "Where do you want to go to?" << endl;
    cin >> StopCode2;
    cout << "How many km do you want to walk?" << endl;
    cin >> walking;

    auto et = StopsToInt.find((StopCode1));
    if (et != StopsToInt.end()) {
        src = et->second;
    }

    auto ot = StopsToInt.find((StopCode2));
    if (ot != StopsToInt.end()) {
        dest = ot->second;
    }


    //Trajeto com menos Stops!!!!!! :DDD
    //cout << graph.bfs(src,dest) << endl;



    //Trajeto com menor distância!!!! :DDDDD
    /*
    list<int> path1 = graph.dijkstra_path(src,dest);
    for (auto it = path1.begin(); it != path1.end(); it++) {
        auto frontStopsCode = StopsCode.begin();
        advance(frontStopsCode,(*it));
        string StopCode = *frontStopsCode;
        cout << StopCode << endl;
    }
     */



    cout << endl;


    //Distancia entre duas stops em km!!!! :DDDD
    //cout << graph.dijkstra_distance(src, dest) << endl;
    /*
    int src1;
    int dest1;

    auto ut = StopsToInt.find(("DL5"));
    if (et != StopsToInt.end()) {
        src1 = et->second;
    }

    auto at = StopsToInt.find(("CNT3"));
    if (ot != StopsToInt.end()) {
        dest1 = ot->second;
    }
    cout << graph.dijkstra_distance(src1, dest1) << endl;

    cout << endl;
     */


    //Trajeto que tem em conta a distancia que o utilizador quer caminhar!!!! :DDDD
    /*
    list<int> path2 = graph.dijkstra_path_walking(src, dest, walking);
    for (auto it = path2.begin(); it != path2.end(); it++) {
        auto frontStopsCode = StopsCode.begin();
        advance(frontStopsCode,(*it));
        string StopCode = *frontStopsCode;
        cout << StopCode << endl;
    }

    if(path1.size() > path2.size()) {
        int diff = path1.size() - path2.size();
        auto it = path1.end();
        for (int i = 0; i < diff; i++) {
            it--;
            cout << "WALKING -> " << CreateGraphs.NodeToStopCode((*it),StopsCode) << endl;
        }
    }
     */

    //Ler o nome de um ficheiro -> criar um grapho
    // -> fazer addEdges no grafo até ter todas as stops
    // -> meter o grapho no vetor -> ir para a proxima linha
    // -> repeat;

    return 0;
}

