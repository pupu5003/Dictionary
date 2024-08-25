#include "FavoritePage.hpp"
#include "SearchResPage.hpp"
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
    detailButton.setButton("asset/Image/DetailButton.png", 998, 237, 1.1);
    detailButton.enable(); xButton.enable();

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
        detailButton.display(0, i * gap + scroll);

        
        int index = favorite.size() - i - 1;
        const Word &word = dictionary.getWord(favorite[index].first, favorite[index].second);
        
        DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[word.data].c_str(), { 142, 226 + i * gap + scroll}, 25, 0.5f, BLACK);

        float width = MeasureTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), 40, 0.5f).x;
        DrawTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), { 620 - width/2, 235 + i * gap + scroll}, 40, 0.5f, BLACK);
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
    resetUpDownWord();
    
    if (backButton.isPressed())
    {
        upWord = 0; downWord = -1;
        scroll = 0;
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        upWord = 0; downWord = -1;
        scroll = 0;
        currentScreen = SETTING;
    }
    else if (clearButton.isPressed())
    {
        dictionary.removeAllFavorite();
        upWord = 0; downWord = -1;
    }
    else
    {
        for (int i = upWord; i <= downWord; i++)
        {
            if (xButton.isPressed(0, i * gap + scroll))
            {
                int index = favorite.size() - i - 1;
                dictionary.removeFavorite(favorite[index].first, favorite[index].second);
                resetUpDownWord();
                break;
            }
            else if (detailButton.isPressed(0, i * gap + scroll))
            {
                int index = favorite.size() - i - 1;
                SearchResPage::setSearchWord(&(dictionary.getWord(favorite[index].first, favorite[index].second)));
                upWord = 0; downWord = -1;
                currentScreen = SEARCH_RES;
                break;
            }
        }
    }

   

}

void FavoritePage::resetUpDownWord()
{
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
}

FavoritePage::~FavoritePage()
{
    UnloadTexture(favoriteTag);
    UnloadTexture(barrier);
    UnloadTexture(Box);
}