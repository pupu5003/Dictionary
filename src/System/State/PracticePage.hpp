#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
using namespace std;

class PracticePage : public Page
{
private:
    Texture2D practiceTag;
    Button backButton;  
    Button settingButton;
    Button byKeywordButton;
    Button byDefinitionButton;

    int& currentScreen;
public:
    PracticePage(int &currentScreen);
    ~PracticePage();
    void display() const override;
    void handleEvent() override;
};