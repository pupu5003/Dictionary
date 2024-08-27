#pragma once
#include <iostream>
#include <raylib.h>
#include "../src/System/Component/page.hpp"
#include <../src/System/Component/button.hpp>
#include <../asset/Color/color.hpp>
#include <functional>
// #include "UILibFunc.hpp"
class DialogYesNo
{
private:
    Texture2D question;
    Texture2D frame;
    Button yesButton;
    Button noButton;
    Vector2 pos;
    function<void()> onYesCallBack;

    // Internal state to manage visibility
    bool isVisible;

public:
    DialogYesNo(Vector2 pos = {400, 220});
    ~DialogYesNo();

    void display() const;
    void handleEvent();
    void show(function<void()> onYes);
    void hide();
    bool isShown() const;
};
