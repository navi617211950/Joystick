#include "point.h"

Point::Point(){
    cout << "> Point无参构造函数被调用" << endl;
}

Point::Point(const Point &p){
    cout << "> Point类拷贝构造函数被调用" << endl;
    this->x = p.x;
    this->y = p.y;
}

Point::~Point(){
    cout << "> Point类析构函数被调用" << endl;
}

Point::Point(int x, int y)
{
    cout << "> Point有参构造函数被调用" << endl;
    this->x = x;
    this->y = y;
}

int Point::get_x()
{
    return this->x;
}

void Point::set_x(int x)
{
    this->x = x;
}

int Point::get_y()
{
    return this->y;
}

void Point::set_y(int y)
{
    this->y = y;
}