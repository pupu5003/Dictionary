#include "TextBox.hpp"
using namespace std;

TextBox::TextBox(fontType font, string text, Rectangle box, int fontSize, float spacing, bool wordWrap, Color color)
{
    this->font = font;
    this->text = text;
    this->box = box;
    this->fontSize = fontSize;
    this->spacing = spacing;
    this->wordWrap = wordWrap;
    this->color = color;
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

void TextBox::display() const
{
    DrawTextBoxed(FontHelper::getInstance().getFont(font), text.c_str(), box, fontSize, spacing, wordWrap, color);
}

void TextBox::zoomIn(float ratio) {
    box.width *= ratio;
    box.height *= ratio;
    fontSize *= ratio;
    spacing *= ratio;
}

TextBox& TextBox::operator=(const TextBox& rhs) {
    if (this == &rhs) return *this;
    this->font = rhs.font;
    this->text = rhs.text;
    this->box = rhs.box;
    this->fontSize = rhs.fontSize;
    this->spacing = rhs.spacing;
    this->wordWrap = rhs.wordWrap;
    this->color = rhs.color;

    return *this;
}