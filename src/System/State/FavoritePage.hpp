#pragma once
#include "UIComponent.hpp"


class FavoritePage : public Page
{
private:
    Texture2D favoriteTag;
    Button backButton;
    Button settingButton; 
    Button clearButton;

    int& currentScreen;

public:
    FavoritePage(int &currentScreen);
    ~FavoritePage();
    void display() const override;
    void handleEvent() override;
};