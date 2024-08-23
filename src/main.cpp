#include <iostream>
#include <raylib.h>
#include "../src/System/system.hpp"
#include "../src/System/Component/Dictionary.hpp"

using namespace std;

int main () {

    cout << "Hello World" << endl;
    System *app = new System();
    app -> run();
    return 0;
    // Dictionary dict;
    // // dict.lodadData();
    // return 0;

}

/*******************************************************************************************
*
*   raylib [text] example - Input Box
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
