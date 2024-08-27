#include <iostream>
#include <raylib.h>
#include <vector>
#include "../src/System/Component/page.hpp"
#include "../src/System/State/HomePage.hpp"
#include "../src/System/State/FavoritePage.hpp"
#include "../src/System/State/HistoryPage.hpp"
#include "../src/System/State/SettingPage.hpp"
#include "../src/System/State/PracticePage.hpp"
#include "../src/System/State/PracticeQuestionPage.hpp"
#include "../src/System/State/AddWordPage.hpp"
#include "../src/System/State/SearchResPage.hpp"
#include "../asset/Color/color.hpp"
#include "../src/System/Component/Dictionary.hpp"
#include "../src/System/Component/SearchBar.hpp"
// #include <funtiona>
using namespace std;

class System
{
private:
    /* data */
    const int screenWidth = 1243;
    const int screenHeight = 725;
    int currentScreen;
    vector<Page*> pages;
    Dictionary dictionary;
    // SearchBar searchBar;
public:
    // Word *searchWord;
    System(/* args */);
    ~System();
    void reset();
    void run();
};