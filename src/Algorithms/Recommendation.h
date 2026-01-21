#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include<vector>
#include "../Graph/graph.h"

class BFSRecommendation{
    public:
        static ::vector<int> recommendItems(graph &g, int userId);
};


#endif