#include "AddWordPage.hpp"
using namespace std;

#define scrollUp 70
#define scrollDown 244
#define scrollSpeed 4
#define visibleUP 100
#define visibleDOWN 800
#define gap 40
#define SLIGHTRED Color{244, 210, 210, 50}


AddWordPage::AddWordPage(int &currentScreen, Dictionary &dictionary): currentScreen(currentScreen), dictionary(dictionary),
    inputDef({184, 268, 872, 420}), inputType({321, 220, 600, 37}), inputWord({294, 261, 600, 41})
{
    inputDef.setFont(FontHelper::getInstance().getFont(Inter), 40);
    inputType.setFont(FontHelper::getInstance().getFont(Inter), 36);
    inputType.centerText(); inputType.setColor(RED); 
    inputType.setOptinal(); inputDef.setRequired();
    inputWord.setFont(FontHelper::getInstance().getFont(InterBold), 40);
    inputWord.setRequired();

    word = Word();
    state = ADDWORD;

    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    AddWordTag = LoadTexture("asset/Image/AddWordTag.png");

    keywordBox = LoadTexture("asset/Image/AddWord.png");
    curDataSet[0] = LoadTexture("asset/Image/engEng1.png");
    curDataSet[1] = LoadTexture("asset/Image/engVie1.png");
    curDataSet[2] = LoadTexture("asset/Image/vieEng1.png");
    curDataSet[3] = LoadTexture("asset/Image/emoji1.png");
    curDataSet[4] = LoadTexture("asset/Image/slang1.png");
    curDataSet[5] = LoadTexture("asset/Image/dataset.png");
    dataSetOptions = LoadTexture("asset/Image/dataSetOptions1.png");
    dataSetBut = {346, 355, 204, 59};
    addNewButton.setButton("asset/Image/AddNewButton.png", 725, 515);
    like.setButton("asset/Image/Heart_ic.png", 912, 260);
    liked.setButton("asset/Image/Hear1_ic.png", 912, 260);
    data = 5; choseeData = false;

    
    barrier = LoadTexture("asset/Image/SearchResTag.png");
    addDefButton.setButton("asset/Image/addDefButton.png", 910, 141, 1.1);
    saveDefButton.setButton("asset/Image/saveDefButton.png", 954, 134, 1.1);
    cancelDefButton.setButton("asset/Image/cancelDefButton.png", 1044, 136, 1.1);
    edit.setButton("asset/Image/Edit_ic.png", 1053, 220, 1.1);
    edit.enable();
    deleteDefButton.setButton("asset/Image/DeleteDef.png", 1142, 190, 1.1);
    deleteDefButton.enable();
    
    doneButton.setButton("asset/Image/DoneButton.png", 994, 132, 1.1);
    
    upDef = 0; downDef = -1; isEdit = 0; 
    scroll = 0;

}

void AddWordPage::display() const
{
    if (state == ADDWORD)
    {
        DrawTexture(AddWordTag, 0, 0, WHITE);
        backButton.display();
        DrawTexture(keywordBox, 233, 206, WHITE);
        if (choseeData) 
            DrawTexture(dataSetOptions, 346, 355, WHITE);
        else
            DrawTexture(curDataSet[data], 346, 355, WHITE);
        addNewButton.display();
        if (word.isFavorite) liked.display();
        else like.display();
        inputWord.display();
    }
    else if (state == ADDDEF)
    {
        DrawTexture(AddWordTag, 0, 0, WHITE);
        saveDefButton.display();
        cancelDefButton.display();

        DrawTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), { 156, 135 }, 50, 0.5f, BLACK);
        DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[word.data].c_str(), {771, 144 }, 33, 0.5f, BLACK);
        DrawLine(107, 192, 1136, 192, BLACK);
        
        float roundness = 0.15*444/500;
        DrawRectangleRounded({120, 210, 1000, 500}, roundness, 0, SLIGHTRED);
        DrawRectangleRoundedLines({120, 210, 1000, 500}, roundness, 0, 1, BLACK);
        DrawRectangleLinesEx({184, 268, 872, 420}, 1.3, BLACK);
        DrawLine(321, 258, 931, 258, BLACK);
        inputDef.display();
        inputType.display();
    } 
    else if (state == COMPELETE)
    {
        for (int i = upDef; i <= downDef; i++)
        {
            float height = Gap[i + 1] - Gap[i] - gap;
            float space = Gap[i] + scroll;
            float heightDef = height - 100;
            float roundness = 0.15*444/height;

            DrawRectangleRounded({120, 210 + space, 1000, height}, roundness, 0, SLIGHTRED);
            DrawRectangleRoundedLines({120, 210 + space, 1000, height}, roundness, 0, 1, BLACK);

            if (i < (int)word.type.size() && (int)word.type[i].size() > 2)
            {
                float dis = GetStringWidth(FontHelper::getInstance().getFont(Inter), word.type[i].c_str(), 36, 0.5f);
                DrawTextEx(FontHelper::getInstance().getFont(Inter), word.type[i].c_str(), { 622 - dis/2, 220 + space}, 36, 0.5f, RED);
            }

            edit.display(0, space);  deleteDefButton.display(0,  space  + height/2);
            DrawTextBoxed(FontHelper::getInstance().getFont(Inter), word.definition[i].c_str(), { 184, 268 + space, 872, heightDef}, 40, 0.5f, true, BLACK);
        }

        DrawTexture(barrier, 0, 0, WHITE);
        DrawTexture(AddWordTag, 0, 0, WHITE);
        backButton.display();
        addDefButton.display();
        doneButton.display();
        DrawTextEx(FontHelper::getInstance().getFont(InterBold), word.word.c_str(), { 156, 135 }, 50, 0.5f, BLACK);
        DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[word.data].c_str(), {771, 144 }, 33, 0.5f, BLACK);
        DrawLine(107, 192, 1136, 192, BLACK);

    }
}

void AddWordPage::handleEvent()
{
    if (confirmDialog.isShown())
    {
        confirmDialog.handleEvent();
        return;
    }

    if (state == ADDWORD)
    {
        inputWord.handleEvent();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (choseeData)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), {dataSetBut.x, dataSetBut.y + dataSetBut.height * (i + 1),  dataSetBut.width,  dataSetBut.height}))
                    {
                        data = i;
                        choseeData = false;
                        break;
                    }
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), dataSetBut))
            {
                choseeData = !choseeData;
            }
            else choseeData = false;
        }
        if (choseeData) return;
        if (addNewButton.isPressed())
        {
            if (inputWord.isValid() && data != 5)
            {
                word.word = inputWord.getText();
                word.data = (dataSet)data;
                isEdit = 0;
                state = ADDDEF;
            }
        }
        else if (!word.isFavorite && like.isPressed())
        {
            word.isFavorite = true;
        }
        else if (word.isFavorite && liked.isPressed())
        {
            word.isFavorite = false;
        }
        else if (backButton.isPressed())
        {
            word = Word();
            currentScreen = SETTING;
        }
    }
    else if (state == ADDDEF)
    {
        inputDef.handleEvent(); inputType.handleEvent();
        if (saveDefButton.isPressed())
        {
            if (inputDef.isValid())
            {
                if (isEdit == word.definition.size())
                {
                    word.definition.push_back(inputDef.getText());
                    word.type.push_back(inputType.getText());
                }
                else
                {
                    word.definition[isEdit] = inputDef.getText();
                    word.type[isEdit] = inputType.getText();
                }
                resetGap();
                resetUpDownDef();
                isEdit = 0; inputDef.reset(); inputType.reset();
                state = COMPELETE;
            }
        }
        else if (cancelDefButton.isPressed())
        {
            isEdit = 0; inputDef.reset(); inputType.reset();
            if (word.definition.size() == 0) state = ADDWORD;
            else state = COMPELETE;
        }
    }
    else if (state == COMPELETE)
    {
        scroll += (int)(GetMouseWheelMove() * scrollSpeed);
        resetUpDownDef();
        if  (doneButton.isPressed())
        {
            dictionary.addWord(word);
            word = Word(); scroll = 0;
            state = ADDWORD;
            inputDef.reset(); inputType.reset(); inputWord.reset();
            resetGap();
            resetUpDownDef();
        }
        else if (backButton.isPressed())
        {
            // word.definition.clear(); word.type.clear();
            state = ADDWORD;
            scroll = 0;
            resetGap();
            resetUpDownDef();
        }
        else if (addDefButton.isPressed())
        {
            isEdit = (int)(word.definition.size());
            state = ADDDEF;
        }
        else 
        {
            for (int i = upDef; i <= downDef; i++)
            {
                float height = Gap[i + 1] - Gap[i] - gap;
                float space = Gap[i] + scroll;
                float heightDef = height - 100;
            
                if (edit.isPressed(0, space))
                {
                    isEdit = i;
                    state = ADDDEF;
                    break;
                }
                if (deleteDefButton.isPressed(0, space + height/2))
                {
                    word.definition.erase(word.definition.begin() + i);
                    word.type.erase(word.type.begin() + i);
                    if (word.definition.size() == 0) state = ADDDEF;
                    resetGap();
                    resetUpDownDef();
                    break;
                }
            }
        }
    }
}

void AddWordPage::resetGap()
{
    Gap.clear();
    float space = 0;
    for (int i = 0; i < (int)word.definition.size(); i++)
    {
        float heightDef = (int)((GetStringWidth(FontHelper::getInstance().getFont(Inter), word.definition[i].c_str(), 40, 0.5f) + 871)/ 872) * 60 + gap;
        float height = 100 + heightDef;
        Gap.push_back(space);
        space += height + gap;
    }
    Gap.push_back(space);
}

void AddWordPage::resetUpDownDef()
{
    if (word.definition.size() == 0)
    {
        upDef = 0; downDef = -1;
        return;
    }
    upDef = lower_bound(Gap.begin(), Gap.end(), visibleUP - scroll - 210) - Gap.begin() - 1;
    downDef = upper_bound(Gap.begin(), Gap.end(), visibleDOWN - scroll - 210) - Gap.begin() - 1;
    if (downDef < 0) downDef = 0; if (upDef < 0) upDef = 0;
    if (downDef > Gap.size() - 2) downDef = Gap.size() - 2; if (upDef > Gap.size() - 2) upDef = Gap.size() - 2; 

    if (upDef == 0 && scroll > scrollUp) 
    {
        scroll = scrollUp;
    }
    else if (downDef == word.definition.size() - 1 && scroll + Gap.back() - gap < scrollDown) 
    {
        scroll = scrollDown - Gap.back() + gap;
    }
}

// void AddWordPage::clear()
// {

//     word = Word();
//     curState = ADDWORD;
//     inputDef.clear();
//     inputType.clear();
//     resetGap();
//     resetUpDownDef();
//     isEdit = -1;
//     scroll = 0;
// }


AddWordPage::~AddWordPage()
{
    UnloadTexture(AddWordTag);
}