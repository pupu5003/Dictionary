#pragma once
#include <chrono>
#include <cstdlib>
#include <vector>
#include <raylib.h>
#include <string>

int random(int min, int max);
Vector2 GetCenterPos(Font font, std::string text, float fontSize, float spacing, float x, float y, float width, float height);
