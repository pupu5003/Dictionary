#include "Home.hpp"
using namespace std;

Home::Home()
{
    homeTag = LoadTexture("asset/Image/homeTag.png");
    
    historyButton.loadTexture("asset/Image/historyButton.png");
    historyButton.setRect(196.25, 204.81, historyButton.texture.width, historyButton.texture.height);

    favoriteButton.loadTexture("asset/Image/favouriteButton.png");
    favoriteButton.setRect(504.88, 204.81, favoriteButton.texture.width, favoriteButton.texture.height);
    
    practiceButton.loadTexture("asset/Image/practiceButton.png");
    practiceButton.setRect(813.51, 204.81, practiceButton.texture.width, practiceButton.texture.height);
    
    settingButton.loadTexture("asset/Image/settings_ic.png");
    settingButton.setRect(1159, 23, settingButton.texture.width, settingButton.texture.height);
}

void Home::display() const
{
    DrawTexture(homeTag, 0, 0, WHITE);

    settingButton.display();
   
    historyButton.display();
    favoriteButton.display();
    practiceButton.display();

    DrawLine(107, 281, 1134, 281, BLACK);
}

void Home::handleEvent()
{
    if (historyButton.isPressed())
    {
        cout << "History button is pressed" << endl;
    }
    else if (favoriteButton.isPressed())
    {
        cout << "Favorite button is pressed" << endl;
    }
    else if (practiceButton.isPressed())
    {
        cout << "Practice button is pressed" << endl;
    }
    else if (settingButton.isPressed())
    {
        cout << "Setting button is pressed" << endl;
    }
}

Home::~Home()
{
    UnloadTexture(homeTag);
}