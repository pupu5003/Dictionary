#pragma once

#include "Dictionary.hpp"
#include <iostream>
#include <vector>

using namespace std;

// enum 

class SearchBar
{
private:
    vector<int> codePoints;
    bool isHandle;
    vector<int> predict;
    Dictionary& dictionary;
public:
    SearchBar(Dictionary& dictionary);
    ~SearchBar();
    // bool isHandle() const;
    void display() const;
    void handleEvent();
};