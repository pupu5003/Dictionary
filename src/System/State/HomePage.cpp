#include "raylib.h"
#include "HomePage.hpp"
#include <string>

#define TEXT_BOX_WIDTH  400
#define TEXT_BOX_HEIGHT 230

HomePage::HomePage(int &currentScreen, Dictionary &dictionary): currentScreen(currentScreen), dictionary(dictionary), randomWord(dictionary.getRandomWord())
{
    homeTag = LoadTexture("asset/Image/HomeTag.png");

    historyButton.setButton("asset/Image/HistoryButton.png", 196.25, 204.81);
    favoriteButton.setButton("asset/Image/FavouriteButton.png", 504.88, 204.81);
    practiceButton.setButton("asset/Image/PracticeButton.png", 813.51, 204.81);
    settingButton.setButton("asset/Image/settings_ic.png", 1159, 23);

    like.setButton("asset/Image/Heart_ic.png", 870, 326, 1.1);
    liked.setButton("asset/Image/Hear1_ic.png", 870, 328, 1.1);
    edit.setButton("asset/Image/Edit_ic.png", 935, 324, 1.1);
    changeWord.setButton("asset/Image/Reload_ic.png", 990, 324, 1.1);

    wordCard.setButton("asset/Image/WordCard.png", 181, 296);
}

void HomePage::display() const {
    DrawTexture(homeTag, 0, 0, WHITE);

    settingButton.display();
    historyButton.display();
    favoriteButton.display();
    practiceButton.display();

    wordCard.display();
    DrawText(randomWord.word.c_str(), 232, 322, 40, BLACK);
    DrawTextBoxed(randomWord.definition[0].c_str(), { 232, 380, TEXT_BOX_WIDTH, TEXT_BOX_HEIGHT }, 30, 0.5f, true);
    
    dataSet data = engEng;
    if (randomWord.isFavorite) {
        liked.display();
    } else {
        like.display();
    }
    edit.display();
    changeWord.display();

    DrawLine(107, 281, 1134, 281, BLACK);
}

void HomePage::handleEvent() {
    if (historyButton.isPressed()) {
        currentScreen = 1;
    } else if (favoriteButton.isPressed()) {
        currentScreen = 2;
    } else if (practiceButton.isPressed()) {
        currentScreen = 3;
    } else if (settingButton.isPressed()) {
        currentScreen = 4;
    } else if (like.isPressed()) {
        randomWord.isFavorite = !randomWord.isFavorite;
        if (randomWord.isFavorite) {
            dictionary.addFavorite(randomWord.id, engEng);
        } else {
            dictionary.removeFavorite(randomWord.id, engEng);
        }
    } else if (edit.isPressed()) {
        cout << "Edit button is pressed" << endl;
    } else if (changeWord.isPressed()) {
        randomWord = dictionary.getRandomWord();
    }
}

HomePage::~HomePage() {
    UnloadTexture(homeTag);
}

void DrawTextBoxed(const char *text, Rectangle rec, int fontSize, float spacing, bool wordWrap) {
    Font font = LoadFontEx("asset/Font/Russo_One.ttf", fontSize, 0, 0);
    Vector2 position = { rec.x, rec.y };
    float scale = (float)fontSize / (float)font.baseSize;

    int textLength = TextLength(text);
    int lastSpace = -1;
    int lineStart = 0;

    for (int i = 0; i < textLength; i++) {
        char currentChar = text[i];

        if (currentChar == ' ') lastSpace = i;

        // Measure the substring from lineStart to the current character
        std::string line(text + lineStart, i - lineStart + 1);
        float textWidth = MeasureTextEx(font, line.c_str(), fontSize, spacing).x;

        // Check if any part of the current line extends beyond the rectangle's width
        if (currentChar == '\n' || (position.x + textWidth > rec.x + rec.width && wordWrap)) {
            if (lastSpace >= 0 && wordWrap) i = lastSpace + 1; // Wrap at last space

            // Draw the current line
            DrawTextEx(font, &text[lineStart], position, fontSize, spacing, BLACK);

            // Calculate the x-coordinate for the next line
            position.x = rec.x;

            // Move down for the next line
            position.y += fontSize + 10;

            // Reset the line start
            lineStart = i;

            // Reset lastSpace for the next line
            lastSpace = -1;

            // If it's a newline, advance the lineStart to skip the '\n'
            if (currentChar == '\n') lineStart++;
        }
    }

    // Draw the last line
    if (lineStart < textLength) {
        DrawTextEx(font, &text[lineStart], position, fontSize, spacing, BLACK);
    }
}