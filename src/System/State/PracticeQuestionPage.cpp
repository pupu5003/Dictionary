#include "PracticeQuestionPage.hpp"
using namespace std;

PracticeQuestionPage::PracticeQuestionPage(int &currentScreen, PracticeQuestion q) : currentScreen(currentScreen)
{
    question = q;

    practiceTag = LoadTexture("asset/Image/PracticeTag.png");
    backButton.setButton("asset/Image/back_ic.png", 45, 31);
    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);
    continueButton.setButton("asset/Image/continueButton.png", 929, 637);

    if (question.type_askByWord) {
        questionBox.setButton("asset/Image/PracticeQuestionBox_Word.png", 75, 140);
        questionBox.disable();
        answerBox[0].setButton("asset/Image/PracticeAnswerBox_Definition.png", 75, 276);
        answerBox[1].setButton("asset/Image/PracticeAnswerBox_Definition.png", 75, 456);
        answerBox[2].setButton("asset/Image/PracticeAnswerBox_Definition.png", 695, 276);
        answerBox[3].setButton("asset/Image/PracticeAnswerBox_Definition.png", 695, 456);
    }
    else {
        questionBox.setButton("asset/Image/PracticeQuestionBox_Definition.png", 75, 140);
        questionBox.disable();
        answerBox[0].setButton("asset/Image/PracticeAnswerBox_Word.png", 118, 375);
        answerBox[1].setButton("asset/Image/PracticeAnswerBox_Word.png", 118, 500);
        answerBox[2].setButton("asset/Image/PracticeAnswerBox_Word.png", 723, 375);
        answerBox[3].setButton("asset/Image/PracticeAnswerBox_Word.png", 723, 500);
    }
}

void PracticeQuestionPage::display() const
{
    DrawTexture(practiceTag, 0, 0, WHITE);
    backButton.display();
    settingButton.display();
    continueButton.display();
    questionBox.display();
    for (int i = 0; i < 4; ++i)
        answerBox[i].display();
}

void PracticeQuestionPage::handleEvent()
{
   if (backButton.isPressed())
    {
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        currentScreen = SETTING;
    }
    else if (continueButton.isPressed())
    {
        chosenAnswer = -1;
        newQuestion();
    }
    else if (chosenAnswer != -1) {}      //If answer has been chosen, do nothing  
    else {
        for (int i = 0; i < 4; ++i) {
            if (answerBox[i].isPressed()) {
                chosenAnswer = i;
                if (question.type_askByWord) {
                    answerBox[question.correctAnswer].loadTexture("asset/Image/PracticeAnswerBox_Definition_Correct.png");
                    if (question.correctAnswer != i)
                        answerBox[i].loadTexture("asset/Image/PracticeAnswerBox_Definition_Wrong.png");
                }
                else {
                    answerBox[question.correctAnswer].loadTexture("asset/Image/PracticeAnswerBox_Word_Correct.png");
                    if (question.correctAnswer != i)
                        answerBox[i].loadTexture("asset/Image/PracticeAnswerBox_Word_Wrong.png");
                }
                for (int j = 0; j < 4; ++j) 
                    answerBox[j].disable();    
            }
        }
    }

}

PracticeQuestionPage::~PracticeQuestionPage()
{
    UnloadTexture(practiceTag);
}

const PracticeQuestionPage& PracticeQuestionPage::operator=(const PracticeQuestionPage& rhs) {
    if (this == &rhs) return *this;
    this->practiceTag = rhs.practiceTag;
    this->question = rhs.question;
    this->questionBox = rhs.questionBox;
    // this->answerBox = rhs.answerBox;
    this->chosenAnswer = rhs.chosenAnswer;
    return *this;
}

void PracticeQuestionPage::newQuestion() {
    question = generateQuestion();
    if (question.type_askByWord) {
        questionBox.setButton("asset/Image/PracticeQuestionBox_Word.png", 75, 140);
        questionBox.disable();
        answerBox[0].setButton("asset/Image/PracticeAnswerBox_Definition.png", 75, 276);
        answerBox[1].setButton("asset/Image/PracticeAnswerBox_Definition.png", 75, 456);
        answerBox[2].setButton("asset/Image/PracticeAnswerBox_Definition.png", 695, 276);
        answerBox[3].setButton("asset/Image/PracticeAnswerBox_Definition.png", 695, 456);
    }
    else {
        questionBox.setButton("asset/Image/PracticeQuestionBox_Definition.png", 75, 140);
        questionBox.disable();
        answerBox[0].setButton("asset/Image/PracticeAnswerBox_Word.png", 118, 375);
        answerBox[1].setButton("asset/Image/PracticeAnswerBox_Word.png", 118, 500);
        answerBox[2].setButton("asset/Image/PracticeAnswerBox_Word.png", 723, 375);
        answerBox[3].setButton("asset/Image/PracticeAnswerBox_Word.png", 723, 500);
    }
    for (int i = 0; i < 4; ++i) answerBox[i].enable();
}