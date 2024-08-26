#pragma once
#include "UILibFunc.hpp"

class AddWordPage : public Page
{
private:
    Texture2D AddWordTag;
    Texture2D keywordTag;
    Texture2D definitionTag;
    Texture2D keywordBox;
    Texture2D definitionBox;
    Button backButton;
    Button addNewButton;
    DialogYesNo confirmDialog;

    int& currentScreen;
    Dictionary &dictionary;

public:
    AddWordPage(int &currentScreen, Dictionary &dictionary);
    ~AddWordPage();
    void display() const override;
    void handleEvent() override;
};