#pragma once
#include "../src/System/State/SearchResPage.hpp"
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
    int &currentScreen;
    Dictionary& dictionary;
public:
    SearchBar(Dictionary& dictionary, int &currentScreen);
    ~SearchBar();
    // bool isHandle() const;
    void display() const;
    void handleEvent();
};