#include "system.hpp"
using namespace std;

System::System(/* args */)
{
    InitWindow(screenWidth, screenHeight,"The Dictionary");
    SetTargetFPS(60);

    // load components
    pages.push_back(new HomePage(currentScreen, dictionary));
    pages.push_back(new HistoryPage(currentScreen, hisManager));
    pages.push_back(new FavoritePage(currentScreen));
    pages.push_back(new PracticeQuestionPage(currentScreen, generateQuestion()));
    pages.push_back(new SettingPage(currentScreen));
    pages.push_back(new AddWordPage(currentScreen)); 
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
    Image AppIcon = LoadImage("asset/Image/AppIcon.png");
    SetWindowIcon(AppIcon);
   
    while (!WindowShouldClose()) 
    {

        //event handling
        pages[currentScreen] -> handleEvent();
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