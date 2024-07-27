#include "FavoriteState.h"
#include <raylib.h>
#include <iostream>
#include <../src/Color/color.h>

const int VISIBLE_HISTORY_ITEMS = 4;

void drawFavoritePage(int screenWidth, int screenHeight) {
    // Load icons
    Texture2D backIcon = LoadTexture("asset/Image/back_ic.png");
    Texture2D settingsIcon = LoadTexture("asset/Image/settings_ic.png");
    Texture2D clearAllImage = LoadTexture("asset/Image/ClearAllButton.png");
    Texture2D Box = LoadTexture("asset/Image/RectangleHistory.png");
    Texture2D XIamge = LoadTexture("asset/Image/X.png");
    Font fontRussoOne = LoadFontEx("asset/Font/Russo_One.ttf", 200, 0, 250);

    // Declare and initialize history items
    std::vector<FavoriteItem> favorite;
    favorite.push_back({"societal1", "connected with society and the way it is..."});
    favorite.push_back({"societal2", "connected with society and the way it is..."});
    favorite.push_back({"societa3", "connected with society and the way it is..."});
    favorite.push_back({"societal4", "connected with society and the way it is..."});
    favorite.push_back({"societal5", "connected with society and the way it is..."});
    favorite.push_back({"societal6", "connected with society and the way it is..."});
    favorite.push_back({"societal7", "connected with society and the way it is..."});
    favorite.push_back({"societal8", "connected with society and the way it is..."});  
          

    // Define rectangles for UI elements
    Rectangle backButton = {17, 25, 60, 60};
    Rectangle settingsButton = {1363, 26, 60, 60};
    Rectangle clearAllButton = {619, 134, 221, 70};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, backButton)) {
                
            }
            if (CheckCollisionPointRec(mousePosition, settingsButton)) {
                
            }
            if (CheckCollisionPointRec(mousePosition, clearAllButton)) {
                favorite.clear();
            }

            for (int i = 0; i < favorite.size(); i++) {
                Rectangle favoriteBox = {50, (float)236 + 150 * i, 1289, 108};
                Rectangle xButton = {1369, favoriteBox.y + 28, (float)XIamge.width, (float)XIamge.height};
                
                if (CheckCollisionPointRec(mousePosition, xButton)) {
                    favorite.erase(favorite.begin() + i);
                    break;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND);
        DrawRectangle(0, 0, screenWidth, 110, LIGHTRED);

        // Draw header
        const char* text = "FAVORITE";
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
        for (int i = 0; i < favorite.size() && i < VISIBLE_HISTORY_ITEMS; i++) {
            Rectangle historyBox = {50, (float)236 + 150 * i, 1289, 108};
            Rectangle xButton = {1369, historyBox.y + 28, (float)XIamge.width, (float)XIamge.height};
            
            DrawTexture(Box, historyBox.x, historyBox.y, WHITE);
            DrawTexture(XIamge, xButton.x, xButton.y, WHITE);

            // Draw word and description
            const char* text2 = favorite[i].word.c_str();
            int fontSize2 = 40;
            float spacing2 = 1.0f; // Spacing between letters
            Vector2 textSize2 = MeasureTextEx(fontRussoOne, text2, fontSize2, spacing2);
            float posY = historyBox.y + (historyBox.height - textSize2.y) / 2;
            DrawTextEx(fontRussoOne, text2, {historyBox.x + 40, posY}, fontSize2, spacing2, BLACK);
        }

        EndDrawing();
    }

    // Unload resources
    UnloadTexture(backIcon);
    UnloadTexture(settingsIcon);
    UnloadFont(fontRussoOne);
}
