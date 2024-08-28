#pragma once
#include "UILibFunc.hpp"

enum AddWordState
{
    ADDWORD,
    ADDDEF,
    COMPELETE
};

class AddWordPage : public Page
{
private:
    Texture2D AddWordTag;
    Button backButton;
    Word word;
    DialogYesNo confirmDialog;
    AddWordState state;

    // state AddWord
    Texture2D keywordBox;
    Texture2D curDataSet[6];
    Texture2D dataSetOptions;
    Rectangle dataSetBut;
    Button addNewButton;
    Button like, liked;
    TextInputBox inputWord;
    int data;
    bool choseeData;

    // state AddDef
    Texture2D barrier;
    TextInputBox inputDef;
    TextInputBox inputType;
    Button addDefButton;
    Button saveDefButton;
    Button cancelDefButton;
    Button deleteDefButton;
    Button edit;
    vector<int> Gap;
    int upDef, downDef;
    int isEdit;

    //state complete
    Button doneButton;
    float scroll;
    int& currentScreen;
    Dictionary &dictionary;

public:
    AddWordPage(int &currentScreen, Dictionary &dictionary);
    ~AddWordPage();
    void display() const override;
    void handleEvent() override;
    void reset() override;
    void resetGap();
    void resetUpDownDef();
    // void clear();
};