#include "PracticeQuestionPage.hpp"
using namespace std;

PracticeQuestionPage::PracticeQuestionPage(int &currentScreen, Dictionary& dictionary) : currentScreen(currentScreen), dictionary(dictionary)
{
    this->dictionary = dictionary;
    question = generateQuestion(dictionary, data);

    practiceTag = LoadTexture("asset/Image/PracticeTag.png");
    backButton.setButton("asset/Image/back_ic.png", 45, 31);
    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);
    continueButton.setButton("asset/Image/continueButton.png", 929, 637);

    curDataSet[0] = LoadTexture("asset/Image/engEng2.png");
    curDataSet[1] = LoadTexture("asset/Image/engVie2.png");
    curDataSet[2] = LoadTexture("asset/Image/vieEng2.png");
    curDataSet[3] = LoadTexture("asset/Image/emoji2.png");
    curDataSet[4] = LoadTexture("asset/Image/slang2.png");
    
    optionBut[0] = LoadTexture("asset/Image/engEng1.png");
    optionBut[1] = LoadTexture("asset/Image/engVie1.png");
    optionBut[2] = LoadTexture("asset/Image/vieEng1.png");
    optionBut[3] = LoadTexture("asset/Image/emoji1.png");
    optionBut[4] = LoadTexture("asset/Image/slang1.png");
    optionBut[5] = LoadTexture("asset/Image/dataSet1.png");

    dataSetOptions = LoadTexture("asset/Image/dataSetOptions2.png");
    dataSetBut = {75, 650, 163, 54};
    choseeData = false;

    setElementBox();
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

    if (choseeData) {
        DrawTexture(dataSetOptions, dataSetBut.x, dataSetBut.y - (dataSetOptions.height - dataSetBut.height), WHITE);
        for (int j = 0; j < 6; ++j) {
            if (CheckCollisionPointRec(GetMousePosition(), {dataSetBut.x, dataSetBut.y - dataSetOptions.height + dataSetBut.height * (j + 1), dataSetBut.width, dataSetBut.height})) {
                DrawTexture(optionBut[j], dataSetBut.x, dataSetBut.y - dataSetOptions.height + dataSetBut.height * (j + 1), LIGHTGRAY);
            }
        }
    }
    else {
        if (CheckCollisionPointRec(GetMousePosition(), dataSetBut))
            DrawTexture(curDataSet[data], dataSetBut.x, dataSetBut.y, LIGHTGRAY);
        else DrawTexture(curDataSet[data], dataSetBut.x, dataSetBut.y, WHITE);
    }

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
    else if (choseeData)
    {
        for (int i = 0; i < 5; i++)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {dataSetBut.x, dataSetBut.y - dataSetOptions.height + dataSetBut.height * (i + 1), dataSetBut.width, dataSetBut.height}))
            {
                data = (dataSet)i;
                choseeData = false;
                newQuestion();
                return;
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), dataSetBut))
            choseeData = false;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), dataSetBut))
        choseeData = true;
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
    UnloadTexture(curDataSet[0]);
    UnloadTexture(curDataSet[1]);
    UnloadTexture(curDataSet[2]);
    UnloadTexture(curDataSet[3]);
    UnloadTexture(curDataSet[4]);

    UnloadTexture(dataSetOptions);

    UnloadTexture(optionBut[0]);
    UnloadTexture(optionBut[1]);
    UnloadTexture(optionBut[2]);
    UnloadTexture(optionBut[3]);
    UnloadTexture(optionBut[4]);
    UnloadTexture(optionBut[5]);
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
    question = generateQuestion(dictionary, data);
    setElementBox();
    for (int i = 0; i < 4; ++i) answerBox[i].enable();
}

void PracticeQuestionPage::setElementBox() {
    if (question.type_askByWord) {
        questionBox.setButton("asset/Image/PracticeQuestionBox_Word.png", 75, 140);
        questionBox.disable();
        answerBox[0].setButton("asset/Image/PracticeAnswerBox_Definition.png", 75, 276);
        answerBox[1].setButton("asset/Image/PracticeAnswerBox_Definition.png", 75, 456);
        answerBox[2].setButton("asset/Image/PracticeAnswerBox_Definition.png", 695, 276);
        answerBox[3].setButton("asset/Image/PracticeAnswerBox_Definition.png", 695, 456);
        questionBox.setText(this->question.question, OpenSanBold, 35, 3, true, BLACK);
        for (int i = 0; i < 4; ++i) 
            answerBox[i].setText(this->question.answer[i], OpenSan, 30, 3, true, BLACK);
    }
    else {
        questionBox.setButton("asset/Image/PracticeQuestionBox_Definition.png", 75, 140);
        questionBox.disable();
        answerBox[0].setButton("asset/Image/PracticeAnswerBox_Word.png", 118, 375);
        answerBox[1].setButton("asset/Image/PracticeAnswerBox_Word.png", 118, 500);
        answerBox[2].setButton("asset/Image/PracticeAnswerBox_Word.png", 723, 375);
        answerBox[3].setButton("asset/Image/PracticeAnswerBox_Word.png", 723, 500);
        questionBox.setText(this->question.question, OpenSan, 30, 3, true, BLACK);
        for (int i = 0; i < 4; ++i) 
            answerBox[i].setText(this->question.answer[i], OpenSanBold, 35, 3, true, BLACK);
    }
}

void PracticeQuestionPage::reset() {
    chosenAnswer = -1;
    newQuestion();
}