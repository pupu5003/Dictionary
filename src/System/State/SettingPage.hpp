#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
using namespace std;

class SettingPage : public Page
{
private:
    Texture2D settingTag;
    Button backButton;  
    Button resetButton;
    Button addWordButton;

    int& currentScreen;
public:
    SettingPage(int &currentScreen);
    ~SettingPage();
    void display() const override;
    void handleEvent() override;
};