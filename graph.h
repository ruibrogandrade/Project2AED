// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#ifndef PROJETO2AED_GRAPH_H
#define PROJETO2AED_GRAPH_H

#include "minHeap.h"
#include "disjointSets.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        string lineCode;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double distance;
        int pred;
        bool visited;
        string name;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string lineCode, double weight);

    double dijkstra_distance(int a, int b,list<string> StopZones);
    list<int> dijkstra_path(int a, int b, int type,list<string> StopZones);

    void bfsDist(int v);

    int distance(int a, int b);

    void dijkstra(int s, int type, list<string> StopZones);

    list<int> dijkstra_path_walking(int a, int b, double d, list<string> StopZones);

    string checkPreviousLineCode(int u, int s);

    bool checkZoneChange(int u, int v, list<string> StopZones);

    double haversine3(list<double> StopsLong, list<double> StopsLat, int src, int dest);
};

#endif
