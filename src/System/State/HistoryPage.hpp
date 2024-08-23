#pragma once
#include <iostream>
#include "UILibFunc.hpp"
// #include "../Component/HistoryManager.hpp"

using namespace std;

class HistoryPage : public Page
{
private:
    Texture2D historyTag;
    Button backButton;
    Button settingButton; 
    Button clearButton;

    int& currentScreen;
public:
    HistoryPage(int &currentScreen);
    ~HistoryPage();
    void display() const override;
    void handleEvent() override;
};