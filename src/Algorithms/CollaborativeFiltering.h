#ifndef COLLABORATIVEFILTER_H
#define COLLABORATIVEFILTER_H

#include<vector>
#include "../Graph/graph.h"

class CollaborativeRecommendation{
    public:
        static ::vector<int> recommend(graph &g, int userId);
};


#endif