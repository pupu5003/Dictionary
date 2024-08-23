#include "SearchBar.hpp"

using namespace std;


SearchBar::SearchBar(Dictionary& dictionary, int& currentScreen) : dictionary(dictionary), currentScreen(currentScreen)
{
    isHandle = false;
}

SearchBar::~SearchBar()
{
}

void SearchBar::display() const
{
    DrawRectangle(339.41, 102, 580.74, 61, WHITE);
    DrawRectangleLines(339.41, 102, 580.74, 61, BLACK); 

    DrawTextCodepoints(FontHelper::getInstance().getFont(Inter), (int*)(codePoints.data()), (int)codePoints.size(), {350, 110}, 40, 0.5, BLACK);

    //print predict
    if (isHandle)
    for (int i = 0; i < predict.size(); i++)
    {
        Word& word = dictionary.getWord(engEng, predict[i]);
        DrawRectangle(339.41, 163 + 61 * i, 580.74, 61, WHITE);
        DrawTextEx(FontHelper::getInstance().getFont(Inter), word.word.c_str(), {(float)350, (float)(163 + 61 * i)}, 40, 0.5, BLACK);
    }

}

void SearchBar::handleEvent()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {339.41, 102, 580.74, 61}))
    {
        isHandle = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isHandle = false;
    }

    for (float i = 0; i < predict.size(); i++)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {339.41, 163 + 61 * i, 580.74, 61}))
        {
            isHandle = false;
            SearchResPage::setSearchWord(&dictionary.getWord(engEng, predict[i]));
            currentScreen = 0;
            dictionary.addHistory(engEng, predict[i]);
            return;
        }
    }

    if (isHandle == false)
    {
        return;
    }
    int key = GetCharPressed();
    while(key > 0)
    {
        if (key >= 32 && key <= 999999)
        {
            if (key >= 65 && key <= 90)
            {
                key += 32;
            }
            cout << key << endl;
            codePoints.push_back(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (codePoints.size() > 0)
        {
            codePoints.pop_back();
        }
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        isHandle = false;
    }

    if (codePoints.size() > 0)
    {
        predict = dictionary.predict(codePoints);
    }
    else
    {
        predict.clear();
    }

    

}