#pragma once
#include "UILibFunc.hpp"

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
    Button detailButton;
    nButton wordCard;
    SearchBar searchBar;
    Word* randomWord;
    int& currentScreen;
    Dictionary& dictionary;

public:
    HomePage(int &currentScreen, Dictionary& dictionary);
    ~HomePage();
    void display() const override;
    void handleEvent() override;
    void reset() override;
};

