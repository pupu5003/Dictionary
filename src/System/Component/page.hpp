#pragma once
#include <raylib.h>
#include<iostream>
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

class Page
{
private:
    int currentScreen;
public:
    virtual void display() const = 0;
    virtual void handleEvent() = 0;
    virtual ~Page() = default;
};