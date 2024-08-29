#include "SettingPage.hpp"
using namespace std;

SettingPage::SettingPage(int &currentScreen, function<void()> resetData)
    :currentScreen(currentScreen), resetData(resetData)
{
    
    settingTag = LoadTexture("asset/Image/SettingTag.png");

    homeButton.setButton("asset/Image/home_ic.png", 45, 31);

    resetButton.setButton("asset/Image/ResetButton.png", 397, 260);

    addWordButton.setButton("asset/Image/AddWordButton.png", 397, 418.87);
    
}

void SettingPage::display() const
{
    DrawTexture(settingTag, 0, 0, WHITE);

    homeButton.display();
    resetButton.display();
    addWordButton.display(); 
    confirmDialog.display();   
}

void SettingPage::handleEvent()
{
    if (confirmDialog.isShown())
    {   
       confirmDialog.handleEvent();
    }
    else
    if (homeButton.isPressed())
    {
        currentScreen = HOME;
    }
    else if (resetButton.isPressed())
    {
        confirmDialog.show(resetData);
    }
    else if (addWordButton.isPressed())
    {
        currentScreen = ADD_WORD;
    }
}

SettingPage::~SettingPage()
{
    UnloadTexture(settingTag);
}

void SettingPage::reset()
{
    // reset
}