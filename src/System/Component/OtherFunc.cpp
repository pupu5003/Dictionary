#include "OtherFunc.hpp"

int random(int min, int max)
{
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    return std::rand() % (max - min + 1) + min;
}

Vector2 GetCenterPos(Font font, std::string text, float fontSize, float spacing, float x, float y, float width, float height) {
	Vector2 centerPos;
	centerPos.x = x + (width - MeasureTextEx(font, text.c_str(), fontSize, spacing).x) / 2;
	centerPos.y = y + (height - MeasureTextEx(font, text.c_str(), fontSize, spacing).y) / 2;
	return centerPos;
}
