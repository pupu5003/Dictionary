#include "SearchBar.hpp"
#include "../src/System/State/PredictionDetailPage.hpp"
#include <algorithm>

using namespace std;

#define STRAIGHT_TO_SEARCH_RES 2

const float widthBar = 685;
const float heightBar = 54;
const float gapTextX = 10.6f;
const float gapTextY = 6;
const int limSymbol = 35;
const int limHIs = 6;
const int limitPredictPrint = 10;

Search SearchBar::typeSearch = Keyword;
dataSet SearchBar::data = engEng;
vector<int> SearchBar::codePoints;
vector<int> SearchBar::predict;

SearchBar::SearchBar(Dictionary& dictionary, int& currentScreen, Vector2 pos) : dictionary(dictionary), pos(pos), currentScreen(currentScreen)
{
    typing = false;
    choseeData = false;
    typeSearch = Keyword;
    data = engEng;
    codePoints.clear();
    predict.clear();

    curDataSet[0] = LoadTexture("asset/Image/engEng.png");
    curDataSet[1] = LoadTexture("asset/Image/engVie.png");
    curDataSet[2] = LoadTexture("asset/Image/vieEng.png");
    curDataSet[3] = LoadTexture("asset/Image/emoji.png");
    curDataSet[4] = LoadTexture("asset/Image/slang.png");
    dataSetOptions = LoadTexture("asset/Image/dataSetOptions.png");

    optDataSet[0] = LoadTexture("asset/Image/dataSet.png");
    optDataSet[1] = LoadTexture("asset/Image/engEng1.png");
    optDataSet[2] = LoadTexture("asset/Image/engVie1.png");
    optDataSet[3] = LoadTexture("asset/Image/vieEng1.png");
    optDataSet[4] = LoadTexture("asset/Image/emoji1.png");
    optDataSet[5] = LoadTexture("asset/Image/slang1.png");

    curTypeSearch[0] = LoadTexture("asset/Image/keywordS.png");
    curTypeSearch[1] = LoadTexture("asset/Image/definitionS.png");
    lockUpic = LoadTexture("asset/Image/lockUpic.png");
    historySic = LoadTexture("asset/Image/historySic.png");

    dataSetBut = {pos.x - dataSetOptions.width, pos.y, (float)dataSetOptions.width, heightBar};
    typeSearchBut = {pos.x + widthBar, pos.y, (float)curTypeSearch[1].width, heightBar};
    cursorPos = 0;
    frame = 0;
    cursorFlick = false;
    resetPredict();
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

    UnloadTexture(lockUpic);
    UnloadTexture(historySic);

    UnloadTexture(optDataSet[0]);
    UnloadTexture(optDataSet[1]);
    UnloadTexture(optDataSet[2]);
    UnloadTexture(optDataSet[3]);
    UnloadTexture(optDataSet[4]);
    UnloadTexture(optDataSet[5]);
}

void SearchBar::display() const
{
    int printNumber = std::min((int)limitPredictPrint, (int)predict.size());

    if (choseeData) {
        DrawTexture(dataSetOptions, dataSetBut.x, dataSetBut.y, WHITE);
        for (int j = 0; j < 6; ++j) {
            if (CheckCollisionPointRec(GetMousePosition(), {dataSetBut.x, dataSetBut.y + dataSetBut.height * j, dataSetBut.width, dataSetBut.height})) {
                DrawTexture(optDataSet[j], dataSetBut.x, dataSetBut.y + dataSetBut.height * j, LIGHTGRAY);
            }
        }
    }
    else {
        if (CheckCollisionPointRec(GetMousePosition(), dataSetBut))
            DrawTexture(curDataSet[data], dataSetBut.x, dataSetBut.y, LIGHTGRAY);
        else DrawTexture(curDataSet[data], dataSetBut.x, dataSetBut.y, WHITE);
    }

    if (CheckCollisionPointRec(GetMousePosition(), typeSearchBut))
        DrawTexture(curTypeSearch[typeSearch], typeSearchBut.x, typeSearchBut.y, LIGHTGRAY);
    else
        DrawTexture(curTypeSearch[typeSearch], typeSearchBut.x, typeSearchBut.y, WHITE);

    DrawRectangleRec({pos.x, pos.y, widthBar, heightBar}, WHITE);
    if (typing)
        DrawRectangleLinesEx({pos.x, pos.y, widthBar, heightBar}, 1.4f, BLUE); 
    else
        DrawRectangleLinesEx({pos.x, pos.y, widthBar, heightBar}, 1.2f, BLACK); 

    
    if ((int)codePoints.size() > 0)
    {
        int start = max(0, (int)codePoints.size() - limSymbol);
        int sz = min((int)codePoints.size(), limSymbol);
        while(GetCodepointsWidth(FontHelper::getInstance().getFont(Inter), (int*)(&codePoints[start]), sz, 37, 0.5f) > widthBar - 2*gapTextX)
        {
            start++;
            sz--;
        }
        DrawTextCodepoints(FontHelper::getInstance().getFont(Inter), (int*)(&codePoints[start]), sz, {pos.x + gapTextX, pos.y + gapTextY}, 37, 0.5f, BLACK);
        if (cursorFlick && typing)
        {
            float width = GetCodepointsWidth(FontHelper::getInstance().getFont(Inter), (int*)(&codePoints[start]), sz, 37, 0.5f);
            DrawTextEx(FontHelper::getInstance().getFont(Inter), "|", {pos.x + gapTextX + width, pos.y + gapTextY}, 37, 0.5f, BLACK);
        }
    } else if (cursorFlick && typing)
    {
        DrawTextEx(FontHelper::getInstance().getFont(Inter), "|", {pos.x + gapTextX, pos.y + gapTextY}, 37, 0.5f, BLACK);
    }
    //print predict
    
    if (typing)
    {
        if (printNumber > 0)
        {
            float roundness = 0.15*300/(30 + heightBar * printNumber);
            DrawRectangleRounded({pos.x, pos.y + heightBar, widthBar, 30 + heightBar * printNumber}, roundness, 0, WHITE);
        }
        for (int i = 0; i < printNumber; i++)
        {
            Word& word = dictionary.getWord(data, predict[i]);
            if (CheckCollisionPointRec(GetMousePosition(), {pos.x, pos.y + heightBar * (i + 1) + 15, widthBar, heightBar}))
            DrawRectangleRec({pos.x, pos.y + heightBar * (i + 1) + 15, widthBar, heightBar}, LIGHTGRAY);
          
            if ((int)codePoints.size() > 0)
                DrawTexture(lockUpic, pos.x + gapTextX - 8, pos.y + gapTextY + 15 + heightBar * (i + 1), WHITE);
            else
                DrawTexture(historySic, pos.x + gapTextX - 6, pos.y + gapTextY + 17 + heightBar * (i + 1), WHITE);
           
            DrawTextEx(FontHelper::getInstance().getFont(Inter), word.word.c_str(), {pos.x + gapTextX + 30, pos.y + gapTextY + 15 + heightBar * (i + 1)}, 37, 0.5f, BLACK);
        }
    }

}

void SearchBar::handleEvent()
{
    int printNumber = std::min((int)limitPredictPrint, (int)predict.size());

    if (CheckCollisionPointRec(GetMousePosition(), {pos.x, pos.y, widthBar, heightBar}))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

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
    for (float i = 0; i < printNumber; i++)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {pos.x + gapTextX, pos.y + gapTextY + heightBar * (i + 1), widthBar, heightBar}))
        {
            typing = false; choseeData = false; cursorFlick = false;
            frame = 0;
            // PredictionDetailPage::setSearchType(STRAIGHT_TO_SEARCH_RES);
            // PredictionDetailPage::setSearchWord(predict[i]);
            // SearchBar::setSearchType(STRAIGHT_TO_SEARCH_RES);
            SearchResPage::setSearchWord(&dictionary.getWord(data, predict[i]));
            dictionary.addHistory(data, predict[i]);
            currentScreen = SEARCH_RES;
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
        
        if (CheckCollisionPointRec(GetMousePosition(), {pos.x, pos.y, widthBar, heightBar}))
        {
            typing = true;
            cursorPos = codePoints.size();
        }
        else
        {
            if (typing)
            {
                frame = 0; cursorFlick = false;
            }
            typing = false;
        }
        if (CheckCollisionPointRec(GetMousePosition(), dataSetBut))
            choseeData = !choseeData;


    }
   
    if (typing == false) return;

    bool change = false;
    int key = GetCharPressed();
    int keyRightHere = key;
    int lengthNow = codePoints.size();
    while(key > 0)
    {
        if (key >= 32)
        {
            cout << key << endl;
            codePoints.insert(codePoints.begin() + cursorPos, key);
            cursorPos++;
            change = true;
        }
        keyRightHere = key;
        key = GetCharPressed();
    }
    int spareCodePoints = codePoints.size() - lengthNow;
    if (spareCodePoints > 1 || keyRightHere > 125) {    //KeyRightHere to determine if the vowel is right before the codepoint (this falls to spareCodePoints = 1)
        vector<int> tmp;
        tmp.assign(codePoints.end() - spareCodePoints, codePoints.end());
        for (int i = 0; i < 2*spareCodePoints; ++i)
            codePoints.pop_back();
        for (int i = 0; i < spareCodePoints; ++i)
            codePoints.push_back(tmp[i]);
        cursorPos -= spareCodePoints;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (cursorPos > 0)
        {
            codePoints.erase(codePoints.begin() + cursorPos - 1);
            cursorPos--;
            change = true;
        }
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        typing = false;
        choseeData = false;
        if (typeSearch == Keyword && predict.size() > 0 && codePoints.size() == dictionary.getWord(data, predict[0]).word.size()) {
            PredictionDetailPage::setSearchType(STRAIGHT_TO_SEARCH_RES);
            PredictionDetailPage::setSearchWord(predict[0]);
            dictionary.addHistory(data, predict[0]);
            currentScreen = PREDICTION_DETAIL;
            return;
        }
        else {
            if (typeSearch == Keyword) 
                PredictionDetailPage::setSearchType(0);
            else 
                PredictionDetailPage::setSearchType(1);
            std::string input;
            for (auto i : codePoints)
                input += static_cast<char>(i);
            PredictionDetailPage::setSearchInput(input);
            PredictionDetailPage::setPredictionList(predict);
            PredictionDetailPage::setDataSet(data);
            currentScreen = PREDICTION_DETAIL;
            return;
        }
    }

    if (change)
    {
        resetPredict();
    }  

    if (frame % 50 == 0)
    {
        cursorFlick = true;
        frame = 0;
    } 
    else if (frame % 25 == 0)
    {
        cursorFlick = false;
    }
    frame++;
}

void SearchBar::resetPredict()
{
    predict.clear();
    if ((int)codePoints.size() > 0)
    {
        if (typeSearch == Keyword)
            predict = dictionary.predictKeyword(data, codePoints);
        else if (typeSearch == Definition)
            predict = dictionary.predictDefinition(data, codePoints);
    }   
    else
    {
        vector<pair<dataSet, int>>& history = dictionary.getHistory();
        for (int i = 0; i < (int)history.size(); i++)
        if (history[i].first == data)
        {
            predict.push_back(history[i].second);
            if (predict.size() == limHIs) break;
        }
    }
}

bool SearchBar::getActive() const
{
    return (typing||choseeData);
}

void SearchBar::reset()
{
    typing = false;
    choseeData = false;
    codePoints.clear();
    predict.clear();
    cursorPos = 0;
    frame = 0;
    cursorFlick = false;
}
