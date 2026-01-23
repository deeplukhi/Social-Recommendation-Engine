#include <iostream>
#include <vector>
#include <cassert>

#include "../src/Graph/graph.h"
#include "../src/Algorithms/Recommendation.h"

using namespace std;

// ---------- Helper ----------
void printResult(const string &testName, bool passed) {
    if (passed)
        cout << "[PASS] " << testName << endl;
    else
        cout << "[FAIL] " << testName << endl;
}

// ---------- Test 1: Graph Edge Creation ----------
void testGraphBasic() {
    graph g;
    g.adjList(1, 1001);   // user -> movie
    g.adjList(1, 1002);

    vector<int> neighbors = g.getNeighbor(1);

    bool passed = (neighbors.size() == 2);
    printResult("Graph basic edge creation", passed);
}

// ---------- Test 2: Recommendation for Normal User ----------
void testNormalRecommendation() {
    graph g;

    // Users & movies
    g.adjList(1, 1001); // game_of_thrones
    g.adjList(1, 1002); // vikings

    g.adjList(2, 1001);
    g.adjList(2, 1003); // house_of_the_dragon

    g.adjList(3, 1002);
    g.adjList(3, 1004); // the_witcher

    BFSRecommendation rec;
    vector<int> result = rec.recommendItems(g, 1);

    bool passed = (!result.empty());
    printResult("Recommendation for existing user", passed);
}

// ---------- Test 3: Cold Start User ----------
void testColdStartUser() {
    graph g;

    // Only one user in graph
    g.adjList(1, 1001);
    g.adjList(2, 1001);
    g.adjList(2, 1002);

    BFSRecommendation rec;
    vector<int> result = rec.recommendItems(g, 3); // new user

    bool passed = (!result.empty());
    printResult("Cold-start user fallback", passed);
}

// ---------- Test 4: Already Watched Movie Not Recommended ----------
void testAlreadyWatchedFilter() {
    graph g;

    g.adjList(1, 1001);
    g.adjList(1, 1002);

    g.adjList(2, 1001);
    g.adjList(2, 1003);

    BFSRecommendation rec;
    vector<int> result = rec.recommendItems(g, 1);

    bool passed = true;
    for (int movie : result) {
        if (movie == 1001 || movie == 1002) {
            passed = false;
        }
    }

    printResult("Already-watched movie filtered", passed);
}

// ---------- MAIN ----------
int main() {
    cout << "\nRunning Recommendation System Tests...\n\n";

    testGraphBasic();
    testNormalRecommendation();
    testColdStartUser();
    testAlreadyWatchedFilter();

    cout << "\nAll tests completed.\n";
    return 0;
}
