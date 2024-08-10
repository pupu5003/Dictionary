// #include "WCharHandle.hpp"


// void DrawTextWChar(const wchar_t *text, int posX, int posY, int fontSize, Color color)
// {
//     // Check if default font has been loaded
//     if (GetFontDefault().texture.id != 0)
//     {
//         Vector2 position = { (float)posX, (float)posY };

//         int defaultFontSize = 10;   // Default Font chars height in pixel
//         if (fontSize < defaultFontSize) fontSize = defaultFontSize;
//         int spacing = fontSize/defaultFontSize;

//         DrawTextEx(GetFontDefault(), text, position, (float)fontSize, (float)spacing, color);
//     }
// }


// int MeasureTextWChar(const wchar_t *text, int fontSize)
// {
//     Vector2 textSize = { 0.0f, 0.0f };

//     // Check if default font has been loaded
//     if (GetFontDefault().texture.id != 0)
//     {
//         int defaultFontSize = 10;   // Default Font chars height in pixel
//         if (fontSize < defaultFontSize) fontSize = defaultFontSize;
//         int spacing = fontSize/defaultFontSize;

//         textSize = MeasureTextEx(GetFontDefault(), text, (float)fontSize, (float)spacing);
//     }

//     return (int)textSize.x;
// }