#include <iostream>
#include <raylib.h>
#include "../src/System/State/HistoryState.h"
#include "../src/System/State/FavoriteState.h"
#include "../src/System/system.hpp"

using namespace std;

int main () {

    cout << "Hello World" << endl;
    System *app = new System();
    app -> run();
    return 0;
}