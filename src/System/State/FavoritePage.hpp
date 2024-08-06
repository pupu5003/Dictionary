#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>

class FavoritePage : public Page
{
private:
    Texture2D favoriteTag;
    Button backButton;
    Button settingButton; 
    Button clearButton;

    int& currentScreen;

public:
    FavoritePage(int &currentScreen);
    ~FavoritePage();
    void display() const override;
    void handleEvent() override;
};