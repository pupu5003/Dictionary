#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include "../src/System/Component/TextHandle.hpp"
using namespace std;


class TextInputBox
{
private:
    /* data */
    Rectangle box;
    Font font;
    float fontSize;
    Color color;
    float spacing;
    bool wordWrap;
    int cursorPos;
    string text;
    vector<int> codePoints;
    int frame;
    bool typing;
    bool isCenter;
    bool isOptional;
    bool isRequired;
public:
    TextInputBox(Rectangle box);
    ~TextInputBox();
    void display() const;
    void handleEvent();
    string getText();
    void setFont(Font font, float fontSize);
    void setColor(Color color);
    void centerText();
    void setOptinal();
    void setRequired();
    bool isValid();
    void reset();
    // void setText(string text);
};