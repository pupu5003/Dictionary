#pragma once
#include "UIComponent.hpp"
#include <../src/System/Component/Dictionary.hpp>
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

 void DrawTextBoxed(const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint = GRAY);
void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);