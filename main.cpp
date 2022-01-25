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

    Graph graph = CreateGraphs.CreateGraph(lines,StopsToInt,StopsLat,StopsLong);
    //Ler o nome de um ficheiro -> criar um grapho
    // -> fazer addEdges no grafo até ter todas as stops
    // -> meter o grapho no vetor -> ir para a proxima linha
    // -> repeat;

    return 0;
}

