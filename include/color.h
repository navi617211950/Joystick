#include <iostream>
#include <windows.h>

using namespace std;

namespace navis
{
    /// @brief 函数用于设置控制台文本颜色
    /// @param color 颜色
    void setColor(int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
}