#include "users.h"

using namespace std;

Users::Users() : id(0), name("") {}
Users::Users(int id, const string &name) : id(id), name(name) {}

int Users::getId() const{
    return id;
}

string Users::getName() const{
    return name;
}