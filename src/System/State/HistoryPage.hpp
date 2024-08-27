#pragma once
#include <iostream>
#include <raylib.h>
#include "UILibFunc.hpp"

class HistoryPage : public Page
{
private:
    Texture2D historyTag;
    Texture2D barrier;
    Texture2D Box;
    Button xButton;
    Button backButton;
    Button settingButton; 
    Button clearButton;
    Button detailButton;
    DialogYesNo confirmDialog;

    float scroll;

    int upWord, downWord;
    int& currentScreen;
    vector<pair<dataSet,int>>& history;
    Dictionary& dictionary;

public:
    HistoryPage(int &currentScreen, Dictionary &dictionary);
    ~HistoryPage();
    void resetUpDownWord();
    void display() const override;
    void handleEvent() override;
};