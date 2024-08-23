#include "HistoryPage.hpp"
using namespace std;

HistoryPage::HistoryPage(int &currentScreen) : currentScreen(currentScreen)
{
    historyTag = LoadTexture("asset/Image/HistoryTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    clearButton.setButton("asset/Image/ClearAllButton.png", 531, 124);

}

void HistoryPage::display() const
{
    DrawTexture(historyTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();

    clearButton.display();

    // display history list
    Texture2D hisRec = LoadTexture("asset/Image/HistoryRec.png");
    // for (int i = 0; i < historyList.size(); i++)
    // {
        
    // }
}

void HistoryPage::handleEvent()
{
    if (backButton.isPressed())
    {
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        currentScreen = SETTING;
    }
    else if (clearButton.isPressed())
    {
        cout << "Clear button is pressed" << endl;
    }
}

HistoryPage::~HistoryPage()
{
    UnloadTexture(historyTag);
}