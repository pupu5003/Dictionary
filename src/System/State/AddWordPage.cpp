#include "AddWordPage.hpp"
using namespace std;

AddWordPage::AddWordPage(int &currentScreen) : currentScreen(currentScreen)
{
    AddWordTag = LoadTexture("asset/Image/AddWordTag.png");

    keywordTag = LoadTexture("asset/Image/KeywordTag.png");

    definitionTag = LoadTexture("asset/Image/DefinitionTag.png");

    keywordBox = LoadTexture("asset/Image/KeywordBox1.png");

    definitionBox = LoadTexture("asset/Image/DefinitionBox1.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    addNewButton.setButton("asset/Image/AddNewButton.png", 924, 586);

}

void AddWordPage::display() const
{
    DrawTexture(AddWordTag, 0, 0, WHITE);

    DrawTexture(keywordTag, 77, 227, WHITE);

    DrawTexture(definitionTag, 77, 374, WHITE);

    DrawTexture(keywordBox, 377, 204, WHITE);

    DrawTexture(definitionBox, 377, 355, WHITE);

    backButton.display();

    addNewButton.display();
}

void AddWordPage::handleEvent()
{
    if (backButton.isPressed())
    {
        currentScreen = 4;
    }
    else if (addNewButton.isPressed())
    {
        cout << "Add new button is pressed" << endl;
    }
}

AddWordPage::~AddWordPage()
{
    UnloadTexture(AddWordTag);
    UnloadTexture(keywordTag);
    UnloadTexture(definitionTag);
}