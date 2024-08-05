#include <iostream>
#include <raylib.h>
#include <vector>
#include "../src/System/State/Component/page.hpp"
#include "../src/System/State/Home.hpp"
#include "../asset/Color/color.hpp"
using namespace std;

class System
{
private:
    /* data */
    const int screenWidth = 1243;
    const int screenHeight = 725;
    int currentScreen;
    vector<Page*> pages;
public:
    System(/* args */);
    ~System();
    void run();
};