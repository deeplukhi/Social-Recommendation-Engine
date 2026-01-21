#ifndef POPULARITY_H
#define POPULARITY_H

#include "../graph/graph.h"
#include<unordered_set>

class Popularity{
    public:
    static  vector<int> getTopKPopular( graph &g,
    unordered_set<int> &userWatched);
};

#endif