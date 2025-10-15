#pragma once

#include <iostream>
#include <string>

using namespace std;

/// @brief 盒子类
class Box
{
private:
    /// @brief 盒子名称属性
    string name;

public:
    /// @brief 获取盒子名称
    /// @return 盒子名称
    string getName();

    /// @brief 设置盒子名称
    /// @param p_name 盒子名称
    void setName(string p_name);

    void sayHi();
};