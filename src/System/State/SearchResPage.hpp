#pragma once
#include <iostream>
#include <raylib.h>
#include "UILibFunc.hpp"
#include "../src/System/Component/page.hpp"
#include "../src/System/Component/SearchBar.hpp"
#include "../src/System/Component/TextInputBox.hpp"

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
    TextInputBox inputDef;
    TextInputBox inputType;
    int isEdit;
    static int upDef, downDef;
    static vector<float> Gap;
    int& currentScreen;
    Dictionary& dictionary;
    static Word* searchWord;
    static float scroll;
    SearchBar searchBar;
public:
    SearchResPage(int &currentScreen, Dictionary &dictionary);
    ~SearchResPage();
    static void setSearchWord(Word* word);
    void display() const override;
    void handleEvent() override;
    static void resetGap();
    void resetUpDownDef();
};
