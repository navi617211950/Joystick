#include "circle.h"

Point Circle::getCenter()
{
    cout << "Circle::getCenter() started" << endl;
    return this->c_point;
}

void Circle::setCenter(Point p)
{
    this->c_point = p;
}

int Circle::getMRange()
{
    return this->m_range;
}

void Circle::setMRange(int range)
{
    this->m_range = range;
}

void isInCircle(Point &p, Circle &c)
{

    int pc = (p.get_x() - c.getCenter().get_x()) * (p.get_x() - c.getCenter().get_x()) + (p.get_y() - c.getCenter().get_y()) * (p.get_y() - c.getCenter().get_y());

    int rc = c.getMRange() * c.getMRange();
    if (pc == rc)
    {
        cout << "点在圆上" << endl;
    }
    else if (pc < rc)
    {
        cout << "点在圆内" << endl;
    }
    else
    {
        cout << "点在圆外" << endl;
    }
}