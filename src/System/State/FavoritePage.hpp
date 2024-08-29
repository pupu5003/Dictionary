#pragma once
#include <iostream>
#include <raylib.h>
#include "UILibFunc.hpp"

class FavoritePage : public Page
{
private:
    Texture2D favoriteTag;
    Texture2D barrier;
    Texture2D Box;
    Button xButton;
    Button backButton;
    Button settingButton; 
    Button clearButton;
    Button detailButton;
    DialogYesNo confirmDialog;
    Texture2D curDataSet[6];
    Texture2D dataSetOptions;
    Rectangle dataSetBut;
    int data;
    bool choseData;

    float scroll;

    int upWord, downWord;
    int& currentScreen;
    vector<pair<dataSet,int>>& favorite;
    Dictionary& dictionary;

public:
    FavoritePage(int &currentScreen, Dictionary &dictionary);
    ~FavoritePage();
    void display() const override;
    void resetUpDownWord();
    void handleEvent() override;
    void reset() override;
};