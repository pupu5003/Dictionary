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
    Keyword = (bool)0,
    Definition = (bool)1
};

class SearchBar
{
private:
    Texture2D curDataSet[5];   
    Texture2D dataSetOptions;
    Texture2D curTypeSearch[2];
    Vector2 pos;
    Rectangle dataSetBut;
    Rectangle typeSearchBut;
    bool typeSearch;
    vector<int> codePoints;
    dataSet data;
    bool typing, choseeData;
    vector<int> predict;
    int &currentScreen;
    Dictionary& dictionary;
public:
    SearchBar(Dictionary& dictionary, int &currentScreen, Vector2 pos);
    ~SearchBar();
    bool getActive() const;
    void resetPredict();
    void display() const;
    void handleEvent();
};