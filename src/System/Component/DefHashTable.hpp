#pragma once
#include <iostream>
#include <vector>
using namespace std;

class DefHashTable
{
private:

public:
    DefHashTable();
    ~DefHashTable();
    void insert(string &def, int Id);
    void remove(string &def);
};