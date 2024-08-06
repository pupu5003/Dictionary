#include "PracticePage.hpp"
using namespace std;

PracticePage::PracticePage(int &currentScreen) : currentScreen(currentScreen)
{
    practiceTag = LoadTexture("asset/Image/PracticeTag.png");

    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    byKeywordButton.setButton("asset/Image/ByKeywordButton.png", 397, 260);

    byDefinitionButton.setButton("asset/Image/ByDefinitionButton.png", 397, 418.67);

}

void PracticePage::display() const
{
    DrawTexture(practiceTag, 0, 0, WHITE);

    backButton.display();
    settingButton.display();
    byKeywordButton.display();
    byDefinitionButton.display();
}

void PracticePage::handleEvent()
{
   if (backButton.isPressed())
    {
        currentScreen = 0;
    }
    else if (settingButton.isPressed())
    {
        currentScreen = 4;
    }
    else if (byKeywordButton.isPressed())
    {
        cout << "By keyword button is pressed" << endl;
    }
    else if (byDefinitionButton.isPressed())
    {
        cout << "By definition button is pressed" << endl;
    }

}

PracticePage::~PracticePage()
{
    UnloadTexture(practiceTag);
}