#include "FavoritePage.hpp"
using namespace std;

#define VISIBLE_HISTORY_ITEMS 4

FavoritePage::FavoritePage(int &currentScreen, Dictionary &dictionary) : currentScreen(currentScreen), dictionary(dictionary)
{
    favoriteTag = LoadTexture("asset/Image/FavouriteTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    clearButton.setButton("asset/Image/ClearAllButton.png", 490, 150);

    Box = LoadTexture("asset/Image/FavoriteBox.png");
    XButton = LoadTexture("asset/Image/XImage.png");
    fontRussoOne = LoadFontEx("asset/Font/Russo_One.ttf", 200, 0, 250);
}

void FavoritePage::display() const
{
    DrawTexture(favoriteTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();

    clearButton.display();

    for (int i = 0; i < dictionary.favorite[engEng].size() && i < VISIBLE_HISTORY_ITEMS; i++) {
        Rectangle historyBox = {80, (float)257 + 114*i, 1043, 75};
        Rectangle xButtonBox = {1163, historyBox.y + 20, XButton.height, XButton.width};
        DrawTexture(Box, historyBox.x, historyBox.y, WHITE);
        DrawTexture(XButton, xButtonBox.x, xButtonBox.y, WHITE);

        // Draw word and description
        const char* text2 = dictionary.favorite[engEng][i].word.c_str();
        int fontSize2 = 40;
        float spacing2 = 1.0f; // Spacing between letters
        Vector2 textSize2 = MeasureTextEx(fontRussoOne, text2, fontSize2, spacing2);
        float posY = historyBox.y + (historyBox.height - textSize2.y) / 2;
        DrawTextEx(fontRussoOne, text2, {historyBox.x + 40, posY}, fontSize2, spacing2, BLACK);
    }

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
        for (auto& word : dictionary.favorite[engEng]) {
            word.isFavorite = false;
        }
        dictionary.favorite[engEng].clear(); 
    }

    for (int i = 0; i < dictionary.favorite[engEng].size(); i++) {
        Rectangle historyBox = {80, (float)257 + 114*i, 1043, 75};
        Rectangle xButtonBox = {1163, historyBox.y + 20, XButton.height, XButton.width};
        DrawTexture(Box, historyBox.x, historyBox.y, WHITE);
        DrawTexture(XButton, xButtonBox.x, xButtonBox.y, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), xButtonBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            dictionary.removeFavorite(dictionary.favorite[engEng][i].id, engEng);
            break;
        }
    }    

}

FavoritePage::~FavoritePage()
{
    UnloadTexture(favoriteTag);
}