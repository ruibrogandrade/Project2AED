// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

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

/*
int Graph::bfs(int v1, int v2) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v1);
    int dist = 0;
    nodes[v1]. visited = true;
    int i = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (w == v2) return dist;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
        dist++;
    }
    return -1;
}
*/

int Graph::distance(int a, int b) {
    if(a == b) return 0;
    for(int i = 1; i <= n; i++)
        nodes[i].distance = -1;
    bfsDist(a);
    return nodes[b].distance;
}

void Graph::bfsDist(int v){
    nodes[v].distance = 0; //distance from v to itself
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
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
double Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].distance == INF) return -1;
    return nodes[b].distance;
}

// Caminho mais curto entre dois nós
list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
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

list<int> Graph::dijkstra_path_walking(int a, int b, double d) {
    dijkstra(a);
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

//O(|E| log |V|)
void Graph::dijkstra(int s) {
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
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].pred = u;
            }
        }
    }
}
