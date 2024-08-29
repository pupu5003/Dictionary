#include "PredictionDetailPage.hpp"
using namespace std;

#define KEY_WORD 0
#define DEFINITION 1
#define STRAIGHT_TO_SEARCH_RES 2
#define visibleItems 7
#define scrollUp 20
#define scrollDown -25
#define scrollSpeed 16
#define gap 115
#define SLIGHTRED Color{244, 210, 210, 50}

vector<int> PredictionDetailPage::predict(0);
int PredictionDetailPage::searchWordID = -1;
std::string PredictionDetailPage::searchInput = "";
int PredictionDetailPage::searchType = 0;
dataSet PredictionDetailPage::data = engEng;
float PredictionDetailPage::scroll = 0;
int PredictionDetailPage::upWord= 0, PredictionDetailPage::downWord= -1;

PredictionDetailPage::PredictionDetailPage(int &currentScreen, Dictionary& dictionary) : currentScreen(currentScreen), dictionary(dictionary), searchBar(dictionary, currentScreen, {280,35})
{
    predict.clear();
    scroll = 0;

    // PredictionDetailTag = LoadTexture("asset/Image/SearchResTag.png");

    Box = LoadTexture("asset/Image/FavoriteBox.png");
    
    barrier = LoadTexture("asset/Image/SearchResTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    scroll = 0;

    upWord= 0; downWord= -1;
}

void PredictionDetailPage::display() const
{
    if (searchType == STRAIGHT_TO_SEARCH_RES) {
        //Do not display anything
        cout << "STRAIGHT TO SEARCH RES\n";
    }
    else {
        for (int i = upWord; i <= downWord; i++)
        {   
            DrawTexture(Box, 120, 217 + i * gap + scroll, WHITE);

            int index = predict.size() - i - 1;
            const Word &word = dictionary.getWord(data, predict[i]);
        
            DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[word.data].c_str(), { 142, 226 + i * gap + scroll}, 25, 0.5f, BLACK);

            float width = MeasureTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), 40, 0.5f).x;
            DrawTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), { 620 - width/2, 235 + i * gap + scroll}, 40, 0.5f, BLACK);
        }

        DrawTexture(barrier, 0, 0, WHITE);

        settingButton.display();
        backButton.display();

        if (searchType == DEFINITION) {
            if (predict.size() == 0)
                DrawTextEx(FontHelper::getInstance().getFont(Inter), "No results found", { 156, 135 }, 36, 0.5f, BLACK);
            else DrawTextEx(FontHelper::getInstance().getFont(Inter), "Search results", { 156, 135 }, 36, 0.5f, BLACK);
        }
        else {
            std::string inputShow = "No results for '" + searchInput + "'. Do you mean:";
            DrawTextEx(FontHelper::getInstance().getFont(Inter), inputShow.c_str(), { 156, 135 }, 36, 0.5f, BLACK);
            if (predict.size() == 0)
                DrawTextEx(FontHelper::getInstance().getFont(Inter), "Can not find similar results", { 156, 204 }, 36, 0.5f, BLACK);
        }

        DrawLine(107, 192, 1136, 192, BLACK);

        searchBar.display();
    }
}

void PredictionDetailPage::handleEvent()
{
    if (searchType == STRAIGHT_TO_SEARCH_RES) 
    {
        SearchResPage::setSearchWord(&(dictionary.getWord(data, searchWordID)));
        upWord = 0; downWord = -1;
        currentScreen = SEARCH_RES;
        return;
    }
    scroll += (int)(GetMouseWheelMove() * scrollSpeed);
    resetUpDownWord();
    if (searchBar.getActive()) 
    {
        searchBar.handleEvent();
        return;
    }
    searchBar.handleEvent();

    if (backButton.isPressed())
    {
        scroll = 0;
        upWord= 0; downWord= -1;
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        scroll = 0;
        upWord= 0; downWord= -1;
        currentScreen = SETTING;
    } 
    else
    {
        for (int i = upWord; i <= downWord; i++)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {120, 217 + i * gap + scroll, 1000, 75}))
            {
                int index = predict.size() - i - 1;
                SearchResPage::setSearchWord(&(dictionary.getWord(data, predict[i])));
                upWord = 0; downWord = -1;
                currentScreen = SEARCH_RES;
                break;
            }
        }
    }
}

void PredictionDetailPage::setPredictionList(vector<int>& prediction)
{
    scroll = 0;
    upWord= 0; downWord= -1;
    predict = prediction;
}

void PredictionDetailPage::setSearchType(int type) {
    searchType = type;
}

void PredictionDetailPage::setSearchInput(std::string input) {
    searchInput = input;
}

void PredictionDetailPage::resetUpDownWord()
{
    if ((int)predict.size() == 0)
    {
        upWord = 0; downWord = -1;
    }
    else
    {
        upWord = (int)(scrollDown - scroll) / gap - 1;
        if (upWord < 0) upWord = 0;
        downWord = min(upWord + visibleItems, (int)predict.size() - 1);

        if (upWord == 0 && scroll > scrollUp) scroll = scrollUp;
        
        if (predict.size() <= 4)
        {
            if (scroll < scrollDown) scroll = scrollDown;
        }
        else
        {
            if (downWord == predict.size() - 1 && scroll + (downWord - 3) * gap < scrollDown) scroll = scrollDown - (downWord - 3) * gap;
        }

    }
}

void PredictionDetailPage::setSearchWord(int ID) {
    searchWordID = ID;
}

void PredictionDetailPage::setDataSet(dataSet dataset) {
    data = dataset;
}

PredictionDetailPage::~PredictionDetailPage()
{
    UnloadTexture(Box);
    UnloadTexture(barrier);
}

void PredictionDetailPage::reset()
{
    scroll = 0;
    upWord= 0; downWord= -1;
    predict.clear();
    searchWordID = -1;
    searchInput = "";
    searchType = 0;
    searchBar.reset();
    // confirmDialog.reset();
}
