#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>

class AddWordPage : public Page
{
private:
    Texture2D AddWordTag;
    Texture2D keywordTag;
    Texture2D definitionTag;
    Texture2D keywordBox;
    Texture2D definitionBox;
    Button backButton;
    Button settingButton; 
    Button addNewButton;

    int& currentScreen;

public:
    AddWordPage(int &currentScreen);
    ~AddWordPage();
    void display() const override;
    void handleEvent() override;
};