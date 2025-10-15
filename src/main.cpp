#include <iostream>
#include "box.h"
#include "point.h"
#include "circle.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Joystick started." << endl;
    Box *b = new Box;
    b->setName("BBox");
    b->sayHi();

    Point p(4,0);

    Point c(2,0);
    Circle cir;
    cir.setCenter(c);
    cir.setMRange(3);
    isInCircle(p, cir);

    return 0;
}
