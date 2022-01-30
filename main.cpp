#include <iostream>
#include <map>
#include <string>
#include <list>
#include "GraphCreate.h"

using namespace std;

void printList(list<string> list) {
    for (auto it = list.begin(); it != list.end(); it++) {
        cout << (*it) << endl;
    }
}


/**
 * \brief Apresenta caminhos pedidos
 * @param StopsName nome
 * @param StopsCode codigo
 * @param lines linha
 * @param LinesCode codigo da linha
 * @param StopsToInt index dos stops
 * @param StopsLat latitude
 * @param StopsLong longitude
 * @param StopsZone zonas
 */


void PathCalculator(list<string> StopsName, list<string> StopsCode, list<string> lines,
                    list<string> LinesCode, map<string,int> StopsToInt, list<double> StopsLat, list<double> StopsLong, list<string> StopsZone) {

    GraphCreate CreateGraphs;
    Graph graph = CreateGraphs.CreateGraph(lines,LinesCode,StopsToInt,StopsLat,StopsLong);
    string stop1;
    string stop2;
    int choice;
    float walkingdistance;
    int src;
    int dest;
    while (true) {
        cout << "Qual e o nome ou codigo da sua paragem inicial?" << endl;
        cin.clear();
        cin.sync();
        getline(cin,stop1);
        if (!CreateGraphs.StopCheck(stop1, StopsCode, StopsName).empty()) {
            stop1 = *CreateGraphs.StopCheck(stop1, StopsCode, StopsName).begin();
            break;
        }
        else {
            cout << "Input Invalido! Por favor tente de novo." << endl;
        }
    }
    while (true) {
        cout << "Qual e o nome ou codigo da sua paragem final?" << endl;
        cin.clear();
        cin.sync();
        getline(cin,stop2);
        if (!CreateGraphs.StopCheck(stop2, StopsCode, StopsName).empty()) {
            stop2 = *CreateGraphs.StopCheck(stop2, StopsCode, StopsName).begin();
            break;
        }
        else {
            cout << "Input Invalido! Por favor tente de novo." << endl;
        }
    }

    auto et = StopsToInt.find((stop1));
    if (et != StopsToInt.end()) {
        src = et->second;
    }

    auto ot = StopsToInt.find((stop2));
    if (ot != StopsToInt.end()) {
        dest = ot->second;
    }

    while(true) {
        cout << "1) Deseja ver qual e o numero minimo de paragens para um certo percurso" << endl;
        cout << "2) Deseja ver o percurso mais curto" << endl;
        cout << "3) Deseja ver o percurso com menos mudanca de autocarros" << endl;
        cout << "4) Deseja ver o percurso mais barato" << endl;
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            cout << graph.distance(src,dest) << endl;
            break;
        }
        else if (choice == 2) {
            list<int> path1 = graph.dijkstra_path(src,dest,0,StopsZone);
            for (auto it = path1.begin(); it != path1.end(); it++) {
                auto frontStopsName = StopsName.begin();
                advance(frontStopsName,(*it));
                string StopCode = *frontStopsName;
                cout << StopCode << endl;
            }
            break;
        }
        else if (choice == 3) {
            list<int> path1 = graph.dijkstra_path(src,dest,1,StopsZone);
            for (auto it = path1.begin(); it != path1.end(); it++) {
                auto frontStopsName = StopsName.begin();
                advance(frontStopsName,(*it));
                string StopCode = *frontStopsName;
                cout << StopCode << endl;
            }
            break;
        }
        else if (choice == 4) {
            list<int> path1 = graph.dijkstra_path(src,dest,2,StopsZone);
            for (auto it = path1.begin(); it != path1.end(); it++) {
                auto frontStopsName = StopsName.begin();
                advance(frontStopsName,(*it));
                string StopCode = *frontStopsName;
                cout << StopCode << endl;
            }
            break;
        }
        else {
            cout << "Input Invalido! Por favor tente de novo." << endl;
            break;
        }
    }
}


/**
 * \brief menu para apresentar stops
 * @param StopsLat latitude
 * @param StopsLong longitude
 * @param StopsName nome
 * @param StopsCode codigo
 */

void StopsClosestTo(list<double> StopsLat, list<double> StopsLong, list<string> StopsName, list<string> StopsCode) {
    GraphCreate CreateGraphs;
    int parameter;
    int numberOfStops;
    string nome;
    double distance;
    double lat;
    double longi;
    int input;
    list<double> coords;
    cout << "1) Quer utilizar as coordenadas de uma paragem ja existente" << endl;
    cout << "2) Quer dar input manualmente das coordenadas" << endl;
    cin >> input;
    if (input == 1) {
        coords = CreateGraphs.StopCodeOrNameToCoords(StopsName,StopsCode,StopsLat,StopsLong);
        auto lit = coords.begin();
        lat = *lit;
        lit++;
        longi = *lit;
        cout << "1) Pretende ver as paragens dentro de uma certa distancia" << endl;
        cout << "2) Pretende ver um certo numero de paragens" << endl;
        cin >> parameter;
        if (parameter == 1) {
            cout << "Que distancia maxima deseja ver da sua localizacao?" << endl;
            cin >> distance;
            list<string> nameStops = CreateGraphs.CoordinatesNearByDistance(distance,lat,longi,StopsLat,StopsLong, StopsName);
            printList(nameStops);
        }
        else if (parameter == 2) {
            cout << "Quantas paragens perto da sua localização pretende ver?" << endl;
            cin >> numberOfStops;
            list<string> nameStops = CreateGraphs.CoordinatesNearByNumberOfStops(numberOfStops,lat,longi,StopsLat,StopsLong, StopsName);
            printList(nameStops);
        }
    }
    else if(input == 2) {
        cout << "Insira as suas coordenadas:" << endl;
        cout << "Latitude:";
        cin >> lat;
        cout << endl;
        cout << "Longitude:";
        cin >> longi;
        cout << endl;
        cout << "1) Pretende ver as paragens dentro de uma certa distancia" << endl;
        cout << "2) Pretende ver um certo numero de paragens" << endl;
        cin >> parameter;
        if (parameter == 1) {
            cout << "Que distancia maxima deseja ver da sua localizacao?" << endl;
            cin >> distance;
            list<string> nameStops = CreateGraphs.CoordinatesNearByDistance(distance,lat,longi,StopsLat,StopsLong, StopsName);
            printList(nameStops);
        }
        else if (parameter == 2) {
            cout << "Quantas paragens perto da sua localização pretende ver?" << endl;
            cin >> numberOfStops;
            list<string> nameStops = CreateGraphs.CoordinatesNearByNumberOfStops(numberOfStops,lat,longi,StopsLat,StopsLong, StopsName);
            printList(nameStops);
        }
    }
    else {
        cout << "Input Invalido! Por favor tente de novo!" << endl;
    }
}

/**
 *\brief chama outras funções
 */

void menu() {

    GraphCreate CreateGraphs;
    list<string> lines = CreateGraphs.readLines();
    map<string,int> StopsToInt = CreateGraphs.StopsToMap();

    list<double> StopsLat = CreateGraphs.StopsLat();
    list<double> StopsLong = CreateGraphs.StopsLong();


    list<string> StopsCode = CreateGraphs.StopsCode();
    list<string> StopsName = CreateGraphs.StopsName();
    list<string> LinesName = CreateGraphs.LinesName();
    list<string> LinesCode = CreateGraphs.LinesCode();
    list<string> StopsZone = CreateGraphs.StopsZone();


    while(true) {
        int input;
        cout << "1) Pretende ver as paragens mais proximas de um certo ponto" << endl;
        cout << "2) Pretende fazer um percurso" << endl;
        cin >> input;
        if (input == 1) {
            StopsClosestTo(StopsLat,StopsLong,StopsName,StopsCode);
            break;
        }
        if (input == 2) {
            PathCalculator(StopsName, StopsCode,lines,LinesCode,StopsToInt,StopsLat,StopsLong,StopsZone);
            break;
        }
        else {
            cout << "Input Invalido! Por favor tente de novo!" << endl;
        }
    }
}


int main() {
    menu();
    return 0;
}
