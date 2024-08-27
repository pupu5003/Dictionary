#pragma once
#include "UILibFunc.hpp"

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

    Rectangle dataSetBut;
    Texture2D curDataSet[5];   
    Texture2D optionBut[6];
    Texture2D dataSetOptions;
    bool choseeData;

    dataSet data = engEng;
    PracticeQuestion question;
    int chosenAnswer = -1;

    int& currentScreen;
    Dictionary& dictionary;
public:
    PracticeQuestionPage(int& currentScreen, Dictionary& dictionary);
    ~PracticeQuestionPage();
    void display() const override;
    void handleEvent() override;

    void setElementBox();
    void newQuestion();

    const PracticeQuestionPage& operator=(const PracticeQuestionPage& rhs);
};