#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include<string>
#include<unordered_map>
#include"../Graph/graph.h"
#include"../Models/users.h"

using namespace std;

class FileManager{
    public:
        static int getNextUserId(const string &userFile);

        static Users addNewUser(const string &userFile, const string &userName);

        static void addInteraction(const string &itemFile, int userId, const string &itemName, graph &g);

        static void loadAllInteraction(const string &itemFile, graph &g);

        static string getItemName(int itemId);

};

#endif