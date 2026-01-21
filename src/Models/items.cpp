#include "items.h"

using namespace std;

Items::Items() : id(0), name("") {}
Items::Items(int id, string &name) : id(id), name(name) {}

int Items::getId(){
    return id;
}

string Items::getName(){
    return name;
}