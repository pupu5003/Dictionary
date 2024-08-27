#include "raylib.h"
#include "HomePage.hpp"
#include "SearchResPage.hpp"
#include <string>

#define TEXT_BOX_WIDTH  400
#define TEXT_BOX_HEIGHT 230

HomePage::HomePage(int &currentScreen, Dictionary &dictionary): currentScreen(currentScreen), dictionary(dictionary), searchBar(dictionary, currentScreen, {280, 90})
{
    randomWord = &dictionary.getRandomWord();
    while(randomWord -> id == -1) randomWord =  &dictionary.getRandomWord();

    homeTag = LoadTexture("asset/Image/HomeTag.png");

    historyButton.setButton("asset/Image/HistoryButton.png", 196.25, 204.81);
    favoriteButton.setButton("asset/Image/FavouriteButton.png", 504.88, 204.81);
    practiceButton.setButton("asset/Image/PracticeButton.png", 813.51, 204.81);
    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    like.setButton("asset/Image/Heart_ic.png", 870, 326, 1.1);
    liked.setButton("asset/Image/Hear1_ic.png", 870, 326, 1.1);
    changeWord.setButton("asset/Image/Reload_ic.png", 990, 324, 1.1);
    detailButton.setButton("asset/Image/DetailButton.png", 935, 324, 1.1);

    wordCard.setButton("asset/Image/WordCard.png", 181, 296);

}

void HomePage::display() const {
    DrawTexture(homeTag, 0, 0, WHITE);


    settingButton.display();
    historyButton.display();
    favoriteButton.display();
    practiceButton.display();

    wordCard.display();
    DrawTextEx(FontHelper::getInstance().getFont(InterBold), randomWord -> word.c_str(), { 234, 320}, 45, 0.5f, BLACK);
    float dis = GetStringWidth(FontHelper::getInstance().getFont(InterBold), randomWord -> word.c_str(), 45, 0.5f);
   
    if (randomWord -> type.size() > 0 && randomWord -> type[0].size() > 2)
    DrawTextBoxed(FontHelper::getInstance().getFont(Inter), randomWord -> type[0].c_str(), { 234 + dis, 328, 636 -dis, 35}, 34, 0.5f, false, BLACK);
   
    DrawTextBoxed(FontHelper::getInstance().getFont(Inter) ,randomWord -> definition[0].c_str(), {232, 380, 800, 280}, 38, 0.5f, true, BLACK);
    
    // if (CheckCollisionPointRec(GetMousePosition(), { 232, 650, 93, 33 })) {
    //     DrawTextEx(FontHelper::getInstance().getFont(OpenSanBold), "(More...)", { 232, 650 }, 33, 0.5f, BLACK);
    // } 
    // else {
    //     DrawTextEx(FontHelper::getInstance().getFont(OpenSan), "(More...)", { 232, 650 }, 33, 0.5f, BLACK);
    // }
    DrawTextEx(FontHelper::getInstance().getFont(RussoOne), dataSetName[randomWord -> data].c_str(), {900, 650 }, 33, 0.5f, BLACK);
   
    if (randomWord -> isFavorite) {
        liked.display();
    } else {
        like.display();
    }
    detailButton.display();
    changeWord.display();

    DrawLine(107, 281, 1134, 281, BLACK);

    searchBar.display();
}

void HomePage::handleEvent() {
    // if (randomWord.isFavorite) exit(0);
    while(randomWord -> id == -1) randomWord =  &dictionary.getRandomWord();

    if (searchBar.getActive()) 
    {
        searchBar.handleEvent();
        return;
    }
    searchBar.handleEvent();

    if (historyButton.isPressed()) {
        currentScreen = HISTORY;
    } else if (favoriteButton.isPressed()) {
        currentScreen = FAVORITE;
    } else if (practiceButton.isPressed()) {
        currentScreen = PRACTICE;
    } else if (settingButton.isPressed()) {
        currentScreen = SETTING;
    } else if (!randomWord -> isFavorite && like.isPressed()) 
    {
        dictionary.addFavorite(randomWord -> data, randomWord -> id);
    } else if (randomWord -> isFavorite && liked.isPressed()) 
    {
        dictionary.removeFavorite(randomWord -> data, randomWord -> id);
    } else if (changeWord.isPressed()) {

        randomWord = &dictionary.getRandomWord();
    }
    else if (detailButton.isPressed()) {
        currentScreen = SEARCH_RES;
        dictionary.addHistory(randomWord -> data, randomWord -> id);
        SearchResPage::setSearchWord(randomWord);
    }

}

HomePage::~HomePage() {
    UnloadTexture(homeTag);
}

