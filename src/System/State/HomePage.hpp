#pragma once
#include "UILibFunc.hpp"
#include <../src/System/Component/Dictionary.hpp>
#include "SearchResPage.hpp"
using namespace std;

class HomePage : public Page
{
private:
    Texture2D homeTag;
    Button historyButton;
    Button favoriteButton;
    Button practiceButton;
    Button settingButton; 
    Button like;
    Button liked;
    Button changeWord;
    Button edit;
    nButton wordCard;

    Word* randomWord;
    int& currentScreen;
    Dictionary& dictionary;

public:
    HomePage(int &currentScreen, Dictionary& dictionary);
    ~HomePage();
    void display() const override;
    void handleEvent() override;
};

