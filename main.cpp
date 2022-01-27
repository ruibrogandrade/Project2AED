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


    //list<string> StopsCode = CreateGraphs.StopsCode();
    //list<string> StopsName = CreateGraphs.StopsName();
    //list<string> LinesName = CreateGraphs.LinesName();
    list<string> LinesCode = CreateGraphs.LinesCode();
    //list<string> StopsZone = CreateGraphs.StopsZone();

    Graph graph = CreateGraphs.CreateGraph(lines,LinesCode,StopsToInt,StopsLat,StopsLong);

    string StopCode1 = "INF1";
    string StopCode2 = "MON3";
    int src;
    int dest;

    cout << "Where do you want to go from?" << endl;
    cin >> StopCode1;
    cout << "Where do you want to go to?" << endl;
    cin >> StopCode2;

    auto et = StopsToInt.find((StopCode1));
    if (et != StopsToInt.end()) {
        src = et->second;
    }

    auto ot = StopsToInt.find((StopCode2));
    if (ot != StopsToInt.end()) {
        dest = ot->second;
    }


    //Trajeto com menos Stops!!!!!! :DDD
    cout << graph.distance(src, dest) << endl;


    //Ler o nome de um ficheiro -> criar um grapho
    // -> fazer addEdges no grafo até ter todas as stops
    // -> meter o grapho no vetor -> ir para a proxima linha
    // -> repeat;

    return 0;
}

