#include "button.hpp"
using namespace std;

Button::Button()
{
    rect = {0, 0, 0, 0};
    mRect = {0, 0, 0, 0};
    color = WHITE;
    mColor = LIGHTGRAY;
    scale = 1.1;
    zoom = false;
    autoZoom = false;
}

Button::Button(const char* path, float x, float y, float scale) {
    setButton(path, x, y, scale);
}

// Button::Button(const char* path, float x, float y, float scale, string text, fontType font, float fontSize, float spacing, bool wordWrap, Color color) {
//     setButton(path, x, y, scale, text, font, fontSize, spacing, wordWrap, color);
// }

void Button::setButton(const char *path, float x, float y, float scale)
{
    loadTexture(path);
    this->scale = scale;
    setRect(x, y, texture.width, texture.height);
}

// void Button::setButton(const char *path, float x, float y, float scale, string text, fontType font, float fontSize, float spacing, bool wordWrap, Color color)
// {
//     loadTexture(path);
//     setRect(x, y, texture.width, texture.height);
//     this->scale = scale;
//     this->text.setTextBox(font, text, this->rect, fontSize, spacing, wordWrap, color);
// }

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::display(float x, float y) const
{
    if ((zoom && !autoZoom)|| (autoZoom && CheckCollisionPointRec(GetMousePosition(), {rect.x + x, rect.y + y, rect.width, rect.height})))
    {
        Texture2D temp = texture;
        temp.width = mRect.width;
        temp.height = mRect.height;
        DrawTexture(temp, mRect.x + x, mRect.y + y, mColor);
        TextBox tempText = text;
        tempText.zoomIn(scale);
        tempText.display();
    }
    else
    {
        DrawTexture(texture, rect.x + x, rect.y + y, color);
        text.display();
    }
}

bool Button::isPressed(float x, float y) 
{
    zoom = false;
    if ( CheckCollisionPointRec(GetMousePosition(), {rect.x + x, rect.y + y, rect.width, rect.height}))
    {
        zoom = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            zoom = false;
            return true;
        }
    }
    return false;
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

void Button::setScale(float scale)
{
    this->scale = scale;
    setRect(rect.x, rect.y, rect.width, rect.height);
}

void Button::setText(string text, fontType font, float fontSize, float spacing, bool wordWrap, Color color) {
        this->text.setTextBox(font, text, {rect.x + 10, rect.y + 10, rect.width - 10, rect.height - 10}, fontSize, spacing, wordWrap, color);
}

void Button::disable()
{
    autoZoom = false;
}

void Button::enable()
{
    autoZoom = true;
}

nButton::nButton()
{
    rect = {0, 0, 0, 0};
    color = WHITE;
}

void nButton::setButton(const char *path, float x, float y)

{
    loadTexture(path);
    setRect(x, y, texture.width, texture.height);
}

nButton::~nButton()
{
    UnloadTexture(texture);
}

void nButton::display() const
{

    DrawTexture(texture, rect.x, rect.y, color);
}

bool nButton::isPressed() const
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect);
}

void nButton::loadTexture(const char *path)
{
    texture = LoadTexture(path);
}

void nButton::setRect(float x, float y, float width, float height)
{
    rect = {x, y, width, height};
}