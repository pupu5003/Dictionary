#include "FavoritePage.hpp"
using namespace std;

FavoritePage::FavoritePage(int &currentScreen) : currentScreen(currentScreen)
{
    favoriteTag = LoadTexture("asset/Image/FavouriteTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    clearButton.setButton("asset/Image/ClearAllButton.png", 490, 150);

}

void FavoritePage::display() const
{
    DrawTexture(favoriteTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();

    clearButton.display();
}

void FavoritePage::handleEvent()
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

FavoritePage::~FavoritePage()
{
    UnloadTexture(favoriteTag);
}