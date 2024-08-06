#include <iostream>
#include <raylib.h>
#include <vector>
#include "../src/System/Component/page.hpp"
#include "../src/System/State/HomePage.hpp"
#include "../src/System/State/FavoritePage.hpp"
#include "../src/System/State/HistoryPage.hpp"
#include "../src/System/Component/HistoryManager.hpp"
#include "../src/System/State/SettingPage.hpp"
#include "../src/System/State/PracticePage.hpp"
#include "../src/System/State/AddWordPage.hpp"
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
    HistoryManager hisManager;
public:
    System(/* args */);
    ~System();
    void run();
};