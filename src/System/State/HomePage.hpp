#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>

class HomePage : public Page
{
private:
    Texture2D homeTag;
    Button historyButton;
    Button favoriteButton;
    Button practiceButton;
    Button settingButton; 
public:
    HomePage();
    ~HomePage();
    void display() const override;
    void handleEvent(int &currentScreen) override;
};