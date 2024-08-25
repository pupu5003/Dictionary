#pragma once
#include <raylib.h>
#include<iostream>
#include "FontHelper.hpp"
#include "TextBox.hpp"

struct Button
{
    Texture2D texture;
    Rectangle rect;
    Rectangle mRect;
    Color color, mColor;
    float scale;
    TextBox text = {Arial, "", rect, 0, 0, 0, WHITE};
    bool zoom;
    Button();
    Button(const char* path, float x, float y, float scale = 1.2);
    ~Button();
    void setButton(const char *path, float x, float y, float scale = 1.2);
    bool isPressed(float x = 0, float y = 0);
    void loadTexture(const char *path);
    void setRect(float x, float y, float width, float height);
    void setScale(float scale);
    void setText(string text, fontType font, float fontSize, float spacing, bool wordWrap, Color color);
    void disable();
    void enable();
    void display(float x = 0, float y = 0) const;
};

struct nButton
{
    Texture2D texture;
    Rectangle rect;
    Color color;
    nButton();
    ~nButton();
    void setButton(const char *path, float x, float y);
    bool isPressed() const;
    void loadTexture(const char *path);
    void setRect(float x, float y, float width, float height);
    void display() const;
};