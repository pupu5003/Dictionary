#pragma once
#include "../src/System/State/SearchResPage.hpp"
#include "Dictionary.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>

using namespace std;

// enum 
enum Search
{
    Keyword = 0,
    Definition = 1
};

class SearchBar
{
private:
    Vector2 pos;
    Search typeSearch;
    vector<int> codePoints;
    dataSet data;
    bool isActive;
    vector<int> predict;
    int &currentScreen;
    Dictionary& dictionary;
public:
    SearchBar(Dictionary& dictionary, int &currentScreen, Vector2 pos);
    ~SearchBar();
    bool getActive() const;
    void display() const;
    void handleEvent();
};