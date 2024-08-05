#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/State/Component/page.hpp"
#include <../src/System/State/Component/button.hpp>
#include <../asset/Color/color.hpp>

class Home : public Page
{
private:
    Texture2D homeTag;
    Button historyButton;
    Button favoriteButton;
    Button practiceButton;
    Button settingButton; 
public:
    Home();
    ~Home();
    void display() const override;
    void handleEvent() override;
};