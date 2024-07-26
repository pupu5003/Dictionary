#include <iostream>
#include <raylib.h>
#include "../src/State/HistoryState.h"


using namespace std;

int main () {

    cout << "Hello World" << endl;
    const int screenWidth = 1460;
    const int screenHeight = 850;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    drawHistoryPage(screenWidth, screenHeight);

    CloseWindow();
    return 0;
}