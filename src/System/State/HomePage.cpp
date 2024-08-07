#include "HomePage.hpp"
#include <chrono>
using namespace std;

int random(int min, int max)
{
    srand(chrono::system_clock::now().time_since_epoch().count());
    return rand() % (max - min + 1) + min;
}

HomePage::HomePage(int &currentScreen, Dictionary &dictionary) : currentScreen(currentScreen), dictionary(dictionary)
{
    
    homeTag = LoadTexture("asset/Image/HomeTag.png");

    historyButton.setButton("asset/Image/HistoryButton.png", 196.25, 204.81);

    favoriteButton.setButton("asset/Image/FavouriteButton.png", 504.88, 204.81);
    
    practiceButton.setButton("asset/Image/PracticeButton.png", 813.51, 204.81);
    
    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    like.setButton("asset/Image/Heart_ic.png", 870, 326, 1.1);

    liked.setButton("asset/Image/Heart1_ic.png", 861, 328, 1.1);

    edit.setButton("asset/Image/Edit_ic.png", 935, 324, 1.1);
    
    changeWord.setButton("asset/Image/Reload_ic.png", 990, 324, 1.1);

    wordCard.setButton("asset/Image/WordCard.png", 181, 296);
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

    wordCard.display();
    like.display();
    edit.display();
    changeWord.display();

    DrawLine(107, 281, 1134, 281, BLACK);
}

void HomePage::handleEvent()
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