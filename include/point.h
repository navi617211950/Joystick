#pragma once

#include <iostream>

using namespace std;

class Point
{
private:
    int x;
    int y;

public:
    /**
     * @brief 无参默认构造函数
     * 没有返回值，不需要写void
     * 函数名和类名相同
     * 函数有参数，可以发生重载
     * 创建对象的时候系统自动调用(只会调用一次)，无需显式调用
     */
    Point();

    /// @brief 析构函数
    /// 没有返回值，不需要写void
    /// 函数名和类名一致，然后最前面添加 ~ 符号
    /// 没有参数，不可以重载
    /// 对象销毁前自动调用
    ~Point();

    /// @brief 構造函數
    /// @param x X坐標
    /// @param y Y坐標
    Point(int x, int y);

    int get_x();
    void set_x(int x);
    int get_y();
    void set_y(int y);
};