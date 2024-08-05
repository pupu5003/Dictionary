#include <iostream>
#include <raylib.h>
#include <vector>

struct HistoryItem {
    std::string word;
    std::string description;
};

void drawHistoryPage(int screenWidth, int screenHeight);
