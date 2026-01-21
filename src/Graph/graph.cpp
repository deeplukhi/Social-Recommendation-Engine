#include "graph.h"

void graph::adjList(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

vector<int> graph::getNeighbor(int node){
    return adj[node];
}

const unordered_map<int, vector<int>>& graph::getAdjList() const {
    return adj;
}