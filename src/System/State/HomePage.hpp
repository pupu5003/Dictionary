#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
using namespace std;

class HomePage : public Page
{
private:
    Texture2D homeTag;
    Button historyButton;
    Button favoriteButton;
    Button practiceButton;
    Button settingButton; 

    int& currentScreen;
public:
    HomePage(int &currentScreen);
    ~HomePage();
    void display() const override;
    void handleEvent() override;
};