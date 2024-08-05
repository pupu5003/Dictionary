#include "HomePage.hpp"
using namespace std;

HomePage::HomePage()
{
    
    homeTag = LoadTexture("asset/Image/HomeTag.png");

    historyButton.setButton("asset/Image/HistoryButton.png", 196.25, 204.81);

    favoriteButton.setButton("asset/Image/FavouriteButton.png", 504.88, 204.81);
    
    practiceButton.setButton("asset/Image/PracticeButton.png", 813.51, 204.81);
    
    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);
}

void HomePage::display() const
{
    DrawTexture(homeTag, 0, 0, WHITE);

    // Texture2D temp = LoadTexture("asset/Image/HistoryButton.png");

    // DrawTexture(temp, 90.25, 90.81, WHITE);

    settingButton.display();
   
    historyButton.display();
    favoriteButton.display();
    practiceButton.display();

    DrawLine(107, 281, 1134, 281, BLACK);
}

void HomePage::handleEvent(int &currentScreen)
{
    if (historyButton.isPressed())
    {
        currentScreen = 1;
    }
    else if (favoriteButton.isPressed())
    {
        currentScreen = 2;
    }
    else if (practiceButton.isPressed())
    {
        currentScreen = 3;
    }
    else if (settingButton.isPressed())
    {
        currentScreen = 4;
    }

}

HomePage::~HomePage()
{
    UnloadTexture(homeTag);
}