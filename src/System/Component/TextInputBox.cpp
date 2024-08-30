#include "TextInputBox.hpp"
using namespace std;

TextInputBox::TextInputBox(Rectangle box): box(box)
{
    cursorPos = 0;
    frame = 0;
    typing = false;
    text = "";
    isCenter = false;
    isOptional = false;
    isRequired = false;
    fontSize = 20;
    font = GetFontDefault();
    color = BLACK;
    spacing = 0.5f;
    wordWrap = true;
}

TextInputBox::~TextInputBox()
{
    // UnloadFont(font);
}

void TextInputBox::display() const
{
    float margin = 0;
    if (isCenter)
    {
        if (!typing && codePoints.size() == 0)
        {   
            if (isOptional)
                margin = (box.width - MeasureTextEx(font, "Parts of Speech (Optional)", fontSize, spacing).x) / 2;
            else if (isRequired)
                margin = (box.width - MeasureTextEx(font, "Keyword/Definition (Required)", fontSize, spacing).x) / 2;           
        }
        else
        {   
            margin = (box.width - MeasureTextEx(font, text.c_str(), fontSize, spacing).x) ;
            if (frame <= 25) margin = (margin + MeasureTextEx(font, "|", fontSize, spacing).x);
            margin /= 2;
        }
    }

    if (!typing && isOptional && codePoints.size() == 0)
    {
        DrawTextBoxed(font, "Parts of Speech (Optional)", {box.x + margin, box.y, box.width, box.height}, fontSize, spacing, wordWrap, LIGHTGRAY);
    } 
    else if (!typing && isRequired && codePoints.size() == 0)
    {
        DrawTextBoxed(font, "Keyword/Definition (Required)",  {box.x + margin, box.y, box.width, box.height}, fontSize, spacing, wordWrap, LIGHTGRAY);
    } 
    else
    {
        DrawTextBoxed(font, text.c_str(),  {box.x + margin, box.y, box.width, box.height}, fontSize, spacing, wordWrap, color);
    }
}

void TextInputBox::handleEvent()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), box))
        {
            typing = true;
            cursorPos = codePoints.size();
        }
        else
        {
            if (typing)
            {
                if (frame <= 25) text.erase(cursorPos, 1);
                frame = 0;
            }
            typing = false;
        }
    }

    if (typing == false) return;

    bool change = false;
    int key = GetCharPressed();
    int keyRightHere = key;
    int lengthNow = codePoints.size();
    while(key > 0)
    {
        if (key >= 32)
        {
            cout << key << endl;
            codePoints.insert(codePoints.begin() + cursorPos, key);
            cursorPos++;
            change = true;
        }
        keyRightHere = key;
        key = GetCharPressed();
    }
    int spareCodePoints = codePoints.size() - lengthNow;
    if (spareCodePoints > 1 || keyRightHere > 125) {    //KeyRightHere to determine if the vowel is right before the codepoint (this falls to spareCodePoints = 1)
        vector<int> tmp;
        tmp.assign(codePoints.end() - spareCodePoints, codePoints.end());
        for (int i = 0; i < 2*spareCodePoints; ++i)
            codePoints.pop_back();
        for (int i = 0; i < spareCodePoints; ++i)
            codePoints.push_back(tmp[i]);
        cursorPos -= spareCodePoints;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (cursorPos > 0)
        {
            codePoints.erase(codePoints.begin() + cursorPos - 1);
            cursorPos--;
            change = true;
        }
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        if (cursorPos < codePoints.size())
        {
            if (frame <= 25)
            {
                text.erase(cursorPos, 1);
                text.insert(cursorPos + 1, "|");
            }
            cursorPos++;
        }
    }
    if  (IsKeyPressed(KEY_LEFT))
    {
        if (cursorPos > 0)
        {
            if (frame <= 25)
            {
                text.erase(cursorPos, 1);
                text.insert(cursorPos - 1, "|");
            }
            cursorPos--;
        }
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        typing = false;
    }

    if (change)
    {
        text = "";
        for (int i = 0; i < codePoints.size(); i++)
        {
            text += (char)codePoints[i];
        }
        if (frame <= 25) text.insert(cursorPos, "|");
    }

    
    if (frame % 50 == 0)
    {
        // text += "|";
        text.insert(cursorPos, "|");
        frame = 0;
    }
    else if (frame % 25 == 0)
    {
        text.erase(cursorPos, 1);
    }
    frame++;
}

string TextInputBox::getText() 
{
    text = "";
    for (int i = 0; i < codePoints.size(); i++)
    {
        text += static_cast<char>(codePoints[i]);
    }
    return text;
}

void TextInputBox::setFont(Font font, float fontSize)
{
    this->font = font;
    this->fontSize = fontSize;
}

void TextInputBox::setColor(Color color)
{
    this->color = color;
}

void TextInputBox::centerText()
{
    isCenter = true;
}

void TextInputBox::setOptinal()
{
    isOptional = true;
}

void TextInputBox::setRequired()
{
    isRequired = true;
}

bool TextInputBox::isValid()
{
    if (isOptional) return true;
    if (isRequired && codePoints.size() == 0) return false;
    return true;
}

void TextInputBox::reset()
{
    codePoints.clear();
    text = "";
    cursorPos = 0;
    frame = 0;
    typing = false;
}

void TextInputBox::setCodePoints(string &st)
{
    for (int i = 0; i < st.size(); i++)
    {
        int cd = utf8ToCodepoint(st, i);
        codePoints.push_back(cd);
    }
    text = st;
}