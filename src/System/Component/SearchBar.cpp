#include "SearchBar.hpp"
using namespace std;

const float widthBar = 685;
const float heightBar = 54;
const float gapTextX = 10.6f;
const float gapTextY = 6;


SearchBar::SearchBar(Dictionary& dictionary, int& currentScreen, Vector2 pos) : dictionary(dictionary), pos(pos), currentScreen(currentScreen)
{
    typing = false;
    choseeData = false;
    typeSearch = Keyword;
    data = engEng;

    curDataSet[0] = LoadTexture("asset/Image/engEng.png");
    curDataSet[1] = LoadTexture("asset/Image/engVie.png");
    curDataSet[2] = LoadTexture("asset/Image/vieEng.png");
    curDataSet[3] = LoadTexture("asset/Image/emoji.png");
    curDataSet[4] = LoadTexture("asset/Image/slang.png");
    dataSetOptions = LoadTexture("asset/Image/dataSetOptions.png");
    curTypeSearch[0] = LoadTexture("asset/Image/keywordS.png");
    curTypeSearch[1] = LoadTexture("asset/Image/definitionS.png");

    dataSetBut = {pos.x - dataSetOptions.width, pos.y, (float)dataSetOptions.width, heightBar};
    typeSearchBut = {pos.x + widthBar, pos.y, (float)curTypeSearch[1].width, heightBar};
}

SearchBar::~SearchBar()
{
    UnloadTexture(curDataSet[0]);
    UnloadTexture(curDataSet[1]);
    UnloadTexture(curDataSet[2]);
    UnloadTexture(curDataSet[3]);
    UnloadTexture(curDataSet[4]);
    UnloadTexture(dataSetOptions);
    UnloadTexture(curTypeSearch[0]);
    UnloadTexture(curTypeSearch[1]);
}

void SearchBar::display() const
{
    if (choseeData)
        DrawTexture(dataSetOptions, dataSetBut.x, dataSetBut.y, WHITE);
    else
        DrawTexture(curDataSet[data], dataSetBut.x, dataSetBut.y, WHITE);

    DrawTexture(curTypeSearch[typeSearch], typeSearchBut.x, typeSearchBut.y, WHITE);

    DrawRectangleRec({pos.x, pos.y, widthBar, heightBar}, WHITE);
    if (typing)
        DrawRectangleLinesEx({pos.x, pos.y, widthBar, heightBar}, 1.4f, BLUE); 
    else
        DrawRectangleLinesEx({pos.x, pos.y, widthBar, heightBar}, 1.2f, BLACK); 

    DrawTextCodepoints(FontHelper::getInstance().getFont(Inter), (int*)(codePoints.data()), (int)codePoints.size(), {pos.x + gapTextX, pos.y + gapTextY}, 37, 0.5f, BLACK);

    //print predict
    if (typing)
    {
        if (predict.size() > 0)
        {
            float roundness = 0.15*300/(heightBar * predict.size());
            DrawRectangleRounded({pos.x, pos.y + heightBar, widthBar, heightBar * predict.size()}, roundness, 0, WHITE);
        }
        for (int i = 0; i < predict.size(); i++)
        {
            Word& word = dictionary.getWord(data, predict[i]);
            // DrawRectangleRec({pos.x, pos.y + heightBar * (i + 1), widthBar, heightBar}, WHITE);
            DrawTextEx(FontHelper::getInstance().getFont(Inter), word.word.c_str(), {pos.x + gapTextX, pos.y + gapTextY + heightBar * (i + 1)}, 37, 0.5f, BLACK);
        }
    }

}

void SearchBar::handleEvent()
{
    if (choseeData)
    {
        for (int i = 0; i < 5; i++)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {dataSetBut.x, dataSetBut.y + heightBar * (i + 1), dataSetBut.width, heightBar}))
            {
                data = (dataSet)i;
                resetPredict();
                choseeData = false;
                break;
            }
        }
    }

    if (typing)
    for (float i = 0; i < predict.size(); i++)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {pos.x + gapTextX, pos.y + gapTextY + heightBar * (i + 1), widthBar, heightBar}))
        {
            typing = false; choseeData = false;
            SearchResPage::setSearchWord(&dictionary.getWord(data, predict[i]));
            currentScreen = 0;
            dictionary.addHistory(data, predict[i]);
            return;
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), typeSearchBut))
        {
            if (typeSearch == Keyword)
                typeSearch = Definition;
            else
                typeSearch = Keyword;
            resetPredict();
        }
        
        choseeData = false; typing = false;
        if (CheckCollisionPointRec(GetMousePosition(), {pos.x, pos.y, widthBar, heightBar}))
            typing = true;

        if (CheckCollisionPointRec(GetMousePosition(), dataSetBut))
            choseeData = true;


    }
   
    if (typing == false) return;

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
        typing = false;
        choseeData = false;
    }

    if (change)
    {
        resetPredict();
    }
}

void SearchBar::resetPredict()
{
    predict.clear();
    if (codePoints.size() > 0)
    {
        if (typeSearch == Keyword)
            predict = dictionary.predictKeyword(data, codePoints);
        else if (typeSearch == Definition)
            predict = dictionary.predictDefinition(data, codePoints);
    }   
    else
    {
        predict.clear();
    }
}

bool SearchBar::getActive() const
{
    return (typing||choseeData);
}