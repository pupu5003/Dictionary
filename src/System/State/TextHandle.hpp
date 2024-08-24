#pragma once

#include <iostream>
#include <raylib.h>
#include <../src/System/Component/FontHelper.hpp>

enum PageType
{
    HOME = 1,
    FAVORITE = 3,
    HISTORY = 2,
    SETTING = 5,
    PRACTICE = 4,
    PRACTICE_QUESTION = 4,
    ADD_WORD = 6,
    SEARCH_RES = 0
};

void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint = GRAY);

void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);

float GetStringWidth(Font font, const char *text, float fontSize, float spacing);

int utf8ToCodepoint(const std::string& utf8Str, int& index);


class CodeHelper
{
private:
    int mapCode[10000];
    int numCode;
    CodeHelper();
    ~CodeHelper();
    CodeHelper(FontHelper const&) = delete;
    CodeHelper& operator=(const CodeHelper&) = delete;

public:
    static CodeHelper& getInstance();
    // void loadFont(const string& path, int size);
    int mapCodepoint(int codepoint);
    int mapChar(string& st, int &index);

};