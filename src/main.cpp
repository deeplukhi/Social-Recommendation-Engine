#include <iostream>
#include <vector>
#include <string>

#include "Graph/graph.h"
#include "Storage/FileManager.h"
#include "Algorithms/Recommendation.h"
#include "Algorithms/CollaborativeFiltering.h"
#include "../Utils/Colors.h"

using namespace std;

void printHeader() {
    cout << BOLD << CYAN;
    cout << "============================================\n";
    cout << "      🎬  MOVIE RECOMMENDATION SYSTEM  🎬     \n";
    cout << "============================================\n";
    cout << RESET << endl;
}

void printDivider() {
    cout << BOLD << "--------------------------------------------" << RESET << endl;
}

int main() {

    printHeader();

    graph g;

    // 1️⃣ Load existing interactions
    cout << GREEN << "[✔] Loading previous user interactions..." << RESET << endl;
    FileManager::loadAllInteraction("data/interactions.txt", g);
    cout << GREEN << "[✔] Data loaded successfully!\n" << RESET << endl;

    printDivider();

    // 2️⃣ User onboarding
    string userName;
    cout << YELLOW << "👤 Enter your name: " << RESET;
    cin >> userName;

    // 3️⃣ Register user
    Users newUser = FileManager::addNewUser("data/users.txt", userName);

    cout << GREEN << "\nWelcome, " << BOLD << newUser.getName() << RESET << GREEN << " 🎉" << endl;
    cout << "Your User ID: " << BOLD << newUser.getId() << RESET << endl;

    printDivider();

    // 4️⃣ Favorite movies input
    int n;
    cout << CYAN << "⭐ How many favorite movies would you like to add? " << RESET;
    cin >> n;

    cout << MAGENTA << "\n🎥 Enter movie names (use '_' instead of space):\n" << RESET;

    for (int i = 0; i < n; i++) {
        cout << "  ➜ ";
        string movie;
        cin >> movie;

        FileManager::addInteraction(
            "data/interactions.txt",
            newUser.getId(),
            movie,
            g
        );

        cout << GREEN << "    [Added] " << movie << RESET << endl;
    }

    printDivider();

    // 5️⃣ Generate recommendations
    cout << BLUE << "🔍 Generating personalized recommendations...\n" << RESET;

    vector<int> recommendedIds =
        CollaborativeRecommendation::recommend(g, newUser.getId());

    // 6️⃣ Display recommendations
    cout << BOLD << CYAN << "\n🎯 Recommended Movies For You\n" << RESET;
    printDivider();

    if (recommendedIds.empty()) {
        cout << RED
             << "❄️ No recommendations found.\n"
             << "   (Cold start user — add more interactions!)\n"
             << RESET;
    } else {
        for (int id : recommendedIds) {
            cout << GREEN << "🎬 "
                 << FileManager::getItemName(id)
                 << RESET << endl;
        }
    }

    printDivider();

    cout << BOLD << GREEN << "✅ Thank you for using the system!" << RESET << endl;
    cout << CYAN << "🚀 Keep watching. Keep exploring.\n" << RESET;

    return 0;
}
