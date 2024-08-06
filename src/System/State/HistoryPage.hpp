#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../src/System/Component/HistoryManager.hpp>
#include <../asset/Color/color.hpp>
using namespace std;

class HistoryPage : public Page
{
private:
    Texture2D historyTag;
    Button backButton;
    Button settingButton; 
    Button clearButton;

    int& currentScreen;
    HistoryManager& hisManeger;
public:
    HistoryPage(int &currentScreen, HistoryManager& hisManeger);
    ~HistoryPage();
    void display() const override;
    void handleEvent() override;
};