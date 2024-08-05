#include "button.hpp"
using namespace std;

const float scale = 1.2;

Button::Button()
{
    rect = {0, 0, 0, 0};
    mRect = {0, 0, 0, 0};
    color = WHITE;
    mColor = LIGHTGRAY;
}

void Button::setButton(const char *path, float x, float y)
{
    loadTexture(path);
    setRect(x, y, texture.width, texture.height);
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::display() const
{
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        Texture2D temp = texture;
        temp.width = mRect.width;
        temp.height = mRect.height;
        DrawTexture(temp, mRect.x, mRect.y, mColor);
    }
    else
    {
        DrawTexture(texture, rect.x, rect.y, color);
    }
}

bool Button::isPressed() const
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect);
}

void Button::loadTexture(const char *path)
{
    texture = LoadTexture(path);
}

void Button::setRect(float x, float y, float width, float height)
{
    rect = {x, y, width, height};
    mRect = {x - (width * scale - width) / 2, y - (height * scale - height) / 2, width * scale, height * scale};
}