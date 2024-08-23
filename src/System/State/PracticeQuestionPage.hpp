#pragma once
#include "UILibFunc.hpp"
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

    dataSet data = engVie;
    PracticeQuestion question;
    int chosenAnswer = -1;

    int& currentScreen;
    Dictionary& dictionary;
public:
    PracticeQuestionPage(int& currentScreen, Dictionary& dictionary);
    ~PracticeQuestionPage();
    void display() const override;
    void handleEvent() override;

    void newQuestion();

    const PracticeQuestionPage& operator=(const PracticeQuestionPage& rhs);
};