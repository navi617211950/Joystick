#include <iostream>
#include <windows.h>
// #include "box.h"
// #include "point.h"
// #include "circle.h"
// #include "person.h"
// #include "building.h"
#include "color.h"
// #include "nvtest.h"
// #include "testfathor.h"
// #include "polymorphism.h"
// #include "testfile.h"

#include "testtemplate.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //设置文本颜色为红色
    navis::setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "Joystick started." << endl;
    methodtemplate::test();
    cout << "Joystick end." << endl;
    //system("pause");
    return 0;
}


