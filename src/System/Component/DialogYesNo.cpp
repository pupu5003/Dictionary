#include "DialogYesNo.hpp"
using namespace std;

DialogYesNo::DialogYesNo(Vector2 pos)
    : pos(pos), isVisible(false)
{
    question = LoadTexture("asset/Image/Question.png");  
    frame = LoadTexture("asset/Image/DialogFrame.png");       

    yesButton.setButton("asset/Image/YesButton.png", pos.x + 261, pos.y + 191);
    noButton.setButton("asset/Image/NoButton.png", pos.x + 77, pos.y + 191);
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
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.3f));
        DrawTexture(frame, pos.x, pos.y, WHITE);  
        DrawTexture(question, pos.x + 45, pos.y + 34, WHITE);  
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
            if (onYesCallBack)
            {
                onYesCallBack();
            }
            hide();  
        }
        else if (noButton.isPressed())
        {
            hide();  
        }
    }
}

void DialogYesNo::show(function<void()> onYes)
{
    onYesCallBack = onYes;
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