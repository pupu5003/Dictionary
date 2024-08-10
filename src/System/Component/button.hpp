#pragma once
#include <raylib.h>
#include<iostream>

struct Button
{
    Texture2D texture;
    Rectangle rect;
    Rectangle mRect;
    Color color, mColor;
    float scale;
    Button();
    Button(const char* path, float x, float y, float scale = 1.2);
    ~Button();
    void setButton(const char *path, float x, float y, float scale = 1.2);
    bool isPressed() const;
    void loadTexture(const char *path);
    void setRect(float x, float y, float width, float height);
    void setScale(float scale);
    void disable();
    void enable();
    void display() const;
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