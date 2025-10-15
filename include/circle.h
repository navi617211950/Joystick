#pragma once

#include <iostream>
#include "point.h"

using namespace std;

class Circle
{
private:
    Point c_point;
    int m_range;

public:
    Point getCenter();
    void setCenter(Point c);
    int getMRange();
    void setMRange(int range);
};

void isInCircle(Point &p, Circle &c);