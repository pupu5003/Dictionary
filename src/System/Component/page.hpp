#pragma once
#include <raylib.h>
#include<iostream>

class Page
{
public:
    virtual void display() const = 0;
    virtual void handleEvent(int &currentScreen) = 0;
    virtual ~Page() = default;
};