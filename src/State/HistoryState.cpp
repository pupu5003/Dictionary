#include "HistoryState.h"
#include <raylib.h>
#include <iostream>
#include <../src/Color/color.h>

const int MAX_HISTORY_ITEMS = 4;

void drawHistoryPage(int screenWidth, int screenHeight) {
    // Load icons
    Texture2D backIcon = LoadTexture("asset/Image/back_ic.png");
    Texture2D settingsIcon = LoadTexture("asset/Image/settings_ic.png");
    Texture2D clearAllImage = LoadTexture("asset/Image/ClearAllButton.png");
    Texture2D Box = LoadTexture("asset/Image/RectangleHistory.png");
    Texture2D XIamge = LoadTexture("asset/Image/X.png");
    Font fontRussoOne = LoadFontEx("asset/Font/Russo_One.ttf", 200, 0, 250);  

    // Initialize history items
    HistoryItem history[MAX_HISTORY_ITEMS] = {
        {"societal", "connected with society and the way it is..."},
        {"societal", "connected with society and the way it is..."},
        {"societal", "connected with society and the way it is..."},
        {"societal", "connected with society and the way it is..."}
    };

    // Define rectangles for UI elements
    Rectangle backButton = { 17, 25, 60, 60 };
    Rectangle settingsButton = { 1363, 26, 60, 60 };
    Rectangle clearAllButton = { 619, 134, 221, 70 };
    Rectangle historyBoxes[MAX_HISTORY_ITEMS];

    // Calculate positions for history boxes
    for (int i = 0; i < MAX_HISTORY_ITEMS; i++) {
        historyBoxes[i] = { 50, (float)236 + 150 * i, 1289, 108};
    }

    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();

            // Handle button clicks
            if (CheckCollisionPointRec(mousePosition, backButton)) {
                // Handle back button click (e.g., switch to a different state)
            }
            if (CheckCollisionPointRec(mousePosition, settingsButton)) {
                // Handle settings button click (e.g., switch to a settings state)
            }
            if (CheckCollisionPointRec(mousePosition, clearAllButton)) {
                // Handle clear all button click
                for (int i = 0; i < MAX_HISTORY_ITEMS; i++) {
                    history[i].word = "";
                    history[i].description = "";
                }
            }

            // Handle history item clicks
            for (int i = 0; i < MAX_HISTORY_ITEMS; i++) {
                if (CheckCollisionPointRec(mousePosition, historyBoxes[i])) {
                    // Handle individual history item click (e.g., display more details)
                    history[i].word = ""; // You might want to clear the word, not the description
                    history[i].description = "";
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND);

        // Draw top section
        DrawRectangle(0, 0, screenWidth, 110, LIGHTRED); 

        // Draw header
        const char* text = "HISTORY";
        int fontSize = 65; 
        float spacing = 1.0f; // Spacing between letters
        Vector2 textSize = MeasureTextEx(fontRussoOne, text, fontSize, spacing);
        float posX = (screenWidth - textSize.x) / 2;
        DrawTextEx(fontRussoOne, text, {posX, 29}, fontSize, spacing, BLACK);


        // Draw buttons
        if (backIcon.id != 0) {
            DrawTexture(backIcon, backButton.x, backButton.y, WHITE);
        }

        if (settingsIcon.id != 0) {
            DrawTexture(settingsIcon, settingsButton.x, settingsButton.y, WHITE);
        }

        if (clearAllImage.id != 0) {
            DrawTexture(clearAllImage, clearAllButton.x, clearAllButton.y, WHITE);
        }

        // Draw history items
        for (int i = 0; i < MAX_HISTORY_ITEMS; i++) {
            DrawTexture(Box, historyBoxes[i].x, historyBoxes[i].y, WHITE);
            DrawTexture(XIamge, 1369, historyBoxes[i].y + 28, WHITE);

            //Draw word and description
            const char* text2 =  history[i].word.c_str();
            int fontSize2 = 40; 
            float spacing2 = 1.0f; // Spacing between letters
            Vector2 textSize = MeasureTextEx(fontRussoOne, text2, fontSize2, spacing2);
            float posY =  historyBoxes[i].y + (historyBoxes[i].height - textSize.y) / 2;
            std::cout << historyBoxes[i].height << std::endl;
            DrawTextEx(fontRussoOne, text2, {historyBoxes[i].x + 40, posY}, fontSize2, spacing2, BLACK);
        }

        EndDrawing();
    }

    // Unload resources
    UnloadTexture(backIcon);
    UnloadTexture(settingsIcon);
    UnloadFont(fontRussoOne);
}