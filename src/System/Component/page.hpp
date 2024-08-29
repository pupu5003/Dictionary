#pragma once
#include <raylib.h>
#include<iostream>
enum PageType
{
    PREDICTION_DETAIL = 0,
    SEARCH_RES = 1,
    HOME = 2,
    FAVORITE = 4,
    HISTORY = 3,
    SETTING = 6,
    PRACTICE = 5,
    ADD_WORD = 7,
};

class Page
{
private:
    int currentScreen;
public:
    virtual void display() const = 0;
    virtual void handleEvent() = 0;
    virtual void reset() = 0;
    virtual ~Page() = default;
};