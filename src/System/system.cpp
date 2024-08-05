#include "system.hpp"
using namespace std;

System::System(/* args */)
{
    InitWindow(screenWidth, screenHeight,"The Dictionary");
    SetTargetFPS(60);

    // load components
    pages.push_back(new HomePage());
    pages.push_back(new HistoryPage());
    pages.push_back(new FavoritePage());
    currentScreen = 0;
    cout << "System is created" << endl;
}

System::~System()
{
    for (auto page : pages)
    {
        delete page;
    }
}

void System::run()
{
   
    while (!WindowShouldClose()) 
    {

        //event handling
        pages[currentScreen] -> handleEvent(currentScreen);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            cout << "Mouse is pressed" << endl;
        }
           
        //display the pages
        BeginDrawing();
        ClearBackground(BACKGROUND);
        pages[currentScreen]->display();
        EndDrawing();
    }


    CloseWindow();
}