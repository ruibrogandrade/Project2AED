// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


/*// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------
​
// ..............................
// a) Distância entre dois nós
//
int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}
​
// ..............................
// b) Caminho mais curto entre dois nós
//
list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
    list<int> path;
    if (nodes[b].dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}
​
// Dijkstra in O(|E| log |V|) using only the MinHeap that was given to you
void Graph::dijkstra(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }
}
​
/*
// Another version of Dijkstra in O(|E| log |V|) using only STL and sets
void Graph::dijkstra(int s) {
    set<pair<int, int>> q;
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert({INF, v});
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.erase({INF, s});
    q.insert({0, s});
    nodes[s].pred = s;
    while (q.size()>0) {
        int u = q.begin()->second;
        q.erase(q.begin());
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                q.erase({nodes[v].dist, v});
                nodes[v].dist = nodes[u].dist + w;
                nodes[v].pred = u;
                q.insert({nodes[v].dist, v});
            }
        }
    }
}
*/