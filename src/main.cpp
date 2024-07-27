#include <iostream>
#include <raylib.h>
#include "../src/State/HistoryState.h"
#include "../src/State/FavoriteState.h"


using namespace std;

int main () {

    cout << "Hello World" << endl;
    const int screenWidth = 1460;
    const int screenHeight = 850;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    drawFavoritePage(screenWidth, screenHeight);

    CloseWindow();
    return 0;
}