#pragma once
#include "UILibFunc.hpp"

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
    // void reset() override;
};