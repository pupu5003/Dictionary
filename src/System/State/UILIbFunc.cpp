#include "UILibFunc.hpp"

int random(int min, int max)
{
    srand(chrono::system_clock::now().time_since_epoch().count());
    return rand() % (max - min + 1) + min;
}
