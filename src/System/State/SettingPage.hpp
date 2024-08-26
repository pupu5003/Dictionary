#pragma once
#include "UILibFunc.hpp"

using namespace std;
class Dictionary;
class SettingPage : public Page
{
private:
    Texture2D settingTag;
    Button backButton;  
    Button resetButton;
    Button addWordButton;
    DialogYesNo confirmDialog;

    int& currentScreen;
    Dictionary &dictionary;
public:
    SettingPage(int &currentScreen, Dictionary& dictionary);
    ~SettingPage();
    void display() const override;
    void handleEvent() override;
};