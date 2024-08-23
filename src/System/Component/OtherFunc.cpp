#include "OtherFunc.hpp"

int random(int min, int max)
{
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    return std::rand() % (max - min + 1) + min;
}
