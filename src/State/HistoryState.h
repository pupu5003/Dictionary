#include <iostream>
#include <raylib.h>

struct HistoryItem {
    std::string word;
    std::string description;
};

void DrawRoundedRectangle(Rectangle rec, float radius, int segments, Color color);
void drawHistoryPage(int screenWidth, int screenHeight);
