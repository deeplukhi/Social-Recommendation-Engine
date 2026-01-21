#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<unordered_map>
using namespace std;

class graph{
    private:
        unordered_map<int, vector<int>> adj;
    public:
        void adjList(int u, int v);
        vector<int> getNeighbor(int node);

         const unordered_map<int, vector<int>>& getAdjList() const;

};

#endif