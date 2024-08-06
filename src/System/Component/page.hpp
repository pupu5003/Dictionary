#pragma once
#include <raylib.h>
#include<iostream>

class Page
{
private:
    int currentScreen;
public:
    virtual void display() const = 0;
    virtual void handleEvent() = 0;
    virtual ~Page() = default;
};