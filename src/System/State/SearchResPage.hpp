#pragma once
#include <iostream>
#include <raylib.h>
#include "UILibFunc.hpp"

using namespace std;

// class SearchBar;

class SearchResPage : public Page
{
private:
    Texture2D searchResTag;
    Button backButton;
    Button settingButton;
    Button like;
    Button liked;
    Button edit;
    Button deleteButton;
    Button addDefButton;
    Button saveDefButton;
    Button cancelDefButton;
    Button deleteDefButton;
    TextInputBox inputDef;
    TextInputBox inputType;
    int isEdit;
    static int upDef, downDef;
    static vector<float> Gap;
    int& currentScreen;
    static Word* searchWord;
    static float scroll;
    DialogYesNo confirmDialog;
    SearchBar searchBar;
    Dictionary& dictionary;
public:
    SearchResPage(int &currentScreen, Dictionary &dictionary);
    ~SearchResPage();
    static void setSearchWord(Word* word);
    void display() const override;
    void handleEvent() override;
    void reset() override;
    static void resetGap();
    void resetUpDownDef();
};
