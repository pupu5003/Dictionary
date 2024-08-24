#include "SearchBar.hpp"
using namespace std;

const float widthBar = 580.74f;
const float heightBar = 61;
const float gapTextX = 10.6f;
const float gapTextY = 8;


SearchBar::SearchBar(Dictionary& dictionary, int& currentScreen, Vector2 pos) : dictionary(dictionary), pos(pos), currentScreen(currentScreen)
{
    isActive = false;
    typeSearch = Definition;
    data = engEng;
}

SearchBar::~SearchBar()
{
}

void SearchBar::display() const
{
    DrawRectangleRec({pos.x, pos.y, widthBar, heightBar}, WHITE);
    DrawRectangleLinesEx({pos.x, pos.y, widthBar, heightBar}, 1.0f,  BLACK); 

    DrawTextCodepoints(FontHelper::getInstance().getFont(Inter), (int*)(codePoints.data()), (int)codePoints.size(), {pos.x + gapTextX, pos.y + gapTextY}, 40, 0.5f, BLACK);

    //print predict
    if (isActive)
    for (int i = 0; i < predict.size(); i++)
    {
        Word& word = dictionary.getWord(engEng, predict[i]);
        DrawRectangleRec({pos.x, pos.y + 61 * (i + 1), widthBar, heightBar}, WHITE);
        DrawTextEx(FontHelper::getInstance().getFont(Inter), word.word.c_str(), {pos.x + gapTextX, pos.y + gapTextY + heightBar * (i + 1)}, 40, 0.5f, BLACK);
    }

}

void SearchBar::handleEvent()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {pos.x, pos.y, widthBar, heightBar}))
    {
        isActive = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isActive = false;
    }

    for (float i = 0; i < predict.size(); i++)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {pos.x + gapTextX, pos.y + gapTextY + heightBar * (i + 1), widthBar, heightBar}))
        {
            isActive = false;
            SearchResPage::setSearchWord(&dictionary.getWord(engEng, predict[i]));
            currentScreen = 0;
            dictionary.addHistory(engEng, predict[i]);
            return;
        }
    }

    if (isActive == false)
    {
        return;
    }
    bool change = false;
    int key = GetCharPressed();
    while(key > 0)
    {
        if (key >= 32 && key <= 999999)
        {
            cout << key << endl;
            codePoints.push_back(key);
            change = true;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (codePoints.size() > 0)
        {
            codePoints.pop_back();
            change = true;
        }
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        isActive = false;
    }

    if (change && codePoints.size() > 0)
    {
        if (typeSearch == Keyword)
        predict = dictionary.predictKeyword(data, codePoints);
        else
        predict = dictionary.predictDefinition(data, codePoints);
    }
    else if (change)
    {
        predict.clear();
    }

}

bool SearchBar::getActive() const
{
    return isActive;
}