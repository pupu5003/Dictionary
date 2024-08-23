#include "FavoritePage.hpp"
using namespace std;

#define visibleItems 7
#define scrollSpeed 4
#define gap 115
#define scrollUp 20
#define scrollDown -25

FavoritePage::FavoritePage(int &currentScreen, Dictionary &dictionary) : currentScreen(currentScreen), dictionary(dictionary), favorite(dictionary.getFavorite())
{
    favoriteTag = LoadTexture("asset/Image/FavouriteTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    clearButton.setButton("asset/Image/ClearAllButton.png", 531, 124);
    xButton.setButton("asset/Image/XImage.png", 1060, 237, 1.1);

    Box = LoadTexture("asset/Image/FavoriteBox.png");

    barrier = LoadTexture("asset/Image/SearchResTag.png");

    scroll = 0;
    
    upWord = 0; downWord = -1;
}

void FavoritePage::display() const
{
    
    for (int i = upWord; i <= downWord; i++)
    {   
        DrawTexture(Box, 120, 217 + i * gap + scroll, WHITE);
        xButton.display(0, i * gap + scroll);
        const Word &word = dictionary.getWord(favorite[i].first, favorite[i].second);
        DrawTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), { 172, 240 + i * gap + scroll}, 40, 0.5f, BLACK);
    }
    
    
    
    DrawTexture(barrier, 0, 0, WHITE);
    DrawTexture(favoriteTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();


    clearButton.display();

    DrawLine(107, 192, 1136, 192, BLACK);

}

void FavoritePage::handleEvent()
{
    scroll += GetMouseWheelMove() * scrollSpeed;
    if ((int)favorite.size() == 0)
    {
        upWord = 0; downWord = -1;
    }
    else
    {
        upWord = (int)(scrollDown - scroll) / gap - 1;
        if (upWord < 0) upWord = 0;
        downWord = min(upWord + visibleItems, (int)favorite.size() - 1);

        if (upWord == 0 && scroll > scrollUp) scroll = scrollUp;
        
        if (favorite.size() <= 4)
        {
            if (scroll < scrollDown) scroll = scrollDown;
        }
        else
        {
            if (downWord == favorite.size() - 1 && scroll + (downWord - 3) * gap < scrollDown) scroll = scrollDown - (downWord - 3) * gap;
        }

    }
    if (backButton.isPressed())
    {
        scroll = 0;
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        scroll = 0;
        currentScreen = SETTING;
    }
    else if (clearButton.isPressed())
    {
       dictionary.removeAllFavorite();
    }
    else
    {
        for (int i = upWord; i <= downWord; i++)
        {
            if (xButton.isPressed(0, i * gap + scroll))
            {
                dictionary.removeFavorite(favorite[i].first, favorite[i].second);
                break;
            }
        }
    }


}

FavoritePage::~FavoritePage()
{
    UnloadTexture(favoriteTag);
    UnloadTexture(barrier);
    UnloadTexture(Box);
}