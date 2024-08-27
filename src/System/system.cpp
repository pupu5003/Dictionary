#include "system.hpp"
using namespace std;

System::System(/* args */)
{
    InitWindow(screenWidth, screenHeight,"The Dictionary");
    SetTargetFPS(60);
    currentScreen = HOME;

    // load components
    pages.push_back(new SearchResPage(currentScreen, dictionary));
    pages.push_back(new HomePage(currentScreen, dictionary));
    pages.push_back(new HistoryPage(currentScreen, dictionary));
    pages.push_back(new FavoritePage(currentScreen, dictionary));
    pages.push_back(new PracticeQuestionPage(currentScreen, dictionary));
    pages.push_back(new SettingPage(currentScreen, dictionary));
    pages.push_back(new AddWordPage(currentScreen, dictionary)); 
    cout << "System created" << endl;
}

System::~System()
{
    cout << "System destructor called\n";
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