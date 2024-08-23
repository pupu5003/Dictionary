#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
#include <../src/System/Component/Dictionary.hpp>
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

    float scroll;

    int upWord, downWord;
    int& currentScreen;
    vector<pair<dataSet,int>>& history;
    Dictionary& dictionary;

public:
    HistoryPage(int &currentScreen, Dictionary &dictionary);
    ~HistoryPage();
    void display() const override;
    void handleEvent() override;
};