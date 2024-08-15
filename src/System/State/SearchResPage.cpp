#include "SearchResPage.hpp"

#define scrollUp 70
#define scrollDown 244
#define scrollSpeed 4
#define visibleUP 100
#define visibleDOWN 800
#define gap 40
using namespace std;


Word *SearchResPage::searchWord = nullptr;
float SearchResPage::scroll = 0;
vector<float> SearchResPage::Gap;

SearchResPage::SearchResPage(int &currentScreen) : currentScreen(currentScreen)
{
    searchResTag = LoadTexture("asset/Image/SearchResTag.png");
    
    backButton.setButton("asset/Image/back_ic.png", 45, 31);

    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    like.setButton("asset/Image/Heart_ic.png", 983, 141, 1.1);
    liked.setButton("asset/Image/Hear1_ic.png", 983, 141, 1.1);
    deleteButton.setButton("asset/Image/Delete_ic.png", 1046, 134, 1.1);
    edit.setButton("asset/Image/Edit_ic.png", 1053, 215, 1.1);
}

void SearchResPage::display() const
{
    // int l = lower_bound(Gap.begin(), Gap.end(), visibleUP - scroll + gap) - Gap.begin() - 1;
    // int r = upper_bound(Gap.begin(), Gap.end(), visibleDOWN - scroll) - Gap.begin() - 1;
    // if (r < 0) r = 0; if (l < 0) l = 0;
    // if (r > Gap.size() - 2) r = Gap.size() - 2; if (l > Gap.size() - 2) l = Gap.size() - 2; 


    // if (l == 0 && scroll > scrollUp) 
    // {
    //     scroll = scrollUp;
    //     space = scroll;
    // }
    // else if (r == searchWord -> definition.size() - 1 && space + height < scrollDown) 
    // {
    //     space -= scroll;    
    //     scroll = scrollDown - height - space;
    //     space += scroll;
    // }

    for (int i = l; i <= r; i++)
    {
        float height = Gap[i + 1] - Gap[i] - gap;
        float space = Gap[i] + scroll;
        float heightDef = height - 100;
        float roundness = 0.15*444/height;

        DrawRectangleRounded({120, 210 + space, 1000, height}, roundness, 0, Color{244, 210, 210, 50});
        DrawRectangleRoundedLines({120, 210 + space, 1000, height}, roundness, 0, 1, BLACK);
        if (i < searchWord -> type.size() && searchWord -> type[i].size() > 2)
        {
            float dis = GetStringWidth(FontHelper::getInstance().getFont(Inter), searchWord -> type[i].c_str(), 36, 0.5f);
            DrawTextEx(FontHelper::getInstance().getFont(Inter), searchWord -> type[i].c_str(), { 622 - dis/2, 220 + space}, 36, 0.5f, RED);
        }
        edit.display(0, space);
        DrawTextBoxed(FontHelper::getInstance().getFont(Inter), searchWord -> definition[i].c_str(), { 184, 268 + space, 872, heightDef}, 40, 0.5f, true, BLACK);
    }

    DrawTexture(searchResTag, 0, 0, WHITE);

    settingButton.display();

    backButton.display();

    if (searchWord -> isFavorite)
    {
        liked.display();
    }
    else
    {
        like.display();
    }
    deleteButton.display();

    DrawTextEx(FontHelper::getInstance().getFont(InterBold), searchWord -> word.c_str(), { 156, 135 }, 50, 0.5f, BLACK);
    DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[searchWord -> data].c_str(), {849, 144 }, 33, 0.5f, BLACK);
    DrawLine(107, 192, 1136, 192, BLACK);


}

void SearchResPage::handleEvent()
{
    
    if (backButton.isPressed())
    {
        currentScreen = HOME;
    }
    else if (settingButton.isPressed())
    {
        currentScreen = SETTING;
    }
    else if (like.isPressed())
    {
        searchWord -> isFavorite = !searchWord -> isFavorite;
    }
    else if (liked.isPressed())
    {
        searchWord -> isFavorite = false;
    }
    else if (deleteButton.isPressed())
    {
        cout << "Delete button is pressed" << endl;
    }

    scroll += (int)(GetMouseWheelMove() * scrollSpeed);
    l = lower_bound(Gap.begin(), Gap.end(), visibleUP - scroll - 210) - Gap.begin() - 1;
    r = upper_bound(Gap.begin(), Gap.end(), visibleDOWN - scroll - 210) - Gap.begin() - 1;
    if (r < 0) r = 0; if (l < 0) l = 0;
    if (r > Gap.size() - 2) r = Gap.size() - 2; if (l > Gap.size() - 2) l = Gap.size() - 2; 

    if (l == 0 && scroll > scrollUp) 
    {
        scroll = scrollUp;
    }
    else if (r == searchWord -> definition.size() - 1 && scroll + Gap.back() - gap < scrollDown) 
    {
        scroll = scrollDown - Gap.back() + gap;
    }

    for (int i = l; i <= r; i++)
    {
        float height = Gap[i + 1] - Gap[i] - gap;
        float space = Gap[i] + scroll;
        float heightDef = height - 100;
    
        if (edit.isPressed(0, space))
        {
            cout << "Edit button is pressed " << i << endl;
        }
    }


        
}

void SearchResPage::setSearchWord(Word* word)
{
    searchWord = word;
    Gap.clear();
    float space = 0;
    for (int i = 0; i < searchWord -> definition.size(); i++)
    {
        float heightDef = (int)((GetStringWidth(FontHelper::getInstance().getFont(Inter), searchWord -> definition[i].c_str(), 40, 0.5f) + 871)/ 872) * 60 + gap;
        float height = 100 + heightDef;
        Gap.push_back(space);
        space += height + 40;
    }
    Gap.push_back(space);
    
}

void SearchResPage::resetSrcoll()
{
    scroll = 0;
}

SearchResPage::~SearchResPage()
{
    UnloadTexture(searchResTag);
}