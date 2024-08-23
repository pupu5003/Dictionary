#pragma once
#include <iostream>
#include <string>
#include "../src/System/State/TextHandle.hpp"
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
    TextBox(fontType font, string text, Rectangle box, int fontSize, float spacing, bool wordWrap, Color color);
    void setTextBox(fontType font, string text, Rectangle box, int fontSize, float spacing, bool wordWrap, Color color);
    void zoomIn(float ratio);
    void display() const;

    TextBox& operator=(const TextBox& rhs);
};