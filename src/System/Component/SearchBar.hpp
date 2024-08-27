#pragma once
#include "Dictionary.hpp"
#include "raylib.h"
#include "TextInputBox.hpp"
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
    Texture2D optDataSet[6];   
    Texture2D dataSetOptions;
    Texture2D curTypeSearch[2];
    Texture2D lockUpic;
    Texture2D historySic;
    Vector2 pos;
    Rectangle dataSetBut;
    Rectangle typeSearchBut;
    
    static Search typeSearch;
    static dataSet data;
    static vector<int> codePoints;
    static vector<int> predict;
    int cursorPos;
    int frame;
    bool typing, choseeData, cursorFlick;
    int &currentScreen;
    Dictionary& dictionary;

public:
    SearchBar(Dictionary& dictionary, int &currentScreen, Vector2 pos);
    ~SearchBar();
    bool getActive() const;
    void resetPredict();
    void display() const;
    void handleEvent();
    // static void resetCodePoints();
};