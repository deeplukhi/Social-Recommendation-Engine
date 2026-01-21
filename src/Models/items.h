#ifndef ITEMS_H
#define ITEMS_H
#include<string>

using namespace std;

class Items{
    private:
        int id;
        string name;
    public:
        Items();
        Items(int id, string &name);

        int getId();
        string getName();
};

#endif