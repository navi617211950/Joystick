#include <iostream>
#include "box.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Joystick started." << endl;
    Box *b = new Box;
    b->setName("BBox");
    b->sayHi();
    return 0;
}
