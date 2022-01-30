// Rui Andrade (FEUP)

#include "graph.h"
#include <queue>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string lineCode, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, lineCode});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

int Graph::distance(int a, int b) {
    if(a == b) return 0;
    for(int i = 1; i <= n; i++)
        nodes[i].distance = -1;
    bfsDist(a);
    cout << endl << endl;
    cout << "Distance: ";
    return nodes[b].distance;
}

/**
 * Algoritmo de BFS
 * Time Complexity = O(V + E)
 * @param v - primeiro node
 */


void Graph::bfsDist(int v){
    nodes[v].distance = 0; //distance from v to itself
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    //cout << "MST:" << endl;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

#define INF (INT_MAX/2)

// Distância entre dois nós
double Graph::dijkstra_distance(int a, int b, list<string> StopZones) {
    dijkstra(a,0,StopZones);
    if (nodes[b].distance == INF) return -1;
    return nodes[b].distance;
}

/**
 * Algoritmo de disjkstra para caminhos
 * @param a
 * @param b
 * @param type
 * @param StopZones
 * @return caminho
 */


// Caminho mais curto entre dois nós
list<int> Graph::dijkstra_path(int a, int b, int type,list<string> StopZones) {
    dijkstra(a,type,StopZones);
    list<int> path;
    if (nodes[b].distance == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}


list<int> Graph::dijkstra_path_walking(int a, int b, double d, list<string> StopZones) {
    dijkstra(a,0,StopZones);
    list<int> path;
    if (nodes[b].distance == INF) return path;
    path.push_back(b);
    int v = b;
    double dist = 0;
    int i = 0;
    while (v != a) {
        i++;
        dist += abs(nodes[v].distance - nodes[nodes[v].pred].distance);
        v = nodes[v].pred;
        path.push_front(v);
        if (dist <= d) path.pop_back();
    }
    return path;
}

/**
 * Algoritmo de dijsktra
 * Complexity = O(|E| log |V|)
 * @param s
 * @param type
 * @param StopZones
 */


void Graph::dijkstra(int s,int type,list<string> StopZones) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].distance = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].distance = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            double w = e.weight;
            if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                nodes[v].distance = nodes[u].distance + w;
                if (type == 1) {
                    if (e.lineCode != checkPreviousLineCode(u,s) && checkPreviousLineCode(u,s) != "null") {
                        nodes[v].distance += 10000;
                    }
                }
                if (type == 2) {
                    if (checkZoneChange(u,v,StopZones)) {
                        nodes[v].distance += 10000;
                    }
                }
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].pred = u;
            }
        }
    }
}

/**
 * checkPreviousLineCode
 * @param u node :D
 * @param s node
 * @return codigo de linha
 */

string Graph::checkPreviousLineCode(int u, int s) {
    int v;
    if (u != s) {
        v = nodes[u].pred;
    } else {
        return "null";
    }
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (w == u) {
            return e.lineCode;
        }
    }
}

/**
 * checkZoneChange
 * @param u node
 * @param v node
 * @param StopZones zonas
 * @return booleano se stops tiverem zonas diferentes
 */

bool Graph::checkZoneChange(int u, int v, list<string> StopZones) {
    auto frontStopZones = StopZones.begin();
    advance(frontStopZones,u);
    string StopZone = *frontStopZones;

    auto frontStopZones2 = StopZones.begin();
    advance(frontStopZones2,v);
    string StopZone2 = *frontStopZones2;

    if (StopZone != StopZone2) {
        return true;
    }
    else return false;
}