#include "Popularity.h"
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Popularity::getTopKPopular(
    graph &g,
    unordered_set<int> &userWatched
) {
    unordered_map<int,int> popularity;
    
    // Count how many users watched each movie
    for (auto &entry : g.getAdjList()) {
        int node = entry.first;

        // movie node
        if (node >= 1000 && !userWatched.count(node)) {
            popularity[node] = entry.second.size();
        }
    }

    vector<pair<int,int>> temp;
    for (auto &p : popularity) {
        temp.push_back(make_pair(p.second, p.first));
    }

    sort(temp.rbegin(), temp.rend());

    vector<int> result;
    for (size_t i = 0; i < temp.size() && i < 5; i++) {
        result.push_back(temp[i].second);
    }

    return result;
}