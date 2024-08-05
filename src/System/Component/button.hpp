#pragma once
#include <raylib.h>
#include<iostream>

struct Button
{
    Texture2D texture;
    Rectangle rect;
    Rectangle mRect;
    Color color, mColor;
    Button();
    ~Button();
    void setButton(const char *path, float x, float y);
    bool isPressed() const;
    void loadTexture(const char *path);
    void setRect(float x, float y, float width, float height);
    void display() const;
};