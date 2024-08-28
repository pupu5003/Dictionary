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
    function<void()> resetData;
    int& currentScreen;
public:
    SettingPage(int &currentScreen, function<void()> resetData);
    ~SettingPage();
    void display() const override;
    void handleEvent() override;
    void reset() override;
};