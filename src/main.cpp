#include <iostream>
#include <raylib.h>
#include "../src/System/system.hpp"

using namespace std;

int main () {

    cout << "Hello World" << endl;
    System *app = new System();
    app -> run();
    return 0;
}