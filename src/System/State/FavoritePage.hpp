#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
#include <../src/System/Component/Dictionary.hpp>

class FavoritePage : public Page
{
private:
    Texture2D favoriteTag;
    Texture2D Box;
    Texture2D XButton;
    Button backButton;
    Button settingButton; 
    Button clearButton;
    Font fontRussoOne;

    int& currentScreen;
    Dictionary& dictionary;

public:
    FavoritePage(int &currentScreen, Dictionary &dictionary);
    ~FavoritePage();
    void display() const override;
    void handleEvent() override;
};