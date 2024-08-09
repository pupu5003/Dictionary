#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
#include <../src/System/Component/Dictionary.hpp>
using namespace std;

class HomePage : public Page
{
private:
    Texture2D homeTag;
    Button historyButton;
    Button favoriteButton;
    Button practiceButton;
    Button settingButton; 
    Button like;
    Button liked;
    Button changeWord;
    Button edit;
    nButton wordCard;

    Word& randomWord;
    int& currentScreen;
    Dictionary& dictionary;

public:
    HomePage(int &currentScreen, Dictionary& dictionary);
    ~HomePage();
    void display() const override;
    void handleEvent() override;
};

void DrawTextBoxed(const char *text, Rectangle rec, int fontSize, float spacing, bool wordWrap);