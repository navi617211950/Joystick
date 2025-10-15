#pragma once

#include <iostream>

using namespace std;

class Point
{
private:
    int x;
    int y;

public:
    Point();
    /// @brief 構造函數
    /// @param x X坐標
    /// @param y Y坐標
    Point(int x, int y);

    int get_x();
    void set_x(int x);
    int get_y();
    void set_y(int y);
};