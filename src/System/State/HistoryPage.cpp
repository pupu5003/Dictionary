#include "HistoryPage.hpp"
#include "SearchResPage.hpp"
using namespace std;

#define visibleItems 7
#define scrollSpeed 16
#define gap 115
#define scrollUp 20
#define scrollDown -25


HistoryPage::HistoryPage(int &currentScreen, Dictionary &dictionary) : currentScreen(currentScreen), dictionary(dictionary), history(dictionary.getHistory())
{
    historyTag = LoadTexture("asset/Image/HistoryTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    clearButton.setButton("asset/Image/ClearAllButton.png", 531, 124);
    xButton.setButton("asset/Image/XImage.png", 1060, 237, 1.1);
    detailButton.setButton("asset/Image/DetailButton.png", 998, 237, 1.1);
    detailButton.enable(); xButton.enable();

    Box = LoadTexture("asset/Image/FavoriteBox.png");

    barrier = LoadTexture("asset/Image/SearchResTag.png");

    curDataSet[0] = LoadTexture("asset/Image/engEng1.png");
    curDataSet[1] = LoadTexture("asset/Image/engVie1.png");
    curDataSet[2] = LoadTexture("asset/Image/vieEng1.png");
    curDataSet[3] = LoadTexture("asset/Image/emoji1.png");
    curDataSet[4] = LoadTexture("asset/Image/slang1.png");
    curDataSet[5] = LoadTexture("asset/Image/all1.png");
    curDataSet[6] = LoadTexture("asset/Image/dataset.png");
    dataSetOptions = LoadTexture("asset/Image/dataSetOptions3.png");
    dataSetBut = {160, 128, 204, 59};

    choseData = false;
    data = -1;

    scroll = 0;
    
    upWord = 0; downWord = -1;
}

void HistoryPage::display() const
{

    for (int j = upWord, i = upWord; i <= downWord && j < history.size(); i++, j++)
    {   
        int index = 0;
        if (data == 5) index = history.size() - i - 1;
        else index = history.size() - j - 1;
        if (data != -1 && data != 5 && history[index].first != data) {i--; continue;}
        DrawTexture(Box, 120, 217 + i * gap + scroll, WHITE);
        xButton.display(0, i * gap + scroll);
        detailButton.display(0, i * gap + scroll);

        const Word &word = dictionary.getWord(history[index].first, history[index].second);
       
        DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[word.data].c_str(), { 142, 226 + i * gap + scroll}, 25, 0.5f, BLACK);

        float width = MeasureTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), 40, 0.5f).x;
        DrawTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), { 620 - width/2, 235 + i * gap + scroll}, 40, 0.5f, BLACK);
    }
    
    DrawTexture(barrier, 0, 0, WHITE);
    DrawTexture(historyTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();

    if (choseData) DrawTexture(dataSetOptions, dataSetBut.x, dataSetBut.y, WHITE);
    else DrawTexture(curDataSet[(data == -1 ? 6 : data)], dataSetBut.x, dataSetBut.y, WHITE);

    clearButton.display();

    DrawLine(107, 192, 1136, 192, BLACK);

    confirmDialog.display();

}

void HistoryPage::handleEvent()
{
    if (confirmDialog.isShown())
    {
        confirmDialog.handleEvent();
        return;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (choseData)
        {
            for (int i = 0; i < 7; i++)
            {
                if (CheckCollisionPointRec(GetMousePosition(), {dataSetBut.x, dataSetBut.y + dataSetBut.height * i,  dataSetBut.width,  dataSetBut.height}))
                {
                    data = i - 1;
                    choseData = false;
                    break;
                }
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), dataSetBut)) choseData = true;
    }

    if (choseData) return;

    scroll += GetMouseWheelMove() * scrollSpeed;
    resetUpDownWord();
    
    if (backButton.isPressed())
    {
        scroll = 0;
        upWord = 0; 
        downWord = -1;
        data = -1;
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        upWord = 0; 
        downWord = -1;
        scroll = 0;
        data = -1;
        currentScreen = SETTING;
    }
    else if (clearButton.isPressed())
    {
        confirmDialog.show([this](){
            dictionary.removeAllHistory();
            scroll = 0; upWord = 0; downWord = -1; data = -1;
        });
    }
    else
    {
         for (int j = upWord, i = upWord; i <= downWord && j < history.size(); i++, j++)
        {   
            int index = 0;
            if (data == 5) index = history.size() - i - 1;
            else index = history.size() - j - 1;
            if (data != -1 && data != 5 && history[index].first != data) {i--; continue;}

            if (xButton.isPressed(0, i * gap + scroll))
            {
                dictionary.removeHistory(history[index].first, history[index].second);
                resetUpDownWord();
                break;
            } else if (detailButton.isPressed(0, i * gap + scroll))
            {
                SearchResPage::setSearchWord(&(dictionary.getWord(history[index].first, history[index].second)));
                upWord = 0; downWord = -1; data = -1; scroll = 0;
                currentScreen = SEARCH_RES;
                break;
            }
        }
    }


}

void HistoryPage::resetUpDownWord()
{
    if ((int)history.size() == 0)
    {
        upWord = 0; 
        downWord = -1;
    }
    else
    {
        upWord = (int)(scrollDown - scroll) / gap - 1;
        if (upWord < 0) upWord = 0;
        downWord = min(upWord + visibleItems, (int)history.size() - 1);

        if (upWord == 0 && scroll > scrollUp) scroll = scrollUp;
        
        if (history.size() <= 4)
        {
            if (scroll < scrollDown) scroll = scrollDown;
        }
        else
        {
            if (downWord == history.size() - 1 && scroll + (downWord - 3) * gap < scrollDown) scroll = scrollDown - (downWord - 3) * gap;
        }

    }
}

HistoryPage::~HistoryPage()
{
    UnloadTexture(historyTag);
    UnloadTexture(barrier);
    UnloadTexture(Box);
}

void HistoryPage::reset()
{
    scroll = 0;
    upWord = 0; 
    downWord = -1;
}