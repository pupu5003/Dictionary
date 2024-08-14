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

    int& currentScreen;

public:
    AddWordPage(int &currentScreen);
    ~AddWordPage();
    void display() const override;
    void handleEvent() override;
};