#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
#include <../src/System/Component/Dictionary.hpp>
#include "UILibFunc.hpp"

class FavoritePage : public Page
{
private:
    Texture2D favoriteTag;
    Texture2D Box;
    Button xButton;
    Button backButton;
    Button settingButton; 
    Button clearButton;

    float scroll;

    int upWord, downWord;
    int& currentScreen;
    vector<pair<dataSet,int>>& favorite;
    Dictionary& dictionary;

public:
    FavoritePage(int &currentScreen, Dictionary &dictionary);
    ~FavoritePage();
    void display() const override;
    void handleEvent() override;
};