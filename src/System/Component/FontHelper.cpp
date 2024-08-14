#include "FontHelper.hpp"
using namespace std;

FontHelper::FontHelper()
{
    fonts.push_back(GetFontDefault());
    fonts.push_back(LoadFontEx("asset/Font/ARIAL.ttf", 40, (int*)VNCodePoints, sizeof(VNCodePoints) / sizeof(int)));
    fonts.push_back(LoadFontEx("asset/Font/Inter.ttf", 40, (int*)VNCodePoints, sizeof(VNCodePoints) / sizeof(int)));
    fonts.push_back(LoadFontEx("asset/Font/Inter_Bold.ttf", 40, (int*)VNCodePoints, sizeof(VNCodePoints) / sizeof(int)));
    fonts.push_back(LoadFontEx("asset/Font/OpenSans-Regular.ttf", 40, (int*)VNCodePoints, sizeof(VNCodePoints) / sizeof(int)));
    fonts.push_back(LoadFontEx("asset/Font/OpenSans-Bold.ttf", 40, (int*)VNCodePoints, sizeof(VNCodePoints) / sizeof(int)));
    fonts.push_back(LoadFontEx("asset/Font/Russo_One.ttf", 40, 0, 250));
}

FontHelper::~FontHelper()
{
    for (int i = 0; i < fonts.size(); i++)
    {
        UnloadFont(fonts[i]);
    }
}

FontHelper& FontHelper::getInstance()
{
    static FontHelper instance;
    return instance;
}

Font& FontHelper::getFont(fontType type)
{
    return fonts[type];
}
