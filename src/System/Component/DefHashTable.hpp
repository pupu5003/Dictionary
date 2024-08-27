#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "../src/System/State/TextHandle.hpp"
using namespace std;

struct Slot
{
    int value;
    vector<int> Ids;
    Slot *next;
    Slot();
    ~Slot();
};

class DefHashTable
{
private:
    static const int Base = 512;
    static const int MOD = 1000000009;
    static const int Size = 100433;
    Slot *table[Size];
    vector<int> count;
    pair<int,int> hashFunction(string &def);
    vector<pair<int,int>> splitnHash(string &def);
public:
    DefHashTable();
    ~DefHashTable();
    void insert(string &def, int Id);
    void remove(string &def, int Id);
    void setCountSize(int size);
    vector<int> predict(vector<int> &codePoints);

};