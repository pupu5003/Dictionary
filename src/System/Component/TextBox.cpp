#include "TextBox.hpp"
using namespace std;

TextBox::TextBox()
{
    font = defaultF;
    text = "";
    box = {0, 0, 0, 0};
    fontSize = 0;
    spacing = 0;
    wordWrap = false;
    color = BLACK;
}

TextBox::~TextBox()
{
}

void TextBox::display() const
{
    DrawTextBoxed(FontHelper::getInstance().getFont(font), text.c_str(), box, fontSize, spacing, wordWrap, color);
}

void TextBox::setTextBox(fontType font, string text, Rectangle box, int fontSize, float spacing, bool wordWrap, Color color)
{
    this->font = font;
    this->text = text;
    this->box = box;
    this->fontSize = fontSize;
    this->spacing = spacing;
    this->wordWrap = wordWrap;
    this->color = color;
}

void TextBox::setBox(Rectangle box)
{
    this->box = box;
}

void TextBox::setFont(fontType font)
{
    this->font = font;
}

void TextBox::setText(string text)
{
    this->text = text;
}

void TextBox::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
}

void TextBox::setSpacing(float spacing)
{
    this->spacing = spacing;
}

void TextBox::setColor(Color color)
{
    this->color = color;
}

void TextBox::setWordWrap(bool wordWrap)
{
    this->wordWrap = wordWrap;
}

