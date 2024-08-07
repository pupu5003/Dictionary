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