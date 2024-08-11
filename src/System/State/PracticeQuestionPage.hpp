#pragma once
#include "UIComponent.hpp"
#include "../Component/Question.hpp"

using namespace std;

class PracticeQuestionPage : public Page 
{
private:
    Texture2D practiceTag;
    Button backButton;  
    Button settingButton;
    Button continueButton;
    Button questionBox;
    Button answerBox[4];

    PracticeQuestion question;
    int chosenAnswer = -1;

    int& currentScreen;
public:
    PracticeQuestionPage(int& currentScreen, PracticeQuestion q);
    ~PracticeQuestionPage();
    void display() const override;
    void handleEvent() override;

    void newQuestion();

    const PracticeQuestionPage& operator=(const PracticeQuestionPage& rhs);
};