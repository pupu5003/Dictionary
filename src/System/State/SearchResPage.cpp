#include "SearchResPage.hpp"
// #include "../src/System/Component/TextHandle.hpp"

using namespace std;

#define scrollUp 70
#define scrollDown 244
#define scrollSpeed 16
#define visibleUP 100
#define visibleDOWN 800
#define gap 40
#define SLIGHTRED Color{244, 210, 210, 50}

Word *SearchResPage::searchWord = nullptr;
float SearchResPage::scroll = 0;
vector<float> SearchResPage::Gap;
int SearchResPage::upDef = 0, SearchResPage::downDef = -1;

SearchResPage::SearchResPage(int &currentScreen, Dictionary& dictionary) : currentScreen(currentScreen), dictionary(dictionary), searchBar(dictionary, currentScreen, {280, 35}), inputDef({184, 268, 872, 420}), inputType({321, 220, 600, 37})
{
    searchWord = nullptr;
    scroll = 0;
    Gap.clear();
    inputDef.setFont(FontHelper::getInstance().getFont(Inter), 40);
    inputType.setFont(FontHelper::getInstance().getFont(Inter), 36);
    inputType.centerText(); inputType.setColor(RED); 
    inputType.setOptinal(); inputDef.setRequired();

    searchResTag = LoadTexture("asset/Image/SearchResTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    addDefButton.setButton("asset/Image/addDefButton.png", 910, 141, 1.1);

    saveDefButton.setButton("asset/Image/saveDefButton.png", 954, 134, 1.1);

    cancelDefButton.setButton("asset/Image/cancelDefButton.png", 1044, 136, 1.1);

    like.setButton("asset/Image/Heart_ic.png", 978, 141, 1.1);

    liked.setButton("asset/Image/Hear1_ic.png", 978, 141, 1.1);

    deleteButton.setButton("asset/Image/Delete_ic.png", 1046, 134, 1.1);

    edit.setButton("asset/Image/Edit_ic.png", 1053, 220, 1.1);
    edit.enable();

    deleteDefButton.setButton("asset/Image/DeleteDef.png", 1142, 190, 1.1);
    deleteDefButton.enable();

    scroll = 0;

    upDef = 0; downDef = -1;
    isEdit = -1;
}

void SearchResPage::display() const
{
    if (isEdit == -1) {
        for (int i = upDef; i <= downDef; i++)
        {
            float height = Gap[i + 1] - Gap[i] - gap;
            float space = Gap[i] + scroll;
            float heightDef = height - 100;
            float roundness = 0.15*444/height;

            DrawRectangleRounded({120, 210 + space, 1000, height}, roundness, 0, SLIGHTRED);
            DrawRectangleRoundedLines({120, 210 + space, 1000, height}, roundness, 0, 1, BLACK);

            if (i < (int)searchWord -> type.size() && (int)searchWord -> type[i].size() > 2)
            {
                float dis = GetStringWidth(FontHelper::getInstance().getFont(Inter), searchWord -> type[i].c_str(), 36, 0.5f);
                DrawTextEx(FontHelper::getInstance().getFont(Inter), searchWord -> type[i].c_str(), { 622 - dis/2, 220 + space}, 36, 0.5f, RED);
            }

            edit.display(0, space); 
            if (searchWord -> definition.size() > 1)
            deleteDefButton.display(0,  space  + height/2);
            DrawTextBoxed(FontHelper::getInstance().getFont(Inter), searchWord -> definition[i].c_str(), { 184, 268 + space, 872, heightDef}, 40, 0.5f, true, BLACK);
        }
    } else {
        float height = 500;
        float roundness = 0.15*444/height;
        DrawRectangleRounded({120, 210, 1000, height}, roundness, 0, SLIGHTRED);
        DrawRectangleRoundedLines({120, 210, 1000, height}, roundness, 0, 1, BLACK);
        DrawRectangleLinesEx({184, 268, 872, 420}, 1.3, BLACK);
        DrawLine(321, 258, 931, 258, BLACK);
        inputDef.display();
        inputType.display();
    }


    DrawTexture(searchResTag, 0, 0, WHITE);

    if (isEdit == -1)
    {
        settingButton.display();

        backButton.display();

        addDefButton.display();
        if (searchWord -> isFavorite)
        {
            liked.display();
        }
        else
        {
            like.display();
        }
        deleteButton.display();
    }
    else
    {
        saveDefButton.display();
        cancelDefButton.display();
    }

    DrawTextEx(FontHelper::getInstance().getFont(InterBold), searchWord -> word.c_str(), { 156, 135 }, 50, 0.5f, BLACK);
    DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[searchWord -> data].c_str(), {771, 144 }, 33, 0.5f, BLACK);
    DrawLine(107, 192, 1136, 192, BLACK);

    searchBar.display();

    confirmDialog.display();
}

void SearchResPage::handleEvent()
{
    if (confirmDialog.isShown())
    {
        confirmDialog.handleEvent();
        return;
    }

    if (isEdit != -1)
    {
        inputDef.handleEvent();
        inputType.handleEvent();

        if (saveDefButton.isPressed())
        {
            if (inputDef.isValid())
            {
                dictionary.editDef(searchWord -> data, searchWord -> id, isEdit, inputType.getText(), inputDef.getText());
                resetGap();
                resetUpDownDef();
                searchBar.resetPredict();
                isEdit = -1; inputDef.reset(); inputType.reset();
            }
        }
        else if (cancelDefButton.isPressed())
        {
            isEdit = -1; inputDef.reset(); inputType.reset();
        }
        return;
    }

    if (searchBar.getActive()) 
    {
        searchBar.handleEvent();
        return;
    }
    searchBar.handleEvent();

    if (backButton.isPressed())
    {
        scroll = 0;
        upDef = 0; downDef = -1;
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        scroll = 0;
        upDef = 0; downDef = -1;
        currentScreen = SETTING;
    } 
    else if (addDefButton.isPressed())
    {
        isEdit = (int)(searchWord -> definition.size());

    }
    else if (!searchWord -> isFavorite && like.isPressed())
    {  
        dictionary.addFavorite(searchWord -> data, searchWord -> id);
    } else if (searchWord -> isFavorite && liked.isPressed())
    {
        dictionary.removeFavorite(searchWord -> data, searchWord -> id);
    } else if (deleteButton.isPressed())
    {
        confirmDialog.show([this](){
            dictionary.removeWord(searchWord -> data, searchWord -> id);
            searchBar.resetPredict();
            resetGap(); resetUpDownDef();
            currentScreen = HOME;
        });
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
                inputType.setCodePoints(searchWord -> definition[i]);
                inputDef.setCodePoints(searchWord -> definition[i]);
                break;
            }
            if (searchWord -> definition.size() == 1) continue;
            if (deleteDefButton.isPressed(0, space + height/2))
            {
                confirmDialog.show([this, i](){
                dictionary.removeDef(searchWord -> data, searchWord -> id, i);
                resetGap();
                resetUpDownDef();
                searchBar.resetPredict();});
                break;
            }
        }
    }        
    scroll += (int)(GetMouseWheelMove() * scrollSpeed);
    resetUpDownDef();
}

void SearchResPage::setSearchWord(Word* word)
{   
    scroll = 0;
    upDef = 0; downDef = -1;
    searchWord = word;
    resetGap();
}

void SearchResPage::resetGap()
{
    Gap.clear();
    float space = 0;
    for (int i = 0; i < (int)searchWord -> definition.size(); i++)
    {
        float heightDef = (int)((GetStringWidth(FontHelper::getInstance().getFont(Inter), searchWord -> definition[i].c_str(), 40, 0.5f) + 871)/ 872) * 60 + gap;
        float height = 100 + heightDef;
        Gap.push_back(space);
        space += height + gap;
    }
    Gap.push_back(space);
}

void SearchResPage::resetUpDownDef()
{
    if (searchWord -> definition.size() == 0)
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
    else if (downDef == searchWord -> definition.size() - 1 && scroll + Gap.back() - gap < scrollDown) 
    {
        scroll = scrollDown - Gap.back() + gap;
    }
}

SearchResPage::~SearchResPage()
{
    UnloadTexture(searchResTag);
}

void SearchResPage::reset()
{
    scroll = 0;
    upDef = 0; downDef = -1;
    searchWord = nullptr;
    Gap.clear();
    searchBar.reset();
    isEdit = -1;
    inputDef.reset(); inputType.reset();
    // confirmDialog.reset();
}

// void SearchResPage::setSearchBar(SearchBar searchBar) {
//     this->searchBar = searchBar;
// }