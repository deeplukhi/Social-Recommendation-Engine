#ifndef USERS_H
#define USERS_H
#include<string>

using namespace std;

class Users{
    private:
        int id;
        string name;
    public:
        Users();
        Users(int id, const string &name);

        int getId() const;
        string getName() const;
};

#endif