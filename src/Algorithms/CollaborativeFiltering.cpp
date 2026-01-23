#include "CollaborativeFiltering.h"
#include "Popularity.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> CollaborativeRecommendation::recommend(graph &g, int userId) {

    unordered_set<int> visited;
    unordered_map<int, int> itemScore;
    unordered_set<int> userWatched;
    unordered_map<int,int> popularity;

    // Step 1: Collect movies already watched by user
    for (int neighbor : g.getNeighbor(userId)) {
        if (neighbor >= 1000) {
            userWatched.insert(neighbor);
        }
    }

    // Step 2: BFS traversal
    queue<pair<int,int>> q;
    q.push(make_pair(userId, 0));
    visited.insert(userId);

    while (!q.empty()) {

        pair<int,int> front = q.front();
        q.pop();

        int current = front.first;
        int depth = front.second;

        if (depth > 2) continue;

        for (int neighbor : g.getNeighbor(current)) {

            popularity[neighbor]++;

            if (visited.count(neighbor)) continue;
            visited.insert(neighbor);

            if (neighbor >= 1000 && !userWatched.count(neighbor)) {
                if (depth == 1)
                    itemScore[neighbor] += 3;
                else
                    itemScore[neighbor] += 1;
            }

            q.push(make_pair(neighbor, depth + 1));
        }
    }

    if (itemScore.empty()) {
        return Popularity::getTopKPopular(g, userWatched);
    }

        //very improtant it is - popularity panelty
    unordered_map<int,double> finalScore;

    for (auto &p : itemScore) {
        int movie = p.first;
        int simScore = p.second;
        int pop = popularity[movie] == 0 ? 1 : popularity[movie];

        finalScore[movie] = (double)simScore / pop;
    }


    vector<pair<double,int>> sorted;
    for (auto &p : finalScore) {
        sorted.push_back(make_pair(p.second, p.first));
    }

    sort(sorted.rbegin(), sorted.rend());


    vector<int> recommendations;
    for (size_t i = 0; i < sorted.size() && i < 4; i++) {
        recommendations.push_back(sorted[i].second);
    }

    return recommendations;
}
