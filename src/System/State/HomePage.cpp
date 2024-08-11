#include "raylib.h"
#include "HomePage.hpp"
#include <string>

#define TEXT_BOX_WIDTH  400
#define TEXT_BOX_HEIGHT 230

HomePage::HomePage(int &currentScreen, Dictionary &dictionary): currentScreen(currentScreen), dictionary(dictionary)
{
    randomWord = &dictionary.getRandomWord();
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
    DrawText(randomWord -> word.c_str(), 232, 322, 40, BLACK);
    DrawTextBoxed(randomWord -> definition[0].c_str(), { 232, 380, 600, 1000 }, 30, 0.5f, true);
    
    dataSet data = engEng;
    if (randomWord -> isFavorite) {
        liked.display();
    } else {
        like.display();
    }
    edit.display();
    changeWord.display();

    DrawLine(107, 281, 1134, 281, BLACK);
}

void HomePage::handleEvent() {
    // if (randomWord.isFavorite) exit(0);
    if (historyButton.isPressed()) {
        currentScreen = 1;
    } else if (favoriteButton.isPressed()) {
        currentScreen = 2;
    } else if (practiceButton.isPressed()) {
        currentScreen = 3;
    } else if (settingButton.isPressed()) {
        currentScreen = 4;
    } else if (like.isPressed()) {
        // randomWord.isFavorite = !randomWord.isFavorite;
        if (!randomWord -> isFavorite) {
            dictionary.addFavorite(randomWord -> id, engEng);
        } else {
            dictionary.removeFavorite(randomWord -> id, engEng);
        }
    } else if (edit.isPressed()) {
        cout << "Edit button is pressed" << endl;
    } else if (changeWord.isPressed()) {

        randomWord = &dictionary.getRandomWord();
    }

}

HomePage::~HomePage() {
    UnloadTexture(homeTag);
}

 void DrawTextBoxed(const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    Font font = LoadFontEx("asset/Font/Russo_One.ttf", fontSize, 0, 0);
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
 void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}