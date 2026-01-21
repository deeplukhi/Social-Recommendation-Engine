#include "FileManager.h"
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

unordered_map<string, int> itemNameToId;
unordered_map<int, string> idToItemName;   
int nextItemId = 1001;                                                                                                               



int FileManager::getNextUserId(const string& userFile) {
    ifstream file(userFile);
    if (!file.is_open()) return 1;

    int maxId = 0;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        int id;
        ss >> id;
        maxId = max(maxId, id);
    }

    return maxId + 1;
}


Users FileManager::addNewUser(const string &userFile, const string &userName){
    int newId =  getNextUserId(userFile);

    ofstream file(userFile, ios::app);
    file << newId << " " << userName << endl;

    return Users(newId, userName);
}

static int getItemId(const string &itemName){
    if(itemNameToId.count(itemName)){
        return itemNameToId[itemName];
    }

    int id = nextItemId++;
    itemNameToId[itemName] = id;
    idToItemName[id] = itemName;
    return id;
}

void FileManager::addInteraction(const string &itemFile, int userId, const string &itemName, graph &g){
    int itemId = getItemId(itemName);

    ofstream file(itemFile, ios::app);
    file << userId << " " << itemName << endl;

    g.adjList(userId, itemId);
}

void FileManager::loadAllInteraction(const string &itemFile, graph &g){
    ifstream file(itemFile);
    int user;
    string item;

    while(file >> user >> item){
        int itemId = getItemId(item);
        g.adjList(user, itemId);
    }
}

string FileManager::getItemName(int itemId){
    return idToItemName[itemId];
}