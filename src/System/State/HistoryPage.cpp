#include "HistoryPage.hpp"
using namespace std;

HistoryPage::HistoryPage()
{
    historyTag = LoadTexture("asset/Image/HistoryTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    clearButton.setButton("asset/Image/ClearAllButton.png", 490, 150);
}

void HistoryPage::display() const
{
    DrawTexture(historyTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();

    clearButton.display();
}

void HistoryPage::handleEvent(int &currentScreen)
{
    if (backButton.isPressed())
    {
        currentScreen = 0;
    }
    else if (settingButton.isPressed())
    {
        currentScreen = 4;
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