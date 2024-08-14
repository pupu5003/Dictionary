#include "SettingPage.hpp"
using namespace std;

SettingPage::SettingPage(int &currentScreen) : currentScreen(currentScreen)
{
    
    settingTag = LoadTexture("asset/Image/SettingTag.png");

    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    resetButton.setButton("asset/Image/ResetButton.png", 397, 260);

    addWordButton.setButton("asset/Image/AddWordButton.png", 397, 418.87);
    

}

void SettingPage::display() const
{
    DrawTexture(settingTag, 0, 0, WHITE);

    backButton.display();
    resetButton.display();
    addWordButton.display();    

}

void SettingPage::handleEvent()
{
   if (backButton.isPressed())
    {
        currentScreen = HOME;
    }
    else if (resetButton.isPressed())
    {
        cout << "Reset button is pressed" << endl;
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