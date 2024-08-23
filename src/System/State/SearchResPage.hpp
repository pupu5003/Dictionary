#pragma once
#include <iostream>
#include <raylib.h>
#include "UILibFunc.hpp"
#include "../src/System/Component/page.hpp"

using namespace std;

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
    int upDef, downDef;
    static vector<float> Gap;
    int& currentScreen;
    Dictionary& dictionary;
    static Word* searchWord;
    static float scroll;
public:
    SearchResPage(int &currentScreen, Dictionary &dictionary);
    ~SearchResPage();
    static void setSearchWord(Word* word);
    static void resetSrcoll();
    void display() const override;
    void handleEvent() override;
};
