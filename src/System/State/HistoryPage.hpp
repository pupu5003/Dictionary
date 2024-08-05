#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>

class HistoryPage : public Page
{
private:
    Texture2D historyTag;
    Button backButton;
    Button settingButton; 
    Button clearButton;

public:
    HistoryPage();
    ~HistoryPage();
    void display() const override;
    void handleEvent(int &currentScreen) override;
};