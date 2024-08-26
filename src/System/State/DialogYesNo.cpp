#include "DialogYesNo.hpp"
using namespace std;

DialogYesNo::DialogYesNo(Dictionary &dictionary)
    : dictionary(dictionary), isVisible(false)
{
    question = LoadTexture("asset/Image/Question.png");  
    frame = LoadTexture("asset/Image/DialogFrame.png");       

    yesButton.setButton("asset/Image/YesButton.png", 477, 411);
    noButton.setButton("asset/Image/NoButton.png", 661, 411);
}

DialogYesNo::~DialogYesNo()
{
    UnloadTexture(question);
    UnloadTexture(frame);
}

void DialogYesNo::display() const
{
    if (isVisible)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
        DrawTexture(frame, 400, 220, WHITE);  
        DrawTexture(question, 445, 254, WHITE);  
        yesButton.display();
        noButton.display();
    }
}

void DialogYesNo::handleEvent()
{
    if (isVisible)
    {
        if (yesButton.isPressed())
        {
            std::cout << "Yes button pressed" << std::endl;
            hide();  
        }
        else if (noButton.isPressed())
        {
            std::cout << "No button pressed" << std::endl;
            hide();  
        }
    }
}

void DialogYesNo::show()
{
    isVisible = true;
}

void DialogYesNo::hide()
{
    isVisible = false;
}

bool DialogYesNo::isShown() const
{
    return isVisible;
}