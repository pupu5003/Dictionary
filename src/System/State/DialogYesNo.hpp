#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
#include <../src/System/Component/Dictionary.hpp>
#include "UILibFunc.hpp"
class Dictionary;
class DialogYesNo : public Page
{
private:
    Texture2D question;
    Texture2D frame;
    Button yesButton;
    Button noButton;
    Dictionary &dictionary;

    // Internal state to manage visibility
    bool isVisible;

public:
    DialogYesNo(Dictionary &dictionary);
    ~DialogYesNo();

    void display() const override;
    void handleEvent() override;
    void show();
    void hide();
    bool isShown() const;
};
