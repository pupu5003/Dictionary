#pragma once
#include <iostream>
#include <string>
#include "../src/System/State/UILibFunc.hpp"
#include "../src/System/Component/FontHelper.hpp"
using namespace std;

struct TextBox
{
    fontType font;
    string text;
    Rectangle box;
    int fontSize;
    float spacing;
    bool wordWrap;
    Color color;
    TextBox();
    ~TextBox();
    void display() const;
    void setTextBox(fontType font, string text, Rectangle box, int fontSize, float spacing, bool wordWrap, Color color);
    void setFont(fontType font);
    void setText(string text);
    void setBox(Rectangle box);
    void setFontSize(int fontSize);
    void setSpacing(float spacing);
    void setWordWrap(bool wordWrap);
    void setColor(Color color);
};