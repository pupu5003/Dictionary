#include "system.hpp"
using namespace std;

System::System(/* args */)
{
    InitWindow(screenWidth, screenHeight,"The Dictionary");
    SetTargetFPS(60);

    // load components
    pages.push_back(new Home());
    // pages.push_back(new FavoriteState());
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
        pages[currentScreen]->handleEvent();
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