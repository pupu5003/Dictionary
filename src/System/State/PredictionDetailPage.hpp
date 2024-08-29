#pragma once
#include <iostream>
#include <raylib.h>
#include "UILibFunc.hpp"
#include "SearchResPage.hpp"

using namespace std;


class PredictionDetailPage : public Page
{
private:
    // Texture2D PredictionDetailTag;
    Texture2D Box;
    Texture2D barrier;
    Button backButton;
    Button settingButton;
    static int upWord, downWord;
    int& currentScreen;
    static float scroll;

    static int searchType;
    static int searchWordID;
    static std::string searchInput;
    static vector<int> predict;
    static dataSet data;

    SearchBar searchBar;
    Dictionary& dictionary;
public:
    PredictionDetailPage(int &currentScreen, Dictionary &dictionary);
    ~PredictionDetailPage();
    static void setPredictionList(vector<int>& prediction);
    static void setSearchType(int type);
    static void setSearchInput(std::string input);
    static void setSearchWord(int ID);
    static void setDataSet(dataSet dataset);
    void display() const override;
    void handleEvent() override;
    void reset() override;
    void resetUpDownWord();
};
