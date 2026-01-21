#include "Recommendation.h"
#include "Popularity.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Improved Graph-Based Recommendation System

    Features:
    - BFS-based collaborative filtering
    - Depth-based scoring
    - Already-watched filtering
    - Cold-start fallback using popularity
*/

vector<int> BFSRecommendation::recommendItems(graph &g, int userId) {

    unordered_set<int> visited;              // visited nodes
    unordered_set<int> userWatched;          // movies already watched
    unordered_map<int, int> itemScore;       // movie -> score

    // --------------------------------------------------
    // STEP 1: Collect movies already watched by user
    // --------------------------------------------------
    vector<int> userNeighbors = g.getNeighbor(userId);
    for (int nei : userNeighbors) {
        if (nei >= 1000) {   // movie node
            userWatched.insert(nei);
        }
    }

    // --------------------------------------------------
    // STEP 2: BFS Traversal (User -> Movie -> User -> Movie)
    // --------------------------------------------------
    queue<pair<int,int>> q;   // {node, depth}
    q.push(make_pair(userId, 0));
    visited.insert(userId);

    while (!q.empty()) {

        pair<int,int> front = q.front();
        q.pop();

        int current = front.first;
        int depth   = front.second;

        // limit BFS depth (performance + relevance)
        if (depth > 2) continue;

        vector<int> neighbors = g.getNeighbor(current);

        for (int nei : neighbors) {

            if (visited.count(nei)) continue;
            visited.insert(nei);

            // --------------------------------------------------
            // STEP 3: Score unseen movies using depth-based weight
            // --------------------------------------------------
            if (nei >= 1000 && !userWatched.count(nei)) {

                // depth-based scoring
                if (depth == 1) {
                    itemScore[nei] += 3;   // strong similarity
                } else {
                    itemScore[nei] += 1;   // weak similarity
                }
            }

            // continue BFS
            q.push(make_pair(nei, depth + 1));
        }
    }

    // --------------------------------------------------
    // STEP 4: Cold-start fallback (no similar items found)
    // --------------------------------------------------
    if (itemScore.empty()) {
        return Popularity::getTopKPopular(g, userWatched);
    }

    // --------------------------------------------------
    // STEP 5: Sort items by score (descending)
    // --------------------------------------------------
    vector<pair<int,int>> ranked;
    for (auto &p : itemScore) {
        ranked.push_back(make_pair(p.second, p.first));
    }

    sort(ranked.rbegin(), ranked.rend());

    // --------------------------------------------------
    // STEP 6: Pick top K recommendations
    // --------------------------------------------------
    vector<int> result;
    for (size_t i = 0; i < ranked.size() && i < 5; i++) {
        result.push_back(ranked[i].second);
    }

    return result;
}
